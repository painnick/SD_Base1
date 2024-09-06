#include <Arduino.h>

#define MAIN_TAG "Main"

// Servo
#define DISABLE_COMPLEX_FUNCTIONS
#define MAX_EASING_SERVOS 6
#define DISABLE_MICROS_AS_DEGREE_PARAMETER

#include <ServoEasing.hpp>

// Controllers
#include "common.h"
#include "controllers/BaseController.h"
#include "controllers/TowerController.h"
#include "controllers/Mp3Controller.h"

BaseController Base(PIN_SERVO1_TABLE, PIN_SERVO1_ARM, PIN_EYE, CH_EYE, PIN_GUN, CH_GUN);
TowerController Tower(PIN_MOTOR1, PIN_MOTOR2, CH_MOTOR1, CH_MOTOR2);

void IRAM_ATTR WhenMin() {
    Tower.onMin();
}

void IRAM_ATTR WhenMax() {
    Tower.onMax();
}

void setup() {
    delay(1000 * 3);
    ESP_LOGI(MAIN_TAG, "Setup!");
    setupSound();
    setDefaultVolume();
    delay(300);
    playBackground();

    Tower.setup();

    gpio_set_direction((gpio_num_t)PIN_HALL_SENSOR_MAX, GPIO_MODE_INPUT);
    gpio_set_direction((gpio_num_t)PIN_HALL_SENSOR_MIN, GPIO_MODE_INPUT);
    attachInterrupt(PIN_HALL_SENSOR_MAX, WhenMax, FALLING);
    attachInterrupt(PIN_HALL_SENSOR_MIN, WhenMin, FALLING);

    Base.setup();
    delay(1000 * 3);
}

void loop() {
    auto degreesPerSecond = (int) random(60, 90);
    ESP_LOGD(MAIN_TAG, "(Table) Degrees per second is %d", degreesPerSecond);

    Base.turnArmUp(degreesPerSecond);
    delay(500);
    for (int i = 0; i < 2; i++) {
        playBeamRifle();
        Base.fireGun(500);
        delay(800);
        stopAdvert();
        delay(500);
    }
    Base.turnArmDown(degreesPerSecond);

    delay(1000);
    playHeadVulcan();
    for (int i = 0; i < 8; i++) {
        Base.fireHeadVulcan(300);
        delay(50);
    }
    stopAdvert();

    Tower.motorMoveDown();
    delay(1000 * 3);
    Tower.motorMoveUp();
    delay(1000 * 3);
    Tower.motorMoveStop();

    delay(1000 * 10);
}