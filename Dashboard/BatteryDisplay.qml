import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

/**
 * @brief BatteryDisplay component
 *
 * This component displays the battery charge level and range of an electric vehicle.
 *
 * Usage:
 * BatteryDisplay {
 *     width: 400
 *     height: 200
 *     chargeValue: 75
 *     rangeValue: 300
 * }
 */

Item {
    id: root


    // Customizable properties
    property real chargeValue: 0 // Battery charge percentage (0-100)
    property real rangeValue: 0 // Range in kilometers
    property real rangeMax: 4.8 // Range in kilometers


    //Input validation
    onChargeValueChanged: {
        //chargeValue = Math.max(0, Math.min(100, chargeValue))
        rangeValue = Math.floor(chargeValue * rangeMax * 0.1)
    }

    onRangeValueChanged: {

    }


    ColumnLayout {
        width: parent.width
        height: parent.height

        // The first row
        Item {
            id: rangeDisplay
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.preferredHeight: 0.5


            RowLayout {

                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 5  // Space between the image and text

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
                    //asynchronous: true
                    Layout.alignment: Qt.AlignVCenter
                    source: "qrc:/assets/img/range.png" // Replace with your image path
                    smooth: true
                }



                // This spacer ensures that the content stays centered
                Item {
                    Layout.fillWidth: true
                }
            }
        }

        // The second row
        Item {
            id: batteryDisplayArea
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.preferredHeight: 1


            Image {
                id: carImage
                anchors.fill: parent
                source: "qrc:/assets/img/car.png"
                fillMode: Image.PreserveAspectFit
            }

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

            Text {
                id: chargePercentageText
                anchors.centerIn: parent
                text: qsTr("%1%").arg(Math.round(root.chargeValue))
                font.pixelSize: Math.min(parent.width, parent.height) * 0.25
                color: "white"
                // Accessible.name: qsTr("Battery charge: %1 percent").arg(Math.round(root.chargeValue))
                // Accessible.role: Accessible.StaticText
            }
        }

        // The third row
        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.preferredHeight: 0.5
        }

    }
}



