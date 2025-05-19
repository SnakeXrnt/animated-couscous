#include "ultrasonic.hpp"

DistanceSensor::DistanceSensor(const uint TriggerPin, const uint EchoPin) : Trigger{TriggerPin}, Echo{EchoPin}
{
}

double DistanceSensor::measure_distance() const
{

    gpio_init(Echo);
    gpio_set_dir(Echo, GPIO_IN);
    gpio_init(Trigger);
    gpio_set_dir(Trigger, GPIO_OUT);
    //printf("gpio initilized \n");
  
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
    float distance = pulse_time * 0.017; //I guess the corrected math
    sleep_ms(10);
    return distance;
}

double DistanceSensor::right_sensor_distance(const DistanceSensor Right_Sensor) const
{
    return Right_Sensor.measure_distance();
}

double DistanceSensor::left_sensor_distance(const DistanceSensor Left_Sensor) const
{
    return Left_Sensor.measure_distance();
}
