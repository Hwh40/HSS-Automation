#include "Pacer.h"
#include <stdint.h>


static uint16_t PERIOD;

void pacer_init(uint8_t pacer)
{
  PERIOD = 15625 / pacer;
  TCNT1 = 0x00;
  TCCR1C = 0x00;
  TCCR1B = 0x05;
  TCCR1A = 0x00;
}

void pacer_wait(void)
{
  while (TCNT1 < PERIOD) {
    continue;
  }
  TCNT1 = 0;
}