/*  Author: Jack Earhart
 *  Start Date:07/05/2020
 *  End Date: 07/29/2020
 *  File: buzzer.c
 *  Description: This file initializes the speaker's pin being used as well as a function to turn the
 *               speaker on to make noise given a noise duration and a frequency to play.
 */
#include "msp.h"
#include "SysTick.h"
//THIS FUNCTION INTIALIZES THE SPEAKER'S PIN BEING USED
void buzzer_init(){
    P2->SEL1 &= ~BIT5;      //clear the SEL1 register
    P2->SEL0 &= ~BIT5;      //clear the SEL0 register
    P2->DIR  |=  BIT5;      //set P2.5 as an output
    P2->OUT  &=~ BIT5;      //drive the speaker LOW initially
}

//THIS FUNCTION GENERATES A TONE FOR THE SPEAKER TO PLAY
void beep(unsigned int note, unsigned int duration)
{
int i;
long delay = (long)(10000/note);              //this is the semi-period of each note.
long time = (long)((duration*100)/(delay*2)); //this is how much time we need to spend on the note.
for (i=0;i<time;i++)

{
P2->OUT |= BIT5;                             //set P2.5 to output noise
delayUs(delay);                              //for a semi-period
P2->OUT &= ~BIT5;                            //Clear P2.5
delayUs(delay);                              //for the other semi-period
}
delayMs(50);                                 //Add a small delay to separate the single notes
}
