#include "BaseController.h"

// Logger
#define SERVOS_TAG "SERVOS"

BaseController::BaseController(uint8_t tablePin,
                               uint8_t armPin,
                               uint8_t eyePin, uint8_t eyeCh,
                               uint8_t gunPin, uint8_t gunCh) :
        _TablePin(tablePin),
        _ArmPin(armPin),
        _EyePin(eyePin), _EyeCh(eyeCh),
        _GunPin(gunPin), _GunCh(gunCh) {
}

void BaseController::setup() {
    servoTable.attach(_TablePin, 90);
    servoTable.setEasingType(EASE_LINEAR);
    servoArm.attach(_ArmPin, 0);
    servoArm.setEasingType(EASE_LINEAR);

    ledcSetup(_EyeCh, 1000, 8);
    ledcAttachPin(_EyePin, _EyeCh);
    ledcSetup(_GunCh, 1000, 8);
    ledcAttachPin(_GunPin, _GunCh);
}

void BaseController::turnTable() {
    auto degreesPerSecond = (int) random(30, 60);
    ESP_LOGD(SERVOS_TAG, "(TurnTable) Degrees per second is %d", degreesPerSecond);
    servoTable.easeTo(90 + (int) random(15, 45), degreesPerSecond);
    delay(500);
    servoTable.easeTo(90 - (int) random(15, 45), degreesPerSecond);
    delay(500);
}

void BaseController::turnArmUp(uint_fast16_t degreesPerSecond) {
    servoArm.easeTo(60, degreesPerSecond);
}

void BaseController::turnArmDown(uint_fast16_t degreesPerSecond) {
    servoArm.easeTo(0, degreesPerSecond);
}

void BaseController::fireGun(uint32_t ms) {
    ESP_LOGD(SERVOS_TAG, "(Gun) Fire!!!");
    ledcWrite(_GunCh, 127);
    servoArm.easeTo(50, 90);
    delay(200);
    servoArm.easeTo(60, 90);
    if(ms -200 > 0) {
        delay(ms - 200);
    }
    ledcWrite(_GunCh, 0);
}

void BaseController::fireHeadVulcan(uint32_t ms) const {
    ESP_LOGD(SERVOS_TAG, "(Head Vulcan) Fire!!!");
    ledcWrite(_EyeCh, 127);
    delay(ms);
    ledcWrite(_EyeCh, 0);
}

void BaseController::loop() {
    // Do something
}

