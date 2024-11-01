import QtQuick
import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Controls

/**
 * @brief Main Dashboard Window
 * Container for all dashboard components including speedometer,
 * battery display, and tachometer
 */
Window {
    id: root

    // Window properties
    visible: true
    visibility: Window.FullScreen
    width: 1024
    height: 576
    minimumWidth: 800
    minimumHeight: 400
    title: qsTr("Dashboard")
    color: "#010e1b"

    // Layout properties
    readonly property real aspectRatio: 16.9 / 9.2

    // Main container
    Item {
        id: frame
        anchors.centerIn: parent
        width: Math.min(parent.width, parent.height * aspectRatio)
        height: width / aspectRatio

        // Background frame
        Image {
            anchors.fill: parent
            source: "qrc:/assets/img/frame.png"
            fillMode: Image.PreserveAspectFit
            asynchronous: true
        }

        // Main layout
        ColumnLayout {
            anchors.fill: parent
            spacing: 0

            // Header section
            Header {
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: parent.width * 0.875
                Layout.preferredHeight: parent.height * 0.1825
                userName: "Hakan"
                signalStrength: 3
            }

            // Content section
            Item {
                Layout.preferredWidth: parent.width * 0.875
                Layout.preferredHeight: parent.height * 0.635
                Layout.alignment: Qt.AlignHCenter

                RowLayout {
                    anchors.fill: parent
                    spacing: 0

                    // Left section - Speedometer
                    Speedometer {
                        Layout.preferredWidth: parent.width * 0.35
                        Layout.fillHeight: true
                        value: canReader.speed
                    }

                    // Center section - Battery Display
                    BatteryDisplay {
                        id: batteryDisplay
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        chargeValue: battery.level
                    }

                    // Right section - Tachometer
                    Tachometer {
                        Layout.preferredWidth: parent.width * 0.35
                        Layout.fillHeight: true
                        value: canReader.rpm
                    }
                }
            }

            // Footer section
            Footer {
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: parent.width * 0.875
                Layout.preferredHeight: parent.height * 0.1825
                activeGear: canReader.gearState
            }
        }
    }
}