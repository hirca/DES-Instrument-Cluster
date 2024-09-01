import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

GroupBox {
    title: "RPM Control"

    ColumnLayout {
        anchors.fill: parent

        RowLayout {
            Label { text: "CAN ID:" }
            TextField {
                text: canBusDataManager.rpmCANId
                onTextChanged: canBusDataManager.rpmCANId = text
            }
        }

        RowLayout {
            Label { text: "Min RPM:" }
            SpinBox {
                id: minRPMSpinBox
                from: 0
                to: 8000
                value: 0
                onValueChanged: canBusDataManager.setRPMRange(value, maxRPMSpinBox.value)
            }

            Label { text: "Max RPM:" }
            SpinBox {
                id: maxRPMSpinBox
                from: 0
                to: 8000
                value: 1000
                onValueChanged: canBusDataManager.setRPMRange(minRPMSpinBox.value, value)
            }
        }

        RowLayout {
            Label { text: "Profile:" }
            RadioButton {
                text: "Increasing"
                checked: true
                onCheckedChanged: if (checked) canBusDataManager.setRPMProfile(true)
            }
            RadioButton {
                text: "Decreasing"
                onCheckedChanged: if (checked) canBusDataManager.setRPMProfile(false)
            }
        }

        RowLayout {
            Label { text: "Step Size:" }
            SpinBox {
                from: 1
                to: 100
                value: 10
                onValueChanged: canBusDataManager.setRPMStepSize(value)
            }
        }
    }
}
