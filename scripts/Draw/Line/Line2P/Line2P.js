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

include("scripts/Draw/Line/Line.js");

//include("scripts/Snap/RestrictAngleLength/RestrictAngleLength.js");

/**
 * \class Line2P
 * \brief Line from two points or sequence of lines.
 * \ingroup ecma_draw_line
 */
function Line2P(guiAction) {
    Line.call(this, guiAction);

    // list of points drawn:
    this.pointList = [];
    // index of point that was drawn last, used for tool undo / redo:
    this.pointListIndex = -1;
    // list of entities drawn:
    this.entityIdList = [];

    this.point1 = undefined;
    this.point2Cursor = undefined;
    this.point2 = undefined;

    this.useLength = false;
    this.len = 1.0;
    this.useAngle = false;
    this.angle = 0.0;

    this.setUiOptions(["../Line.ui", "Line2P.ui"]);
}

Line2P.prototype = new Line();

Line2P.RestrictingOptions = [ "SeparatorRestrictions", "UseLength", "Length", "SeparatorLengthAngle", "UseAngle", "Angle" ];

Line2P.State = {
    SettingFirstPoint : 0,
    SettingNextPoint : 1
};

Line2P.prototype.beginEvent = function() {
    Line.prototype.beginEvent.call(this);

    this.setState(Line2P.State.SettingFirstPoint);
    this.updateButtonStates();
};

Line2P.prototype.setState = function(state) {
    Line.prototype.setState.call(this, state);

    this.getDocumentInterface().setClickMode(RAction.PickCoordinate);
    this.setCrosshairCursor();

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case Line2P.State.SettingFirstPoint:
        var trFirstPoint = qsTr("First point");
        this.setCommandPrompt(trFirstPoint);
        this.setLeftMouseTip(trFirstPoint);
        this.setRightMouseTip(EAction.trCancel);
        this.pointList = [];
        this.pointListIndex = -1;
        this.entityIdList = [];
        break;

    case Line2P.State.SettingNextPoint:
        var trNextPoint = qsTr("Next point");
        this.setCommandPrompt(trNextPoint);
        this.setLeftMouseTip(trNextPoint);
        this.setRightMouseTip(EAction.trDone);
        break;
    }

    EAction.showSnapTools();
};

Line2P.prototype.showUiOptions = function(resume, restoreFromSettings) {
    Line.prototype.showUiOptions.call(this, resume, restoreFromSettings);

//    var optionsToolBar = EAction.getOptionsToolBar();
//    var w = optionsToolBar.findChild("Restrict");
//    var guiAction = RGuiAction.getByScriptFile("scripts/Snap/RestrictAngleLength/RestrictAngleLength.js");
//    w.setDefaultAction(guiAction);

    this.updateButtonStates();
};

Line2P.prototype.initUiOptions = function(resume, optionsToolBar, forDialog) {
    Line.prototype.initUiOptions.call(this, resume, optionsToolBar, forDialog);

    var leLength = optionsToolBar.findChild("Length");
    var cbLength = optionsToolBar.findChild("UseLength");
    var leAngle = optionsToolBar.findChild("Angle");
    var cbAngle = optionsToolBar.findChild("UseAngle");

    if (!resume) {
        if (!isNull(cbLength)) {
            cbLength.checked = false;
            cbLength.setProperty("Loaded", true);
            cbLength.setProperty("Saved", true);
        }
        if (!isNull(cbAngle)) {
            cbAngle.checked = false;
            cbAngle.setProperty("Loaded", true);
            cbAngle.setProperty("Saved", true);
        }

        //if (!isNull(cbLength)) cbLength.checked = false;
        //if (!isNull(cbAngle)) cbAngle.checked = false;

        var self = this;
        if (!isNull(leLength)) {
            leLength.textEdited.connect(function() {
                // prevent selection and overwriting of text when typing numbers:
                cbLength.blockSignals(true);
                cbLength.checked = true;
                self.useLength = true;
                cbLength.blockSignals(false);
            });
        }

        if (!isNull(leAngle)) {
            leAngle.textEdited.connect(function() {
                cbAngle.blockSignals(true);
                cbAngle.checked = true;
                self.useAngle = true;
                cbAngle.blockSignals(false);
            });
        }
    }
};

/**
 * Shows the restriction options for the line tool (length / angle).
 * called from RestrictAngleLength to avoid redundant options.
 */
Line2P.showRestrictingOptions = function() {
    var optionsToolBar = EAction.getOptionsToolBar();
    for (var i=0; i<Line2P.RestrictingOptions.length; i++) {
        var w = optionsToolBar.findChild(Line2P.RestrictingOptions[i] + "Action");
        if (!isNull(w)) {
            w.visible = true;
        }
    }

};

/**
 * Hides the restriction options for the line tool (length / angle).
 * called from RestrictAngleLength to avoid redundant options.
 */
Line2P.hideRestrictingOptions = function() {
    var optionsToolBar = EAction.getOptionsToolBar();
    for (var i=0; i<Line2P.RestrictingOptions.length; i++) {
        var w = optionsToolBar.findChild(Line2P.RestrictingOptions[i] + "Action");
        if (!isNull(w)) {
            w.visible = false;
        }
    }
    var cbLength = optionsToolBar.findChild("UseLength");
    if (!isNull(cbLength)) {
        cbLength.checked = false;
    }
    var cbAngle = optionsToolBar.findChild("UseAngle");
    if (!isNull(cbAngle)) {
        cbAngle.checked = false;
    }
};

Line2P.prototype.escapeEvent = function() {
    switch (this.state) {
    case Line2P.State.SettingFirstPoint:
        EAction.prototype.escapeEvent.call(this);
        return;

    case Line2P.State.SettingNextPoint:
        this.setState(Line2P.State.SettingFirstPoint);
        this.updateButtonStates();
        break;
    }
};

Line2P.prototype.keyPressEvent = function(event) {
    var di = this.getDocumentInterface();

    if ((event.key() === Qt.Key_Enter.valueOf()) || (event.key() === Qt.Key_Return.valueOf())) {
        if (this.state === Line2P.State.SettingFirstPoint) {
            this.point1 = di.getLastPosition();
            di.setRelativeZero(this.point1);
            this.setState(Line2P.State.SettingNextPoint);
            di.clearPreview();
            di.previewOperation(this.getOperation(true));
        } else {
            EAction.prototype.keyPressEvent(event);
        }
    } else {
        EAction.prototype.keyPressEvent(event);
    }
};

Line2P.prototype.pickCoordinate = function(event, preview) {
    var di = this.getDocumentInterface();

    switch (this.state) {
    case Line2P.State.SettingFirstPoint:
        if (!preview) {
            this.point1 = event.getModelPosition();
            this.pointList.splice(0, 0, this.point1);
            this.pointListIndex = 0;
            di.setRelativeZero(this.point1);
            this.setState(Line2P.State.SettingNextPoint);
        }
        break;

    case Line2P.State.SettingNextPoint:
        this.point2Cursor = event.getModelPosition();
        //this.point2 = this.getRestrictedEndPoint();
        if (preview) {
            this.updatePreview();
        }
        else {
            var op = this.getOperation(preview);
            if (!isNull(op)) {
                if (!this.isRayOrXLine()) {
                    this.pointListIndex++;
                }

                var doc = this.getDocument();
                var trans = di.applyOperation(op);
                var id = this.getLineEntityId(trans);

                if (!this.isRayOrXLine()) {
                    this.pointList.splice(this.pointListIndex, 0, this.point2);
                    this.entityIdList.splice(this.pointListIndex-1, 0, id);
                    di.setRelativeZero(this.point2);
                    this.point1 = this.point2;
                }

//                qDebug("this.pointList: ", this.pointList);
//                qDebug("this.entityIdList: ", this.entityIdList);
//                qDebug("this.pointListIndex: ", this.pointListIndex);
            }
        }
        break;
    }

    if (!preview) {
        this.updateButtonStates();
    }
};

Line2P.prototype.getRestrictedEndPoint = function() {
    var p2 = this.point2Cursor;

    if (this.useLength || this.useAngle) {
        var length = this.point1.getDistanceTo(this.point2Cursor);
        var angle = this.point1.getAngleTo(this.point2Cursor);

        if (this.useLength && this.useAngle) {
            p2 = this.point1.operator_add(RVector.createPolar(this.len, this.angle));
        }
        else if (this.useLength) {
            p2 = this.point1.operator_add(RVector.createPolar(this.len, angle));
        }
        else if (this.useAngle) {
            p2 = this.point1.operator_add(RVector.createPolar(length, this.angle));
        }
    }

    return p2;
};

Line2P.prototype.getOperation = function(preview) {
    if (!isVector(this.point1) || !isVector(this.point2Cursor)) {
        return undefined;
    }

    this.point2 = this.getRestrictedEndPoint();

    var e = this.createLineEntity(this.getDocument(), this.point1, this.point2);

    return new RAddObjectOperation(e, this.getToolTitle());
};

Line2P.prototype.slotClose = function() {
    if (this.isRayOrXLine()) {
        return;
    }

    if (this.pointList.length >= 3) {
        var di = this.getDocumentInterface();
        this.point2 = this.pointList[0];
        var e = this.createLineEntity(this.getDocument(), this.point1, this.point2);
        di.applyOperation(new RAddObjectOperation(e, this.getToolTitle()));
        this.pointList.push(this.point2);
        di.setRelativeZero(this.point2);
        this.setState(Line2P.State.SettingFirstPoint);
    }
    
    this.updateButtonStates();
};

Line2P.prototype.slotUndo = function() {
    if (this.isRayOrXLine()) {
        return;
    }

    if (this.pointListIndex > 0) {
        var di = this.getDocumentInterface();
        var doc = this.getDocument();

        this.pointListIndex--;
        this.point1 = this.pointList[this.pointListIndex];
        di.setRelativeZero(this.point1);

        var id = this.entityIdList[this.pointListIndex];
        var entity = doc.queryEntity(id);
        di.applyOperation(new RDeleteObjectOperation(entity));

        di.clearPreview();
        di.previewOperation(this.getOperation(true));

//        qDebug("undone: this.pointListIndex: ", this.pointListIndex);
//        qDebug("undone: this.pointList: ", this.pointList);
//        qDebug("undone: this.entityIdList: ", this.entityIdList);
    }

    this.updateButtonStates();
};

Line2P.prototype.slotRedo = function() {
    if (this.isRayOrXLine()) {
        return;
    }
    if (this.pointListIndex < this.pointList.length-1) {
        var di = this.getDocumentInterface();
        var doc = this.getDocument();

        this.pointListIndex++;
        this.point1 = this.pointList[this.pointListIndex];
        di.setRelativeZero(this.point1);

        var e = this.createLineEntity(doc, this.pointList[this.pointListIndex-1], this.pointList[this.pointListIndex]);
        var trans = di.applyOperation(new RAddObjectOperation(e));
        var id = this.getLineEntityId(trans);
        this.entityIdList[this.pointListIndex-1] = id;

        di.clearPreview();
        di.previewOperation(this.getOperation(true));

//        qDebug("redone: this.pointListIndex: ", this.pointListIndex);
//        qDebug("redone: this.pointList: ", this.pointList);
//        qDebug("redone: this.entityIdList: ", this.entityIdList);
    }

    this.updateButtonStates();
};

Line2P.prototype.updateButtonStates = function() {
    var optionsToolBar = EAction.getOptionsToolBar();

    var w = optionsToolBar.findChild("Undo");
    if (!isNull(w)) {
        if (this.pointListIndex > 0 && !this.isRayOrXLine()) {
            w.enabled = true;
        } else {
            w.enabled = false;
        }
    }

    w = optionsToolBar.findChild("Redo");
    if (!isNull(w)) {
        //qDebug("this.pointList: ", this.pointList);
        //qDebug("this.pointListIndex: ", this.pointListIndex);
        //qDebug("this.entityIdList.length: ", this.entityIdList.length);
        if (this.pointListIndex >= 0 &&
            this.pointListIndex < this.entityIdList.length &&
            !this.isRayOrXLine()) {

            w.enabled = true;
        } else {
            w.enabled = false;
        }
    }
    
    w = optionsToolBar.findChild("Close");
    if (!isNull(w)) {
        if (this.pointList.length > 2 && !this.isRayOrXLine()) {
            w.enabled = true;
        } else {
            w.enabled = false;
        }
    }

    w = optionsToolBar.findChild("UseLength");
    if (!isNull(w)) {
        w.checked = false;
    }

    w = optionsToolBar.findChild("UseAngle");
    if (!isNull(w)) {
        w.checked = false;
    }
};

Line2P.prototype.getLineEntityId = function(trans) {
    var objIds = trans.getAffectedObjects();
    for (var i=0; i<objIds.length; i++) {
        var objId = objIds[i];
        var obj = this.getDocument().queryObjectDirect(objId);
        if (isLineEntity(obj)) {
            return obj.getId();
        }
    }

    return RObject.INVALID_ID;
};

/**
 * Allows commands to be entered in command line
 *
 * "Using the 'startsWith' function allows the user to enter only as many characters
 * as needed to distinguish between commands
 * In this case only the first character is needed. (But entering 'c', 'cl', 'clo', 'clos'
 * or 'close' would all invoke the close command. Similarly with undo and redo)"
 *
 */
Line2P.prototype.commandEvent = function(event) {
    var str;

    var cmd = event.getCommand();
    cmd = cmd.toLowerCase();

    str = "close";
    if (str.startsWith(cmd)) {
        this.slotClose();
        event.accept();
        return;
    }
    str = "undo";
    if (str.startsWith(cmd)) {
        this.slotUndo();
        event.accept();
        return;
    }
    str = "redo";
    if (str.startsWith(cmd)) {
        this.slotRedo();
        event.accept();
        return;
    }
};

Line2P.prototype.typeChanged = function() {
    if (this.pointList.length!==0) {
        this.pointList = [this.pointList[this.pointList.length-1]];
    }
    this.pointListIndex = 0;
    this.entityIdList = [];
    this.updateButtonStates();
};

Line2P.prototype.slotUseLengthChanged = function(v) {
    this.useLength = v;
    this.updatePreview(true);
};

Line2P.prototype.slotLengthChanged = function(v) {
    this.len = v;
    this.updatePreview(true);
};

Line2P.prototype.slotUseAngleChanged = function(v) {
    this.useAngle = v;
    this.updatePreview(true);
};

Line2P.prototype.slotAngleChanged = function(v) {
    this.angle = v;
    this.updatePreview(true);
};
