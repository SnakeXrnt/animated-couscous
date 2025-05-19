#include "servo.hpp"

Servo::Servo(const uint pin) : Servo_PIN{pin}
{
    servo_enable(Servo_PIN);
}

void Servo::set_angle(int angle)
{
    servo_set_position(Servo_PIN, angle);
}

void Servo::lookRight()
{
    this->set_angle(245); //or 170
}

void Servo::lookLeft()
{
    this->set_angle(0); //or 10
}

void Servo::lookForward()
{
    this->set_angle(145);
}
