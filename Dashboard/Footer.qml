import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

/**
 * @brief Footer component
 * Displays gear state and navigation controls
 */
Item {
    id: root

    property string activeGear: "P"

    // Main layout
    RowLayout {
        anchors.fill: parent
        anchors.topMargin: 0
        spacing: 0

        // Left navigation buttons
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
                    delegate: NavigationButton {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        iconSource: modelData.icon
                        iconSize: leftNavigation.height * 0.35
                        alignment: modelData.alignment
                    }
                }
            }
        }

        // Left spacer
        Item {
            Layout.fillWidth: true
        }

        // Gear indicator
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
                    delegate: GearIndicator {
                        size: Math.max(contentText.width, contentText.height) * 1.2
                        gearText: modelData
                        isActive: modelData === root.activeGear
                        textHeight: gearContainer.height * 0.5
                    }
                }
            }
        }

        // Right spacer
        Item {
            Layout.fillWidth: true
        }

        // Right navigation buttons
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
                    delegate: NavigationButton {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        iconSource: modelData.icon
                        iconSize: rightNavigation.height * 0.35
                        alignment: modelData.alignment
                    }
                }
            }
        }
    }

    // Component for navigation buttons
    component NavigationButton: Item {
        property string iconSource
        property real iconSize
        property int alignment

        Button {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: alignment === Qt.AlignVCenter ? parent.verticalCenter : undefined
            anchors.bottom: alignment === Qt.AlignBottom ? parent.bottom : undefined
            anchors.top: alignment === Qt.AlignTop ? parent.top : undefined
            
            icon.source: iconSource
            icon.width: iconSize
            icon.height: iconSize
            background: Item {}
            flat: true

            onClicked: console.log("Clicked:", iconSource)
        }
    }

    // Component for gear indicators
    component GearIndicator: Item {
        property real size
        property string gearText
        property bool isActive
        property real textHeight

        width: size
        height: size

        Rectangle {
            id: gearCircle
            anchors.fill: parent
            color: "#f89e00"
            opacity: isActive ? 0.3 : 0
            visible: isActive
            radius: width / 2
        }

        Text {
            id: contentText
            anchors.centerIn: parent
            text: gearText
            font.pixelSize: textHeight
            color: "white"
        }
    }
}