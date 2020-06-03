#include "msp.h"


/**
 * main.c
 */
void main(void)
{

    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer
        //configure GPI0 for output on P1.0 LED1 on MSP432 Launchpad
        P1-> DIR = BIT0;
                //temporary variable for loop-maintenance
                int i;
                int x=50000;
        while(1){

            P1->OUT ^=BIT0;         //toggle LED status
            for (i=x;i>0;i--);  //Crude delay

        }

}
