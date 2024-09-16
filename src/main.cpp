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
    ESP_LOGI(MAIN_TAG, "Setup!");
    setupSound();
    dfmp3.delayForResponse(1000 * 1);
    setDefaultVolume();
    dfmp3.delayForResponse(300);
    playBackground();

    Base.setup();
}

void fireGun() {
    auto degreesPerSecond = (int) random(60, 90);

    Base.turnArmUp(degreesPerSecond);
    dfmp3.delayForResponse(500);
    for (int i = 0; i < 2; i++) {
        playBeamRifle();
        Base.fireGun(500);
        dfmp3.delayForResponse(800);
        dfmp3.delayForResponse(500); // Wait
    }
    Base.turnArmDown(degreesPerSecond);
}

void fireHeadVulcan() {
    playHeadVulcan();
    for (int i = 0; i < 10; i++) {
        Base.fireHeadVulcan(250);
        dfmp3.delayForResponse(50);
    }
}

void fireHeadVulcanAround() {
    ESP_LOGD(MAIN_TAG, "(Table) Turn Left");
    Base.startTurnTable(-60, 15); // 4s
    dfmp3.delayForResponse(1000);
    fireHeadVulcan(); // 3s

    dfmp3.delayForResponse(1000); // Wait...

    ESP_LOGD(MAIN_TAG, "(Table) Move to End of Right");
    Base.startTurnTable(60, 60); // 2s
    dfmp3.delayForResponse(1000 * 2);

    dfmp3.delayForResponse(1000); // Wait

    ESP_LOGD(MAIN_TAG, "(Table) Move to Center");
    Base.startTurnTable(0, 20); // 3s
    fireHeadVulcan(); // 3s

    dfmp3.delayForResponse(1000); // Wait
}

int lastDegrees = 0;
bool lastDirectionIsLeft = true;
void loop() {
    dfmp3.loop();
    auto mode = (int) random(0, 12);
    switch (mode) {
        case 0:
        case 1:
        case 2:
            ESP_LOGD(MAIN_TAG, "[Fire Gun]");
            fireGun();
            dfmp3.delayForResponse(1000);
            break;
        case 3:
            ESP_LOGD(MAIN_TAG, "[Fire Head-Vulcan]");
            fireHeadVulcan();
            dfmp3.delayForResponse(1000);
            break;
        case 4:
            ESP_LOGD(MAIN_TAG, "[Fire Head-Vulcan Around!]");
            Base.turnTable(0, 15);
            fireHeadVulcanAround();
            dfmp3.delayForResponse(1000 * 3);
            break;
        case 5:
            ESP_LOGD(MAIN_TAG, "[Fire Gun & Head-Vulcan]");
            fireGun();
            dfmp3.delayForResponse(1000);
            fireHeadVulcan();
            dfmp3.delayForResponse(1000);
            break;
        default:
            lastDegrees = (int) random(30, 60);
            lastDegrees = lastDegrees * (lastDirectionIsLeft ? 1 : -1);
            lastDirectionIsLeft = !lastDirectionIsLeft;
            Base.turnTable(lastDegrees, 30);

            dfmp3.delayForResponse(1000 * random(1, 7));
            break;
    }
}