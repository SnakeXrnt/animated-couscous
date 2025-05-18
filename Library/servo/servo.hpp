#include "pico_servo.h"

class Servo
{
private:
    const uint Servo_PIN;
public:
    Servo(const uint pin);
    void set_angle(int angle);
    void lookRight();
    void lookLeft();
    void lookForward();

};

