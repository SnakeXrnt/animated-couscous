#include "pico/stdlib.h"
#include "Library/ultrasonic/ultrasonic.hpp"
#include "Library/motor/motor.hpp"
#include "Library/servo/servo.hpp"


int main() {

    stdio_init_all();

    const uint gpio_pin = 19;

    Servo Frontservo(gpio_pin);
    printf("initialzing servo in %d \n", gpio_pin);

    while (1){
        printf("looking left \n");
        Frontservo.lookLeft();
        printf("looking left done \n");
        sleep_ms(500);
        
        printf("looking forward \n");
        Frontservo.lookForward();
        printf("looking forward done \n");
        sleep_ms(500);

        printf("looking right \n");
        Frontservo.lookRight();
        printf("looking right done \n");
        sleep_ms(500);
    }
    
}