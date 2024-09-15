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
#include "controllers/Mp3Controller.h"

BaseController Base(PIN_SERVO1_TABLE, PIN_SERVO1_ARM, PIN_EYE, CH_EYE, PIN_GUN, CH_GUN);

void setup() {
    delay(1000 * 3);
    ESP_LOGI(MAIN_TAG, "Setup!");
    setupSound();
    setDefaultVolume();
    delay(300);
    playBackground();

    Base.setup();
    delay(1000 * 3);
}

void fireGunAndHeadVulcan() {
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
}

void loop() {
    Base.turnTable(0, 60);
    delay(1000 * 5);

    fireGunAndHeadVulcan();
    delay(1000 * 3);

    Base.turnTable((int) random(45, 60), 60);
    fireGunAndHeadVulcan();
    delay(1000 * 2);

    Base.turnTable(0, 60);
    delay(1000 * 5);

    Base.turnTable((int) random(45, 60) * -1, 60);
    fireGunAndHeadVulcan();
    delay(1000 * 2);
}