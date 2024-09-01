import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

GroupBox {
    title: "Battery Control"

    ColumnLayout {
        anchors.fill: parent

        RowLayout {
            Label { text: "CAN ID:" }
            TextField {
                text: canBusDataManager.batteryCANId
                onTextChanged: canBusDataManager.batteryCANId = text
            }
        }

        RowLayout {
            Label { text: "Battery Level:" }
            Slider {
                from: 0
                to: 100
                value: 50
                onValueChanged: canBusDataManager.setBatteryLevel(value)
            }
            Label {
                text: Math.round(parent.children[1].value) + "%"
            }
        }
    }
}
