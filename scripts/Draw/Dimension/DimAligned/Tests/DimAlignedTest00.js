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
// File        : scripts/Draw/Dimension/DimAligned/Tests/DimAlignedTest00.js
// Timestamp   : 2011-04-26 15:23:19
// Description : 

include('scripts/Pro/Developer/TestingDashboard/TdbTest.js');

function DimAlignedTest00() {
    TdbTest.call(this, 'scripts/Draw/Dimension/DimAligned/Tests/DimAlignedTest00.js');
}

DimAlignedTest00.prototype = new TdbTest();

DimAlignedTest00.prototype.test00 = function() {
    qDebug('running DimAlignedTest00.test00()...');
    this.setUp();
    this.importFile('scripts/Draw/Dimension/Tests/floor_plan.dxf');
    TdbTest.clickOnWidget('MainWindow::CadToolBar::MainToolsPanel::DimensionToolsPanelButton');
    TdbTest.clickOnWidget('MainWindow::CadToolBar::DimensionToolsPanel::DimAlignedButton');
    this.setToolOption('Dimension/Prefix', '(No prefix)');
    this.setToolOption('Dimension/Text', '');
    this.setToolOption('Dimension/UpperTolerance', '');
    this.setToolOption('Dimension/LowerTolerance', '');
    this.updateToolOptions();
    this.setZoom(10.154826958105648, new RVector(1.77161, 7.37305, 0) );
    var p = new RVector(9.946951, 30.146054);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(10.154826958105648, new RVector(1.77161, 7.37305, 0) );
    var p = new RVector(29.937444, 30.047578);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(10.154826958105648, new RVector(1.77161, 7.37305, 0) );
    var p = new RVector(29.642018, 33.888117);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(10.154826958105648, new RVector(1.77161, 7.37305, 0) );
    var p = new RVector(29.937444, 29.949103);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(10.154826958105648, new RVector(1.77161, 7.37305, 0) );
    var p = new RVector(39.981928, 20.10157);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(10.154826958105648, new RVector(1.77161, 7.37305, 0) );
    var p = new RVector(43.822466, 23.154305);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setToolOption('Dimension/Prefix', '(No prefix)');
    this.setToolOption('Dimension/Text', '');
    this.setToolOption('Dimension/UpperTolerance', '0.1');
    this.setToolOption('Dimension/LowerTolerance', '0.2');
    this.updateToolOptions();
    this.setZoom(10.154826958105648, new RVector(1.77161, 7.37305, 0) );
    var p = new RVector(40.080404, 20.10157);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(10.154826958105648, new RVector(1.77161, 7.37305, 0) );
    var p = new RVector(40.474305, 3.853139);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(10.154826958105648, new RVector(1.77161, 7.37305, 0) );
    var p = new RVector(45.988924, 4.148565);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setToolOption('Dimension/Prefix', '(No prefix)');
    this.setToolOption('Dimension/Text', '0.02');
    this.setToolOption('Dimension/UpperTolerance', '');
    this.setToolOption('Dimension/LowerTolerance', '');
    this.updateToolOptions();
    this.setZoom(10.154826958105648, new RVector(1.77161, 7.37305, 0) );
    var p = new RVector(35.944439, -0.282825);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(10.154826958105648, new RVector(1.77161, 7.37305, 0) );
    var p = new RVector(37.716996, -0.282825);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(10.154826958105648, new RVector(1.77161, 7.37305, 0) );
    var p = new RVector(44.117892, -4.812691);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setToolOption('Dimension/Prefix', '\u00F8 (Diameter)');
    this.setToolOption('Dimension/Text', '');
    this.setToolOption('Dimension/UpperTolerance', '');
    this.setToolOption('Dimension/LowerTolerance', '');
    this.updateToolOptions();
    this.setZoom(10.154826958105648, new RVector(1.77161, 7.37305, 0) );
    var p = new RVector(14.969193, 19.018341);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(10.154826958105648, new RVector(1.77161, 7.37305, 0) );
    var p = new RVector(14.969193, 15.079327);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(10.154826958105648, new RVector(1.77161, 7.37305, 0) );
    var p = new RVector(20.08991, 15.079327);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setToolOption('Dimension/Prefix', '± (Plus/Minus)');
    this.setToolOption('Dimension/Text', '');
    this.setToolOption('Dimension/UpperTolerance', '');
    this.setToolOption('Dimension/LowerTolerance', '');
    this.updateToolOptions();
    this.setZoom(10.154826958105648, new RVector(1.77161, 7.37305, 0) );
    var p = new RVector(15.264619, 10.155561);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(10.154826958105648, new RVector(1.77161, 7.37305, 0) );
    var p = new RVector(14.969193, 5.822646);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(10.154826958105648, new RVector(1.77161, 7.37305, 0) );
    var p = new RVector(23.733498, 6.216547);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    var p = new RVector(18.61278, 1.194305);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.RightButton, 2, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.RightButton, 0, 0);
    this.verifyDrawing('DimAlignedTest00_000.dxf');
    this.tearDown();
    qDebug('finished DimAlignedTest00.test00()');
};

