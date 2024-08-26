# Arduino CAN Bus RPM and Speed Sensor

This project implements a CAN bus communication system for transmitting RPM and speed data from an Arduino to a Raspberry Pi.

## Hardware Requirements

- Arduino board (e.g., Arduino Uno, Nano)
- MCP2515 CAN Bus module
- RPM sensor (e.g., Hall effect sensor)
- Connecting wires

## Software Requirements

- Arduino IDE
- MCP2515 CAN Bus library

## Setup

1. Connect the MCP2515 CAN Bus module to your Arduino:
   - CS -> Pin 10
   - SO -> Pin 12
   - SI -> Pin 11
   - SCK -> Pin 13
   - INT -> Pin 2
   - VCC -> 5V
   - GND -> GND

2. Connect your RPM sensor to the Arduino (adjust pin number in code if necessary).

3. Install the MCP2515 library in your Arduino IDE.

4. Upload the provided Arduino sketch to your board.

## Arduino Sketch Overview

The Arduino sketch does the following:

1. Reads RPM data from the sensor
2. Calculates vehicle speed based on RPM and wheel circumference
3. Packages this data into a CAN frame
4. Sends the CAN frame every 100ms

## CAN Frame Format

- Frame ID: 0x123
- Data Length: 4 bytes
- Byte 0-1: RPM (16-bit integer)
- Byte 2-3: Speed (16-bit integer, speed * 100 for two decimal places)

## Customization

- Adjust `wheelCircumference` in the code to match your specific wheel size.
- Modify `PulsesPerRevolution` if your RPM sensor gives a different number of pulses per revolution.

## Troubleshooting

- Ensure all connections are secure.
- Verify that the CAN Bus module is properly initialized (check serial output).
- If using with a Raspberry Pi, make sure the Pi's CAN interface is properly configured.

For any issues or questions, please open an issue on this GitHub repository.

