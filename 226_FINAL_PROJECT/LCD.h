/*  Name: Jack Earhart & Joe besta
 *  Date: 6/28/2020
 *  File: LCD.h
 *  Description: This file prototypes all functions populated in the .c source file. In addition to this
 *               it defines all the RS, RW, and EN pins located on the MSP.
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
