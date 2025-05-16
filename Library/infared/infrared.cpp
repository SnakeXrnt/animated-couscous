#include "infrared.hpp"

InfraredSensor::InfraredSensor

void InfraredSensor::init() {
    gpio_init(pin_);
    gpio_set_dir(pin_, GPIO_IN);
}

bool InfraredSensor::detected() {
    if (gpio_get(pin_) == 0)
    {
      return false;
    }
    else
    {
      return true;
    }
}

InfaredSensor::InfaredSensor(uint gpio_pin) : pin_(gpio_pin) {}
{
}
