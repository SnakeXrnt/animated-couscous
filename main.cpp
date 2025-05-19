#include "pico/stdlib.h"
#include "Library/ultrasonic/ultrasonic.hpp"
#include "Library/motor/motor.hpp"
#include "Library/servo/servo.hpp"


int main() {

    stdio_init_all();

    int gpio_pin = 19;
sleep_ms(200);
    Servo Frontservo(gpio_pin);
    sleep_ms(200);
    servo_enable(19);

    printf("initialzing servo in %d \n", gpio_pin);


for (int i = 0; i < 181; i++)
{
    Frontservo.set_angle(i);
    printf("angle : %d \n", i);
    sleep_ms(100);

}


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