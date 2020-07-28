/*  Author: Jack Earhart
 *  Start Date:07/05/2020
 *  End Date: 07/29/2020
 *  File: sevenseg.c
 *  Description: This file configures the seven segment display, it has functions to initialize the display,
 *               print any individual number, and a function that takes keypad user input.
 */
#include "msp.h"
#include "sevenseg.h"
//FUNCTION THAT INITIAILIZES THE PINS USED FOR THE SEVEN SEGMENT DISPLAY, AND PRINTS ZERO INTIALLY
void seg_init(){
    P3->SEL1 &= ~(BIT2|BIT3|BIT5|BIT6|BIT7);
    P3->SEL0 &= ~(BIT2|BIT3|BIT5|BIT6|BIT7);
    P3->DIR  |=  (BIT2|BIT3|BIT5|BIT6|BIT7);
    P5->SEL1 &= ~(BIT0|BIT1|BIT2);
    P5->SEL0 &= ~(BIT0|BIT1|BIT2);
    P5->DIR  |=  (BIT0|BIT1|BIT2);
    print0();
}
//FUNCTION THAT PRINTS A NUMBER 0-9 GIVEN AN INPUT VARIABLE, THAT VARIABLE BEING A NUMBER 1-9, AND 11 TO PRINT 0
void sevensegement(uint8_t sevenseg){
          if (sevenseg==1){
            print1();
}
          if (sevenseg==2){
            print2();
}
          if (sevenseg==3){
            print3();
}
          if (sevenseg==4){
             print4();
}
          if (sevenseg==5){
             print5();
}
          if (sevenseg==6){
              print6();
}
          if (sevenseg==7){
              print7();
}
          if (sevenseg==8){
            print8();
}
          if (sevenseg==9){
             print9();
}
          if (sevenseg==11){
             print0();
}
}
void print0(){
    P3->OUT |= (BIT2|BIT3|BIT5|BIT6|BIT7);
    P3->OUT &= ~(BIT0);
    P5->OUT |= (BIT2);
    P5->OUT &=~(BIT0|BIT1);
}
void print1(){
    P3->OUT |= (BIT5|BIT6);
    P3->OUT &= ~(BIT2|BIT3|BIT7);
    P5->OUT &=~(BIT0|BIT1|BIT2);
}
void print2(){
    P3->OUT |= (BIT3|BIT5|BIT7);
    P3->OUT &= ~(BIT6|BIT2);
    P5->OUT |= (BIT1|BIT2);
    P5->OUT &=~(BIT0);
}
void print3(){
    P3->OUT |= (BIT3|BIT5|BIT6|BIT7);
    P3->OUT &= ~(BIT2);
    P5->OUT &= ~(BIT2|BIT0);
    P5->OUT |= BIT1;
}
void print4(){
    P3->OUT |= (BIT2|BIT5|BIT6);
    P3->OUT &= ~(BIT3|BIT7);
    P5->OUT &= ~(BIT2|BIT0);
    P5->OUT |= BIT1;
}
void print5(){
    P3->OUT |= (BIT3|BIT2|BIT6|BIT7);
    P3->OUT &= ~(BIT5);
    P5->OUT &= ~(BIT2|BIT0);
    P5->OUT |= BIT1;
}
void print6(){
    P3->OUT |= (BIT3|BIT2|BIT6|BIT7);
     P3->OUT &= ~(BIT5);
     P5->OUT |=(BIT2|BIT1);
     P5->OUT &= ~(BIT0);
}
void print7(){
    P3->OUT |= (BIT3|BIT5|BIT6);
    P3->OUT &= ~(BIT2|BIT7);
    P5->OUT &= ~(BIT1|BIT2|BIT0);
}
void print8(){
    P3->OUT |= (BIT3|BIT5|BIT6|BIT7|BIT2);
    P5->OUT |=(BIT1|BIT2);
    P5->OUT &= ~(BIT0);
}
void print9(){
    P3->OUT |= (BIT3|BIT5|BIT0|BIT2|BIT6);
    P3->OUT &= ~(BIT7);
    P5->OUT |=(BIT1);
    P5->OUT &= ~(BIT2|BIT0);
}
