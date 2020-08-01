/*  Name: Jack Earhart
 *  Start Date:07/05/2020
 *  End Date: 07/29/2020
 *  File: LCD.c
 *  Description: Populates the functions used in the main.c, such as an LCD_init function that initializes
 *               the use of the LCD and sets its initial cursor position. An LCD_command and LCD_data function
 *               that uses the LCD_nibble_write function to send commands to the LCD via the upper and bottom
 *               nibble of a byte since the LCD uses 4 bit mode. The second to last function, scrolling_text
 *               defines a string of characters and scrolls the string off the screen and back onto the other side
 *               by manipulating the array.
 */
//5V pin used to power the breadboard power strip
//VSS goes to GND
//VDD goes to 5V
//V0 controls the contrast of the characters being displayed by a potentiometer
//RS is on P4.0
//R/W is on P4.1
//E is on P4.2
//nothing on P4.3
//DB4-DB7 are located on P4.4-P4.7
//LEDA is connected to 3.3V
//LEDK is connected to drain pin of mosfet 2N7000
#include "msp.h"
#include "LCD.h"
#include "keypad.h"
#include "SysTick.h"
#include "menus.h"
#include <string.h>
#include <stdio.h>

//description: FUNCTION THAT INITIALIZE THE LCD SCREEN FOR USE (4 BIT MODE, SCREEN ON, CURSOR AT THE TOP LEFT POSITION BLINKING)
//inputs:void
//outputs: void
void LCD_init(void){
    P4->DIR = 0xFF;                          //make P4 pins output for data and controls (DIR=1)
    delayMs(30);                             //initialization begins after delay
    LCD_nibble_write (0x30,0);
    delayMs(10);
    LCD_nibble_write (0x30,0);
    delayMs(1);
    LCD_nibble_write (0x30,0);
    delayMs(1);
    LCD_nibble_write (0x20,0);               //use 4 bit data mode
    delayMs(1);

    LCD_command(0x28);                       //set 4 bit data 2-line, 5x7 font
    LCD_command(0x06);                       //move cursor right after each char
    LCD_command(0x01);                       //clear screen, move cursor to home
    LCD_command(0x0F);                       //turn on display, cursor blinking
}
//description: FUNCTION USED TO RIGHT A BYTE OF DATA (THE INPUT) AS TWO SEPERATE NIBBLES, THE UPPER THEN LOWER
//input: unsigned char, unsigned char
//output: void
void LCD_nibble_write (char data, unsigned char control){
    data &= 0xF0;                            //clear lower nibble for control
    control &= 0x0F;                         //clear upper nibble for data
    P4->OUT = data|control;                  //RS=0, R/W=0
    P4->OUT = data|control|EN;               //pulse E
    delayMs(2);
    P4->OUT = data;                          //clear E
    P4->OUT = 0;
}
//description: FUNCTION USED TO SEND COMMANDS TO THE LCD, LIKE MOVING THE CURSOR TO A POSTITION
//input: unsigned char
//output: void
void LCD_command(unsigned char command){
    LCD_nibble_write (command & 0xF0, 0);   //send inputed command to upper nibble first
    LCD_nibble_write (command << 4, 0);     //then lower nibble
    if (command < 4)
        delayMs(4);                         //the two commands above need 1.64 microseconds
    else
        delayMs(1);                         //other commands are 40 microseconds
}
//description: FUNCTION USED TO SEND DATA TO THE LCD, LIKE TEXT
//input: char
//output: void
void LCD_data(char data){
    LCD_nibble_write (data & 0xF0, RS);    //upper nibble first
    LCD_nibble_write (data << 4, RS);      //then the lower nibble
    delayMs(1);
}

