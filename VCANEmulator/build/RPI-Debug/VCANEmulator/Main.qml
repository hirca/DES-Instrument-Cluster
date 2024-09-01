import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts

Window {
    visible: true
    width: 800
    height: 700
    title: "Virtual CAN Bus Emulator"

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10
        spacing: 10

        RowLayout {
            Button {
                text: "Start"
                onClicked: canBusDataManager.start()
                enabled: !canBusDataManager.isRunning
            }
            Button {
                text: "Stop"
                onClicked: canBusDataManager.stop()
                enabled: canBusDataManager.isRunning
            }
            Label {
                text: canBusDataManager.isRunning ? "Status: Running" : "Status: Stopped"
            }
        }

        SpeedControl {
            Layout.fillWidth: true
        }

        RowLayout {
            Label { text: "Speed Update Interval (ms):" }
            Slider {
                from: 50
                to: 1000
                value: canBusDataManager.speedUpdateInterval
                onValueChanged: canBusDataManager.speedUpdateInterval = value
            }
            Label { text: canBusDataManager.speedUpdateInterval.toFixed(0) + " ms" }
        }

        RPMControl {
            Layout.fillWidth: true
        }

        RowLayout {
            Label { text: "RPM Update Interval (ms):" }
            Slider {
                from: 50
                to: 1000
                value: canBusDataManager.rpmUpdateInterval
                onValueChanged: canBusDataManager.rpmUpdateInterval = value
            }
            Label { text: canBusDataManager.rpmUpdateInterval.toFixed(0) + " ms" }
        }

        GearControl {
            Layout.fillWidth: true
        }

        BatteryControl {
            Layout.fillWidth: true
        }
    }
}
