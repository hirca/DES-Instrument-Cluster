import QtQuick
import QtQuick.Controls

/**
 * @brief Speedometer component
 *
 * This component represents a customizable speedometer with a dynamic needle and digital speed display.
 *
 * Usage:
 * Speedometer {
 *     width: 300
 *     height: 300
 *     value: 75
 *     minValue: 0
 *     maxValue: 140
 * }
 */
Item {
    id: root

    // Customizable properties
    property real value: 0 // Current speed value
    property real minValue: 0 // Minimum speed value
    property real maxValue: 140 // Maximum speed value
    property real startAngle: -180 // Starting angle for the needle
    property real endAngle: 135 // Ending angle for the needle

    // EMA filter properties
    property real filteredValue: value
    property real emaAlpha: 0.2 // Adjust this value to change filter responsiveness (0.1 to 0.3 is a good range)

    property int speedLabelIncrement: 20
    property int numLabels: Math.floor((maxValue - minValue) / speedLabelIncrement) + 1
    property real labelRadiusFactor: 0.275

    property color colorZoneEndColor: "#8f610c"
    property real colorZoneRadiusFactor: 0.8  // Increased to move arc outwards

    property var colorZones: [
        { endSpeed: maxValue * 0.6, color: "#0e4d2b" }, // #0e4d2b
        { endSpeed: maxValue * 0.8, color: "#ffcc00" }, // #ffcc00
        { endSpeed: maxValue, color: "#c72c41" } // #c72c41
    ]


    // Apply EMA filter when value changes
    onValueChanged: {
        filteredValue = applyEMAFilter(value, filteredValue, emaAlpha)
    }

    // EMA filter function
    function applyEMAFilter(newValue, oldValue, alpha) {
        return alpha * newValue + (1 - alpha) * oldValue
    }

    /**
     * @brief Bound speed value between min and max values
     * @param angle The angle to convert
     * @return The corresponding speed value
     */
    function speedBound(speed) {
        return Math.floor(Math.max(minValue, Math.min(maxValue, speed)))
    }

    /**
     * @brief Convert angle to speed
     * @param angle The angle to convert
     * @return The corresponding speed value
     */
    function angleToSpeed(angle) {
        return minValue + (angle - startAngle) * (maxValue - minValue) / (endAngle - startAngle)
    }

    /**
     * @brief Convert speed to angle
     * @param speed The speed to convert
     * @return The corresponding angle value
     */
    function speedToAngle(speed) {
        return startAngle + (speedBound(speed) - minValue) * (endAngle - startAngle) / (maxValue - minValue)
    }

    // Speedometer dial background
    Image {
        id: dial
        anchors.fill: parent
        source: "qrc:/assets/img/speedometer.png"
        fillMode: Image.PreserveAspectFit
        cache: true

        onStatusChanged: {
            if (status === Image.Error) {
                console.error("Failed to load speedometer dial image:", source)
            }
        }
    }

    // Speed labels
    Repeater {
        model: numLabels

        Text {
            property real labelAngle: speedToAngle(index * speedLabelIncrement)
            x: dial.width / 2 + (dial.width * labelRadiusFactor * Math.cos((labelAngle - 90) * Math.PI / 180)) - width / 2
            y: dial.height / 2 + (dial.height * labelRadiusFactor * Math.sin((labelAngle - 90) * Math.PI / 180)) - height / 2
            text: (index * speedLabelIncrement).toString()
            color: "white"
            font.pixelSize: dial.height * 0.05
            font.bold: true
        }
    }



    // Speedometer needle
    Image {
        id: needle
        height: dial.height * 0.3
        source: "qrc:/assets/img/speed-needle.png"
        cache: true
        anchors {
            bottom: parent.verticalCenter
            horizontalCenter: parent.horizontalCenter
        }
        transformOrigin: Item.Bottom

        onStatusChanged: {
            if (status === Image.Error) {
                console.error("Failed to load speedometer needle image:", source)
            }
        }

        transform: Rotation {
            id: needleRotation
            origin.x: needle.width / 2
            origin.y: needle.height
            angle: speedToAngle(root.filteredValue) // Use filteredValue instead of value
            Behavior on angle {
                SpringAnimation {
                    spring: 1.4
                    damping: 0.15
                }
            }
        }
    }

    // Color zone arc with gradient
    Canvas {
         id: colorZoneCanvas
         anchors.fill: parent
         onPaint: {
             var ctx = getContext("2d");
             var centerX = width / 2;
             var centerY = height / 2;
             var radius = Math.min(width, height) / 2 * colorZoneRadiusFactor;

             ctx.lineWidth = dial.height * 0.07;

             var startAngle = speedToAngle(minValue);
             colorZones.forEach(function(zone, index) {
                 var endAngle = speedToAngle(zone.endSpeed);

                 var gradient = ctx.createLinearGradient(0, 0, width, height);
                 gradient.addColorStop(0, "transparent");
                 gradient.addColorStop(1, zone.color);

                 ctx.beginPath();
                 ctx.arc(centerX, centerY, radius, (startAngle - 90) * Math.PI / 180, (endAngle - 90) * Math.PI / 180, false);
                 ctx.strokeStyle = gradient;
                 ctx.stroke();

                 startAngle = endAngle;
             });
         }
     }

    // Speed display text
    Text {
        anchors {
            top: parent.verticalCenter
            topMargin: 5
            horizontalCenter: parent.horizontalCenter
        }
        font.pixelSize: dial.height * 0.20
        color: "white"
        text: qsTr("%1").arg(speedBound(angleToSpeed(needleRotation.angle)))
    }

    // Smooth transition for filteredValue changes
    Behavior on filteredValue {
        SmoothedAnimation {
            duration: 300
        }
    }
}
