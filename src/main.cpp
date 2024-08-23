#include <Arduino.h>

#define MAIN_TAG "Main"

#define PIN_HALL_SENSOR_MAX 21
#define PIN_HALL_SENSOR_MIN 22

#define PIN_TOUCH_UP 12
#define PIN_TOUCH_DOWN 14

#define PIN_MOTOR1 25
#define PIN_MOTOR2 26

#define CH_MOTOR1 2
#define CH_MOTOR2 3

boolean motorStop = false;
boolean isMotorUp = false;

boolean nearMax = false;
boolean nearMin = false;

void motorMoveUp(boolean noLimit = false) {
    if (noLimit) {
        ESP_LOGI(MAIN_TAG, "Motor up(NO LIMIT)...");
        motorStop = false;
        isMotorUp = true;
        ledcWrite(CH_MOTOR1, 255);
        ledcWrite(CH_MOTOR2, 0);
    } else {
        if (nearMax) {
            ESP_LOGW(MAIN_TAG, "Skip Motor up!");
        } else {
            ESP_LOGI(MAIN_TAG, "Motor up...");
            motorStop = false;
            isMotorUp = true;
            ledcWrite(CH_MOTOR1, 255);
            ledcWrite(CH_MOTOR2, 0);
        }
    }
}

void motorMoveDown(boolean noLimit = false) {
    if (noLimit) {
        ESP_LOGI(MAIN_TAG, "Motor down(NO LIMIT)...");
        motorStop = false;
        isMotorUp = false;
        ledcWrite(CH_MOTOR1, 0);
        ledcWrite(CH_MOTOR2, 255);
    } else {
        if (nearMin) {
            ESP_LOGW(MAIN_TAG, "Skip Motor down!");
        } else {
            ESP_LOGI(MAIN_TAG, "Motor down...");
            motorStop = false;
            isMotorUp = false;
            ledcWrite(CH_MOTOR1, 0);
            ledcWrite(CH_MOTOR2, 255);
        }
    }
}

void motorMoveStop() {
    ESP_LOGI(MAIN_TAG, "Motor stop");
    motorStop = true;
    ledcWrite(CH_MOTOR1, 0);
    ledcWrite(CH_MOTOR2, 0);
}

void IRAM_ATTR WhenMin() {
    ESP_LOGW(MAIN_TAG, "Min!");
    motorMoveStop();
    nearMin = true;
}

void IRAM_ATTR WhenMax() {
    ESP_LOGW(MAIN_TAG, "Max!");
    motorMoveStop();
    nearMax = true;
}

void setup() {
    ESP_LOGI(MAIN_TAG, "Setup!");
    attachInterrupt(PIN_HALL_SENSOR_MAX, WhenMax, FALLING);
    attachInterrupt(PIN_HALL_SENSOR_MIN, WhenMin, FALLING);

    ledcSetup(CH_MOTOR1, 1000, 8);
    ledcAttachPin(PIN_MOTOR1, CH_MOTOR1);
    ledcSetup(CH_MOTOR2, 1000, 8);
    ledcAttachPin(PIN_MOTOR2, CH_MOTOR2);
}

void loop() {
    auto isUp = touchRead(PIN_TOUCH_UP) < 32;
    auto isDown = touchRead(PIN_TOUCH_DOWN) < 32;
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
    delay(100);
}