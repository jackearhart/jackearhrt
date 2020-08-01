/*  Author: Jack Earhart
 *  Start Date:07/05/2020
 *  End Date: 07/29/2020
 *  File: keypad.h
 *  Description: This file prototypes the custom functions defined in the keypad.c source file.
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_
void keypad_init(void);
uint8_t read_keypad();
uint8_t keypad_pin();
void print_key();
int keypad_door();
#endif /* KEYPAD_H_ */
