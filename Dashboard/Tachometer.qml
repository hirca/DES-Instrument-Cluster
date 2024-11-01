import QtQuick
import QtQuick.Controls

Item {
    id: root
    // Customizable properties
    property real value: 0 // Current RPM value
    property real minValue: 0 // Minimum RPM value
    property real maxValue: 500 // Maximum RPM value
    property real startAngle: -70 // Starting angle for the needle
    property real endAngle: 70 // Ending angle for the needle

    // Input validation

    onMinValueChanged: {
        if (minValue >= maxValue) {
            console.error("Minimum RPM must be less than maximum RPM.")
            minValue = maxValue - 1
        }
    }
    onMaxValueChanged: {
        if (maxValue <= minValue) {
            console.error("Maximum RPM must be greater than minimum RPM.")
            maxValue = minValue + 1
        }
    }

    /**
     * @brief Bound rpm value between min and max values
     * @param rpm The rpm to apply
     * @return The corresponding rpm value
     */
    function rpmBound(rpm) {
        return Math.floor(Math.max(minValue, Math.min(maxValue, rpm)))
    }
    /**
     * @brief Convert angle to RPM
     * @param angle The angle to convert
     * @return The corresponding RPM value
     */
    function angleToRpm(angle) {
        return minValue + (angle - startAngle) * (maxValue - minValue) / (endAngle - startAngle)
    }
    /**
     * @brief Convert RPM to angle
     * @param rpm The RPM to convert
     * @return The corresponding angle value
     */
    function rpmToAngle(rpm) {
        if (rpm <= minValue) return startAngle
        return startAngle + (rpmBound(rpm) - minValue) * (endAngle - startAngle) / (maxValue - minValue)
    }
    // Tachometer background
    Image {
        id: dial
        anchors.fill: parent
        source: "qrc:/assets/img/tachometer.png"
        fillMode: Image.PreserveAspectFit
        cache: true
        onStatusChanged: {
            if (status === Image.Error) {
                console.error("Failed to load tachometer dial image:", source)
            }
        }
    }
    // Tachometer needle
    Image {
        id: needle
        height: dial.height * 0.3
        source: "qrc:/assets/img/tacho-needle.png"
        cache: true
        anchors {
            bottom: parent.verticalCenter
            horizontalCenter: parent.horizontalCenter
        }
        transformOrigin: Item.Bottom
        onStatusChanged: {
            if (status === Image.Error) {
                console.error("Failed to load tachometer needle image:", source)
            }
        }
        transform: Rotation {
            id: needleRotation
            origin.x: needle.width / 2
            origin.y: needle.height
            angle: rpmToAngle(root.value)
        }
    }
}
