#ifndef INFARED_HPP
#define INFARED_HPP

#include "pico/stdlib.h"
#include <stdint.h>

class InfaredSensor
{
private:
    const uint pin_;
public:
    InfaredSensor(uint gpio_pin);
    void init();
    bool detected();
};

#endif