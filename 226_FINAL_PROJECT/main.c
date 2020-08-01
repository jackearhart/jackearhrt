/*  Author: Jack Earhart
 *  Start Date:07/05/2020
 *  End Date: 07/29/2020
 *  File: Main.c
 *  Description: this file calls the initialization functions for all equipment used, such as
 *               the RGB LED, the LCD screen, the ADC, the seven segment display, the speaker,
 *               the motor, the keypad, and the servo motor, the ADC handler is also modified
 *               at the bottom.
 */
//including all source files used in this project by including their respective .h files
#include "sevenseg.h"
#include "msp.h"
#include "LCD.h"
#include "keypad.h"
#include "SysTick.h"
#include "menus.h"
#include "servo.h"
#include "LED.h"
#include "ADC.h"
#include "motor.h"
#include "buzzer.h"
#include <stdio.h>
volatile float nADC;      //global variable used in the ADC handler
volatile uint16_t result; //global variable used in the ADC handler
int main(void){
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;    // stop watchdog timer
    NVIC->ISER[1] = 1 << ((PORT1_IRQn)& 31);       //enable port 1 interrupt on the NVIC
    //initialization Functions
    buzzer_init();                                 //initialize the speaker
    seg_init();                                    //initialize the seven segment display
    ADC14_pinInit();                               //initialize the ADC
    ADC14_preiphInit();                            //configure the ADC
    LCD_init();                                    //initialize the LCD
    RBG_LED_init();                                //initialize the RGB LED
    motor_init();                                  //initialize the motor
    keypad_init();                                 //initialize the keypad
    intial_servo();                                //initialize the servo

    NVIC->ISER[0] |= 1 << ((ADC14_IRQn) & 31);     //enable ADC interrupts
    __enable_irq();                                //enable global interrupt
    main_menu();                                   //begin program at the main menu
while(1){};
}

void ADC14_IRQHandler(void){
     ADC14->CTL0|= ADC14_CTL0_SC;                //start conversions on the ADC
     result = ADC14->MEM[0];                     //store the value of result to memory location 0, result being the value from the ADC potentiometer value
     nADC = (result * 3.3)/16384;                //convert the value of "result" into an actual voltage value reading and store it to "nADC"
     TIMER_A0->CCTL[1] = TIMER_A_CCTLN_OUTMOD_7; //P2.4 is associated with TA0.1, channel 1 corresponds with P2.4 (set the output mode in CCTL[0] register, 7 for reset/set)
     TIMER_A0->CCR[0] = 600;                     //count up to the value of 600 in the TIMER_A0 CCR register
     TIMER_A0->CTL = TIMER_A_CTL_SSEL__SMCLK|    //using the sub-master clock (SMCLK) selecting it in the CTL register (TASSEL for the clock source select)
                  TIMER_A_CTL_MC__UP|            //mode control is going to be UP selecting it in the CTL register (mode control for the counting direction)
                  TIMER_A_CTL_CLR;               //clear the the timer in the CTL register, TACLR to clear it
     TIMER_A0->CCR[1] = (300*nADC);              //continuously updating the CCR[1] with a value based on the "nADC" voltage from the potentiometer
     ADC14->IV=0;
}
