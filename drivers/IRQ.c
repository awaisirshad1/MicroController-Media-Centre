/*----------------------------------------------------------------------------
 * Name:    IRQ.c
 * Purpose: IRQ Handler
 * Note(s):
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2011 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/

#include "LPC17xx.h"                         /* LPC17xx definitions           */
#include "LED.h"
#include "Board_ADC.h"
#include "main.h"

uint8_t  clock_ms;                           /* Flag activated every 10 ms    */


/*----------------------------------------------------------------------------
  Systick Interrupt Handler
  SysTick interrupt happens every 10 ms
 *----------------------------------------------------------------------------*/
void SysTick_Handler1 (void) {
  static unsigned long ticks = 0;
  static unsigned long timetick;
  static unsigned int  leds = 0x01;

  if (ticks++ >= 9) {                       /* Set Clock1s to 10ms */
    ticks    = 0;
    clock_ms = 1;
  }

  /* Blink the LEDs depending on ADC_ConvertedValue                           */
  if (timetick++ >= (ADC_last >> 8)) {
    timetick   = 0;
    leds     <<= 1;
    if (leds > (1 << LED_NUM)) leds = 0x01;
    LED_Out (leds);
  }

  ADC_StartConversion();
}
