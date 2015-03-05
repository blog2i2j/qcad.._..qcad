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
// File        : scripts/Draw/Circle/Circle2PR/Tests/Circle2PRTest00.js
// Timestamp   : 2011-02-28 13:46:16
// Description : 2 circles, same 2 points, different radii and solutions

include('scripts/Pro/Developer/TestingDashboard/TdbTest.js');

function Circle2PRTest00() {
    TdbTest.call(this, 'scripts/Draw/Circle/Circle2PR/Tests/Circle2PRTest00.js');
}

Circle2PRTest00.prototype = new TdbTest();

Circle2PRTest00.prototype.test00 = function() {
    qDebug('running Circle2PRTest00.test00()...');
    this.setUp();
    this.clickOnWidget('MainWindow::MainToolsPanel::LineToolsPanelButton');
    this.clickOnWidget('MainWindow::LineToolsPanel::Line2PButton');
    this.setZoom(10, new RVector(5, 5, 0) );
    var p = new RVector(14, 17.3);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    var p = new RVector(14, 17.3);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(10, new RVector(5, 5, 0) );
    var p = new RVector(34.1, 17.1);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    var p = new RVector(34.1, 17.1);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    var p = new RVector(9.2, 25.9);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.RightButton, 2, 0);
    var p = new RVector(9.2, 25.9);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.RightButton, 0, 0);
    var p = new RVector(3.7, 28.4);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.RightButton, 2, 0);
    var p = new RVector(3.7, 28.4);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.RightButton, 0, 0);
    this.clickOnWidget('MainWindow::MainToolsPanel::CircleToolsPanelButton');
    this.clickOnWidget('MainWindow::CircleToolsPanel::Circle2PRButton');
    this.setToolOption('Circle2PR/Radius',  [ 8, 0 ] );
    this.setToolOption('Circle2PR/Solution', 'Solution1');
    this.updateToolOptions();
    this.setZoom(10, new RVector(5, 5, 0) );
    var p = new RVector(13.8, 17.1);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    var p = new RVector(13.8, 17.1);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(10, new RVector(5, 5, 0) );
    var p = new RVector(21.6, 17);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    var p = new RVector(21.6, 17);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setToolOption('Circle2PR/Radius',  [ 10, 0 ] );
    this.setToolOption('Circle2PR/Solution', 'Solution2');
    this.updateToolOptions();
    this.setZoom(10, new RVector(5, 5, 0) );
    var p = new RVector(34, 16.9);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    var p = new RVector(34, 16.9);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(10, new RVector(5, 5, 0) );
    var p = new RVector(21.9, 17.1);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    var p = new RVector(21.9, 17.1);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    var p = new RVector(25.4, 10.4);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.RightButton, 2, 0);
    var p = new RVector(25.4, 10.4);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.RightButton, 0, 0);
    this.tearDown();
    qDebug('finished Circle2PRTest00.test00()');
};

