#include "BaseController.h"

// Logger
#define SERVOS_TAG "SERVOS"

BaseController::BaseController(int table, int arm, int eye, int bazuka) :
        _TablePin(table),
        _ArmPin(arm),
        _EyePin(eye),
        _GunPin(bazuka) {
}

void BaseController::setup() {
    servoTable.attach(_TablePin, 90);
    servoTable.setEasingType(EASE_LINEAR);
    servoArm.attach(_ArmPin, 0);
    servoArm.setEasingType(EASE_LINEAR);
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
    servoArm.easeTo(45, degreesPerSecond);
    delay(2 * 1000);
    servoArm.easeTo(0, degreesPerSecond);
}

void BaseController::loop() {
    // Do something
}