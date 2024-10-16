import QtQuick
import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Controls

/**
 * @brief Main Dashboard Window
 *
 * This component represents the main dashboard window, containing the speedometer,
 * battery display, and tachometer.
 */

Window {
    id: root
    visible: true
    width: 1024
    height: 576
    minimumWidth: 800
    minimumHeight: 400
    title: qsTr("Dashboard")
    color: "#010e1b"

    readonly property real aspectRatio: 16.9 / 9.2
    property bool isDataSourceAvailable: idashboardBridge !== null && idashboardBridge !== undefined


    // Frame Container
    Item {
        id: frame
        anchors.centerIn: parent
        width: Math.min(parent.width, parent.height * aspectRatio)
        height: width / aspectRatio

        // Frame Background
        Image {
            anchors.fill: parent
            source: "qrc:/assets/img/frame.png"
            fillMode: Image.PreserveAspectFit
            asynchronous: true
        }

        ColumnLayout {
            anchors.fill: parent
            spacing: 0

            // Header Area
            Header {
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: parent.width * 0.875
                Layout.preferredHeight: parent.height * 0.1825

                // Header Properties
                userName: "User"
                signalStrength: 3
            }

            // Content Area
            Item {
                Layout.preferredWidth: parent.width * 0.875
                Layout.preferredHeight: parent.height * 0.635
                Layout.alignment: Qt.AlignHCenter


                RowLayout {
                    anchors.fill: parent
                    spacing: 0

                    Speedometer {
                        Layout.preferredWidth: parent.width * 0.35
                        Layout.fillHeight: true

                        // Speedometer properties
                        value: isDataSourceAvailable ? idashboardBridge.speed : 0
                    }

                    // Battery Display
                    BatteryDisplay {
                        id: batteryDisplay
                        Layout.fillHeight: true
                        Layout.fillWidth: true

                        // Battery Display properties
                        chargeValue: isDataSourceAvailable ? idashboardBridge.batteryLevel : 0

                        // // Add a connection to log when the chargeValue changes
                        //   Connections {
                        //       target: idashboardBridge
                        //       function onBatteryLevelChanged() {
                        //           console.log("Dashboard: Battery level changed to", idashboardBridge.batteryLevel)
                        //           console.log("Dashboard: BatteryDisplay chargeValue is", batteryDisplay.chargeValue)
                        //       }
                        //   }
                    }

                    // Tachometer
                    Tachometer {
                        Layout.preferredWidth: parent.width * 0.35
                        Layout.fillHeight: true

                        // Tachometer properties
                        value: idashboardBridge.rpm
                    }

                }

            }

            // Footer Area
            Footer {
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: parent.width * 0.875
                Layout.preferredHeight: parent.height * 0.1825

                // Footer Properties
                activeGear : idashboardBridge.gear

            }

        }
    }


}
