/*  Author: Jack Earhart
 *  Start Date:07/05/2020
 *  End Date: 07/29/2020
 *  File: LED.h
 *  Description: This file prototypes the custom functions defined in the LED.c source file.
 */
#ifndef LED_H_
#define LED_H_
void RBG_LED_init();
void red_LED(float DC);
void green_LED(float DC);
void blue_LED(float DC);
#endif /* LED_H_ */
