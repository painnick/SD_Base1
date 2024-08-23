#ifndef SD_BASE1_BASE_CONTROLLER_H
#define SD_BASE1_BASE_CONTROLLER_H

#include <ServoEasing.h>

class BaseController {
public:
    BaseController(int table, int arm, int eye, int bazuka);
    void setup();
    void turnTable();
    void turnArm();
    void loop();

protected:
    int _TablePin;
    int _ArmPin;
    int _EyePin;
    int _GunPin;

    ServoEasing servoArm;
    ServoEasing servoTable;
};

#endif //SD_BASE1_BASE_CONTROLLER_H
