/*
# File: EEPROM.cpp
# Author: Henry Hall
# Date: 30/11/2022
# Description: Stores data into the microcontrollers eeprom 
  and sends it to a slave controller across SPI conncections. 
*/

#include "Sensors.h"
#include "Output.h"
#include "SPIDATA.h"
#include <stdint.h>

static uint8_t address = 0;

void SPI_init(void)
{
  //Initialises SPI and DDR 
  DDRB = 0x2C;
  SPCR = 0x51;
}

static void transmit(uint16_t data)
{
  //Puts 8 bits into the data register for SPI
  SPDR = data;
  while((SPSR & (1 << 7)) == 0) {
    continue;
  }
}

void SPI_send(status_t status)
{
  //Sends SPI data via SPI
  PORTB &= ~(1<<2);
  transmit('S');
  transmit(status.error);
  transmit(status.is_doorShut);
  transmit((status.sensitivity / 11.36));
  PORTB |= (1<<2);
}