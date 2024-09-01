import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Item {
    id: root

    property string activeGear: "P"

    RowLayout {
        anchors.fill: parent
        anchors.topMargin: 0
        spacing: 0

        // Footer Left - Navigation
        Item {
            id: leftNavigation
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop
            Layout.preferredWidth: parent.width * 0.35
            Layout.preferredHeight: parent.height * 0.75

            RowLayout {
                anchors.horizontalCenter: parent.horizontalCenter
                width: leftNavigation.width * 0.6
                height: leftNavigation.height * 0.85
                spacing: 5

                Repeater {
                    model: [
                        {icon: "qrc:/assets/img/icon-battery.png", alignment: Qt.AlignBottom},
                        {icon: "qrc:/assets/img/icon-navi.png", alignment: Qt.AlignVCenter},
                        {icon: "qrc:/assets/img/icon-speed.png", alignment: Qt.AlignTop}
                    ]
                    delegate: Item {
                        Layout.fillWidth: true
                        Layout.fillHeight: true

                        Button {
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.verticalCenter: modelData.alignment === Qt.AlignVCenter ? parent.verticalCenter : undefined
                            anchors.bottom: modelData.alignment === Qt.AlignBottom ? parent.bottom : undefined
                            anchors.top: modelData.alignment === Qt.AlignTop ? parent.top : undefined
                            icon.source: modelData.icon
                            icon.width: leftNavigation.height * 0.35
                            icon.height: leftNavigation.height * 0.35
                            background: Item {}
                            flat: true

                            onClicked: console.log("Clicked:", modelData.icon)
                        }
                    }
                }
            }
        }

        // Spacer Element
        Item {
            Layout.fillWidth: true
        }

        // Gear Indicator
        Item {
            id: gearContainer
            Layout.preferredWidth: parent.width * 0.175
            Layout.preferredHeight: parent.height * 0.35
            Layout.alignment: Qt.AlignCenter | Qt.AlignTop

            Row {
                anchors.centerIn: parent
                spacing: 5

                Repeater {
                    model: ["P", "R", "N", "D"]
                    delegate: Item {
                        width: Math.max(contentText.width, contentText.height) * 1.2
                        height: width

                        Rectangle {
                            id: gearCircle
                            anchors.fill: parent
                            color: "#f89e00"
                            opacity: modelData === root.activeGear ? 0.3 : 0
                            visible: modelData === root.activeGear
                            radius: width / 2

                            SequentialAnimation on opacity {
                                loops: Animation.Infinite
                                running: false // modelData === root.activeGear
                                NumberAnimation { from: 0; to: 0.3; duration: 1000; easing.type: Easing.InOutQuad }
                                NumberAnimation { from: 0.3; to: 0; duration: 1000; easing.type: Easing.InOutQuad }
                            }
                        }

                        Text {
                            id: contentText
                            anchors.centerIn: parent
                            text: modelData
                            font.pixelSize: gearContainer.height * 0.5
                            color: "white" // modelData === root.activeGear ? "#f89e00" : "white"
                        }
                    }
                }
            }
        }

        // Spacer Element
        Item {
            Layout.fillWidth: true
        }

        // Footer Right - Navigation
        Item {
            id: rightNavigation
            Layout.alignment: Qt.AlignRight | Qt.AlignTop
            Layout.preferredWidth: parent.width * 0.35
            Layout.preferredHeight: parent.height * 0.75

            RowLayout {
                anchors.horizontalCenter: parent.horizontalCenter
                width: rightNavigation.width * 0.6
                height: rightNavigation.height * 0.85
                spacing: 5

                Repeater {
                    model: [
                        {icon: "qrc:/assets/img/icon-media.png", alignment: Qt.AlignTop},
                        {icon: "qrc:/assets/img/icon-phone.png", alignment: Qt.AlignVCenter},
                        {icon: "qrc:/assets/img/icon-lock.png", alignment: Qt.AlignBottom}
                    ]
                    delegate: Item {
                        Layout.fillWidth: true
                        Layout.fillHeight: true

                        Button {
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.verticalCenter: modelData.alignment === Qt.AlignVCenter ? parent.verticalCenter : undefined
                            anchors.bottom: modelData.alignment === Qt.AlignBottom ? parent.bottom : undefined
                            anchors.top: modelData.alignment === Qt.AlignTop ? parent.top : undefined
                            icon.source: modelData.icon
                            icon.width: rightNavigation.height * 0.35
                            icon.height: rightNavigation.height * 0.35
                            background: Item {}
                            flat: true

                            onClicked: console.log("Clicked:", modelData.icon)
                        }
                    }
                }
            }
        }
    }
}
