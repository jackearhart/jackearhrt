/*  Author: Jack Earhart
 *  Start Date:07/05/2020
 *  End Date: 07/29/2020
 *  File: SysTick.c
 *  Description: This value includes two SysTick delay functions, one to delay milliseconds given a 1-9 numeric input,
 *               and another to delay microseconds given a 1-9 input, either function can be used to delay the program
 *               a maximum of 5.192 seconds with the proper input; however I found it easiest to just have two separate
 *               functions that could delay the program either microseconds or milliseconds.
 */
#include "msp.h"
#include "Systick.h"
#include"motor.h"
//SysTick delay function that takes in a number input to make delays
void delayMs(uint32_t n){
    SysTick-> CTRL = 0;             //set CTRL register  to zero
       SysTick-> LOAD = 0xFFFFFF;   //load max value for a 24 bit counter
       SysTick-> VAL =  0;          //any value written to this clears it
       SysTick-> CTRL = (BIT2|BIT0);//enable the timer
    SysTick->LOAD=(3000*n)-1;       //3MHz * 1 millisecond = 3,000
    SysTick->VAL=0;                 //clear SysTick timer value by writing a zero to it
    SysTick->CTRL=(BIT2|BIT0);      //enable timer and interrupts
while((SysTick->CTRL & 0x10000)==0) //busy while loop
           {}
    SysTick->CTRL = 0;              //reset CTRL register once flag has been set
}
//SysTick delay function that takes in a number input to make delays (an input of 1 makes a microsecond delay)
void delayUs(uint32_t n){
    SysTick-> CTRL = 0;             //set CTRL register  to zero
       SysTick-> LOAD = 0xFFFFFF;   //load max value for a 24 bit counter
       SysTick-> VAL =  0;          //any value written to this clears it
       SysTick-> CTRL = (BIT2|BIT0);//enable the timer
    SysTick->LOAD=(3*n)-1;          //3MHz * 1 microsecond = 3
    SysTick->VAL=0;                 //clear SysTick timer value by writing a zero to it
    SysTick->CTRL=(BIT2|BIT0);      //enable timer and interrupts
while((SysTick->CTRL & 0x10000)==0) //busy while loop
           {}
    SysTick->CTRL = 0;              //reset CTRL register once flag has been set
}
//SysTick delay function that delays milliseconds but has interrupts enabled
void SysTickInit_WithInterrupts(uint32_t delay_ms){
    SysTick->CTRL  &= ~BIT0;                                             //clears enable to stop the counter
    SysTick->LOAD   = delay_ms * 3000;                                   //sets the period
    SysTick->VAL    = 0;                                                 //clears the value
    SysTick->CTRL   = 0x07;        //enable SysTick with core clock, interrupts on -> this is the ENABLE, TICKINT, and CLKSOURSE bits: Systic->CTRL |= 0x07;
    return;
}

