/*
# File: Pacer.cpp
# Author: Henry Hall
# Date: 30/11/2022
# Description: Pacer functions for timed round robin
  scheduling in main function. 
*/

#include "Pacer.h"
#include <stdint.h>

static uint16_t PERIOD;

void pacer_init(uint8_t pacer)
{
  //Initialises the timer and calculates the ticks needed
  PERIOD = 15625 / pacer;
  TCNT1 = 0x00;
  TCCR1C = 0x00;
  TCCR1B = 0x05;
  TCCR1A = 0x00;
}

void pacer_wait(void)
{
  //Waits until the timer reaches a certain value then resets
  while (TCNT1 < PERIOD) {
    continue;
  }
  TCNT1 = 0x00;
}