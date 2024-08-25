#pragma once

// These are all GPIO pins on the ESP32
// Recommended pins include 2,4,12-19,21-23,25-27,32-33
// for the ESP32-S2 the GPIO pins are 1-21,26,33-42

#define PIN_MP3_TX 33 // dfplayer(FIXED)
#define PIN_MP3_RX 32 // dfplayer(FIXED)

// Tower PIN
#define PIN_HALL_SENSOR_MAX 21
#define PIN_HALL_SENSOR_MIN 22

#define PIN_TOUCH_UP 12
#define PIN_TOUCH_DOWN 14

#define PIN_MOTOR1 25
#define PIN_MOTOR2 26

// Base PIN & Channel
#define PIN_SERVO1_TABLE 19
#define PIN_SERVO1_ARM 23
#define PIN_EYE 4
#define PIN_GUN 18

#define CH_MOTOR1 2
#define CH_MOTOR2 3
#define CH_EYE 4
#define CH_GUN 5