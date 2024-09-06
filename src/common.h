#pragma once

// These are all GPIO pins on the ESP32
// Recommended pins include 2,4,12-19,21-23,25-27,32-33
// for the ESP32-S2 the GPIO pins are 1-21,26,33-42

#define PIN_MP3_TX 6 // OK
#define PIN_MP3_RX 5 // OK

// Tower PIN
#define PIN_HALL_SENSOR_MAX 3 // OK
#define PIN_HALL_SENSOR_MIN 4 // OK

#define PIN_MOTOR1 20
#define PIN_MOTOR2 21

// Base PIN & Channel
#define PIN_SERVO1_TABLE 1 // OK
#define PIN_SERVO1_ARM 10 // OK
#define PIN_EYE 7 // OK
#define PIN_GUN 0 // OK

// I2C
#define PIN_SDA 8
#define PIN_SCL 9

#define CH_MOTOR1 2
#define CH_MOTOR2 3
#define CH_EYE 4
#define CH_GUN 5