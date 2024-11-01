import QtQuick
import QtQuick.Layouts

/**
 * @brief Header component
 * Displays user information, date, time and system status
 */
Item {
    id: root

    // Properties
    property string userName: "User"
    property int signalStrength: 3  // 0-3 signal levels

    // Time management
    Timer {
        id: clockTimer
        interval: 1000
        running: true
        repeat: true
        onTriggered: {
            dateDisplay.text = formatDate()
            timeDisplay.text = formatTime()
        }
    }

    // Utility functions
    function formatDate() {
        return Qt.formatDateTime(new Date(), "dd MMM yyyy").toUpperCase()
    }

    function formatTime() {
        return Qt.formatDateTime(new Date(), "hh:mm AP")
    }

    // Layout
    RowLayout {
        anchors.fill: parent
        anchors.bottomMargin: 0
        spacing: 0

        // User greeting section
        Item {
            id: userGreeting
            Layout.alignment: Qt.AlignLeft | Qt.AlignBottom
            Layout.preferredWidth: parent.width * 0.35
            Layout.preferredHeight: parent.height * 0.35

            RowLayout {
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 10

                Image {
                    id: userAvatar
                    source: "qrc:/assets/img/user.png"
                    Layout.preferredHeight: userGreeting.height * 0.9
                    Layout.preferredWidth: height
                    fillMode: Image.PreserveAspectFit
                    smooth: true
                }

                Text {
                    id: greetingText
                    text: "Hello " + root.userName + "!"
                    font.pixelSize: userAvatar.height * 0.4
                    color: "white"
                }

                Item { Layout.fillWidth: true }
            }
        }

        // Center spacer
        Item { 
            Layout.fillWidth: true 
        }

        // Status information section
        Item {
            id: statusInfo
            Layout.alignment: Qt.AlignRight | Qt.AlignBottom
            Layout.preferredWidth: parent.width * 0.35
            Layout.preferredHeight: parent.height * 0.35

            RowLayout {
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 10

                Image {
                    source: "qrc:/assets/img/weather-rain.png"
                    Layout.preferredHeight: statusInfo.height * 0.75
                    Layout.preferredWidth: height * (sourceSize.width / sourceSize.height)
                    fillMode: Image.PreserveAspectFit
                }

                Text {
                    id: dateDisplay
                    font.pixelSize: statusInfo.height * 0.35
                    text: formatDate()
                    color: "white"
                }

                Image {
                    id: wifiIcon
                    source: "qrc:/assets/img/wifi-" + root.signalStrength + ".png"
                    Layout.preferredHeight: statusInfo.height * 0.6
                    Layout.preferredWidth: height * (sourceSize.width / sourceSize.height)
                    fillMode: Image.PreserveAspectFit
                    smooth: true

                    Behavior on source {
                        PropertyAnimation {
                            target: wifiIcon
                            property: "opacity"
                            from: 0
                            to: 1
                            duration: 200
                        }
                    }
                }

                Text {
                    id: timeDisplay
                    font.pixelSize: statusInfo.height * 0.35
                    text: formatTime()
                    color: "white"
                }
            }
        }
    }
}