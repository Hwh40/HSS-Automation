/*
# File: SPI Slave.INO
# Author: Henry Hall
# Date: 6/12/2022
# Description: For use with a arduino connected to arduino IDE 
  through a serial port. Receives 255 bytes from a controller
  and prints to the serial port. 
*/

#include <stdint.h>
uint8_t data = 0xFF;

void SPI_init(void)
{
  //Initialises DDR and SPI
  DDRB = 0x08;
  SPCR = 0x40;
}

uint8_t receive(void)
{
  //Returns 8 bits from an SPI transmission
  SPDR = 0xFF;
  while (!(SPSR & (1 << 7))) {
    continue;
  }
  return SPDR;
}

void setup() {
  //Initialisiation
  DDRB |= (1<<2);
  SPI_init();
  Serial.begin(9600);
}

void loop() {
  //Receives an SPI transmission of a controllers EEPROM memory and prints it to a serial monitor
  if (/*(PINB & (1<<2)) == 0*/ 1) {
    data = receive();
    Serial.print(data);
    Serial.println();
  }


}
