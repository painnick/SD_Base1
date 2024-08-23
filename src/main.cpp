#include <Arduino.h>

#define MAIN_TAG "Main"

// Tower PIN
#define PIN_HALL_SENSOR_MAX 21
#define PIN_HALL_SENSOR_MIN 22

#define PIN_TOUCH_UP 12
#define PIN_TOUCH_DOWN 14

#define PIN_MOTOR1 25
#define PIN_MOTOR2 26

// Base PIN & Channel
#define PIN_SERVO1_TABLE 14
#define PIN_SERVO1_ARM 17
#define PIN_EYE 4
#define PIN_GUN 18

#define CH_MOTOR1 2
#define CH_MOTOR2 3

// Servo
#define DISABLE_COMPLEX_FUNCTIONS
#define MAX_EASING_SERVOS 6
#define DISABLE_MICROS_AS_DEGREE_PARAMETER

#include <ServoEasing.hpp>

// Controllers
#include "controllers/BaseController.h"
#include "controllers/TowerController.h"

BaseController Base(PIN_SERVO1_TABLE, PIN_SERVO1_ARM, PIN_EYE, PIN_GUN);
TowerController Tower(PIN_MOTOR1, PIN_MOTOR2, CH_MOTOR1, CH_MOTOR2);

void IRAM_ATTR WhenMin() {
    Tower.onMin();
}

void IRAM_ATTR WhenMax() {
    Tower.onMax();
}

void setup() {
    ESP_LOGI(MAIN_TAG, "Setup!");

    Tower.setup();
    attachInterrupt(PIN_HALL_SENSOR_MAX, WhenMax, FALLING);
    attachInterrupt(PIN_HALL_SENSOR_MIN, WhenMin, FALLING);

    Base.setup();
    delay(1000 * 3);
}

void loop() {
    auto isUp = touchRead(PIN_TOUCH_UP) < 32;
    auto isDown = touchRead(PIN_TOUCH_DOWN) < 32;
    Tower.loop(isUp, isDown);
    delay(100);
}