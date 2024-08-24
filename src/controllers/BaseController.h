#ifndef SD_BASE1_BASE_CONTROLLER_H
#define SD_BASE1_BASE_CONTROLLER_H

#include <ServoEasing.h>

class BaseController {
public:
    BaseController(uint8_t tablePin,
                   uint8_t armPin,
                   uint8_t eyePin, uint8_t eyeCh,
                   uint8_t gunPin, uint8_t gunCh);

    void setup();

    void turnTable();

    void turnArm();

    void fireGun() const;
    void fireHeadVulkan() const; // First

    void loop();

protected:
    uint8_t _TablePin;
    uint8_t _ArmPin;
    uint8_t _EyePin;
    uint8_t _GunPin;
    uint8_t _EyeCh;
    uint8_t _GunCh;

    ServoEasing servoArm;
    ServoEasing servoTable;
};

#endif //SD_BASE1_BASE_CONTROLLER_H
