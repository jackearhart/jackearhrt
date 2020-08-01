/*  Author: Jack Earhart
 *  Start Date:07/05/2020
 *  End Date: 07/29/2020
 *  File: menus.h
 *  Description: This file prototypes the custom functions defined in the menus.c source file.
 */
#ifndef MENUS_H_
#define MENUS_H_

void main_menu(void);
void door_menu();
void motor_menu();
void light_menu();
void red_LED_menu();
void green_LED_menu();
void blue_LED_menu();
uint8_t DebounceSwitch(void);
void servo_menu();
void disarm_menu();
#endif /* MENUS_H_ */
