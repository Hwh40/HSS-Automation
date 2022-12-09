/*
# File: EEPROM.cpp
# Author: Henry Hall
# Date: 30/11/2022
# Description: Stores data into the microcontrollers eeprom 
  and sends it to a slave controller across SPI conncections. 
*/

#include "Sensors.h"
#include "Output.h"
#include <stdint.h>
#include <EEPROM.h>

static int8_t address = 0

static void SPI_init()
{
  //Initialises SPI and DDR 
  DDRB = 0x2C;
  SPCR = 0x51;
}

static void transmit(char data)
{
  //Puts 8 bits into the data register for SPI
  SPDR = data;
  while(!(SPSR & (1 << SPIF)));
}

void Sensor_toEEPROM(status_t status) 
{
  if (address < 255){
    EEPROM.write(status.error, address);
    address++;
    address++;
    EEPROM.write(status.is_doorShut, address);
    address++;
  }
}

void SPI_send(status_t status)
{
  PORTB &= ~(1 << 2);
  transmit(status.error);
  PORTB |= (1 << 2);
  delay(100);
  PORTB &= ~(1 << 2);
  transmit(status.is_doorShut);
  PORTB |= (1 << 2);
}
 