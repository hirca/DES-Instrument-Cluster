import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

GroupBox {
    title: "Gear Control"

    ColumnLayout {
        anchors.fill: parent

        RowLayout {
            Label { text: "CAN ID:" }
            TextField {
                text: canBusDataManager.gearCANId
                onTextChanged: canBusDataManager.gearCANId = text
            }
        }

        RowLayout {
            Label { text: "Selected Gear:" }
            ComboBox {
                model: ["P", "N", "R", "D"]
                onCurrentTextChanged: canBusDataManager.setGear(currentText)
            }
        }
    }
}
