/*******************************************************************************
 * File Name    : arduino-sensor-can.ino
 * Description  : Arduino RPM and Speed Measurement with CAN Communication
 * Author       : Hakan Hirca
 * Creation Date: [Current Date, e.g., 2023-08-30]
 *
 * Copyright (c) 2024 SEA:ME
 * All rights reserved.
 *
 * Version History:
 * v1.0 - Initial version
 * v1.1 - Added detailed comments for all variables
 * v1.2 - Updated to use wheel diameter instead of circumference
 * v1.3 - Added CAN communication using MCP2515
 * v1.4 - Updated speed resolution to 0.1 km/h in CAN message
 *
 *******************************************************************************/

/**
 * @file arduino_rpm_speed_can.ino
 * @brief This Arduino sketch measures RPM from a wheel sensor, calculates
 *        vehicle speed, and sends the data via CAN bus using MCP2515.
 *
 * @note Hardware Setup:
 *       - Arduino board (e.g., Arduino Uno, Nano)
 *       - Wheel speed sensor connected to digital pin 2
 *       - MCP2515 CAN controller connected via SPI
 */

#include <stdint.h>
#include <SPI.h>
#include <mcp2515.h>

/* Constants */
#define PULSES_PER_REVOLUTION ((uint8_t)2U)    /**< Number of pulses per wheel revolution */
#define ZERO_TIMEOUT ((uint32_t)100000U)       /**< 100ms timeout for zero speed detection */
#define NUM_READINGS ((uint8_t)10U)            /**< Number of readings for moving average filter */
#define WHEEL_DIAMETER (0.5F)                  /**< Wheel diameter in meters */
#define PI (3.14159F)                          /**< Value of pi for calculations */
#define SERIAL_BAUD_RATE ((uint32_t)115200U)   /**< Baud rate for serial communication */
#define RPM_SENSOR_PIN ((uint8_t)2U)           /**< Digital pin number for the RPM sensor */
#define UPDATE_INTERVAL ((uint32_t)100U)       /**< Update interval in milliseconds */
#define CAN_CS_PIN ((uint8_t)10U)              /**< CS pin for MCP2515 */
#define CAN_MESSAGE_ID ((uint32_t)0x123U)      /**< CAN message ID for RPM and speed data */

/* Global variables */
static volatile uint32_t g_lastPulseTime = 0U;        /**< Timestamp of the last detected pulse */
static volatile uint32_t g_periodBetweenPulses = ZERO_TIMEOUT + 1000U;  /**< Time period between two consecutive pulses */
static volatile uint32_t g_pulseCount = 0U;           /**< Counter for the number of pulses detected */

static uint32_t g_rpmReadings[NUM_READINGS] = {0U};   /**< Array to store recent RPM readings for moving average */
static uint8_t g_readIndex = 0U;                      /**< Current index in the RPM readings array */
static uint32_t g_rpmTotal = 0U;                      /**< Sum of all RPM readings in the array */
static uint32_t g_rpmAverage = 0U;                    /**< Calculated average RPM */

MCP2515 mcp2515(CAN_CS_PIN);  /**< MCP2515 CAN controller object */

/* Function prototypes */
static void countPulse(void);
static uint32_t calculateRPM(void);
static float calculateSpeed(uint32_t rpm);
static void sendCANMessage(uint32_t rpm, float speed);

/**
 * @brief Arduino setup function. Initializes serial communication, interrupts, and CAN.
 */
void setup(void) {
    Serial.begin(SERIAL_BAUD_RATE);
    pinMode(RPM_SENSOR_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(RPM_SENSOR_PIN), countPulse, RISING);
    
    mcp2515.reset();
    mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);
    mcp2515.setNormalMode();
    
    Serial.println("Arduino RPM, Speed, and CAN setup complete");
}

/**
 * @brief Arduino main loop function. Periodically calculates RPM and speed, and sends CAN messages.
 */
void loop(void) {
    static uint32_t lastUpdateTime = 0U;  /**< Timestamp of the last update */
    uint32_t currentTime = millis();      /**< Current time in milliseconds */
    
    /* Update measurements and send data every UPDATE_INTERVAL milliseconds */
    if ((currentTime - lastUpdateTime) >= UPDATE_INTERVAL) {
        uint32_t rpm = calculateRPM();     /**< Calculated RPM value */
        float speed_kph = calculateSpeed(rpm);  /**< Calculated speed in km/h */
        
        sendCANMessage(rpm, speed_kph);
        
        Serial.print("RPM: ");
        Serial.print(rpm);
        Serial.print(", Speed: ");
        Serial.print(speed_kph);
        Serial.println(" km/h");
        
        lastUpdateTime = currentTime;
    }
}

/**
 * @brief Interrupt Service Routine for pulse counting.
 * 
 * This function is called on each rising edge of the sensor signal.
 * It calculates the period between pulses and increments the pulse count.
 */
static void countPulse(void) {
    uint32_t currentTime = micros();  /**< Current time in microseconds */
    g_periodBetweenPulses = currentTime - g_lastPulseTime;
    g_lastPulseTime = currentTime;
    g_pulseCount++;
}

/**
 * @brief Calculates RPM using the period between pulses.
 * 
 * This function calculates the RPM based on the period between pulses,
 * applies a moving average filter, and handles zero speed detection.
 * 
 * @return The calculated and smoothed RPM value.
 */
static uint32_t calculateRPM(void) {
    uint32_t currentTime = micros();  /**< Current time in microseconds */
    uint32_t period;                  /**< Time period between pulses */
    uint32_t rpm;                     /**< Calculated RPM value */
    
    noInterrupts();
    period = g_periodBetweenPulses;
    g_pulseCount = 0U;  /* Reset pulse count */
    interrupts();
    
    if ((currentTime - g_lastPulseTime) > ZERO_TIMEOUT) {
        rpm = 0U;
    } else {
        /* RPM calculation: (60 * 1,000,000 / period) / PULSES_PER_REVOLUTION */
        rpm = (60000000UL / period) / PULSES_PER_REVOLUTION;
    }
    
    /* Apply Moving Average Filter */
    g_rpmTotal = g_rpmTotal - g_rpmReadings[g_readIndex];
    g_rpmReadings[g_readIndex] = rpm;
    g_rpmTotal = g_rpmTotal + rpm;
    g_readIndex = (g_readIndex + 1U) % NUM_READINGS;
    
    g_rpmAverage = g_rpmTotal / NUM_READINGS;
    
    return g_rpmAverage;
}

/**
 * @brief Calculates speed in km/h based on RPM and wheel diameter.
 * 
 * This function converts the calculated RPM to speed in kilometers per hour
 * using the wheel diameter.
 * 
 * @param rpm The current RPM value.
 * @return The calculated speed in km/h.
 */
static float calculateSpeed(uint32_t rpm) {
    /* Speed (km/h) = (RPM * π * wheel diameter * 60) / 1000 */
    return ((float)rpm * PI * WHEEL_DIAMETER * 3.6F) / 60.0F;
}

/**
 * @brief Sends RPM and speed data via CAN bus.
 * 
 * This function prepares and sends a CAN message containing RPM and speed data.
 * The message uses 2 bytes for RPM and 2 bytes for speed.
 * Speed is sent with a resolution of 0.1 km/h.
 * 
 * @param rpm The current RPM value.
 * @param speed The current speed in km/h.
 */
static void sendCANMessage(uint32_t rpm, float speed) {
    struct can_frame canMsg;
    canMsg.can_id = CAN_MESSAGE_ID;
    canMsg.can_dlc = 4;  // 4 bytes: 2 for RPM, 2 for speed
    
    // Pack RPM into the first 2 bytes
    canMsg.data[0] = (uint8_t)(rpm >> 8);
    canMsg.data[1] = (uint8_t)(rpm & 0xFF);
    
    // Pack speed into the last 2 bytes (convert to uint16_t, resolution 0.1 km/h)
    uint16_t speed_int = (uint16_t)(speed * 10.0F);
    canMsg.data[2] = (uint8_t)(speed_int >> 8);
    canMsg.data[3] = (uint8_t)(speed_int & 0xFF);
    
    mcp2515.sendMessage(&canMsg);
}