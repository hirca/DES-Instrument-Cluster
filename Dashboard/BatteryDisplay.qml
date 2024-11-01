import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

/**
 * @brief BatteryDisplay component for electric vehicle dashboard
 * 
 * Displays battery charge level and range information with visual indicators
 * including a car silhouette, charging indicator, and range display.
 * 
 * Features:
 * - Dynamic battery level indicator
 * - Range calculation and display
 * - Animated charging line
 * - Glow effect for battery status
 * 
 * Example usage:
 * ```qml
 * BatteryDisplay {
 *     width: 400
 *     height: 200
 *     chargeValue: 75  // Battery percentage
 * }
 * ```
 */
Item {
    id: root

    // Public properties
    property real chargeValue: 0    /// Battery charge percentage (0-100)
    property real rangeValue: 0     /// Current range in kilometers
    property real rangeMax: 4.8     /// Maximum range in kilometers
    
    // Calculate range when charge value changes
    onChargeValueChanged: {
        rangeValue = Math.floor(chargeValue * rangeMax * 0.1)
    }

    // Main layout container
    ColumnLayout {
        width: parent.width
        height: parent.height
        spacing: 0

        // Range indicator section
        Item {
            id: rangeDisplay
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.preferredHeight: 0.5

            RowLayout {
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 5

                Text {
                    id: rangeText
                    Layout.alignment: Qt.AlignVCenter
                    text: qsTr("%1 KM").arg(Math.round(rangeValue))
                    font.pixelSize: rangeIcon.height * 0.5
                    color: "white"
                }

                Image {
                    id: rangeIcon
                    height: rangeDisplay.height * 0.5
                    width: height
                    fillMode: Image.PreserveAspectFit
                    Layout.alignment: Qt.AlignVCenter
                    source: "qrc:/assets/img/range.png"
                    smooth: true
                }

                // Spacer for center alignment
                Item {
                    Layout.fillWidth: true
                }
            }
        }

        // Battery visualization section
        Item {
            id: batteryDisplayArea
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.preferredHeight: 1

            // Base car silhouette
            Image {
                id: carImage
                anchors.fill: parent
                source: "qrc:/assets/img/car.png"
                fillMode: Image.PreserveAspectFit
            }

            // Battery glow effect
            Item {
                id: glowContainer
                anchors.fill: carImage
                clip: true

                Image {
                    id: glowImage
                    anchors.fill: parent
                    source: "qrc:/assets/img/battery_light.png"
                    fillMode: Image.Stretch
                }
            }

            // Charging indicator line
            Item {
                id: needleContainer
                anchors.fill: carImage
                clip: true

                Image {
                    id: needleImage
                    source: "qrc:/assets/img/charging-line.png"
                    height: parent.height
                    fillMode: Image.PreserveAspectFit
                    x: (parent.width - width) * (root.chargeValue / 100)
                }
            }

            // Battery percentage display
            Text {
                id: chargePercentageText
                anchors.centerIn: parent
                text: qsTr("%1%").arg(Math.round(root.chargeValue))
                font.pixelSize: Math.min(parent.width, parent.height) * 0.25
                color: "white"
            }
        }

        // Bottom spacing section
        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.preferredHeight: 0.5
        }
    }
}