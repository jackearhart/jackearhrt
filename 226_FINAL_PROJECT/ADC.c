/*  Author: Jack Earhart
 *  Start Date:07/05/2020
 *  End Date: 07/29/2020
 *  File: ADC.c
 *  Description: This file sets up the ADC on the MSP432 by configuring the pins used, and configures the
 *               the peripherals used by the ADC.
 */
#include "msp.h"
#include "ADC.h"
//FUNCTION THAT INTIALIZES THE PINS USED FOR THE ADC CONVERSIONS
void ADC14_pinInit(void){
    P5->SEL1 |= BIT5;       //clear SEL1 register for P5.5
    P5->SEL0 |= BIT5;       //clear SEL0 register for P5.5
    P5->DIR &=~ BIT5;       //set P5.5 as an input by clearing the DIR register

    //P2.4 is the pin that outputs the ADC conversion to the LCD
    P2->SEL0|=BIT4;         //set P2.4 as a GPIO pin, set the SEL0 register
    P2->SEL1 &=~BIT4;       //clear the SEL1 register
    P2->DIR |=BIT4;         //set P2.4 as an output
    P2->OUT |= BIT4;        //drive P2.4 HIGH
}
//FUNCTION THAT CONFIGURES THE PERIPHALS USED BY THE ADC
void ADC14_preiphInit(void){
    ADC14->CTL0 &=~ ADC14_CTL0_ENC;         //disable ADC conversions initially
    ADC14->CTL0    |= ADC14_CTL0_PDIV__64|  //pre-divide the ADC clock by 64
                      ADC14_CTL0_SHP|       //signal is sourced from the sampling timer
                      ADC14_CTL0_SHT1__192| //sample and hold time of 192 for memory locations 8-23
                      ADC14_CTL0_SHT0__192| //sample and hold time of 192 for memory locations 24-31
                      ADC14_CTL0_ON;        //turn the ACD14 on when a valid conversion is made

    ADC14->CTL1    |= ADC14_CTL1_RES__14BIT; //turn on 14 bit conversion for the ADC
    ADC14->MCTL[0]  = 0;                     //store ADC conversion results in memory location 0
    ADC14->IER0    |= ADC14_IER0_IE0;        //enable interrupts
    ADC14->CTL0    |= ADC14_CTL0_ENC;        //turn the ADC on for use
}




