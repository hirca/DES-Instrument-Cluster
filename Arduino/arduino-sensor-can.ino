#include <SPI.h>
#include "mcp2515_can.h"

// Pin definitions
#define RPM_SENSOR_PIN 3
#define CAN_CS_PIN 9

// CAN configuration
mcp2515_can CAN(CAN_CS_PIN);

// RPM calculation constants
const int WHEEL_HOLES = 20;
const long MEASUREMENT_INTERVAL = 100;  // milliseconds
const float SECONDS_PER_INTERVAL = MEASUREMENT_INTERVAL / 1000.0;

// Volatile variables for interrupt handling
volatile unsigned int pulseCount = 0;

// Timing variables
unsigned long currentMillis = 0;
unsigned long lastMillis = 0;

// CAN message buffer
unsigned char data[8];

/**
 * Initialize serial communication, CAN bus, and RPM sensor
 */
void setup() {
    // Initialize serial communication
    SERIAL_PORT_MONITOR.begin(115200);
    
    // Initialize CAN bus
    initializeCAN();
    
    // Configure RPM sensor
    setupRPMSensor();
	
}

/**
 * Main program loop
 */
void loop() {
    currentMillis = millis();

    // Check if it's time for a new measurement
    if (currentMillis - lastMillis >= MEASUREMENT_INTERVAL) {
        lastMillis = currentMillis;
        
        // Get and send RPM reading
        float rpm = calculateRPM();
        sendRPMviaCAN(rpm);
        
        // Reset pulse counter
        pulseCount = 0;
    }
}

/**
 * Initialize CAN bus communication
 */
void initializeCAN() {
    while (CAN_OK != CAN.begin(CAN_500KBPS)) {
        SERIAL_PORT_MONITOR.println("CAN init fail, retry...");
        delay(100);
    }
    SERIAL_PORT_MONITOR.println("CAN init ok!");
}

/**
 * Configure RPM sensor input and interrupt
 */
void setupRPMSensor() {
    pinMode(RPM_SENSOR_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(RPM_SENSOR_PIN), 
                   countPulses, 
                   RISING);
}

/**
 * Interrupt service routine for RPM sensor pulses
 */
void countPulses() {
    pulseCount++;
}

/**
 * Calculate current RPM based on pulse count
 * @return Calculated RPM value
 */
float calculateRPM() {
    float rotations = (float)pulseCount / WHEEL_HOLES;
    float rotationsPerSecond = rotations / SECONDS_PER_INTERVAL;
    float rpm = rotationsPerSecond * 60.0;
    
    Serial.println(rpm);  // Debug output
    return rpm;
}

/**
 * Send RPM reading over CAN bus
 * @param rpm Current RPM value to send
 */
void sendRPMviaCAN(float rpm) {
    memcpy(data, &rpm, sizeof(rpm));
    CAN.sendMsgBuf(0x100, 0, 4, data);
    SERIAL_PORT_MONITOR.println("CAN BUS sendMsgBuf ok!");
}