/**
 * Copyright (c) 2011-2018 by Andrew Mustun. All rights reserved.
 * 
 * Various changes added 2014 by Robert S.
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

include("../Polyline.js");
include("scripts/Snap/RestrictAngleLength/RestrictAngleLength.js");

/**
 * \class DrawPolyline
 * \brief Draw polyline, segment by segment.
 * This is also the base class for PolylineAppendNode.
 * \ingroup ecma_draw_polyline
 */
function DrawPolyline(guiAction) {
    Polyline.call(this, guiAction);

    this.polylineEntity = undefined;
    this.arcMode = false;
    this.radius = 1.0;
    this.actualRadius = 0.0;
    this.prepend = false;
    this.segment = undefined;
    this.redoList = [];
    this.sweep = 0.0;

    // point of the last mouse click:
    this.point = RVector.invalid;

    // next polyline vertex:
    this.vertex = RVector.invalid;
    this.bulge = 0.0;

    this.setUiOptions(DrawPolyline.includeBasePath + "/DrawPolyline.ui");
}

DrawPolyline.prototype = new Polyline();
DrawPolyline.includeBasePath = includeBasePath;

DrawPolyline.State = {
    SettingFirstVertex : 0,
    SettingNextVertex : 1
};

DrawPolyline.prototype.beginEvent = function() {
    Polyline.prototype.beginEvent.call(this);

    this.setState(DrawPolyline.State.SettingFirstVertex);
    this.updateButtonStates();
};

DrawPolyline.prototype.initState = function() {
    Polyline.prototype.initState.call(this);

    this.setCrosshairCursor();

    switch (this.state) {
    case DrawPolyline.State.SettingFirstVertex:
        // do not move this outside of the case, since inheriting actions
        // might add more states:
        this.getDocumentInterface().setClickMode(RAction.PickCoordinate);
        var trFirstVertex = qsTr("First vertex");
        this.setCommandPrompt(trFirstVertex);
        this.setLeftMouseTip(trFirstVertex);
        this.setRightMouseTip(EAction.trCancel);
        this.segment = undefined;
        EAction.showSnapTools();
        this.redoList = [];
        break;
    case DrawPolyline.State.SettingNextVertex:
        this.getDocumentInterface().setClickMode(RAction.PickCoordinate);
        var trNextVertex = qsTr("Next vertex");
        this.setCommandPrompt(trNextVertex);
        this.setLeftMouseTip(trNextVertex);
        this.setRightMouseTip(EAction.trDone);
        EAction.showSnapTools();
        break;
    }
};


DrawPolyline.prototype.escapeEvent = function() {
    var di = this.getDocumentInterface();

    switch (this.state) {
    case DrawPolyline.State.SettingFirstVertex:
        EAction.prototype.escapeEvent.call(this);
        break;

    case DrawPolyline.State.SettingNextVertex:
        if (!isNull(this.polylineEntity)) {
            // remove polyline with one or zero vertices:
            if (this.polylineEntity.countVertices()<=1) {
                var op = new RDeleteObjectOperation(this.polylineEntity, false);
                this.applyOperation(op);
            }
        }

        this.setState(DrawPolyline.State.SettingFirstVertex);
        this.polylineEntity = undefined;
        this.updateButtonStates();
        break;
    }
};

DrawPolyline.prototype.keyPressEvent = function(event) {
    var di = this.getDocumentInterface();

    if ((event.key() === Qt.Key_Enter.valueOf()) || (event.key() === Qt.Key_Return.valueOf())) {
        if (this.state === DrawPolyline.State.SettingFirstVertex) {
            var view = di.getLastKnownViewWithFocus();
            var pos = di.getLastPosition();
            var e = new RCoordinateEvent(pos, view.getScene(), getRGraphicsView(view));
            this.pickCoordinate(e, false);
        }
    } else {
        EAction.prototype.keyPressEvent(event);
    }
};

DrawPolyline.prototype.showUiOptions = function(resume) {
    Draw.prototype.showUiOptions.call(this, resume);

    var optionsToolBar = EAction.getOptionsToolBar();
    var w = optionsToolBar.findChild("Restrict");
    var guiAction = RGuiAction.getByScriptFile("scripts/Snap/RestrictAngleLength/RestrictAngleLength.js");
    w.setDefaultAction(guiAction);

    this.updateButtonStates();
};

DrawPolyline.prototype.pickCoordinate = function(event, preview) {
    var op;
    
    var di = this.getDocumentInterface();
    var document = this.getDocument();

    switch (this.state) {
    // set first vertex, create polyline entity:
    case DrawPolyline.State.SettingFirstVertex:
        if (!preview) {
            this.point = event.getModelPosition();

            var pl = new RPolylineEntity(document, new RPolylineData());
            pl.appendVertex(this.point);
            op = new RAddObjectOperation(pl, this.getToolTitle());
            this.applyOperation(op);

            di.setRelativeZero(this.point);
            if (!isNull(this.polylineEntity)) {
                this.setState(DrawPolyline.State.SettingNextVertex);
            }
        }
        break;

    // set next vertex:
    case DrawPolyline.State.SettingNextVertex:
        this.point = event.getModelPosition();

        // number of existing vertices:
        var numberOfVertices;
        if (isNull(this.polylineEntity)) {
            numberOfVertices = 0;
        }
        else {
            numberOfVertices = this.polylineEntity.countVertices();
        }

        if (numberOfVertices>0) {
            this.updateData();

            // append or prepend vertex:
            if (!preview) {
                if (this.prepend) {
                    this.polylineEntity.prependVertex(this.vertex, this.bulge);
                }
                else {
                    this.polylineEntity.setBulgeAt(numberOfVertices-1, this.bulge);
                    this.polylineEntity.appendVertex(this.vertex, 0.0);
                }
            }
        }

        if (preview) {
            this.updatePreview();
        }
        else {
            op = this.getOperation(false);
            if (!isNull(op)) {
                this.applyOperation(op);
                di.setRelativeZero(this.vertex);
                //this.uncheckArcMode();
            }
        }
        break;
    }

    if (!preview) {
        this.updateButtonStates();
    }
};

DrawPolyline.prototype.updateData = function() {
    var numberOfVertices;
    if (isNull(this.polylineEntity)) {
        numberOfVertices = 0;
    }
    else {
        numberOfVertices = this.polylineEntity.countVertices();
    }

    var appendPoint;
    if (this.prepend) {
        appendPoint = this.polylineEntity.getStartPoint();
    }
    else {
        appendPoint = this.polylineEntity.getEndPoint();
    }

    if (this.arcMode===true) {
        var dir = 0.0;
        if (numberOfVertices>1) {
            if (this.prepend) {
                dir = this.polylineEntity.getDirection1() + Math.PI;
            }
            else {
                dir = this.polylineEntity.getDirection2() + Math.PI;
            }
        }

        this.segment = this.createArcSegment(appendPoint, this.point, dir);
        this.actualRadius = this.segment.getRadius();

        this.vertex = this.segment.getEndPoint();

        if (this.prepend) {
            this.segment.reverse();
        }

        this.bulge = this.segment.getBulge();
        this.center = this.segment.getCenter();
        this.angle = this.segment.getEndAngle();
    }
    else {
        this.segment = new RLine(appendPoint, this.point);

        this.bulge = 0.0;
        this.vertex = this.point;
        this.center = undefined;
        this.angle = undefined;
    }
};

DrawPolyline.prototype.createArcSegment = function(appendPoint, point, dir) {
    var arc = new RArc();

    arc.radius = this.radius;

    // orthogonal to base entity:
    var ortho = new RVector();
    ortho.setPolar(this.radius, dir + Math.PI/2.0);

    // two possible center points for arc:
    var center1 = appendPoint.operator_add(ortho);
    var center2 = appendPoint.operator_subtract(ortho);
    if (center1.getDistanceTo(point) < center2.getDistanceTo(point)) {
        arc.setCenter(center1);
    } else {
        arc.setCenter(center2);
    }

    // angles:
    arc.setStartAngle(arc.getCenter().getAngleTo(appendPoint));
    arc.setEndAngle(arc.getCenter().getAngleTo(point));

    // handle arc direction:
    arc.setReversed(false);
    var diff = RMath.getNormalizedAngle(arc.getDirection1() - dir);
    if (Math.abs(diff-Math.PI) < 1.0e-1) {
        arc.setReversed(true);
    }

    // handle sweep here
    // change end angle
    // if sweep equals zero then do nothing
    if (this.sweep < 0.0 || this.sweep > 360.0) {
        // print error message
        this.sweep = 0.0;
    }
    if (this.sweep !== 0.0) {
        var curSweep = arc.getSweep();
        if (curSweep !== this.sweep) {
            var startAngle = RMath.rad2deg(arc.getStartAngle());
            var reversed = arc.isReversed();
            if (reversed) {
                var endAngle = startAngle - this.sweep;
                if (endAngle < 0.0) {
                    endAngle = endAngle + 360.0;
                }
            } else {
                endAngle = startAngle + this.sweep;
                if (endAngle > 360.0) {
                    endAngle = endAngle - 360.0;
                }
            }
            arc.setEndAngle(RMath.deg2rad(endAngle));
        }
    }

    return arc;
};

DrawPolyline.prototype.getOperation = function(preview) {
    if (isNull(this.polylineEntity)) {
        return undefined;
    }

    // for preview, only add current segment:
    if (preview) {
        // refresh next polyline segment data:
        this.updateData();

        var entity;
        if (isLineShape(this.segment)) {
            entity = new RLineEntity(
                    this.getDocument(),
                    new RLineData(this.segment)
            );
        }
        else if (isArcShape(this.segment)) {
            entity = new RArcEntity(
                    this.getDocument(),
                    new RArcData(this.segment)
            );
        }
        if (!isEntity(entity)) {
            return undefined;
        }
        entity.copyAttributesFrom(getPtr(this.polylineEntity));
        return new RAddObjectOperation(entity, false);
    }
    else {
        return new RAddObjectOperation(this.polylineEntity, this.getToolTitle(), true, false);
    }
};

/**
 * Updates the polyline in storage and makes sure that this.polylineEntity
 * points to new new clone of the original entity.
 */
DrawPolyline.prototype.applyOperation = function(op) {
    this.polylineEntity = undefined;
    var di = this.getDocumentInterface();
    var document = this.getDocument();
    var transaction = di.applyOperation(op);

    // find out ID of polyline, that was added to the document:
    var ids = transaction.getAffectedObjects();
    for (var i=0; i<ids.length; ++i) {
        var id = ids[i];
        var entity = document.queryEntity(id);
        if (isPolylineEntity(entity)) {
            this.polylineEntity = entity;
            break;
        }
    }
};

/**
 * Called when user clicks the 'Close' button to close the polyline.
 */
DrawPolyline.prototype.slotClose = function() {
    if (isNull(this.polylineEntity)) {
        return;
    }

    if (this.polylineEntity.countVertices() >= 3) {
        var di = this.getDocumentInterface();
        di.setRelativeZero(this.polylineEntity.getVertexAt(0));
        this.polylineEntity.setClosed(true);
        var op = this.getOperation(false);
        if (!isNull(op)) {
            this.applyOperation(op);
        }
        this.setState(DrawPolyline.State.SettingFirstVertex);
        this.polylineEntity = undefined;
    }
    
    this.updateButtonStates();
};

/**
 * Called when user clicks the 'Undo' button to remove the last added vertex.
 */
DrawPolyline.prototype.slotUndo = function() {
    if (isNull(this.polylineEntity)) {
        return;
    }

    if (this.polylineEntity.countVertices() >= 2) {
        var di = this.getDocumentInterface();
        var bulge = this.polylineEntity.getBulgeAt(this.polylineEntity.countVertices() - 1);
        var vertex = this.polylineEntity.getVertexAt(this.polylineEntity.countVertices() - 1);
        this.polylineEntity.removeLastVertex();
        di.setRelativeZero(this.polylineEntity.getVertexAt(this.polylineEntity.countVertices() - 1));
        di.clearPreview();
        var op = this.getOperation(false);
        if (!isNull(op)) {
            this.applyOperation(op);
            // add last vertex and bulge to redoList
            this.redoList.push(bulge);
            this.redoList.push(vertex);
        }
        this.simulateMouseMoveEvent();
    }

    this.updateButtonStates();
};

/**
 * Called when user clicks the 'Redo' button to redo the last vertex.
 */
DrawPolyline.prototype.slotRedo = function() {
    if (isNull(this.polylineEntity)) {
        return;
    }

    if (this.redoList.length >= 2) {
        var di = this.getDocumentInterface();
        // redo last vertex and bulge
        var vertex = this.redoList.pop();
        var bulge = this.redoList.pop();
        this.polylineEntity.appendVertex(vertex, bulge);
        di.clearPreview();
        var op = this.getOperation(false);
        if (!isNull(op)) {
            this.applyOperation(op);
        }
        di.setRelativeZero(vertex);
        this.simulateMouseMoveEvent();
    }

    this.updateButtonStates();
};


/**
 * Called when user toggles 'Arc segment' check box to indicate if the next
 * segment is a line or an arc segment.
 */
DrawPolyline.prototype.slotArcModeChanged = function(value) {
    this.arcMode = value;
    this.updatePreview(true);
};

/**
 * Called when user enters a radius for the next arc segment.
 */
DrawPolyline.prototype.slotRadiusChanged = function(value) {
    this.radius = value;
    this.updatePreview(true);
};

/**
 * Called when user enters a sweep for the next arc segment.
 */
DrawPolyline.prototype.slotSweepChanged = function(value) {
    this.sweep = value;
    this.updatePreview(true);
};

/**
 * Called internally to automatically uncheck the 'Arc segment' check box.
 */
DrawPolyline.prototype.uncheckArcMode = function() {
    var w = objectFromPath("MainWindow::Options::ArcMode");
    if (!isNull(w)) {
        w.checked = false;
    }
};


/**
 * Updates the state (enabled / disabled) of the undo and the close buttons
 * depending on the current progress.
 */
DrawPolyline.prototype.updateButtonStates = function() {
    var w;
    
    if (this.state === DrawPolyline.State.SettingFirstVertex) {
        this.uncheckArcMode();
    }

    var optionsToolBar = EAction.getOptionsToolBar();
    w = optionsToolBar.findChild("Close");
    if (!isNull(this.polylineEntity)) {
        w.enabled = (this.polylineEntity.countVertices() >= 3) ? true : false;
    }
    else {
        w.enabled = false;
    }

    w = optionsToolBar.findChild("Undo");
    if (!isNull(this.polylineEntity)) {
        w.enabled = (this.polylineEntity.countVertices() >= 2) ? true : false;
    }
    else {
        w.enabled = false;
    }

    w = optionsToolBar.findChild("Redo");
    w.enabled = (this.redoList.length >= 2) ? true : false;
};

DrawPolyline.prototype.getAuxPreview = function() {
    var ret = [];

    if (this.state === DrawPolyline.State.SettingNextVertex) {
        if (!isNull(this.center) && !isNull(this.angle)) {
            var v = RVector.createPolar(this.actualRadius, this.angle);
            ret.push(new RLine(this.center, this.center.operator_add(v)));
        }
    }

    return ret;
};

/**
 * Allows commands to be entered in command line
 * Using the 'startsWith' function allows the user to enter only as many characters
 * as needed to distinguish between commands
 * In this case only the first character is needed. (But entering 'c', 'cl', 'clo', 'clos'
 * or 'close' would all invoke the close command. Similarly with undo and redo)
 */
DrawPolyline.prototype.commandEvent = function(event) {
    var str;

    var cmd = event.getCommand();
    cmd = cmd.toLowerCase();

    str = qsTr("close");
    if (str.startsWith(cmd)) {
        this.slotClose();
        event.accept();
        return;
    }
    str = qsTr("undo");
    if (str.startsWith(cmd)) {
        this.slotUndo();
        event.accept();
        return;
    }
    str = qsTr("redo");
    if (str.startsWith(cmd)) {
        this.slotRedo();
        event.accept();
        return;
    }
    str = qsTr("arc");
    if (str.startsWith(cmd)) {
        var ob = objectFromPath("MainWindow::Options::ArcMode");
        ob.checked = !ob.checked
        this.slotArcModeChanged(ob.checked);
        event.accept();
        return;
    }
};
