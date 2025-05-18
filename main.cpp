#include "pico/stdlib.h"
#include "Library/ultrasonic/ultrasonic.hpp"
#include "Library/motor/motor.hpp"
#include "Library/servo/servo.hpp"

// Pin assignments (update as needed)
#define TRIG_PIN 2
#define ECHO_PIN 3

// Thresholds (in cm)
#define WALL_DIST 20.0
#define BALANCE_TOLERANCE 1.0
#define BALANCE_ADJUST_SPEED 50
#define BALANCE_ADJUST_TIME 60 // ms

void balance(DistanceSensor& frontSensor, Servo& servo, Motor& motor) {
    printf("[BALANCE] Checking balance...\n");

    // Look left and measure
    servo.lookLeft();
    sleep_ms(200); // Wait for servo to settle
    double left = frontSensor.measure_distance();
    printf("[BALANCE] Left distance: %.2f cm\n", left);

    // Look right and measure
    servo.lookRight();
    sleep_ms(200);
    double right = frontSensor.measure_distance();
    printf("[BALANCE] Right distance: %.2f cm\n", right);

    // Return to forward
    servo.lookForward();
    sleep_ms(200);

    double diff = left - right;
    printf("[BALANCE] Difference (left - right): %.2f cm\n", diff);

    if (diff > BALANCE_TOLERANCE) {
        printf("[BALANCE] Too close to left wall, steering right.\n");
        motor.set(StareRight, BALANCE_ADJUST_SPEED);
        sleep_ms(BALANCE_ADJUST_TIME);
        motor.set(Forward, BALANCE_ADJUST_SPEED);
    } else if (diff < -BALANCE_TOLERANCE) {
        printf("[BALANCE] Too close to right wall, steering left.\n");
        motor.set(StareLeft, BALANCE_ADJUST_SPEED);
        sleep_ms(BALANCE_ADJUST_TIME);
        motor.set(Forward, BALANCE_ADJUST_SPEED);
    } else {
        printf("[BALANCE] Centered, going straight.\n");
        motor.set(Forward, BALANCE_ADJUST_SPEED);
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
            motor.set(Forward, 60);
            sleep_ms(400); // Move forward a bit
        } else if (front > WALL_DIST) {
            printf("[MAIN] Front is open (%.2f cm). Moving forward with balance.\n", front);
            balance(frontSensor, servo, motor);
            sleep_ms(400);
        } else if (left > WALL_DIST) {
            printf("[MAIN] Left is open (%.2f cm). Turning left.\n", left);
            motor.set(CounterClockwise, 100);
            sleep_ms(350); // Adjust for 90 degree turn
            motor.set(Forward, 60);
            sleep_ms(400);
        } else {
            printf("[MAIN] Dead end. Turning around.\n");
            motor.set(Clockwise, 100);
            sleep_ms(700); // 180 degree turn
        }
        printf("[MAIN] Stopping motors.\n");
        motor.set(Stop, 0);
        sleep_ms(100);
    }
    return 0;
}