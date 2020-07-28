/*
 * SysTick.h
 *
 *  Created on: Jul 5, 2020
 *      Author: jackearhart
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_
void delayMs(uint32_t n);
void delayUs(uint32_t n);
void SysTickInit_WithInterrupts(uint32_t delay_ms);

#endif /* SYSTICK_H_ */
