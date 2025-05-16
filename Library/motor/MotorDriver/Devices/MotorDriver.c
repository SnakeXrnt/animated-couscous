/*****************************************************************************
* | File        :   MotorDriver.c
* | Author      :   Waveshare team
* | Function    :   Drive TB6612FNG
* | Info        :
*                TB6612FNG is a driver IC for DC motor with output transistor in
*                LD MOS structure with low ON-resistor. Two input signals, IN1
*                and IN2, can choose one of four modes such as CW, CCW, short
*                brake, and stop mode.
*----------------
* |	This version:   V1.0
* | Date        :   2018-09-04
* | Info        :   Basic version
*
******************************************************************************/
#include "MotorDriver.h"
#include "Debug.h"

int MotorPin[4][3]={ {0,1,2},{3,4,5},{6,7,8},{9,10,11} } ;//MA,MB,MC,MD
int MotorDir[2][2]={ {0,1},{1,0} } ;//forward, backward

/**
 * Motor rotation.
 *
 * Example:
 * Motor_Init();
 */
void Motor_Init(void)
{
    PCA9685_Init(0x40);
    PCA9685_SetPWMFreq(100);
}

/**
 * Motor rotation.
 *
 * @param motor: Motor A and Motor B.
 * @param dir: forward and backward.
 * @param speed: Rotation speed.  //(0~100)
 *
 * Example:
 * @code
 * Motor_Run(MOTORA, FORWARD, 50);
 * Motor_Run(MOTORB, BACKWARD, 100);
 */
void Motor_Run(UBYTE motor, DIR dir, UWORD speed)
{
    if(speed > 100)
        speed = 100;

    PCA9685_SetPwmDutyCycle(MotorPin[motor][0], speed);
    PCA9685_SetLevel(MotorPin[motor][1], MotorDir[dir][0]);
    PCA9685_SetLevel(MotorPin[motor][2], MotorDir[dir][1]);
}

/**
 * Motor stop rotation.
 *
 * @param motor: Motor A and Motor B.
 *
 * Example:
 * @code
 * Motor_Stop(MOTORA);
 */
void Motor_Stop(UBYTE motor)
{
    PCA9685_SetPwmDutyCycle(MotorPin[motor][0], 0);
}

/**
 * Motor stop rotation.
 *
 * @param motor: Motor A and Motor B.
 *
 * Example:
 * @code
 * Motor_Stop(MOTORA);
 */
void Motor_test(void)
{
    //1.System Initialization
    if(DEV_Module_Init()!=0){
        return;
    }
    DEV_Delay_ms(3000);
    printf("MOTOR TEST");
    // int x = 0;
    // while(1){
        // x++;
        // printf("MOTOR TEST\r\n");
        // DEV_Delay_ms(1000);
        
         // 2.Motor Initialization
        // Motor_Init();
        // printf("Motor_Init\r\n");
        
        // printf("Motor_Run time = %d\r\n", x );
        // Motor_Run(MOTORA, FORWARD, 100);
        
    // }
    
    //2.Motor Initialization
    Motor_Init();
    printf("Motor_Init\r\n");
    
    printf("Motor_Run\r\n");
    Motor_Run(MOTORA, FORWARD, 100);
    Motor_Run(MOTORB, FORWARD, 100);
    Motor_Run(MOTORC, FORWARD, 100);
    Motor_Run(MOTORD, FORWARD, 100);
    // Motor_Run(MOTORB, BACKWARD, 100);
}
