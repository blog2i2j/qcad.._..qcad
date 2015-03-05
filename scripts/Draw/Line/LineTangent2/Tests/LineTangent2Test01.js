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
// File        : scripts/Draw/Line/LineTangent2/Tests/LineTangent2Test01.js
// Timestamp   : 2011-02-28 16:05:38
// Description : 2 arcs, 4 tangents

include('scripts/Pro/Developer/TestingDashboard/TdbTest.js');

function LineTangent2Test01() {
    TdbTest.call(this, 'scripts/Draw/Line/LineTangent2/Tests/LineTangent2Test01.js');
}

LineTangent2Test01.prototype = new TdbTest();

LineTangent2Test01.prototype.test00 = function() {
    qDebug('running LineTangent2Test01.test00()...');
    this.setUp();
    this.clickOnWidget('MainWindow::MainToolsPanel::ArcToolsPanelButton');
    this.clickOnWidget('MainWindow::ArcToolsPanel::ArcCPAButton');
    this.setToolOption('ArcCPA/Direction', 'CounterClockwise');
    this.updateToolOptions();
    this.setZoom(10, new RVector(5, 5, 0) );
    var p = new RVector(9.9, 10);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    var p = new RVector(9.9, 10);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(10, new RVector(5, 5, 0) );
    var p = new RVector(15.3, 9.7);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    var p = new RVector(15.3, 9.7);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(10, new RVector(5, 5, 0) );
    var p = new RVector(13.4, 7.3);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    var p = new RVector(13.4, 7.3);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(10, new RVector(5, 5, 0) );
    var p = new RVector(9.2, 6.7);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    var p = new RVector(9.2, 6.7);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(10, new RVector(5, 5, 0) );
    var p = new RVector(29.3, 24.7);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    var p = new RVector(29.3, 24.7);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(10, new RVector(5, 5, 0) );
    var p = new RVector(35.9, 24.6);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    var p = new RVector(35.9, 24.6);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(10, new RVector(5, 5, 0) );
    var p = new RVector(32.6, 31.1);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    var p = new RVector(32.6, 31.1);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(10, new RVector(5, 5, 0) );
    var p = new RVector(34.7, 22.1);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    var p = new RVector(34.7, 22.1);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    var p = new RVector(36, 15.3);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.RightButton, 2, 0);
    var p = new RVector(36, 15.3);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.RightButton, 0, 0);
    this.clickOnWidget('MainWindow::MainToolsPanel::LineToolsPanelButton');
    this.clickOnWidget('MainWindow::LineToolsPanel::LineTangent2Button');
    this.setZoom(10, new RVector(5, 5, 0) );
    var p = new RVector(23.8, 30.5);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    var p = new RVector(23.8, 30.5);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(10, new RVector(5, 5, 0) );
    var p = new RVector(4.8, 11.4);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    var p = new RVector(4.8, 11.4);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(10, new RVector(5, 5, 0) );
    var p = new RVector(33.7, 19.4);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    var p = new RVector(33.7, 19.4);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(10, new RVector(5, 5, 0) );
    var p = new RVector(8, 4.7);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    var p = new RVector(8, 4.7);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(10, new RVector(5, 5, 0) );
    var p = new RVector(23.1, 29.1);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    var p = new RVector(23.1, 29.1);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(10, new RVector(5, 5, 0) );
    var p = new RVector(22.3, 25);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    var p = new RVector(22.3, 25);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(10, new RVector(5, 5, 0) );
    var p = new RVector(15.3, 9.9);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    var p = new RVector(15.3, 9.9);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(10, new RVector(5, 5, 0) );
    var p = new RVector(27.3, 18.2);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    var p = new RVector(27.3, 18.2);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(10, new RVector(5, 5, 0) );
    var p = new RVector(10.3, 14.8);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    var p = new RVector(10.3, 14.8);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    var p = new RVector(31.9, 8.7);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.RightButton, 2, 0);
    var p = new RVector(31.9, 8.7);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.RightButton, 0, 0);
    this.verifyDrawing('LineTangent2Test01_000.dxf');
    this.tearDown();
    qDebug('finished LineTangent2Test01.test00()');
};

