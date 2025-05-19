#include "pico/stdlib.h"
#include "Library/ultrasonic/ultrasonic.hpp"
#include "Library/motor/motor.hpp"
#include "Library/servo/servo.hpp"
#include <cmath>
// Pin assignments (update as needed)
#define TRIG_PIN 10
#define ECHO_PIN 11

// Thresholds (in cm)
#define WALL_DIST 15.0
#define BALANCE_TOLERANCE 5.0
#define BALANCE_ADJUST_SPEED 50
//#define BALANCE_ADJUST_TIME 60 // ms
//void balance(Motor& motor) {

    
    
//}

int main() {
    stdio_init_all();
    sleep_ms(1000);

    printf("[INIT] Starting up...\n");
    sleep_ms(1000);
    //Motor_test();



    // Initialize sensors and motors
    DistanceSensor frontSensor(TRIG_PIN, ECHO_PIN);
    Motor motor;
    Servo servo(17);


    DistanceSensor left_sen(8, 9);
    DistanceSensor right_sen(6, 7);

    sleep_ms(1000); // Wait for sensors and servo to settle
    servo.lookForward();
    printf("[INIT] Initialization complete.\n");

   // float distance_between_walls = right_sen.measure_distance() + left_sen.measure_distance();

    while (true) {
        // Always look forward before measuring front
        servo.lookForward();
        sleep_ms(200);
        float front = frontSensor.measure_distance();
        float left_distance = left_sen.measure_distance();
        float right_distance = right_sen.measure_distance();

        printf("[MAIN] Front distance: %.2f cm\n", front);

        while (front > 20)
        {
            motor.set(Forward, 40);
            sleep_ms(15);
            left_distance = left_sen.measure_distance();
            if (left_distance < 15)
            {
                printf("balance left \n");
                motor.set(StareLeft, 40);
                sleep_us(500);
            }
                if (right_distance < 15)
            {
                printf("balance left \n");
                motor.set(StareRight, 40);
                sleep_us(500);
            }
            
            front = frontSensor.measure_distance();
            printf("Front distance: %.2f cm\n", front);
            printf("left distance: %.2f cm\n", left_distance);

            

        }
        printf("[MAIN] Wall is too close, stopping motors.\n");
        motor.set(Stop, 0);
        sleep_ms(100);
        // Right hand rule:
        // 1. If right is open, turn right and move forward
        // 2. Else if front is open, move forward (with balance)
        // 3. Else if left is open, turn left
        // 4. Else, turn around (dead end)

        // Check right
        servo.lookRight();
        sleep_ms(200);
        double right = frontSensor.measure_distance();
        printf("[MAIN] Right distance: %.2f cm\n", right);

        // Check left
        servo.lookLeft();
        sleep_ms(200);
        double left = frontSensor.measure_distance();
        printf("[MAIN] Left distance: %.2f cm\n", left);

        // Return to forward
        servo.lookForward();
        sleep_ms(200);

        if (right > WALL_DIST) {
            printf("[MAIN] Right is open (%.2f cm). Turning right.\n", right);
            motor.set(Clockwise, 60);
            sleep_ms(285); // Adjust for 90 degree turn
            //motor.set(Forward, 60);
            //sleep_ms(400); // Move forward a bit
        } else if (front > WALL_DIST) {
            printf("[MAIN] Front is open (%.2f cm). Moving forward with balance.\n", front);
            //balance(motor);
            //sleep_ms(100);
        } else if (left > WALL_DIST) {
            printf("[MAIN] Left is open (%.2f cm). Turning left.\n", left);
            motor.set(CounterClockwise, 60);
            sleep_ms(285); // Adjust for 90 degree turn
            //motor.set(Forward, 60);
            //sleep_ms(400);
        } else {
            printf("[MAIN] Dead end. Turning around.\n");
            motor.set(Clockwise, 60);
            sleep_ms(570); // 180 degree turn
        }
    }
        
    return 0;
}