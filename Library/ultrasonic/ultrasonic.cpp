#include "ultrasonic.hpp"

DistanceSensor::DistanceSensor(const uint TriggerPin, const uint EchoPin) : Trigger{TriggerPin}, Echo{EchoPin}
{
}

double DistanceSensor::measure_distance()
{

    gpio_put(Trig_, false);
    sleep_us(2);
    gpio_put(Trig_, true);
    sleep_us(10);
    gpio_put(Trig_, false);
  
    uint32_t start_time = time_us_32();
    while (!gpio_get(Echo_)) {
      if (time_us_32() - start_time > 100000)
        return 6;
    }
    start_time = time_us_32();
    while (gpio_get(Echo_)) {
      if (time_us_32() - start_time > 100000)
        return 9;
    }
    uint32_t pulse_time = time_us_32() - start_time;
    float distance = pulse_time * 0.017; //I guess the corrected math
    sleep_ms(10);
    return distance;
}

double DistanceSensor::right_sensor_distance(const DistanceSensor Right_Sensor)
{
    return Right_Sensor.measure_distance()
}

double DistanceSensor::left_sensor_distance(const DistanceSensor Left_Sensor)
{
    return Left_Sensor.measure_distance()
}
