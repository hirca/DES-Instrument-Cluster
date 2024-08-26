/*
 * File: arduino-sensor-can.ino
 * 
 * Title: Arduino RPM Measurement and CAN Bus Integration
 * 
 * Author: Hakan Hirca
 * Contact: hakan[at]hirca[dot]de
 * 
 * Date Created: [Current Date, e.g., 2023-08-26]
 * Last Modified: [Current Date, e.g., 2023-08-26]
 * 
 * Description:
 * This Arduino sketch measures RPM from a wheel sensor, calculates vehicle speed,
 * and transmits this data over a CAN bus. It uses interrupt-based pulse counting
 * for RPM measurement, implements a moving average filter for smoothing the RPM
 * readings, and sends the data via CAN messages every 100ms.
 * 
 * Key Features:
 * - Interrupt-based RPM measurement
 * - Moving average filter for RPM smoothing
 * - Speed calculation based on RPM and wheel circumference
 * - CAN bus integration for data transmission
 * - Efficient 4-byte CAN message (2 bytes RPM, 2 bytes Speed)
 * 
 *  Apply Moving Average Filter
 *  Explanation of Moving Average Filter:
 *  1. Subtract the oldest reading from the total
 *  2. Add the new reading to the total
 *  3. Store the new reading in the array, overwriting the oldest
 *  4. Move to the next position in the array (wrapping around if necessary)
 *  5. Calculate the average by dividing the total by the number of readings
 * 
 *  Formula: average = sum(last n readings) / n
 *  This filter helps smooth out fluctuations in the RPM readings,
 *  reducing noise and providing a more stable output.
 * 
 * Hardware:
 * - Arduino board (e.g., Arduino Uno, Nano)
 * - Wheel speed sensor connected to digital pin 2
 * - MCP2515 CAN controller connected via SPI
 * 
 * Dependencies:
 * - SPI library
 * - mcp2515 library for CAN communication
 * 
 * License: MIT
 */


#include <SPI.h>
#include <mcp2515.h>

// Pin Definitions
const int rpmSensorPin = 2;  // Digital pin for the RPM sensor

// RPM Calculation Variables
const byte PulsesPerRevolution = 2;  // Number of pulses per revolution of the wheel
volatile unsigned long lastPulseTime = 0;  // Time of the last pulse
volatile unsigned long pulseCount = 0;  // Number of pulses counted

// Speed Calculation
const float wheelCircumference = 0.075;  // Wheel circumference in meters (adjust to your wheel size)

// Moving Average Filter Variables
const int numReadings = 10;  // Number of readings to average
unsigned long rpmReadings[numReadings];  // Array to store RPM readings
int readIndex = 0;  // Index of the current reading
unsigned long rpmTotal = 0;  // Running total of RPM readings
unsigned long rpmAverage = 0;  // Calculated average RPM

// CAN Communication Setup
struct can_frame canMsg;
MCP2515 mcp2515(10);  // CS pin for the MCP2515 chip

void setup() {
  Serial.begin(115200);
  
  // Set up RPM sensor
  pinMode(rpmSensorPin, INPUT_PULLUP);
  // Attach interrupt to the RPM sensor pin
  attachInterrupt(digitalPinToInterrupt(rpmSensorPin), countPulse, RISING);
  
  // Initialize CAN module
  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);
  mcp2515.setNormalMode();
  
  Serial.println("Arduino RPM, Speed, and CAN setup complete");
}

void loop() {
  static unsigned long lastUpdateTime = 0;
  unsigned long currentTime = millis();
  
  // Update measurements and send data every 100ms
  if (currentTime - lastUpdateTime >= 100) {
    unsigned int rpm = calculateRPM();
    float speed_kph = calculateSpeed(rpm);
    
    sendDataViaCAN(rpm, speed_kph);
    
    // Print data to serial monitor
    Serial.print("RPM: ");
    Serial.print(rpm);
    Serial.print(", Speed: ");
    Serial.print(speed_kph);
    Serial.println(" km/h");
    
    lastUpdateTime = currentTime;
  }
}

// Interrupt Service Routine for pulse counting
void countPulse() {
  unsigned long currentTime = micros();
  // Simple debounce: ignore pulses that arrive too quickly after the last one
  if (currentTime - lastPulseTime > 50) { // 50 microseconds debounce time
    pulseCount++;
    lastPulseTime = currentTime;
  }
}

// Calculate RPM using pulse count and elapsed time
unsigned int calculateRPM() {
  static unsigned long lastCalcTime = 0;
  unsigned long currentTime = micros();
  unsigned long elapsedTime = currentTime - lastCalcTime;
  
  // Calculate RPM every 100ms
  if (elapsedTime >= 100000) {
    noInterrupts();  // Disable interrupts to safely read pulseCount
    unsigned long pulses = pulseCount;
    pulseCount = 0;  // Reset pulse count
    interrupts();  // Re-enable interrupts
    
    // Calculate RPM
    // Formula: RPM = (pulses / pulses_per_rev) * (60 seconds / elapsed_time_in_minutes)
    //        = (pulses * 60 * 1,000,000) / (pulses_per_rev * elapsed_time_in_microseconds)
    unsigned int rpm = (pulses * 600000UL) / (elapsedTime * PulsesPerRevolution);
    
    // Apply Moving Average Filter
    rpmTotal = rpmTotal - rpmReadings[readIndex];  // Remove the oldest reading
    rpmReadings[readIndex] = rpm;  // Store the new reading
    rpmTotal = rpmTotal + rpm;  // Add the new reading to the total
    readIndex = (readIndex + 1) % numReadings;  // Move to the next index, wrapping around if necessary
    
    rpmAverage = rpmTotal / numReadings;  // Calculate the average
    
    lastCalcTime = currentTime;
    return rpmAverage;
  }
  return rpmAverage;  // Return last average if not enough time has passed
}

// Calculate speed in km/h based on RPM
float calculateSpeed(unsigned int rpm) {
  // Speed (m/s) = (RPM * wheel circumference) / 60
  // Speed (km/h) = Speed (m/s) * 3.6
  return (rpm * wheelCircumference * 3.6) / 60.0;
}

// Send RPM and speed data via CAN bus
void sendDataViaCAN(unsigned int rpm, float speed_kph) {
  canMsg.can_id = 0x123;  // CAN ID for our data
  canMsg.can_dlc = 4;  // Data length (2 bytes for RPM, 2 bytes for speed)
  
  // Split 16-bit RPM value into two 8-bit bytes
  canMsg.data[0] = rpm >> 8;  // High byte (most significant)
  canMsg.data[1] = rpm & 0xFF;  // Low byte (least significant)
  
  // Speed data (multiply by 100 to preserve two decimal places)
  uint16_t speed_int = (uint16_t)(speed_kph * 100);
  canMsg.data[2] = speed_int >> 8;  // High byte
  canMsg.data[3] = speed_int & 0xFF;  // Low byte
  
  mcp2515.sendMessage(&canMsg);  // Send the CAN message
}