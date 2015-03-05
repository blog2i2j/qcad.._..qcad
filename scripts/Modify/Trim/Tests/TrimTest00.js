/**
 * Copyright (c) 2011-2013 by Andrew Mustun. All rights reserved.
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
// Auto generated by Testing Dashboard
// File        : scripts/Modify/Trim/Tests/TrimTest00.js
// Timestamp   : 2011-08-16 11:07:53
// Description : 

include('scripts/Pro/Developer/TestingDashboard/TdbTest.js');

function TrimTest00() {
    TdbTest.call(this, 'scripts/Modify/Trim/Tests/TrimTest00.js');
}

TrimTest00.prototype = new TdbTest();

TrimTest00.prototype.test00 = function() {
    qDebug('running TrimTest00.test00()...');
    this.setUp();
    var w = objectFromPath('MainWindow::CadToolBar::MainToolsPanel');
    this.sendMouseEvent(w, QEvent.MouseButtonPress, new QPoint(41, 440), Qt.LeftButton, 1, 0);
    var w = objectFromPath('MainWindow::CadToolBar::MainToolsPanel');
    this.sendMouseEvent(w, QEvent.MouseButtonRelease, new QPoint(41, 440), Qt.LeftButton, 0, 0);
    this.importFile('scripts/Modify/Trim/Tests/data/entities.dxf');
    this.triggerCommand('trim');
    this.setZoom(10.379746835443038, new RVector(5.37439, 4.21341, 0) );
    var p = new RVector(28.24878, 25.556098);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(10.379746835443038, new RVector(5.37439, 4.21341, 0) );
    var p = new RVector(25.262195, 31.336585);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(10.379746835443038, new RVector(5.37439, 4.21341, 0) );
    var p = new RVector(19.481707, 23.05122);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(10.379746835443038, new RVector(5.37439, 4.21341, 0) );
    var p = new RVector(11.292683, 16.885366);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.verifyDrawing('TrimTest00_000.dxf');
    this.tearDown();
    qDebug('finished TrimTest00.test00()');
};

