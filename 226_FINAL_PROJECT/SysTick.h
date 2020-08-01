/*  Author: Jack Earhart
 *  Start Date:07/05/2020
 *  End Date: 07/29/2020
 *  File: SysTick.h
 *  Description: This file prototypes the custom functions defined in the SysTick.c source file.
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_
void delayMs(uint32_t n);
void delayUs(uint32_t n);
void SysTickInit_WithInterrupts(uint32_t delay_ms);
#endif /* SYSTICK_H_ */
