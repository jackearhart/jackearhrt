/*  Author: Jack Earhart
 *  Start Date:07/05/2020
 *  End Date: 07/29/2020
 *  File: menus.c
 *  Description: This file uses custom functions to display any menu option used in the program,
 *               it calls other functions from other source files to turn on or off specific hardware.
 */
//including all source files used in this project by including their respective .h files
#include "sevenseg.h"
#include "msp.h"
#include "menus.h"
#include "keypad.h"
#include "LCD.h"
#include "SysTick.h"
#include "servo.h"
#include "LED.h"
#include "motor.h"
#include "ADC.h"
#include "buzzer.h"
#include <stdio.h>  //library for printing things to the console window
#include <string.h> //library to display strings of text to the LCD
volatile int button_check;

//global variable to be used in different alarm menu
volatile int pin_check;
volatile int door_check=0;
volatile int door_pin=0;
volatile int door_pin2=0;
volatile int door_pin3=0;
volatile int beep_check;
volatile int arm_check;
volatile uint8_t motor_choice=0;
volatile uint8_t button;
volatile uint8_t green_LED_choice;
volatile uint8_t blue_LED_choice;
volatile uint8_t red_LED_choice;

//inital screen shown to the user to choose an option
void main_menu(void){

  LCD_command(0x01);  //clear the LCD of any previous text
  char data[16] = "";   //data array to copy strings into it
  int i;                //variable for counter

  sprintf(data,"(1) Door Menu");            //first string to be copied onto the LCD
  LCD_command(0x81);                        // move to the first line fourth position
  for (i=0;i<(unsigned) strlen(data);i++){  //print data string character by character that's held in the data array
     LCD_data(*(data+i));                   //print the data string of text to the LCD
  }
  sprintf(data,"(2) Motor Menu");           //re-populate the data string to hold the new line of text
  LCD_command(0xC1);                        //move to the second line 4th position
  for (i=0;i<(unsigned) strlen(data);i++){  //print data string character by character that's held in the data array
      LCD_data(*(data+i));                  //print the character and move to the next on the second line
   }
  sprintf(data,"(3) Lights Menu");          //re-populate the data string to hold the new line of text
  LCD_command(0x91);                        //move to the third line 1st position
  for (i=0;i<(unsigned) strlen(data);i++){  //print data string character by character that's held in the data array
      LCD_data(*(data+i));                  //print the character and move to the next on the third line
   }
  sprintf(data,"(4) Alarm Menu");           //re-populate the data string to hold the new line of text
  LCD_command(0xD1);                        //move to the fourth line 6th position
  for (i=0;i<(unsigned) strlen(data);i++){  //print data string character by character that's held in the data array
      LCD_data(*(data+i));                  //print the character and move to the next on the fourth line
   }
  while(1){
      ADC14->CTL0|= ADC14_CTL0_SC;
      __sleep();
      delayMs(100);
      ADC14->IV=1;
//variable "choice" stores the value returned from the keypad input and checks if any of the "if" statements below are true
  uint8_t choice = read_keypad();
      if (choice==1){
          door_menu();
      }
      if (choice==2){
          motor_menu();
      }
      if (choice==3){
          light_menu();
      }
      if (choice==4){
          disarm_menu();
      }
  }
}
//1st menu option on the main menu, turns the servo 90 degrees if open->close or close->open
void door_menu(){
//if the alarm has not been set, the "door_check" variable is zero and the servo menu is called
    if (door_check==0){
        servo_menu();
    }
//if the alarm has been set, and the user has selected the door menu, then they must reenter their alarm pass-key
    if (door_check==1){
        LCD_command(0x01);
        char data[16] = "";                      //data array to copy strings into it
        int i;                                   //variable for counter
        sprintf(data,"DOOR  MENU");              //first string to be copied onto the LCD
        LCD_command(0x83);                       // move to the first line 4th position
        for (i=0;i<(unsigned) strlen(data);i++){ //print data string character by character that's held in the data array
        LCD_data(*(data+i));                     //print the data string of text to the LCD
             }
        sprintf(data,"Re-enter ");               //re-populate the data string to hold the new line of text
        LCD_command(0xC1);                       //move to the second line 2nd position
        for (i=0;i<(unsigned) strlen(data);i++){ //print data string character by character that's held in the data array
        LCD_data(*(data+i));                     //print the character and move to the next on the second line
              }
        sprintf(data,"key to arm door:");        //re-populate the data string to hold the new line of text
        LCD_command(0x91);                       //move to the third line 2nd position
        for (i=0;i<(unsigned) strlen(data);i++){ //print data string character by character that's held in the data array
        LCD_data(*(data+i));                     //print the character and move to the next on the third line
              }

       int door_pin2 = keypad_door();            //variable "door_pin2" stores the verification code returned from keypad_door
       printf ("you entered %d\n\n",door_pin2);  //PRINTF STATEMENT
       if (door_pin == door_pin2){               //if the pass key is the same as the verification key just entered
           beep_check=1;                         //variable to beep the motor when the servo is opened, used in the servo_menu() function
           servo_menu();                         //go to the servo menu, since the pass key has been correctly entered
    }
       if (door_pin!=door_pin2){                 //if the door pin code is not equal to the one entered for verification return to the main menu
           main_menu();
           return;
       }
  }
}
//2nd menu option on the main menu, user can turn the motor on different speeds
void motor_menu(){
     LCD_command(0x01);
     char data[16] = "";                        //data array to copy strings into it
     int i;                                     //variable for counter
     sprintf(data,"MOTOR MENU");                //first string to be copied onto the LCD
     LCD_command(0x83);                         // move to the first line fourth position
     for (i=0;i<(unsigned) strlen(data);i++){   //print data string character by character that's held in the data array
        LCD_data(*(data+i));                    //print the data string of text to the LCD
     }
     sprintf(data,"Enter a speed ");           //re-populate the data string to hold the new line of text
     LCD_command(0xC0);                        //move to the second line 4th position
     for (i=0;i<(unsigned) strlen(data);i++){  //print data string character by character that's held in the data array
         LCD_data(*(data+i));                  //print the character and move to the next on the second line
      }
     sprintf(data,"for the motor to");         //re-populate the data string to hold the new line of text
     LCD_command(0x90);                        //move to the third line 1st position
     for (i=0;i<(unsigned) strlen(data);i++){  //print data string character by character that's held in the data array
         LCD_data(*(data+i));                  //print the character and move to the next on the third line
      }

     sprintf(data,"spin at (0-9)");           //re-populate the data string to hold the new line of text
     LCD_command(0xD0);                       //move to the fourth line 6th position
     for (i=0;i<(unsigned) strlen(data);i++){ //print data string character by character that's held in the data array
         LCD_data(*(data+i));                 //print the character and move to the next on the fourth line
        }
while(1){
            motor_choice = read_keypad();     //variable motor_choice stores the value entered from the keypad input
            if (motor_choice!=0){             //if the keypad value returned isn't NULL
            motor_PWM(motor_choice);          //calling the function that spins the motor at a DC corresponding to the keypad input
            sevensegement(motor_choice);      //calling the 7 segment display function that displays the number entered from the keypad
            main_menu();                      //go back to the main menu
            return;
            }
}
}

void light_menu(){
    LCD_command(0x01);
    char data[16] = "";                       //data array to copy strings into it
     int i;                                   //variable for counter

     sprintf(data,"LIGHT MENU");              //first string to be copied onto the LCD
     LCD_command(0x83);                       // move to the first line fourth position
     for (i=0;i<(unsigned) strlen(data);i++){ //print data string character by character that's held in the data array
        LCD_data(*(data+i));                  //print the data string of text to the LCD
     }
     sprintf(data,"(1)for red LED ");         //re-populate the data string to hold the new line of text
     LCD_command(0xC0);                       //move to the second line 1st position
     for (i=0;i<(unsigned) strlen(data);i++){ //print data string character by character that's held in the data array
         LCD_data(*(data+i));                 //print the character and move to the next on the second line
      }

     sprintf(data,"(2)for green LED");        //re-populate the data string to hold the new line of text
     LCD_command(0x90);                       //move to the third line 1st position
     for (i=0;i<(unsigned) strlen(data);i++){ //print data string character by character that's held in the data array
         LCD_data(*(data+i));                 //print the character and move to the next on the third line
      }

     sprintf(data,"(3)for blue LED");           //re-populate the data string to hold the new line of text
       LCD_command(0xD0);                       //move to the fourth line 1st position
       for (i=0;i<(unsigned) strlen(data);i++){ //print data string character by character that's held in the data array
           LCD_data(*(data+i));                 //print the character and move to the next on the fourth line
        }
       while(1){
     uint8_t LED_choice = read_keypad();       //variable that reads which LED color option was selected from the keypad
       if (LED_choice==1){
           red_LED_menu();                     //if 1 was entered, go to the red LED menu
       }
       if (LED_choice==2){
          green_LED_menu();                    //if 2 was entered, go to the green LED menu
       }
       if (LED_choice==3){
           blue_LED_menu();                    //if 3 was entered, go to the blue LED menu
       }
       if (LED_choice==10){
            main_menu();                       //if * was entered, go the main menu
    return;

        }
       }

}
void red_LED_menu(){
   LCD_command(0x01);                       //clear the LCD screen of any information
   char data[16] = "";                      //data array to copy strings into it
   int i;                                   //variable for counter
   sprintf(data,"RED LED MENU");            //first string to be copied onto the LCD
   LCD_command(0x82);                       // move to the first line 3rd position
   for (i=0;i<(unsigned) strlen(data);i++){ //print data string character by character that's held in the data array
        LCD_data(*(data+i));                //print the data string of text to the LCD
     }
  sprintf(data,"Set brightness:");          //re-populate the data string to hold the new line of text
  LCD_command(0xC0);                        //move to the second line 1st position
  for (i=0;i<(unsigned) strlen(data);i++){  //print data string character by character that's held in the data array
        LCD_data(*(data+i));                //print the character and move to the next on the second line
      }
  sprintf(data,"Any digit 0-100.");         //re-populate the data string to hold the new line of text
  LCD_command(0x90);                        //move to the third line 1st position
  for (i=0;i<(unsigned) strlen(data);i++){  //print data string character by character that's held in the data array
          LCD_data(*(data+i));              //print the character and move to the next on the third line
       }
  sprintf(data,"Press # to enter");         //re-populate the data string to hold the new line of text
  LCD_command(0xD0);                        //move to the fourth line 1st position
  for (i=0;i<(unsigned) strlen(data);i++){  //print data string character by character that's held in the data array
            LCD_data(*(data+i));            //print the character and move to the next on the third line
         }
        while(1){
            red_LED_choice = keypad_pin();  //variable to check the brightness value for the red LED entered by the user
            red_LED(red_LED_choice);        //turn on the red LED, by calling the function with the input entered by user
            blue_LED_choice=0;              //turn the blue LED choice to 0
            green_LED_choice=0;             //turn the green LED to 0
            blue_LED(0);                    //turn the blue LED off completely by giving it a Duty Cycle of 0
            green_LED(0);                   //turn the green LED off completely by giving it a Duty Cycle of 0
            motor_PWM(motor_choice);          //calling the function that spins the motor at a DC corresponding to the keypad input
            sevensegement(motor_choice);      //calling the 7 segment display function that displays the number entered from the keypad
            main_menu();                    //after the above tasks are complete go back to the main menu
            return;
        }
}

void green_LED_menu(){
  LCD_command(0x01);
  char data[16] = "";                       //data array to copy strings into it
  int i;                                    //variable for counter
  sprintf(data,"GREEN LED MENU");           //first string to be copied onto the LCD
  LCD_command(0x81);                        // move to the first line fourth position
  for (i=0;i<(unsigned) strlen(data);i++){  //print data string character by character that's held in the data array
        LCD_data(*(data+i));                //print the data string of text to the LCD
     }
  sprintf(data,"Set brightness:");          //re-populate the data string to hold the new line of text
  LCD_command(0xC0);                        //move to the second line 4th position
  for (i=0;i<(unsigned) strlen(data);i++){  //print data string character by character that's held in the data array
         LCD_data(*(data+i));               //print the character and move to the next on the second line
      }
  sprintf(data,"Any digit 0-100.");         //re-populate the data string to hold the new line of text
  LCD_command(0x90);                        //move to the third line 1st position
  for (i=0;i<(unsigned) strlen(data);i++){  //print data string character by character that's held in the data array
          LCD_data(*(data+i));              //print the character and move to the next on the third line
       }
  sprintf(data,"Press # to enter");         //re-populate the data string to hold the new line of text
  LCD_command(0xD0);                        //move to the third line 1st position
  for (i=0;i<(unsigned) strlen(data);i++){  //print data string character by character that's held in the data array
            LCD_data(*(data+i));            //print the character and move to the next on the third line
         }
        while(1){
          green_LED_choice = keypad_pin();  //variable to check the brightness value for the green LED entered by the user
          green_LED(green_LED_choice);      //turn on the green LED, by calling the function with the input entered by user
          blue_LED_choice=0;                //turn the blue LED choice to 0
          red_LED_choice=0;                 //turn the red LED choice to 0
          blue_LED(0);                      //turn the blue LED off completely by giving it a Duty Cycle of 0
          red_LED(0);                       //turn the red LED off completely by giving it a Duty Cycle of 0
          motor_PWM(motor_choice);          //calling the function that spins the motor at a DC corresponding to the keypad input
          sevensegement(motor_choice);      //calling the 7 segment display function that displays the number entered from the keypad
          main_menu();                      //after the above tasks are complete go back to the main menu
          return;
        }
}

void blue_LED_menu(){

  LCD_command(0x01);
  char data[16] = "";                       //data array to copy strings into it
  int i;                                    //variable for counter
  sprintf(data,"BLUE LED MENU");            //first string to be copied onto the LCD
  LCD_command(0x82);                        // move to the first line 3rd position
  for (i=0;i<(unsigned) strlen(data);i++){  //print data string character by character that's held in the data array
        LCD_data(*(data+i));                //print the data string of text to the LCD
     }
  sprintf(data,"Set brightness");           //re-populate the data string to hold the new line of text
  LCD_command(0xC0);                        //move to the second line 1st position
  for (i=0;i<(unsigned) strlen(data);i++){  //print data string character by character that's held in the data array
         LCD_data(*(data+i));               //print the character and move to the next on the second line
      }
  sprintf(data,"Any digit 0-100.");         //re-populate the data string to hold the new line of text
  LCD_command(0x90);                        //move to the third line 1st position
  for (i=0;i<(unsigned) strlen(data);i++){  //print data string character by character that's held in the data array
          LCD_data(*(data+i));              //print the character and move to the next on the third line
       }
  sprintf(data,"Press # to enter");         //re-populate the data string to hold the new line of text
  LCD_command(0xD0);                        //move to the fourth line 1st position
  for (i=0;i<(unsigned) strlen(data);i++){  //print data string character by character that's held in the data array
            LCD_data(*(data+i));            //print the character and move to the next on the third line
         }
        while(1){
          blue_LED_choice = keypad_pin();   //variable to check the brightness value for the blue LED entered by the user
          blue_LED(blue_LED_choice);        //turn on the blue LED, by calling the function with the input entered by user
          red_LED_choice=0;                 //turn the red LED choice to 0
          green_LED_choice=0;               //turn the blue LED choice to 0
          green_LED(0);                     //turn the green LED off completely by giving it a Duty Cycle of 0
          red_LED(0);                       //turn the red LED choice off completely by giving it a Duty Cycle of 0
          motor_PWM(motor_choice);          //calling the function that spins the motor at a DC corresponding to the keypad input
          sevensegement(motor_choice);      //calling the 7 segment display function that displays the number entered from the keypad
          main_menu();                      //after the above tasks are complete go back to the main menu
          return;
        }

}
void disarm_menu(){

  if (door_check==0){                       //if no passcode has been entered yet and the user chooses the disarm menu option
  LCD_command(0x01);
  char data[16] = "";                       //data array to copy strings into it
  int i;                                    //variable for counter
  sprintf(data,"ARM ALARM");                //first string to be copied onto the LCD
  LCD_command(0x84);                        // move to the first line 5th position
  for (i=0;i<(unsigned) strlen(data);i++){  //print data string character by character that's held in the data array
        LCD_data(*(data+i));                //print the data string of text to the LCD
     }
  sprintf(data,"Enter 4 digit ");            //re-populate the data string to hold the new line of text
  LCD_command(0xC1);                         //move to the second line 2nd position
  for (i=0;i<(unsigned) strlen(data);i++){   //print data string character by character that's held in the data array
         LCD_data(*(data+i));                //print the character and move to the next on the second line
      }

  sprintf(data,"key to arm door:");         //re-populate the data string to hold the new line of text
  LCD_command(0x91);                        //move to the third line 2nd position
  for (i=0;i<(unsigned) strlen(data);i++){  //print data string character by character that's held in the data array
         LCD_data(*(data+i));               //print the character and move to the next on the third line
      }
while(1){
    char data[16] = "";                     //data array to copy strings into it
    int i;                                  //variable for counter

   door_pin = keypad_door();
   if (door_pin!=0){
   sprintf(data,"%d",door_pin);              //re-populate the data string to hold the new line of text
   LCD_command(0xD5);                        //move to the fourth line 6th position
   for (i=0;i<(unsigned) strlen(data);i++){  //print data string character by character that's held in the data array
          LCD_data(*(data+i));               //print the character and move to the next on the fourth line
       }
     }
   delayMs(2000);                           //delay the LCD screen for 2 seconds to show the passcode entered by the user

   LCD_command(0x01);                       //clear the LCD screen
   printf ("you entered %d\n\n",door_pin);

  sprintf(data,"ALARM ARMED!");             //re-populate the data string to hold the new line of text
  LCD_command(0x92);                        //move to the third line 3rd position
  for (i=0;i<(unsigned) strlen(data);i++){  //print data string character by character that's held in the data array
         LCD_data(*(data+i));               //print the character and move to the next on the third line

      }
  delayMs(1500);                            //delay the LCD screen for 1.5 seconds to show the ALARM ARMED text
  door_check=1;                             //set the door check alarm to 1 so the user must enter the pass code and so the alarm can beep

main_menu();
return;
}
    }

   if (door_check==1){                     //if the alarm has been armed and the ARM/DISARM MENU option was chosen, the user can disarm the alarm
   LCD_command(0x01);                      //Clear the LCD screen
   char data[16] = "";                     //data array to copy strings into it
   int i;                                  //variable for counter
   sprintf(data,"DISARM ALARM");           //first string to be copied onto the LCD
   LCD_command(0x82);                      // move to the first line fourth position
   for (i=0;i<(unsigned) strlen(data);i++){//print data string character by character that's held in the data array
                LCD_data(*(data+i));       //print the data string of text to the LCD
             }
   sprintf(data,"Your 4 digit key");       //re-populate the data string to hold the new line of text
   LCD_command(0xC0);                      //move to the second line 4th position
   for (i=0;i<(unsigned) strlen(data);i++){//print data string character by character that's held in the data array
                 LCD_data(*(data+i));      //print the character and move to the next on the second line
              }

   sprintf(data,"used to arm door:");      //re-populate the data string to hold the new line of text
   LCD_command(0x90);                      //move to the third line 1st position
   for (i=0;i<(unsigned) strlen(data);i++){//print data string character by character that's held in the data array
                 LCD_data(*(data+i));      //print the character and move to the next on the third line
              }
   while(1){
   door_pin3 = keypad_door();              //variable to check if the disarm pass-key is equal to the arm
   printf ("you entered %d\n\n",door_pin); //PRINTF statement
   if (door_pin3!=0){                      //if the pass-key entered is not equal to a none zero value
   sprintf(data,"%d",door_pin3);           //re-populate the data string to hold the new line of text
   LCD_command(0xD5);                      //move to the fourth line 6th position
   for (i=0;i<(unsigned) strlen(data);i++){//print data string character by character that's held in the data array
                 LCD_data(*(data+i));      //print the character and move to the next on the fourth line
              }
            }
  delayMs(2000);                           //delay for 2 seconds to display the disarm pass-key on the LCD
  if (door_pin3==door_pin){                //if the disarm pass-key is equal to the initial pass-key entered to arm the alarm
  door_check=0;                            //set the door_check variable to 0 to let the program know there isn't a pass-key
  LCD_command(0x01);                       //clear the LCD screen
  char data[16] = "";                      //data array to copy strings into it
  int i;                                   //variable for counter
  sprintf(data,"ALARM DISARMED!");         //re-populate the data string to hold the new line of text
  LCD_command(0x90);                       //move to the third line 1st position
  for (i=0;i<(unsigned) strlen(data);i++){ //print data string character by character that's held in the data array
            LCD_data(*(data+i));           //print the character and move to the next on the third line

          }
 delayMs(1500);                            //delay for 2 seconds to display ALARM DISARMED on the LCD
 beep_check=0;                             //set the beep_check variable to zero so the speaker doesn't beep when the servo is opened, when the pass-key is not on
}
 if (door_pin3!=door_pin){                 //if the pass-key doesn't equal the initial pass-key put in place to arm the alarm
       main_menu();                        //go back to the main menu
       return;
            }
      main_menu();
      return;
        }
    }
    }

void servo_menu(){
  LCD_command(0x01);                      //clear the LCD screen
  char data[16] = "";                     //data array to copy strings into it
  int i;                                  //variable for counter
  sprintf(data,"DOOR  MENU");             //first string to be copied onto the LCD
  LCD_command(0x83);                      // move to the first line fourth position
  for (i=0;i<(unsigned) strlen(data);i++){//print data string character by character that's held in the data array
        LCD_data(*(data+i));              //print the data string of text to the LCD
     }
  sprintf(data,"(1) Open door");          //re-populate the data string to hold the new line of text
  LCD_command(0xC1);                      //move to the second line 4th position
  for (i=0;i<(unsigned) strlen(data);i++){//print data string character by character that's held in the data array
         LCD_data(*(data+i));             //print the character and move to the next on the second line
      }

  sprintf(data,"(2) Close door");         //re-populate the data string to hold the new line of text
  LCD_command(0x91);                      //move to the third line 1st position
  for (i=0;i<(unsigned) strlen(data);i++){//print data string character by character that's held in the data array
         LCD_data(*(data+i));             //print the character and move to the next on the third line
      }
  sprintf(data,"(*) main menu");          //re-populate the data string to hold the new line of text
  LCD_command(0xD1);                      //move to the fourth line 6th position
  for (i=0;i<(unsigned) strlen(data);i++){//print data string character by character that's held in the data array
         LCD_data(*(data+i));             //print the character and move to the next on the fourth line
      }
while(1){
  uint8_t servo_choice = read_keypad();  //variable that keeps track of which option is chosen in the door_menu option
  if (servo_choice==1&&beep_check==1){   //if the alarm pass-key was set (beep_check==1) and the open servo choice was selected
  int i;                                 //variable to beep the speaker a certain amount of times
       open_servo();                     //open servo

  for (i=0; i<5;i++){                    //for loop used to beep the alarm 5 times in a row after the servo was opened
       beep(100,1000);                   //beep the speaker by calling the beep function
       delayMs(150);                     //delay 150 milliseconds between each beep of the speaker
           }
       P10->OUT &=~BIT5;                 //turn the servo off
       main_menu();                      //go to the main menu

       return;
       }
 if (servo_choice==1){                  //if the alarm hasn't been set but the open servo choice was selected

        open_servo();                   //open the servo
        P10->OUT &=~BIT5;               //turn the servo off
        main_menu();                    //go to main menu
        return;
    }
    if (servo_choice==2){               //if the close servo choice was selected
          close_servo();                //close the servo
          P10->OUT &=~BIT5;             //turn the servo off
          main_menu();                  //go to main_menu
          return;
       }

    if (servo_choice==10){             //if * was entered then go to the main menu
        main_menu();
return;
    }
}
}

uint8_t DebounceSwitch(void){
    int check = 0;

        if( ( P1IN & BIT6 )  == 0x00){                      //If P1.1 is equal to zero
            SysTickInit_WithInterrupts(5);                                     //delaying the cycles for 5ms using delayMS custom function
            if( ( P1IN & BIT6 ) == 0x00){                   //Checking a second time to see if P1.1 is equal to zero
                while( ( P1IN & BIT6 ) == 0x00);            //Keeping the code here while the button is being held down
                check = 1;                                  //Once let go check is set to 1 to be returned
            }
        }
        return check;
}

void PORT1_IRQHandler(void){
   // ADC14->IV=0;
    int check = 0;
           if( ( P1IN & BIT6 )  == 0x00){                      //If P1.1 is equal to zero
               SysTickInit_WithInterrupts(5);                                     //delaying the cycles for 5ms using delayMS custom function
               if( ( P1IN & BIT6 ) == 0x00){                   //Checking a second time to see if P1.1 is equal to zero
                   while( ( P1IN & BIT6 ) == 0x00);            //Keeping the code here while the button is being held down
                   check = 1;                                  //Once let go check is set to 1 to be returned
               }
           }
    if (check && button==1) {  //if the interrupt button for the lights was turned off and pressed again to turn the lights back on
           P1->IFG &=~BIT6;                  //clear the interrupt flag
           green_LED(green_LED_choice);      //turn the green LED back to the brightness it was at
           blue_LED(blue_LED_choice);        //turn the blue LED back to the brightness it was at
           red_LED(red_LED_choice);          //turn the red LED back to the brightness it was at
           motor_PWM(motor_choice);          //calling the function that spins the motor at a DC corresponding to the keypad input
           sevensegement(motor_choice);      //calling the 7 segment display function that displays the number entered from the keypad
           button=0;                         //let the program know that the button was pressed to turn the LEDs back on
           return;


       }
       if (check){               //if the lights were turned on
           P1->IFG &=~BIT6;                  //clear the interrupt flag
           green_LED(0);                    //turn off any light that was on prior to the button being pushed
           red_LED(0);
           blue_LED(0);
           motor_PWM(motor_choice);          //calling the function that spins the motor at a DC corresponding to the keypad input
           sevensegement(motor_choice);      //calling the 7 segment display function that displays the number entered from the keypad
           button=1;                         //set the button variable to zero
           return;
   }
    if (P1->IFG & BIT7){
        motor_choice=0;
        TIMER_A2->CCR[1] = (72000*0); //turn the motor off by making the CCR[1] register equal to 0
        P1->IFG &=~BIT7;              //clear the interrupt flag that was set and initiated the interrupt
        print0();                     //print 0 on the seven segment display
    }

}



