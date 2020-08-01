/*  Author: Jack Earhart
 *  Start Date:07/05/2020
 *  End Date: 07/29/2020
 *  File: keypad.c
 *  Description: This file populates the custom functions prototyped in the keypad.h
 *               header file and called in the main.c. The delay1ms() function settles the
 *               keypad after a column is set to low, and also acts as a button debounce
 *               function using SysTick. The keypad_init() configures the rows to have pull up resistors
 *               The read_keypad() function scans through all 3 columns, setting one as a low
 *               input and the others being high and checks all 4 rows of the low column, if
 *               nothing is pressed it turns that column to high and the next to low and reads
 *               the rows in there, if something is pressed it breaks out of the loop and returns
 *               the value of the key being pressed
 */
#include "msp.h"
#include "keypad.h"
#include "SysTick.h"
#include "menus.h"
#include <stdio.h>


//all rows are initialized on pins 6.0-6.3
//all columns are initialized on pins 6.4-6.6
//Description: FUNCTION THAT INITIALIZIES THE KEYPADS ROWS WITH PULL UP RESISTORS AND OUTPUTS
//Input: void
//Output: void
void keypad_init(void){
    P6->DIR=0;
    P6->REN=(BIT0|BIT1|BIT2|BIT3);      //enable pull resistors for row pins
    P6->OUT=(BIT0|BIT1|BIT2|BIT3);      // make row pins pull-ups
}
//description:FUNCTION THAT READS THE KEYPADS ROWS AND COLUMNS CONSTATNLY FOR A BUTTON BEING PRESSED
//            IF A ROW AND COLUMN ARE CONNECTED THE FUNCTION RETURNS THE KEY VALUE WHERE THE CONNECTION WAS MADE (USED FOR DEBUGGING)
//Input: void
//Output: return the number of the key pressed on the keypad
uint8_t read_keypad(){
    uint8_t row, col;                   //two unsigned 8 bit integers for rows and columns
    for (col=0; col<3; col++){          //looping through each column to see if a key is being pressed
        P6->DIR &= ~(BIT4|BIT5|BIT6);   //set columns to inputs (all columns on P6.4-6.6 set to 0b00000000)
        P6->DIR|= (1<<(col+4));         //set column pin as output (first column on P6.4 = 0b0001000)
        P6->OUT &= ~(1<<(col+4));       //setting the same column pin as above to a low output
        delayMs(1);                     //delay 1ms to allow the ports to settle (also acts as a debounce sorta)
        row=P6->IN & 0x0F;              //capture the row input values

        while(!(P6->IN&BIT3)|!(P6->IN&BIT2)|!(P6->IN&BIT1)|!(P6->IN&BIT0));     //stay in this while loop while a key is being held down
        if (row!=0x0F)break;
    }
    P6->DIR &= ~(BIT4|BIT5|BIT6);
    if (col==3)
        return 0;
    if (row==0b00001110) return   col+1;
    if (row==0b00001101) return 3+col+1;
    if (row==0B00001011) return 6+col+1;
    if (row==0b00000111) return 9+col+1;

    return 0;
}
//Description:THIS FUNCTION PRINTS THE VALUE OF THE KEY BEING PRESSED, PRINTS THE PROPER VALUE FOR *, 0, AND #
//Input: void
//Output: void
void print_key(){
    uint8_t key;                                    //variable to store the value returned from the read_keypad function
    key = read_keypad();                            //call the read_keypad function and store the value returned in the "key" variable
    if(key!=0 && key!=10 && key!=11 && key!=12){    //if the value returned isnt * (10), 0 (11), or # (12)
    printf ("key: %d\n",key);                       //print the value stored in key to the console window
    }
    if (key!=0 && key==10){                         //if the * was pressed then print the *, not 10
        printf ("key: *\n");
    }
    if (key!=0 && key==11){                         // if 0 was pressed then print 0, not 11
        printf ("key: 0\n");
    }
    if (key!=0 && key==12){                         //if the # was pressed then print #, not 12
        printf ("key: #\n");
    }
}
//Description: THIS FUNCTION IS FOR THE LED BRIGHTNESS, IT IS CALLED IN THE MENUS.C SOURCE FILE AND RETURNS A 0-3 DIGIT NUMBER ONCE THE # IS PRESSED
//Input: none
//Output: a 3 digits pass-key entered by the user
uint8_t keypad_pin(){
    printf ("Enter a 3 digit number:\n");
    int i=0;                                         //counter for array to keep track of PIN digits
   while(1){                                         //infinite while loop
       float value;                                  //variable to store the user's number into
       int j;                                        //j is an integer value called in the for loop to print the pin number, k is used to enter the for loop
       uint8_t key;                                  //key is used to store the values returned from read_keypad()
       uint8_t pin[1000];                            //an unsigned 8 bit integer that keeps a running tab of the user's entered pin
       key = read_keypad();                          //reading the keypad and storing the returned value
       if(key!=0 && key!=10 && key!=11 && key!=12){  //if the digits 1-9 were pressed
       printf ("key: %d\n",key);                     //print the digit
       pin[i]=key;                                   //store the digit in the array
       i++;                                          //increment i for the next key press
       }
       if (key!=0 && key==10){                       //if the * key was pressed
           printf ("key: *\n");                      //print the actual key to the screen not 10
           printf ("please enter a valid input, numbers 0-9\n"); //don't count the entry as part of the pin[i] array and display error message
       }
       if (key!=0 && key==11){                       //if the 0 key was pressed
           printf ("key: 0\n");                      //print the actual key to the screen not 11
           pin[i]=0;                                 //change the value of the stored entry from 10 to 0 to be displayed properly when the PIN is displayed
           i++;                                      //increment i for the next key press
       }
       if (key!=0 && key==12){                       //if the # key was pressed
           if (i==1){                               //if only one number has been entered
               printf("pin number=");
               for (j=0;j<1;j++){                    //increment j starting at 0 and don't stop until it's equal to 1
               printf("%d",pin[j]);                 //display each element of the array
               }
               value=pin[0];                        //if only 1 digit was entered, make the value of the variable "value" equal to the value stored into pin[0]
               printf("\n");
               for (i=0;i<=1;++i){                  //clear the values held in pin[i] and pin[j] for the next time this function is called
                   pin[i]=0.0;
                   pin[j]=0.0;
               }
               i=0;                                  //reset i back to 0 for new PIN entry
               }
           if (i==2){                                //if two numbers have been entered and the # was pressed
               printf("pin number=");
               for (j=0;j<=1;j++){                   //increment j starting at 0 and don't stop until it's equal to 2
               printf("%d",pin[j]);                  //display each element of the array
               }
               value=(10*pin[0])+pin[1];            //store the value of the the two button entries into the variable value
               for (i=0;i<=2;++i){                  //clear the values held in pin[i] and pin[j] for the next time this function is called
                   pin[i]=0.0;
                   pin[j]=0.0;
               }
               i=0;
               }
           if (i>=3){                               //if 3 or more numbers have been entered by the user and # was pressed
           printf("pin number=");
           for (j=0;j<=2;j++){                      //increment j starting at 0 and don't stop until it's equal to 3 (AKA the 4 digits of the PIN have been displayed)
           printf("%d",pin[j]);                      //display each element of the array
           }
           for (i=0;i<=2;++i){
               pin[i]=0.0;
               pin[j]=0.0;
           }
           i=0;
           value=100;                               //maximum value that the LED can be turned to is 100, so the value returned is 100
           printf("\n");
           }
           return value;                            //return the updated value number
       }
       }
}
//Description: THIS FUNCTION IS FOR ALARM CODE, IT IS CALLED IN THE MENUS.C SOURCE FILE AND RETURNS A 4 DIGIT NUMBER ONCE THE # IS PRESSED
//Input: none
//Output: a 4 digits pass-key entered by the user
int keypad_door(){
    printf ("Enter a 4 digit number:\n");
    int i=0;                                            //counter for array to keep track of PIN digits
   while(1){                                            //infinite while loop
       float value;                                     //variable for the keypad entries to be stored into
       int j;                                           //j is an integer value called in the for loop to print the pin number, k is used to enter the for loop
       uint8_t key;                                     //key is used to store the values returned from read_keypad()
       uint8_t pin[1000];                               //an unsigned 8 bit integer that keeps a running tab of the user's entered pin
       key = read_keypad();                             //reading the keypad and storing the returned value
       if(key!=0 && key!=10 && key!=11 && key!=12){     //if the digits 1-9 were pressed
       printf ("key: %d\n",key);                        //print the digit
       pin[i]=key;                                      //store the digit in the array
       i++;                                             //increment i for the next key press
       }
       if (key!=0 && key==10){                          //if the * key was pressed
           printf ("key: *\n");                         //print the actual key to the screen not 10
           printf ("please enter a valid input, numbers 0-9\n"); //don't count the entry as part of the pin[i] array and display error message


       }
       if (key!=0 && key==11){                            //if the 0 key was pressed
           printf ("key: 0\n");                           //print the actual key to the screen not 11
           pin[i]=0;                                      //change the value of the stored entry from 10 to 0 to be displayed properly when the PIN is displayed
           i++;                                           //increment i for the next key press
       }
       if (key!=0 && key==12){                            //if the # key was pressed
           if (i<3){
               return '\0';                               //if 'i' is less than 3 (4 digits) return a null character
           }
           if (i>=3){
           printf("pin number=");
           for (j=0;j<=3;j++){                           //increment j starting at 0 and don't stop until it's equal to 3 (AKA the 4 digits of the PIN have been displayed)
           printf("%d",pin[j]);                          //display each element of the array
           }
           value=(1000*pin[0])+(100*pin[1])+(10*pin[2])+pin[3];     //store the 4 digit value from the pin array
           for (j=0;j<=i;++j){                          //reset the arrays used for the next program iteration
               pin[i]=0.0;
               pin[j]=0.0;
           }
           i=0;                                        //reset i for the next iteration
           printf("\n");
           }
           return value;                              //return the value from the function
       }
       }
}
