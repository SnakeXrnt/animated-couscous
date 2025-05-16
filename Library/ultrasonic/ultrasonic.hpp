#ifndef SENSOR_H
#define SENSOR_H
#include "pico/stdlib.h"
#include <stdint.h>

class DistanceSensor
{
private:
    const ushort Trigger; //or maybe use ushort
    const ushort Echo;
public:
    DistanceSensor( const uint TriggerPin , const uint EchoPin );
/**
 * Measure the distance between wall and the sensor
 *
 * Example:
 * double distance = MainSensor.measure()
 */
    double measure_distance(); const
    double right_sensor_distance(const DistanceSensor Right_Sensor);
    double left_sensor_distance(const DistanceSensor Left_Sensor);

};

#endif
