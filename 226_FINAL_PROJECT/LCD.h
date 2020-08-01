/*  Author: Jack Earhart
 *  Start Date:07/05/2020
 *  End Date: 07/29/2020
 *  File: LCD.h
 *  Description: This file prototypes the custom functions defined in the LCD.c source file.
 */
#ifndef LCD_H_
#define LCD_H_
#define RS 1
#define RW 2
#define EN 4
#define num1 05
#define num2 20
void LCD_command(unsigned char command);
void LCD_data(char data);
void LCD_init(void);
void LCD_nibble_write (char data, unsigned char control);
#endif /* LCD_H_ */
