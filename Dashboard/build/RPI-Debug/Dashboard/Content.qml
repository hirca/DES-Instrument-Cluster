import QtQuick

Rectangle {
    color: "transparent"

    Row {
        anchors.centerIn: parent
        spacing: 10

        Rectangle {
            width: parent.width * 0.35 // 1st column
            height: parent.height
            color: "lightblue"
        }

        Rectangle {
            width: parent.width * 0.30 // 2nd column
            height: parent.height
            color: "blue"
        }

        Rectangle {
            width: parent.width * 0.35 // 3rd column
            height: parent.height
            color: "darkblue"
        }
    }
}
