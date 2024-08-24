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

void BaseController::turnArm() {
    auto degreesPerSecond = (int) random(60, 90);
    ESP_LOGD(SERVOS_TAG, "(Table) Degrees per second is %d", degreesPerSecond);
    servoArm.easeTo(60, degreesPerSecond);
    delay(500);
    fireGun();
    delay(500);
    servoArm.easeTo(0, degreesPerSecond);
}

void BaseController::fireGun() const {
    ESP_LOGD(SERVOS_TAG, "(Gun) Fire!!!");
    for (auto i = 0; i < 3; i++) {
        ledcWrite(_GunCh, 127);
        delay(500);
        ledcWrite(_GunCh, 0);
        delay(200);
    }
}

void BaseController::fireHeadVulkan() const {
    ESP_LOGD(SERVOS_TAG, "(Head Vulkan) Fire!!!");
    for (auto i = 0; i < 7; i++) {
        ledcWrite(_EyeCh, 127);
        delay(100);
        ledcWrite(_EyeCh, 0);
        delay(100);
    }
}


void BaseController::loop() {
    // Do something
}

