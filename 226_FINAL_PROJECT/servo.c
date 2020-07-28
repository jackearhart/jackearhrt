/*  Author: Jack Earhart
 *  Start Date:07/05/2020
 *  End Date: 07/29/2020
 *  File: servo.c
 *  Description: This file configures the servo and the ON-board LEDs associated with the servo being "opened" or "closed".
 */
#include"msp.h"
#include "servo.h"
#include "SysTick.h"
#include "menus.h"
#include "buzzer.h"
//function that initializes the servo and the on-board LED, the green and red colors of LED 2
    void intial_servo(){
        //initialize the GREEN color of LED 2
        P2->SEL1 &=~ BIT1;
        P2->SEL0 &=~ BIT1;
        P2->DIR  |=  BIT1;            //set the direction of the green LED as an output
        P2->OUT  &=~ BIT1;            //drive the green output low initially
        //initialize the RED color of LED 2
        P2->SEL1 &=~ BIT0;
        P2->SEL0 &=~ BIT0;
        P2->DIR  |=  BIT0;            //set the direction of the red LED as an output
        P2->OUT  |=  BIT0;            //drive the red color of LED 2 high initially
        //initialize the pin being used for the servo
        P10->SEL0 |= BIT5;            //set BIT5 of SEL0 register for port 5
        P10->SEL1 &=~ BIT5;           //clear SEL1 register
        P10->DIR |= BIT5;             //configure P10.5 as output (DIR=1)
        P10->OUT |=BIT5;              //drive the motor high
        close_servo();                //close the servo initially
    }

void open_servo(){
        P10->OUT |=BIT5;             //drive the output high
        P2->OUT  &=~  BIT0;                              //turn off the red LED
        P2->OUT  |=  BIT1;                               //turn on the green LED
        float P=300;                 //variable for the CCR[1] register to count to
        float period=20000;          //variable for the period to be used by the CCR[0] register

        TIMER_A3->CCTL[1] = TIMER_A_CCTLN_OUTMOD_7;      //P10.5 is associated with TA3.1, channel 1 corresponds with P10.5 (set the output mode in CCTL[0] register, 7 for reset/set)
        TIMER_A3->CCR[0] = period;                       //count up to the value of 3,000 in the TIMER_A0 CCR register
        TIMER_A3->CTL = TIMER_A_CTL_SSEL__SMCLK|         //using the sub-master clock (SMCLK) selecting it in the CTL register (TASSEL for the clock source select)
                         TIMER_A_CTL_MC__UP|             //mode control is going to be UP selecting it in the CTL register (mode control for the counting direction)
                         TIMER_A_CTL_ID__8|              //divide the clock by 8 to run it slower
                         TIMER_A_CTL_ID__2|              //divide by 2 as well
                         TIMER_A_CTL_CLR;                //clear the the timer in the CTL register, TACLR to clear it
                         TIMER_A3->CCR[1] = P;           //continuously updating the CCR[3] with a value of DC(0-10) * P
                         P10->OUT &=~BIT5;               //turn off the motor
    }
    void close_servo(){
        P2->OUT  |=  BIT0;           //turn on the red LED
        P2->OUT  &=~  BIT1;          //turn off the green LED if on

        P10->OUT |=BIT5;                                 //drive the output HIGH
        float P=680;                                     //variable for the CCR[1] register to count to
        float period=20000;                              //variable for the period to be used by the CCR[0] register

             TIMER_A3->CCTL[1] = TIMER_A_CCTLN_OUTMOD_7; //P2.6 is associated with TA0.3, channel 3 corresponds with P2.6 (set the output mode in CCTL[0] register, 7 for reset/set)
             TIMER_A3->CCR[0] = period;                  //count up to the value of 3,000 in the TIMER_A0 CCR register
             TIMER_A3->CTL = TIMER_A_CTL_SSEL__SMCLK|    //using the sub-master clock (SMCLK) selecting it in the CTL register (TASSEL for the clock source select)
                     TIMER_A_CTL_MC__UP|                 //mode control is going to be UP selecting it in the CTL register (mode control for the counting direction)
                     TIMER_A_CTL_ID__8|                  //divide the clock by 8 to run it slower
                     TIMER_A_CTL_ID__2|                  //divide by 2 as well
                     TIMER_A_CTL_CLR;                    //clear the the timer in the CTL register, TACLR to clear it

                     TIMER_A3->CCR[1] = P; //continuously updating the CCR[3] with a value of DC(0-10) * P
                     P10->OUT &=~BIT5;     //turn off the motor

    }
