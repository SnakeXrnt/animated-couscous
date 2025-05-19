#include "pico/stdlib.h"
#include "Library/ultrasonic/ultrasonic.hpp"
#include "Library/motor/motor.hpp"
#include "Library/servo/servo.hpp"

// Pin assignments (update as needed)
#define TRIG_PIN 2
#define ECHO_PIN 3

// Thresholds (in cm)
#define WALL_DIST 20.0
#define BALANCE_TOLERANCE 2.0
#define BALANCE_ADJUST_SPEED 50
//#define BALANCE_ADJUST_TIME 60 // ms
void balance(Motor& motor) {
    printf("[BALANCE] Checking balance...\n");

    DistanceSensor right_sen(10, 11);
    DistanceSensor left_sen(12, 13);

    while (true) {
        double right = right_sen.right_sensor_distance(right_sen); //a verry stupid implementation. if im calling the function with the object i might as well use this, Ill change this asap
        sleep_ms(100);
        double left = left_sen.left_sensor_distance(left_sen);
        sleep_ms(100);
        double diff = left - right;
        printf("[BALANCE] Left: %.2f cm, Right: %.2f cm, Diff: %.2f cm\n", left, right, diff);

        if (diff > BALANCE_TOLERANCE) {
            printf("[BALANCE] Too close to left wall, steering right.\n");
            motor.set(StareRight, BALANCE_ADJUST_SPEED);
        } else if (diff < -BALANCE_TOLERANCE) {
            printf("[BALANCE] Too close to right wall, steering left.\n");
            motor.set(StareLeft, BALANCE_ADJUST_SPEED);
        } else {
            printf("[BALANCE] Centered, going straight.\n");
            motor.set(Forward, BALANCE_ADJUST_SPEED);
            break; // Exit loop when balanced
        }
        sleep_ms(100); // Small delay to avoid busy loop
    }
}

int main() {
    stdio_init_all();
    printf("[INIT] Starting up...\n");

    // Initialize sensors and motors
    DistanceSensor frontSensor(TRIG_PIN, ECHO_PIN);
    Motor motor;
    Servo servo(14);

    sleep_ms(1000); // Wait for sensors and servo to settle
    servo.lookForward();
    printf("[INIT] Initialization complete.\n");

    while (true) {
        // Always look forward before measuring front
        servo.lookForward();
        sleep_ms(200);
        double front = frontSensor.measure_distance();
        printf("[MAIN] Front distance: %.2f cm\n", front);

        while (front > 20)
        {
            motor.set(Forward, 60);
            sleep_ms(10);
            front =frontSensor.measure_distance();
            printf("Front distance: %.2f cm\n", front);
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
            motor.set(Clockwise, 100);
            sleep_ms(350); // Adjust for 90 degree turn
            //motor.set(Forward, 60);
            //sleep_ms(400); // Move forward a bit
        } else if (front > WALL_DIST) {
            printf("[MAIN] Front is open (%.2f cm). Moving forward with balance.\n", front);
            balance(motor);
            sleep_ms(400);
        } else if (left > WALL_DIST) {
            printf("[MAIN] Left is open (%.2f cm). Turning left.\n", left);
            motor.set(CounterClockwise, 100);
            sleep_ms(350); // Adjust for 90 degree turn
            //motor.set(Forward, 60);
            //sleep_ms(400);
        } else {
            printf("[MAIN] Dead end. Turning around.\n");
            motor.set(Clockwise, 100);
            sleep_ms(700); // 180 degree turn
        }
    }
    return 0;
}