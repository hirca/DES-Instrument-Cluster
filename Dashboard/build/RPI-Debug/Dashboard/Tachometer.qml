import QtQuick
import QtQuick.Controls

/**
 * @brief Tachometer component
 *
 * This component represents a customizable tachometer with a dynamic needle and RPM display.
 *
 * Usage:
 * Tachometer {
 *     width: 300
 *     height: 300
 *     value: 50
 *     minValue: 0
 *     maxValue: 100
 * }
 */
Item {
    id: root

    // Customizable properties
    property real value: 0 // Current RPM value
    property real minValue: 0 // Minimum RPM value
    property real maxValue: 1000 // Maximum RPM value
    property real startAngle: -70 // Starting angle for the needle
    property real endAngle: 70 // Ending angle for the needle

    // EMA filter properties
    property real filteredValue: value
    property real emaAlpha: 0.2 // Adjust this value to change filter responsiveness (0.1 to 0.3 is a good range)


    // Input validation
    // Apply EMA filter when value changes
    onValueChanged: {
        filteredValue = applyEMAFilter(value, filteredValue, emaAlpha)
    }

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

    // EMA filter function
    function applyEMAFilter(newValue, oldValue, alpha) {
        return alpha * newValue + (1 - alpha) * oldValue
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
            angle: rpmToAngle(root.filteredValue)
            Behavior on angle {
                SpringAnimation {
                    spring: 1.4
                    damping: 0.15
                }
            }
        }
    }


    // Smooth transition for value changes
    Behavior on value {
        SmoothedAnimation {
            duration: 300
        }
    }
}
