/**
 * Copyright (c) 2011-2018 by Andrew Mustun. All rights reserved.
 * 
 * This file is part of the QCAD project.
 *
 * QCAD is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * QCAD is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with QCAD.
 */

include("scripts/Modify/Modify.js");
include("scripts/ShapeAlgorithms.js");

function Explode(guiAction) {
    Modify.call(this, guiAction);
}

Explode.prototype = new Modify();

Explode.getPreferencesCategory = function() {
    return [qsTr("Modify"), qsTr("Explode")];
};

Explode.initPreferences = function(pageWidget, calledByPrefDialog, document) {
    var widgets = getWidgets(pageWidget);
    if (!RTextBasedData.hasProxy()) {
        // remove MultilineTextToSimpleText option:
        widgets["MultilineTextToSimpleText"].visible = false;
    }

    if (!RSpline.hasProxy()) {
        widgets["SplineTolerance"].visible = false;
        widgets["SplineTolerance_Label"].visible = false;
        widgets["SplinesToLineSegments"].visible = false;
        destr(widgets["Indent"]);
        pageWidget.findChild("GridLayout").addWidget(widgets["SplineSegments_Label"], 2, 0, 1, 2);
    }
    else {
        widgets["SplinesToLineSegments"].toggled.connect(function(state) {
            widgets["SplineSegments"].enabled = state;
            widgets["SplineSegments_Label"].enabled = state;
        });

        widgets["SplineSegments"].enabled = widgets["SplinesToLineSegments"].checked;
        widgets["SplineSegments_Label"].enabled = widgets["SplinesToLineSegments"].checked;
    }
};

Explode.prototype.beginEvent = function() {
    Modify.prototype.beginEvent.call(this);
    var di = this.getDocumentInterface();
    Explode.explodeSelection(di, this.getToolTitle());
    this.terminate();
};

/**
 * Explodes all selected entities.
 * \param di Document interface
 * \param toolTitle Tool title used for undo/redo information.
 */
Explode.explodeSelection = function(di, toolTitle) {
    var document = di.getDocument();
    var storage = document.getStorage();
    var ids = document.querySelectedEntities();
    var i, k, e, n;
    var polyline, shapes;

    var options = {};
    options["splineTolerance"] = RSettings.getDoubleValue("Explode/SplineTolerance", 0.01);
    options["splineSegments"] = RSettings.getIntValue("Explode/SplineSegments", 64);
    options["ellipseSegments"] = RSettings.getIntValue("Explode/EllipseSegments", 32);
    options["splinesToLineSegments"] = RSettings.getBoolValue("Explode/SplinesToLineSegments", false);
    options["textToPolylines"] = RSettings.getBoolValue("Explode/TextToPolylines", true);
    options["textSplineToLineOrArc"] = RSettings.getBoolValue("Explode/TextSplineToLineOrArc", true);
    options["multilineTextToSimpleText"] = RSettings.getBoolValue("Explode/MultilineTextToSimpleText", true);
    options["circlesToPolylines"] = RSettings.getBoolValue("Explode/CirclesToPolylines", true);

    var op = new RAddObjectsOperation();
    if (!isNull(toolTitle)) {
        op.setText(toolTitle);
    }

    // map old block reference IDs to block reference entities:
    var blockReferenceMap = {};
    // list of attribute entities:
    var attributeEntities = [];

    for (i=0; i<ids.length; i++) {
        var id = ids[i];
        var entity = document.queryEntity(id);
        if (isNull(entity)) {
            debugger;
        }

        //var newShapes = [];
        //var newEntities = [];

        // list of new entities and shapes:
        var news = Explode.explodeEntity(entity, options);

        if (isNull(news)) {
            // do nothing:
            continue;
        }

        // add explosion result and delete original:
        if (news.length!==0) {
            // add entities based on shapes that resulted from the explosion:
            for (k=0; k<news.length; k++) {
                if (isEntity(news[k])) {
                    var newEntity = news[k];

                    // add entities based on entities that resulted from the explosion:
                    op.addObject(newEntity, false, true);

                    if (isBlockReferenceEntity(newEntity)) {
                        blockReferenceMap[newEntity.getId()] = newEntity;
                    }
                    else if (isAttributeEntity(newEntity)) {
                        attributeEntities.push(newEntity);
                    }
                }
                else {
                    var newShape = news[k];

                    e = shapeToEntity(entity.getDocument(), newShape);
                    if (!isNull(e)) {
                        e.setSelected(true);
                        e.copyAttributesFrom(getPtr(entity));
                        if (!isNull(newShape.color)) {
                            e.setColor(new RColor(newShape.color));
                        }
                        op.addObject(e, false);
                    }
                }
            }

            // delete original entity:
            op.deleteObject(entity);
        }
        else {
            // delete original entity:
            op.deleteObject(entity);
        }
    }

    var t = di.applyOperation(op);

    // update block reference attributes:
    if (attributeEntities.length>0) {

        op = new RAddObjectsOperation();
        //op.setTransactionGroup(doc.getTransactionGroup());
        if (!isNull(toolTitle)) {
            op.setText(toolTitle);
        }

        // fix attribute links to block references:
        for (i=0; i<attributeEntities.length; i++) {
            var attributeEntity = attributeEntities[i].clone();

            // 20250102: not needed anymore, since using QSharedPointer:
            // if (RSettings.getQtVersion()>=0x060000) {
            //     var newAttributeId = t.getNewObjectId(attributeEntity.getId());
            //     storage.setObjectId(attributeEntity, newAttributeId);
            // }

            // find parent entity of attribute:
            var blockReferenceEntity = blockReferenceMap[attributeEntity.getParentId()];
            if (!isNull(blockReferenceEntity)) {
                // update parent ID:
                // 20250102: not needed anymore, since using QSharedPointer:
                // if (RSettings.getQtVersion()>=0x060000) {
                //     var newAttributeParentId = t.getNewObjectId(blockReferenceEntity.getId());
                //     storage.setEntityParentId(attributeEntity, newAttributeParentId);
                // }
                // else {
                    storage.setEntityParentId(getPtr(attributeEntity), blockReferenceEntity.getId());
                // }
                op.addObject(attributeEntity, false);
            }
        }

        di.applyOperation(op);
    }
};

/**
 * \return Array of new shapes and entities or undefined to do nothing.
 */
Explode.explodeEntity = function(entity, options) {
    var ret = [];

    if (isNull(options)) {
        options = {};
    }

    // these entity types are not explodable:
    if (isPointEntity(entity) ||
        isLineEntity(entity) ||
        isXLineEntity(entity) ||
        isRayEntity(entity) ||
        isImageEntity(entity) ||
        isArcEntity(entity) ||
        isViewportEntity(entity)) {
        return undefined;
    }

    var k, e, n, d;
    var col, row;
    var painterPaths;

    var document = entity.getDocument();
    var storage = document.getStorage();

    var splineTolerance = options["splineTolerance"];
    var splineSegments = options["splineSegments"];
    var ellipseSegments = options["ellipseSegments"];
    var splinesToLineSegments = options["splinesToLineSegments"];
    var textToPolylines = options["textToPolylines"];
    var textSplineToLineOrArc = options["textSplineToLineOrArc"];
    var multilineTextToSimpleText = options["multilineTextToSimpleText"];
    var circlesToPolylines = options["circlesToPolylines"];

    if (isNull(splineTolerance)) {
        splineTolerance = RSettings.getDoubleValue("Explode/SplineTolerance", 0.01);
    }
    if (isNull(splineSegments)) {
        splineSegments = RSettings.getIntValue("Explode/SplineSegments", 64);
    }
    if (isNull(ellipseSegments)) {
        ellipseSegments = RSettings.getIntValue("Explode/EllipseSegments", 32);
    }
    if (isNull(splinesToLineSegments)) {
        splinesToLineSegments = RSettings.getBoolValue("Explode/SplinesToLineSegments", false);
    }
    if (isNull(textToPolylines)) {
        textToPolylines = RSettings.getBoolValue("Explode/TextToPolylines", true);
    }
    if (isNull(textSplineToLineOrArc)) {
        textSplineToLineOrArc = RSettings.getBoolValue("Explode/TextSplineToLineOrArc", true);
    }
    if (isNull(multilineTextToSimpleText)) {
        multilineTextToSimpleText = RSettings.getBoolValue("Explode/MultilineTextToSimpleText", true);
    }
    if (isNull(circlesToPolylines)) {
        circlesToPolylines = RSettings.getBoolValue("Explode/CirclesToPolylines", true);
    }

    // explode ellipse into polyline with arc segments:
    if (isEllipseEntity(entity)) {
        if (REllipse.hasProxy()) {
            var ellipse = entity.getData().castToShape();
            var polyline = ellipse.approximateWithArcs(ellipseSegments);
            if (!polyline.isEmpty()) {
                ret.push(polyline);
            }
        }
        else {
            return undefined;
        }
    }

    // explode circle into polyline with two arc segments:
    else if (isCircleEntity(entity)) {
        if (circlesToPolylines) {
            var circle = entity.getData().castToShape();
            polyline = new RPolyline();
            polyline.appendShape(new RArc(circle.getCenter(), circle.getRadius(), 0.0, Math.PI, false));
            polyline.appendShape(new RArc(circle.getCenter(), circle.getRadius(), Math.PI, 2*Math.PI, false));
            polyline.autoClose();
            ret.push(polyline);
        }
        else {
            return undefined;
        }
    }

    // explode polyline into line and arc segments:
    else if (isPolylineEntity(entity)) {
        polyline = entity.getData().castToShape();

        // explode polyline with segment widths:
        if (RPolyline.hasProxy() && polyline.hasWidths()) {

            // list of polyline pairs (left / right):
            var pls;
            if (RSettings.getQtVersion() >= 0x060000) {
                pls = [];
                var plsLeft = polyline.getLeftOutline();
                var plsRight = polyline.getRightOutline();
                for (var i=0; i<plsLeft.length && i<plsRight.length; i++) {
                    pls.push([plsLeft[i], plsRight[i]]);
                }
            }
            else {
                pls = polyline.getLeftRightOutline();
            }

            var first = true;
            var lastSegment = undefined;
            var prevLeftPl = undefined;
            var prevRightPl = undefined;

            for (k=0; k<pls.length; k++) {
                if (pls[k].length!==2) {
                    qWarning("invalid result from RPolyline::getLeftRightOutline");
                    continue;
                }

                var leftPl = pls[k][0];
                var rightPl = pls[k][1];

                if (leftPl.countSegments()===1 && rightPl.countSegments()===1) {
                    if (first) {
                        // add orthogonal segment at start of this sequence:
                        //ret.push(pls[k].getSegmentAt(3));
                        if (isNull(prevLeftPl) || isNull(prevRightPl)) {
                            ret.push(new RLine(leftPl.getStartPoint(), rightPl.getStartPoint()));
                        }
                        else {
                            var dirLeft = prevLeftPl.getDirection2() + Math.PI;
                            var dirRight = prevRightPl.getDirection2() + Math.PI;
                            //qDebug("dirLeft:", dirLeft);
                            //qDebug("new dir:", leftPl.getDirection1());
                            if (!RMath.fuzzyAngleCompare(dirLeft, leftPl.getDirection1(), 0.01) ||
                                !RMath.fuzzyAngleCompare(dirRight, rightPl.getDirection1(), 0.01)) {
                                ret.push(new RLine(leftPl.getStartPoint(), rightPl.getStartPoint()));
                            }
                        }
                    }

                    // add left segment:
                    ret.push(leftPl);
                    // add right segment:
                    ret.push(rightPl);

                    lastSegment = new RLine(leftPl.getEndPoint(), rightPl.getEndPoint());
                    prevLeftPl = leftPl;
                    prevRightPl = rightPl;
                }

                else if (leftPl.countSegments()===1) {
                    // add only left segment:
                    ret.push(leftPl);
                }

                else if (rightPl.countSegments()===1) {
                    // add only right segment:
                    ret.push(rightPl);
                }

                //else if (leftPl.countSegments()>1 || rightPl.countSegments()>1) {
                else if (!leftPl.isEmpty()) {
                    //ret.push(pls[k]);
                    if (!rightPl.isEmpty()) {
                        ret.push(new RLine(leftPl.getStartPoint(), rightPl.getStartPoint()));
                    }

                    ret.push(leftPl);
                    if (!rightPl.isEmpty()) {
                        ret.push(rightPl);
                        ret.push(new RLine(leftPl.getEndPoint(), rightPl.getEndPoint()));
                    }
                    first = true;
                    if (!isNull(lastSegment)) {
                        ret.push(lastSegment);
                        lastSegment = undefined;
                        prevLeftPl = undefined;
                        prevRightPl = undefined;
                    }

                    continue;
                }
            }
            if (!isNull(lastSegment)) {
                ret.push(lastSegment);
            }

            // special case of donut shape with hole diameter=0 which explodes to circle:
            if (ret.length===2) {
                if (isPolylineShape(ret[0]) && isPolylineShape(ret[1]) &&
                    ret[0].countSegments()===1 && ret[1].countSegments()===1 &&
                    ret[0].getStartPoint().equalsFuzzy(ret[1].getEndPoint()) &&
                    ret[0].getEndPoint().equalsFuzzy(ret[1].getStartPoint()) &&
                    RMath.fuzzyCompare(ret[0].getBulgeAt(0), 1.0) &&
                    RMath.fuzzyCompare(ret[1].getBulgeAt(0), 1.0)) {

                    var seg = ret[0].getSegmentAt(0);
                    ret = [ new RCircle(seg.getCenter(), seg.getRadius()) ];
                }
            }
        }
        else {
            var polySegments = polyline.getExploded();
            if (polySegments.length>0) {
                for (k=0; k<polySegments.length; k++) {
                    var shape = getPtr(polySegments[k]);

                    // last shape might have zero length if polyline is closed geometrically and logically:
                    if (k===polySegments.length-1) {
                        if (shape.getLength()<1.0e-5) {
                            break;
                        }
                    }

                    ret.push(shape.clone());
                }
            }
        }
    }

    else if (isWipeoutEntity(entity)) {
        ret.push(entity.getData().getBoundary());
    }

    // explode spline into polyline with arc or line segments:
    else if (isSplineEntity(entity)) {
        var spline = entity.getData().castToShape();
        var pl;
        if (RSpline.hasProxy() && !splinesToLineSegments) {
            pl = spline.approximateWithArcs(splineTolerance);
        }
        else {
            pl = spline.toPolyline(splineSegments);
        }

        pl.simplify();
        ret.push(pl);
    }

    // explode hatch into lines / solid fill into boundary:
    else if (isHatchEntity(entity)) {
        if (entity.isSolid()) {
            for (k=0; k<entity.getLoopCount(); k++) {
                var shapes = entity.getLoopBoundary(k);
                if (shapes.length===1) {
                    // polyline boundary:
                    shape = shapes[0];
                    ret.push(shape.clone());
                }
                else {
                    // loose segments:
                    var pl = new RPolyline();
                    for (n=0; n<shapes.length; n++) {
                        shape = shapes[n];
                        var shapeClone = shape.clone()
                        pl.appendShape(getPtr(shapeClone));
                        //ret.push(shape.clone());
                    }
                    ret.push(pl);
                }
            }
        }
        else {
            painterPaths = entity.getPainterPaths(false);
            for (k=0; k<painterPaths.length; k++) {
                shapes = painterPaths[k].getShapes();
                for (n=0; n<shapes.length; n++) {
                    shape = getPtr(shapes[n]);
                    if (isSplineShape(shape)) {
                        shape = ShapeAlgorithms.splineToLineOrArc(shape, 0.01);
                    }
                    ret.push(shape.clone());
                }
            }
        }
    }

    // explode dimension into lines, solids (triangles) and a text entity:
    else if (isDimensionEntity(entity)) {
        shapes = entity.getShapes();
        for (k=0; k<shapes.length; k++) {
            if (shapes[k].isValid()) {
                ret.push(shapes[k]);
            }
        }
        var textData = entity.getData().getTextData();
        e = new RTextEntity(entity.getDocument(), textData);
        e.setSelected(true);
        e.copyAttributesFrom(getPtr(entity));
        var textColor = document.getKnownVariable(RS.DIMCLRT, new RColor(RColor.ByBlock));
        e.setColor(textColor);
        ret.push(e);
    }

    // explode leaders into lines and solids (triangles):
    else if (isLeaderEntity(entity)) {
        shapes = entity.getShapes();
        for (k=0; k<shapes.length; k++) {
            shape = getPtr(shapes[k]);
            ret.push(shape.clone());
        }
    }

    // explode tolerances into lines and texts:
    else if (isToleranceEntity(entity)) {
        shapes = entity.getFrame();
        for (k=0; k<shapes.length; k++) {
            shape = shapes[k];
            ret.push(shape.clone());
        }

        var textDatas = entity.getTextLabels();
        for (k=0; k<textDatas.length; k++) {
            var d = textDatas[k];
            e = new RTextEntity(document, new RTextData(d))
            e.setSelected(true);
            e.copyAttributesFrom(getPtr(entity));
            if (e.getColor()!==d.getColor()) {
                e.setColor(d.getColor());
            }
            ret.push(e);
        }
    }

    // explode solids into polylines:
    else if (isSolidEntity(entity)) {
        shapes = entity.getShapes();
        for (k=0; k<shapes.length; k++) {
            shape = getPtr(shapes[k]);
            if (shape.countVertices()===4) {
                var v3 = shape.getVertexAt(3);
                shape.setVertexAt(3, shape.getVertexAt(2));
                shape.setVertexAt(2, v3);
            }
            ret.push(shape.clone());
        }
    }

    // explode faces into polylines:
    else if (isFaceEntity(entity)) {
        shapes = entity.getShapes();
        for (k=0; k<shapes.length; k++) {
            shape = getPtr(shapes[k]);
            ret.push(shape.clone());
        }
    }

    // explode text entities into text blocks or lines, arcs and splines:
    else if (isTextEntity(entity)) {
        // explode multi-block text into simple text entities:
        // each text block with the same format is converted into one individual simple text entity:
        if (!entity.isSimple() && multilineTextToSimpleText && RTextBasedData.hasProxy()) {
            var textDatas = entity.getSimpleTextBlocks();

            for (k=0; k<textDatas.length; k++) {
                var d = textDatas[k];
                e = new RTextEntity(document, new RTextData(d))
                e.setSelected(true);
                e.copyAttributesFrom(getPtr(entity));
                if (e.getColor()!==d.getColor()) {
                    e.setColor(d.getColor());
                }
                ret.push(e);
            }
        }
        else {
            painterPaths = entity.getPainterPaths();
            for (k=0; k<painterPaths.length; k++) {
                var p = painterPaths[k].getPen();
                var b = painterPaths[k].getBrush();
                var col = undefined;

                if (p.style()!==Qt.NoPen) {
                    if (p.color().isValid()) {
                        col = p.color().name();
                    }
                }
                else if (b.style()!==Qt.NoBrush) {
                    if (b.color().isValid()) {
                        col = b.color().name();
                    }
                }

                // ignore text bounding box, used only to display instead of
                // text at small zoom factors:
                if (painterPaths[k].getFeatureSize()<0) {
                    continue;
                }

                var plText = undefined;

                shapes = painterPaths[k].getShapes();
                for (n=0; n<shapes.length; n++) {
                    shape = shapes[n];
                    if (isSplineShape(shape)) {
                        // spline to arc or line or spline:
                        if (textSplineToLineOrArc) {
                            shape = ShapeAlgorithms.splineToLineOrArc(shape, splineTolerance);
                        }

                        if (textToPolylines) {
                            // spline to polyline with arcs:
                            if (isSplineShape(shape)) {
                                if (RSpline.hasProxy() && !splinesToLineSegments) {
                                    shape = shape.approximateWithArcs(splineTolerance);
                                }
                                else {
                                    shape = shape.toPolyline(splineSegments);
                                }
                            }
                        }
                    }

                    if (!isNull(shape)) {
                        var sc = shape.clone();
                        sc.color = col;

                        if (textToPolylines) {
                            // explode to polylines:
                            if (!isNull(plText) && plText.getEndPoint().equalsFuzzy(shape.getStartPoint())) {
                                plText.appendShape(getPtr(sc));
                            }
                            else {
                                if (!isNull(plText)) {
                                    plText.toLogicallyClosed();
                                }

                                plText = new RPolyline();
                                ret.push(plText);
                                plText.appendShape(getPtr(sc));
                            }
                        }
                        else {
                            // explode to lines, arcs, polylines:
                            ret.push(sc);
                        }
                    }
                }

                if (textToPolylines) {
                    if (!isNull(plText)) {
                        plText.toLogicallyClosed();
                    }
                }
            }
        }
    }

    // explode attribute entities into texts:
    else if (isAttributeEntity(entity)) {
        // create text data from attribute data:
        d = new RTextData(entity.getData());
        // unlink from parent (block ref):
        d.setParentId(RObject.INVALID_ID);
        e = new RTextEntity(document, d);
        e.setSelected(true);
        e.copyAttributesFrom(getPtr(entity));
        ret.push(e);
    }

    // explode block reference or block reference array:
    else if (isBlockReferenceEntity(entity)) {
        var data = entity.getData();
        var pos = entity.getPosition();
        var uniform = RMath.fuzzyCompare(entity.getScaleFactors().x, entity.getScaleFactors().y);

        // explode array into multiple block references:
        if (data.getColumnCount()>1 || data.getRowCount()>1) {
            for (col=0; col<data.getColumnCount(); col++) {
                for (row=0; row<data.getRowCount(); row++) {
                    var offset = data.getColumnRowOffset(col, row, true);

                    e = entity.clone();
                    e.setRowCount(1);
                    e.setColumnCount(1);
                    e.setPosition(pos.operator_add(offset));
                    storage.setObjectId(getPtr(e), RObject.INVALID_ID);
                    e.setSelected(true);
                    ret.push(e);
                }
            }
        }

        // explode block reference into contained entities:
        else {
            var subIds = document.queryBlockEntities(data.getReferencedBlockId());
            for (k=0; k<subIds.length; k++) {
                var subEntity = data.queryEntity(subIds[k], true);
                if (isNull(subEntity)) {
                    continue;
                }

                if (!isBlockReferenceEntity(subEntity)) {
                    subEntity.scaleVisualProperties(data.getScaleFactors().x);
                }

                // ignore attribute definitions:
                if (isAttributeDefinitionEntity(subEntity)) {
                    continue;
                }

                // hatch in non-uniformly scaled block reference:
                if (!uniform && isHatchEntity(subEntity)) {
                    // query source entity from block (no transform):
                    var untransformedSubEntity = data.queryEntity(subIds[k], false);

                    // explode source entity:
                    var untransformedEntitites = Explode.explodeEntity(untransformedSubEntity, options);

                    var explodedHatchData = undefined;
                    if (subEntity.isSolid()) {
                        // solid hatch: create new solid hatch:
                        explodedHatchData = new RHatchData();
                        explodedHatchData.newLoop();
                    }

                    // transform by block transforms:
                    for (var n=0; n<untransformedEntitites.length; n++) {
                        var untransformedEntity = untransformedEntitites[n];

                        if (isShape(untransformedEntity)) {
                            untransformedEntity = shapeToEntity(document, untransformedEntity);
                        }

                        e = data.getTransformed(untransformedEntity);

                        if (!isNull(explodedHatchData)) {
                            // solid hatch: add transformed boundary to exploded hatch entity:
                            explodedHatchData.addBoundary(e.castToShape());
                        }
                        else {
                            // hatch pattern: add transformed entity:
                            e.setSelected(true);
                            e.copyAttributesFrom(getPtr(subEntity));
                            ret.push(e);
                        }
                    }

                    if (!isNull(explodedHatchData)) {
                        // solid hatch: add new solid hatch:
                        e = new RHatchEntity(document, explodedHatchData);
                        e.setSelected(true);
                        e.copyAttributesFrom(getPtr(subEntity));
                        ret.push(e);
                    }
                    continue;
                }

                e = subEntity.clone();
                //data.applyColumnRowOffsetTo(e, col, row);
                // we need the old ID to update attribute parent IDs:
                //storage.setObjectId(e, RObject.INVALID_ID);
                e.setBlockId(document.getCurrentBlockId());

                e.setSelected(true);
                ret.push(e);
            }
        }
    }

    return ret;
};
