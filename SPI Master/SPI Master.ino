/*
# File: SPI Master.INO
# Author: Henry Hall
# Date: 6/12/2022
# Description: For use with a microcontroller without a serial 
  port available. Transmits the whole EEPROM memory to a slave 
  controller via SPI.
*/

#include <EEPROM.h>

int data[255]; 

void SPI_init()
{
  //Initialises SPI and DDR 
  DDRB = 0x2C;
  SPCR = 0x51;
}

void transmit(char data)
{
  //Puts 8 bits into the data register for SPI
  SPDR = data;
  while(!(SPSR & (1 << SPIF)));
}

void setup() {
  //Makes a copy of EEPROM memory and transmits via SPI
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);
  SPI_init();
  for (int i = 0; i < 255; i++) {
    data[i] = EEPROM.read(i);
  }
  digitalWrite(4, LOW);
  delay(100);
  digitalWrite(4, HIGH);
  for (int i =0; i < 255; i++) {
    PORTB &= ~(1 << 2);
    transmit(data[i]);
    PORTB |= (1 << 2);
  }
  for (int i = 0; i < 3; i++) {
    digitalWrite(4, HIGH);
    delay(100);
    digitalWrite(4, LOW);
    delay(100);
  }
}

void loop() {
}
