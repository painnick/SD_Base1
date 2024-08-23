//
// Created by painnick on 2024-08-24.
//

#ifndef SD_BASE1_TOWER_CONTROLLER_H
#define SD_BASE1_TOWER_CONTROLLER_H

#include <Arduino.h>

class TowerController {
public:
    bool motorStop = false;
    bool isMotorUp = false;

    bool nearMax = false;
    bool nearMin = false;

    uint8_t Motor1PIN = 0;
    uint8_t Motor2PIN = 0;
    uint8_t Motor1Ch = 0;
    uint8_t Motor2Ch = 0;

    TowerController(uint8_t pin1, uint8_t pin2, uint8_t ch1, uint8_t ch2);
    void setup();
    void loop(bool isUp, bool isDown);

    void motorMoveUp(bool noLimit = false);
    void motorMoveDown(bool noLimit = false);
    void motorMoveStop();

    void onMax();
    void onMin();
};

#endif //SD_BASE1_TOWER_CONTROLLER_H
