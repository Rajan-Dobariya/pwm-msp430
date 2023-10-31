/*
 * Simple-PWM.h
 *
 *  Created on: Apr 2, 2022
 *      Author: Jake
 */

#ifndef SIMPLE_PWM_H_
#define SIMPLE_PWM_H_


volatile unsigned int __absolute_trash__; // useful for assigning addresses to NULL, legitimate safety feature

// A structure to keep track of what pin is being modified when 
typedef struct PWM_PIN
{
    volatile unsigned int *TCCR_Period;
    volatile unsigned int *TCCR_PWM;
}PWM;

// Supports Period up to 1 second , and duty cycle from 0-100%
struct PWM_PIN Init_PWM(float Duty_Cycle, float period, char PIN[4]);

// Adjusts Duty Cycle
// Possible values of ms: ~0.1 - a high number
void Adjust_Period(float ms, struct PWM_PIN PIN);

// Adjusts Duty Cycle, from 0 to 100
void Adjust_DutyCycle(float DUTY, struct PWM_PIN tmp);

void Adjust_PWM(int DUTY, float period, struct PWM_PIN tmp);

PWM  __null_PWM_struct();

#endif /* SIMPLE_PWM_H_ */
