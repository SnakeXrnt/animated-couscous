#include "motor.hpp"

Motor::Motor()
{
    Motor_Init();
}

void Motor::set(const uint Dir, uint8_t Speed)
{
    switch (Dir) {
        case Forward:
          Motor_Run(MOTORA, FORWARD, Speed);
          Motor_Run(MOTORB, FORWARD, Speed);
          Motor_Run(MOTORC, FORWARD, Speed);
          Motor_Run(MOTORD, FORWARD, Speed);
          break;
        case Backward:
          Motor_Run(MOTORA, BACKWARD, Speed);
          Motor_Run(MOTORB, BACKWARD, Speed);
          Motor_Run(MOTORC, BACKWARD, Speed);
          Motor_Run(MOTORD, BACKWARD, Speed);
          break;
        case Stop:
          Motor_Stop(MOTORA);
          Motor_Stop(MOTORB);
          Motor_Stop(MOTORC);
          Motor_Stop(MOTORD);
          break;
        case StareRight:
          Motor_Run(MOTORA, FORWARD, Speed);
          Motor_Run(MOTORB, FORWARD, Speed);
          Motor_Run(MOTORC, BACKWARD, Speed);
          Motor_Run(MOTORD, BACKWARD, Speed);
          break;
        case StareLeft:
          Motor_Run(MOTORA, BACKWARD, Speed);
          Motor_Run(MOTORB, BACKWARD, Speed);
          Motor_Run(MOTORC, FORWARD, Speed);
          Motor_Run(MOTORD, FORWARD, Speed);
          break;
        case Clockwise:
          Motor_Run(MOTORA, FORWARD, Speed);
          Motor_Run(MOTORB, BACKWARD, Speed);
          Motor_Run(MOTORC, FORWARD, Speed);
          Motor_Run(MOTORD, BACKWARD, Speed);
          break;
        case CounterClockwise:
          Motor_Run(MOTORA, BACKWARD, Speed);
          Motor_Run(MOTORB, FORWARD, Speed);
          Motor_Run(MOTORC, BACKWARD, Speed);
          Motor_Run(MOTORD, FORWARD, Speed);
          break;
        }
}