/*
# File: SPI Slave.INO
# Author: Henry Hall
# Date: 6/12/2022
# Description: For use with a arduino connected to arduino IDE 
  through a serial port. Receives 255 bytes from a controller
  and prints to the serial port. 
*/

#include <stdint.h>
uint16_t array[3] = {0, 0, 0};
uint16_t i = 4;

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
  Serial.begin(115200);
}

void loop() {
  //Receives an SPI transmission and prints it to a serial monitor
    char data = receive();
    if (data == 'S') {
      uint8_t byte1 = receive(); 
      uint8_t byte2 = receive(); 
      uint8_t byte3 = receive();  
      Serial.print('S');
      Serial.print('\n');      
      Serial.print(byte1 * 256 + byte2);
      Serial.print('\n');
      if (byte3 == 1) {
        Serial.print(100);
      } else {
        Serial.print(0);
      }
      Serial.print('\n');
    }
}
