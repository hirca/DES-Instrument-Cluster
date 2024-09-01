import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

GroupBox {
    title: "Speed Control"

    ColumnLayout {
        anchors.fill: parent

        RowLayout {
            Label { text: "CAN ID:" }
            TextField {
                text: canBusDataManager.speedCANId
                onTextChanged: canBusDataManager.speedCANId = text
            }
        }

        RowLayout {
            Label { text: "Min Speed:" }
            SpinBox {
                id: minSpeedSpinBox
                from: 0
                to: 200
                value: 0
                onValueChanged: canBusDataManager.setSpeedRange(value, maxSpeedSpinBox.value)
            }

            Label { text: "Max Speed:" }
            SpinBox {
                id: maxSpeedSpinBox
                from: 0
                to: 200
                value: 140
                onValueChanged: canBusDataManager.setSpeedRange(minSpeedSpinBox.value, value)
            }
        }

        RowLayout {
            Label { text: "Profile:" }
            RadioButton {
                text: "Increasing"
                checked: true
                onCheckedChanged: if (checked) canBusDataManager.setSpeedProfile(true)
            }
            RadioButton {
                text: "Decreasing"
                onCheckedChanged: if (checked) canBusDataManager.setSpeedProfile(false)
            }
        }

        RowLayout {
            Label { text: "Step Size:" }
            SpinBox {
                from: 1
                to: 20
                value: 1
                onValueChanged: canBusDataManager.setSpeedStepSize(value)
            }
        }
    }
}
