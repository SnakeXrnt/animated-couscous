#include "infrared.hpp"

InfaredSensor::InfaredSensor(uint gpio_pin) : pin_(gpio_pin) {}

void InfaredSensor::init() {
    gpio_init(pin_);
    gpio_set_dir(pin_, GPIO_IN);
}

bool InfaredSensor::detected() {
    return gpio_get(pin_) != 0;
}
