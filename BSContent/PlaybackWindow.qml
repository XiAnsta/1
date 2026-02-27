import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtCharts
import TEM.System 1.0

Window {
    id: playbackWindow
    width: 1400
    height: 900
    title: "TEM Data Playback"
    visible: true
    color: "#F0F2F5"

    PlaybackBackend {
        id: playBackend
    }

    // Colors
    property color cBlue: "#1976D2"
    property color cBlueDark: "#1565C0"
    property color cNavy: "#263238"
    property color cPanel: "#FFFFFF"
    property color cBg: "#F4F6F8"
    property color cText: "#2C3E50"
    property color cTextLt: "#546E7A"
    property color cBorder: "#CFD8DC"
    property color cGreen: "#43A047"
    property color cOrange: "#F57C00"

    // Font definitions
    property int f14: 18; property int f12: 16; property int f11: 15; property int f10: 14; property int f9: 13; property int f8: 12

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        // Toolbar
        Rectangle {
            Layout.fillWidth: true
            height: 48
            color: cBlueDark
            RowLayout {
                anchors.fill: parent
                anchors.leftMargin: 16
                anchors.rightMargin: 16
                Text { text: "TEM Data Playback"; font.pixelSize: f12; font.bold: true; color: "white" }
                Item { Layout.fillWidth: true }
                
                Button {
                    text: "Load Database"
                    background: Rectangle { color: "white"; radius: 4 }
                    onClicked: openDbDialog.open()
                }
            }
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 0

            // Left Panel - Project Tree
            Rectangle {
                Layout.preferredWidth: 260
                Layout.fillHeight: true
                color: cPanel
                border.color: cBorder
                border.width: 1

                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 10
                    spacing: 10

                    Text { text: playBackend.currentProjectName !== "" ? playBackend.currentProjectName : "No DB Loaded"; font.pixelSize: f11; font.bold: true; color: cText }
                    
                    ScrollView {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        clip: true
                        
                        Column {
                            width: parent.width
                            spacing: 2
                            Repeater {
                                model: playBackend.getProjectTree()
                                delegate: Column {
                                    width: parent.width
                                    Rectangle {
                                        width: parent.width
                                        height: 30
                                        color: "#ECEFF1"
                                        Text { anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: 5; text: "📁 " + modelData.name; font.pixelSize: f9 }
                                    }
                                    Repeater {
                                        model: modelData.points
                                        delegate: Rectangle {
                                            width: parent.width
                                            height: 28
                                            color: ptMouse.containsMouse ? "#E3F2FD" : "white"
                                            Text { anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: 25; text: "📄 " + modelData.name; font.pixelSize: f9; color: cText }
                                            MouseArea {
                                                id: ptMouse
                                                anchors.fill: parent
                                                hoverEnabled: true
                                                onDoubleClicked: {
                                                    playBackend.loadPointData(modelData.id)
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }

            // Center Panel - Waveforms
            Rectangle {
                Layout.fillWidth: true
                Layout.fillHeight: true
                color: cBg

                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 10
                    spacing: 10

                    // Waveform Display Area
                    Rectangle {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        color: "white"
                        border.color: cBorder
                        border.width: 1

                        ColumnLayout {
                            anchors.fill: parent
                            spacing: 1

                            // Recv
                            ChartView {
                                Layout.fillWidth: true; Layout.fillHeight: true
                                title: "Recv Waveform (V)"
                                titleColor: cNavy; titleFont.pixelSize: f10; titleFont.bold: true
                                margins { top: 0; bottom: 0; left: 0; right: 0 }
                                legend.visible: false
                                antialiasing: true
                                backgroundColor: "#FAFAFA"
                                ValueAxis { id: playAxisXRecv; min: 0; max: 20000; labelFormat: "%.0f μs" }
                                ValueAxis { id: playAxisYRecv; min: -0.1; max: 10.0 }
                                LineSeries { id: playRecvSeries; axisX: playAxisXRecv; axisY: playAxisYRecv; color: cBlue; width: 2 }
                            }

                            // Send
                            ChartView {
                                Layout.fillWidth: true; Layout.fillHeight: true
                                title: "Send Current (A)"
                                titleColor: cNavy; titleFont.pixelSize: f10; titleFont.bold: true
                                margins { top: 0; bottom: 0; left: 0; right: 0 }
                                legend.visible: false
                                antialiasing: true
                                backgroundColor: "#FAFAFA"
                                ValueAxis { id: playAxisXSend; min: 0; max: 20000; labelFormat: "%.0f μs" }
                                ValueAxis { id: playAxisYSend; min: -5; max: 30 }
                                LineSeries { id: playSendSeries; axisX: playAxisXSend; axisY: playAxisYSend; color: cGreen; width: 2 }
                            }

                            // Off
                            ChartView {
                                Layout.fillWidth: true; Layout.fillHeight: true
                                title: "Turn-off Waveform (V)"
                                titleColor: cNavy; titleFont.pixelSize: f10; titleFont.bold: true
                                margins { top: 0; bottom: 0; left: 0; right: 0 }
                                legend.visible: false
                                antialiasing: true
                                backgroundColor: "#FAFAFA"
                                ValueAxis { id: playAxisXOff; min: 0; max: 5000; labelFormat: "%.0f μs" }
                                ValueAxis { id: playAxisYOff; min: -0.1; max: 5.0 }
                                LineSeries { id: playOffSeries; axisX: playAxisXOff; axisY: playAxisYOff; color: cOrange; width: 2 }
                            }
                        }
                    }

                    // Playback Controls
                    Rectangle {
                        Layout.fillWidth: true
                        height: 70
                        color: "white"
                        border.color: cBorder
                        border.width: 1

                        RowLayout {
                            anchors.fill: parent
                            anchors.margins: 10
                            spacing: 15

                            Button {
                                text: playBackend.isPlaying ? "⏸ Pause" : "▶ Play"
                                font.pixelSize: f11
                                font.bold: true
                                onClicked: {
                                    if(playBackend.isPlaying) playBackend.pause()
                                    else playBackend.play()
                                }
                            }

                            Slider {
                                Layout.fillWidth: true
                                from: 0.0
                                to: 1.0
                                value: playBackend.playbackProgress
                                onMoved: {
                                    playBackend.pause()
                                    playBackend.seek(value)
                                }
                            }

                            Text {
                                text: (playBackend.playbackProgress * 100).toFixed(1) + "%"
                                font.pixelSize: f10
                                color: cTextLt
                            }
                        }
                    }
                }
            }

            // Right Panel - Info & Export
            Rectangle {
                Layout.preferredWidth: 260
                Layout.fillHeight: true
                color: cPanel
                border.color: cBorder
                border.width: 1

                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 10
                    spacing: 15

                    Rectangle {
                        Layout.fillWidth: true
                        height: 36
                        color: cNavy
                        Row {
                            anchors.left: parent.left; anchors.leftMargin: 10; anchors.verticalCenter: parent.verticalCenter; spacing: 6
                            Text { text: "ℹ️"; font.pixelSize: f12 }
                            Text { text: "Playback Info"; font.pixelSize: f11; font.bold: true; color: "white" }
                        }
                    }

                    Text { text: "Point: " + playBackend.currentPointName; font.pixelSize: f11; font.bold: true; color: cText }
                    
                    Rectangle {
                        Layout.fillWidth: true; height: 1; color: cBorder
                    }

                    Text { text: "📱 Device State At Acquisition"; font.pixelSize: f10; color: cTextLt }
                    
                    RowLayout {
                        Text { text: "Battery:"; font.pixelSize: f9; color: cTextLt }
                        Text { text: playBackend.batteryVoltage.toFixed(1) + " V"; font.pixelSize: f9; font.bold: true; color: cGreen }
                    }
                    RowLayout {
                        Text { text: "Temp:"; font.pixelSize: f9; color: cTextLt }
                        Text { text: playBackend.internalTemp.toFixed(1) + " °C"; font.pixelSize: f9; font.bold: true; color: cOrange }
                    }
                    RowLayout {
                        Text { text: "Signal:"; font.pixelSize: f9; color: cTextLt }
                        Text { text: playBackend.signalStrength.toFixed(0) + " %"; font.pixelSize: f9; font.bold: true; color: cBlue }
                    }

                    Item { Layout.fillHeight: true }

                    Button {
                        Layout.fillWidth: true
                        height: 40
                        text: "Export CSV"
                        font.pixelSize: f10
                        font.bold: true
                        onClicked: playBackend.exportCsv("D:/")
                    }
                }
            }
        }
    }

    Connections {
        target: playBackend
        function onWaveformChanged() {
            playBackend.updateRecvSeries(playRecvSeries)
            playBackend.updateSendSeries(playSendSeries)
            playBackend.updateOffSeries(playOffSeries)
        }
    }

    // Dialogs would go here (FileDialog for opening DB)
}
