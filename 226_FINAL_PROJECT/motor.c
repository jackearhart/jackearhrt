/*  Author: Jack Earhart
 *  Start Date:07/05/2020
 *  End Date: 07/29/2020
 *  File: motor.c
 *  Description: This file configures the motor in its entirety, the motor is initialized in the motor_init function
 *               and the motor_PWM function constantly updates the motor's speed.
 */
#include "msp.h"
#include "motor.h"
#include "LED.h"
#include "keypad.h"
//FUNCTION THAT INITIALIZES THE MOTOR AND ITS INTERRUPT SWITCH
void motor_init(){
       P5->SEL0 |= BIT6;        //set BIT6 of SEL0 register for port 5
       P5->SEL1 &=~ BIT6;       //clear SEL1 register
       P5->DIR |= BIT6;         //configure P5.6 as output (DIR=1)
    //SWITCH TO STOP MOTOR
       P1->SEL1 &=~BIT7;        //setting interrupt switch
       P1->SEL0 &=~BIT7;        //setting interrupt switch
       P1->DIR  &=~BIT7;        //setting P1.7 as input
       P1->REN  |= BIT7;        //resistor enabled button
       P1->OUT  |= BIT7;        //pull-up resistor enabled
       //interrupt setup for P1.7
       P1->IES  |= BIT7;        //set pin interrupt to trigger it goes from high to low
       P1->IE   |= BIT7;        //enable interrupt on P1.7

       P1->IFG   = 0;           //clear all interrupt flags on port 1

       TIMER_A2->CCR[0] = 60000-1;                          //count up to the value of 60,000 in the TIMER_A2 CCR register
       TIMER_A2->CCTL[1] = TIMER_A_CCTLN_OUTMOD_7;          //P2.6 is associated with TA2.1, channel 1 corresponds with P5.6 (set the output mode in CCTL[0] register, 7 for reset/set)
       TIMER_A2->CTL = TIMER_A_CTL_SSEL__SMCLK|             //using the sub-master clock (SMCLK) selecting it in the CTL register (TASSEL for the clock source select)
                       TIMER_A_CTL_MC__UP|                  //mode control is going to be UP selecting it in the CTL register (mode control for the counting direction)
                       TIMER_A_CTL_CLR;                     //clear the the timer in the CTL register, TACLR to clear it

}
//FUNCTION THAT SPINS THE DC MOTOR CONSTATNLY BY UPDATING THE CCR REGISTER WITH THE KEYPAD VALUE ENTERED IN THE MOTOR MENU OPTION
void motor_PWM(uint8_t DC){
    TIMER_A2->CCR[1] = 72000*DC;                            //update the CCR[1] register with the value inputed into the function
}




