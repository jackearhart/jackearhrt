/*  Name: Jack Earhart & Joe Besta
 *  Date: 06/15/2020
 *  File: keypad.h
 *  Description: This file prototypes the functions used in the main.c and defined
 *               in the keypad.c source file, only 4 functions, a resistor configure
 *               function (void keypad_init(void)), a keypad reader (uint8_t read_keypad()),
 *               a systick delay function (void delay1ms(void)), and a print key
 *               function (void print_key()).
 *

 */

#ifndef KEYPAD_H_
#define KEYPAD_H_
void keypad_init(void);
uint8_t read_keypad();
uint8_t keypad_pin();
void print_key();
int keypad_door();
#endif /* KEYPAD_H_ */
