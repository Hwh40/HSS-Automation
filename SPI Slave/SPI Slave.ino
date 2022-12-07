/*
# File: SPI Slave.INO
# Author: Henry Hall
# Date: 6/12/2022
# Description: For use with a arduino connected to arduino IDE 
  through a serial port. Receives 255 bytes from a controller
  and prints to the serial port. 
*/

int data[255];
size_t i = 0;

void SPI_init(void)
{
  //Initialises DDR and SPI
  DDRB = 0x08;
  SPCR = 0x40;
}

char receive(void)
{
  //Returns 8 bits from an SPI transmission
  while (!(SPSR & (1 << SPIF)));
  return SPDR;
}

void setup() {
  //Initialisiation
  SPI_init();
  Serial.begin(9600);
  for (int i = 0; i < 10; i++){
    Serial.print(i);
    Serial.println();
  }
}

void loop() {
  //Receives an SPI transmission of a controllers EEPROM memory and prints it to a serial monitor
  if (PINB & (1 << 2)) {
    data[i] = receive();
    Serial.print(i);
    i++;
  }
  if (i > 255) {
    for (size_t j = 0; i < 255; i++) {
      Serial.print(data[j]);
    }
  }
}
