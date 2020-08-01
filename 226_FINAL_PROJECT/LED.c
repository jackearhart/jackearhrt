/*  Author: Jack Earhart
 *  Start Date:07/05/2020
 *  End Date: 07/29/2020
 *  File: LED.c
 *  Description: This file initializes the RGB LED pins and Timer_A modules associated with them.
 *               In addition, it also has functions to drive a PWM signal to a specific LED to control
 *               the brightness of the LED.
 */
#include "LED.h"
#include "msp.h"
#include "LCD.h"
#include "keypad.h"
#include "SysTick.h"
#include "menus.h"
#include "servo.h"
#include "ADC.h"
//description: FUNCTION USED TO INTIALIZE ALL PINS USED ON THE RGB LED, AS WELL AS THE BUTTON USED TO INTERRUPT THE RGB LED
//Input: void
//Output: void
void RBG_LED_init(){
       //INITIALIZATION FOR P2.6 (TIMER_A PIN FUNCTIONALITY) P2.6= TA0.3
       //sel1=0, and sel0=0 allows for PWM functionality
       //red LED
        P7->SEL1 &=~ 0;           //clear SEL1 register
        P7->SEL0 |= (BIT5);      //set BIT6 of SEL0
        P7->DIR = (BIT5);       //configure P2.6 as output (DIR=1)
        P7->OUT &=~ BIT5;            //drive P2.6 LOW initially (OUT=0), after being declared as an output

       //green LED
       P5->SEL1 &=~ 0;           //clear SEL1 register
       P5->SEL0 |= (BIT7);      //set BIT6 of SEL0
       P5->DIR |= (BIT7);       //configure P2.6 as output (DIR=1)
       P5->OUT &=~ BIT7;            //drive P2.6 LOW initially (OUT=0), after being declared as an output
      //blue LED
       P2->SEL1 &=~ 0;           //clear SEL1 register
       P2->SEL0 |= (BIT6);      //set BIT6 of SEL0
       P2->DIR |= (BIT6);       //configure P2.6 as output (DIR=1)
       P2->OUT &=~ BIT6;            //drive P2.6 LOW initially (OUT=0), after being declared as an output

       //SWITCH TO STOP LED
          P1->SEL1 &=~BIT6; //setting switch 1 as simple GPIO pin
          P1->SEL0 &=~BIT6; //setting switch 1 as simple GPIO pin
          P1->DIR  &=~BIT6; //setting P2.6 as input
          P1->REN  |= BIT6; //resistor enabled button
          P1->OUT  |= BIT6; //pull-up resistor enabled
          //interrupt setup for P1.7
          P1->IES  |= BIT6; //set pin interrupt to trigger it goes from high to low
          P1->IE   |= BIT6; //enable interrupt on P1.7
          P1->IFG   = 0; //clear all interrupt flags on port 1


}
//description: FUNCTION THAT CONTROLS THE BRIGHTNESS OF THE BLUE LED, GIVEN AN INPUT FOR THE DUTY CYCLE TO BE INPUTTED INTO THE CCR[3] REGISTER
//Input: void
//Output: void
void blue_LED(float DC){

         TIMER_A0->CCR[0] = 3000;                       //count up to the value of 3,000 in the TIMER_A0 CCR register
         TIMER_A0->CCTL[3] = TIMER_A_CCTLN_OUTMOD_7; //P2.6 is associated with TA0.3, channel 3 corresponds with P2.6 (set the output mode in CCTL[0] register, 7 for reset/set)

         TIMER_A0->CTL = TIMER_A_CTL_SSEL__SMCLK| //using the sub-master clock (SMCLK) selecting it in the CTL register (TASSEL for the clock source select)
                 TIMER_A_CTL_MC__UP|             //mode control is going to be UP selecting it in the CTL register (mode control for the counting direction)
                 TIMER_A_CTL_CLR;                //clear the the timer in the CTL register, TACLR to clear it

                 TIMER_A0->CCR[3] = (3*DC); //continuously updating the CCR[3] with a value of DC(0-10) * P

}

//description: FUNCTION THAT CONTROLS THE BRIGHTNESS OF THE GREEN LED, GIVEN AN INPUT FOR THE DUTY CYCLE TO BE INPUTTED INTO THE CCR[2] REGISTER
//Input: void
//Output: void
void green_LED(float DC){

    TIMER_A2->CCR[1] = 3000;                       //count up to the value 3,000 in the TIMER_A2 CCR register
    TIMER_A2->CCTL[2] = TIMER_A_CCTLN_OUTMOD_7; // P5.7 is associated with the TA2.2, channel 2 corresponds with P5.7 (set output mode in CCTL[2] register, 7 for reset/set)

    TIMER_A2->CTL = TIMER_A_CTL_SSEL__SMCLK|    //using the sub-master clock (SMCLK) selecting it in the CTL register (TASSEL for the clock source select)
            TIMER_A_CTL_MC__UP|                //mode control is going to be UP selecting it in the CTL register (mode control for the counting direction)
            TIMER_A_CTL_CLR;                    //clear the timer in the CTL register, TACLR to clear it

             TIMER_A2->CCR[2] = (30*DC);//continuously updating the CCR[2] with a value of DC1(0-1) * P

}
//description: FUNCTION THAT CONTROLS THE BRIGHTNESS OF THE RED LED, GIVEN AN INPUT FOR THE DUTY CYCLE TO BE INPUTTED INTO THE CCR[3] REGISTER
//Input: void
//Output: void
void red_LED(float DC){

             TIMER_A1->CCR[0] = 3000;                       //count up to the value of 3,000 in the TIMER_A1 CCR register
             TIMER_A1->CCTL[3] = TIMER_A_CCTLN_OUTMOD_7; //P2.6 is associated with TA1.3, channel 3 corresponds with P7.5 (set the output mode in CCTL[0] register, 7 for reset/set)

             TIMER_A1->CTL = TIMER_A_CTL_SSEL__SMCLK| //using the sub-master clock (SMCLK) selecting it in the CTL register (TASSEL for the clock source select)
                     TIMER_A_CTL_MC__UP|             //mode control is going to be UP selecting it in the CTL register (mode control for the counting direction)
                     TIMER_A_CTL_CLR;                //clear the the timer in the CTL register, TACLR to clear it

                     TIMER_A1->CCR[3] = (30*DC); //continuously updating the CCR[3] with a value of DC(0-10) * P


}
