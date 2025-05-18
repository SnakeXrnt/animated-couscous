#include "MotorDriver/Devices/MotorDriver.h"

const uint Stop = 0;
const uint Forward = 1;
const uint Backward = 2;
const uint StareRight = 3;
const uint StareLeft = 4;
const uint Clockwise = 5;
const uint CounterClockwise = 6;

class Motor
{
private:
    /* data */
public:
    Motor();
    void set(const uint Dir, uint8_t Speed);
};

