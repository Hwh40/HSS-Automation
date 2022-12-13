/*
# File: SPI Slave.INO
# Author: Henry Hall
# Date: 6/12/2022
# Description: For use with a arduino connected to arduino IDE 
  through a serial port. Receives 255 bytes from a controller
  and prints to the serial port. 
*/

#include <stdint.h>
uint16_t data1;
uint16_t data2;
uint16_t data3;

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
  //Receives an SPI transmission and prints it to a serial monitor
    data1 = receive();
    data2 = receive();
    data3 = receive();
    Serial.print("F ");
    Serial.print((data1 * 256 + data2));
    Serial.println();
    Serial.print("P ");
    Serial.print(data3);
    Serial.println();
}
