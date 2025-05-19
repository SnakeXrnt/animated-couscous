#ifndef SENSOR_H
#define SENSOR_H
#include "pico/stdlib.h"
#include <stdint.h>

class DistanceSensor
{
private:
    int Trigger; //or maybe use ushort
    int Echo;
public:
    DistanceSensor( int TriggerPin , int EchoPin );
/**
 * Measure the distance between wall and the sensor
 *
 * Example:
 * double distance = MainSensor.measure()
 */
    float measure_distance() const;
    float right_sensor_distance( DistanceSensor Right_Sensor);
    float left_sensor_distance( DistanceSensor Left_Sensor);

};

#endif
