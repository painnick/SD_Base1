#include "TowerController.h"

#include "esp_log.h"

// Logger
#define TOWER_TAG "TOWER"

TowerController::TowerController(uint8_t pin1, uint8_t pin2, uint8_t ch1, uint8_t ch2) :
        Motor1PIN(pin1), Motor2PIN(pin2),
        Motor1Ch(ch1), Motor2Ch(ch2) {
}

void TowerController::setup() {
    ledcSetup(Motor1Ch, 1000, 8);
    ledcAttachPin(Motor1PIN, Motor1Ch);
    ledcSetup(Motor2Ch, 1000, 8);
    ledcAttachPin(Motor2PIN, Motor2Ch);
}

void TowerController::motorMoveUp(bool noLimit) {
    if (noLimit) {
        ESP_LOGI(TOWER_TAG, "Motor up(NO LIMIT)...");
        motorStop = false;
        isMotorUp = true;
        ledcWrite(Motor1Ch, 255);
        ledcWrite(Motor2Ch, 0);
    } else {
        if (nearMax) {
            ESP_LOGW(TOWER_TAG, "Skip Motor up!");
        } else {
            ESP_LOGI(TOWER_TAG, "Motor up...");
            motorStop = false;
            isMotorUp = true;
            ledcWrite(Motor1Ch, 255);
            ledcWrite(Motor2Ch, 0);
        }
    }
}

void TowerController::motorMoveDown(bool noLimit) {
    if (noLimit) {
        ESP_LOGI(TOWER_TAG, "Motor down(NO LIMIT)...");
        motorStop = false;
        isMotorUp = false;
        ledcWrite(Motor1Ch, 0);
        ledcWrite(Motor2Ch, 255);
    } else {
        if (nearMin) {
            ESP_LOGW(TOWER_TAG, "Skip Motor down!");
        } else {
            ESP_LOGI(TOWER_TAG, "Motor down...");
            motorStop = false;
            isMotorUp = false;
            ledcWrite(Motor1Ch, 0);
            ledcWrite(Motor2Ch, 255);
        }
    }
}

void TowerController::onMax() {
    ESP_LOGW(TOWER_TAG, "Max!");
    motorMoveStop();
    nearMax = true;
}

void TowerController::onMin() {
    ESP_LOGW(TOWER_TAG, "Min!");
    motorMoveStop();
    nearMin = true;
}

void TowerController::motorMoveStop() {
    ESP_LOGI(TOWER_TAG, "Motor stop");
    motorStop = true;
    ledcWrite(Motor1Ch, 0);
    ledcWrite(Motor2Ch, 0);
}

void TowerController::loop(bool isUp, bool isDown) {
    if (isUp && isDown) {
        if (isMotorUp) {
            motorMoveUp(true);
        } else {
            // Should be stop!
            // motorMoveDown(true);
        }
    } else {
        if (isUp) {
            motorMoveUp();
            nearMin = false;
        } else if (isDown) {
            motorMoveDown();
            nearMax = false;
        } else {
            if (!motorStop)
                motorMoveStop();
        }
    }
}
