#include "ultrasonic.hpp"
#include <cstdio>

DistanceSensor::DistanceSensor(int TriggerPin, int EchoPin) : Trigger{TriggerPin}, Echo{EchoPin}
{
}
float DistanceSensor::measure_distance() 
{
    gpio_init(Echo);
    gpio_set_dir(Echo, GPIO_IN);
    gpio_init(Trigger);
    gpio_set_dir(Trigger, GPIO_OUT);
printf("Triggering sensor...\n");
gpio_put(Trigger, 0);
sleep_us(2);
gpio_put(Trigger, 1);
sleep_us(10);
gpio_put(Trigger, 0);
printf("Waiting for echo...\n");

    uint32_t start_time = time_us_32();
    while (!gpio_get(Echo)) {
        if (time_us_32() - start_time > 100000)
            return 6;
    }
    start_time = time_us_32();
    while (gpio_get(Echo)) {
        if (time_us_32() - start_time > 100000)
            return 9;
    }
    uint32_t pulse_time = time_us_32() - start_time;
    float distance = pulse_time * 0.017;
    sleep_ms(10);
    return distance;
}

float DistanceSensor::right_sensor_distance( DistanceSensor Right_Sensor) 
{
    return Right_Sensor.measure_distance();
}

float DistanceSensor::left_sensor_distance( DistanceSensor Left_Sensor) 
{
    return Left_Sensor.measure_distance();
}
