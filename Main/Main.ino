/*
# File: Main.INO
# Author: Henry Hall
# Date: 30/11/2022
# Description: Provides processing and control of sensor data 
    from a proximity sensor and potentiometer in order to 
    detect faults in a Yardmaster Horizontal Screw Separator. 
*/

#include <stdint.h>
#include <stdbool.h>
#include <avr/wdt.h>
#include "Pacer.h"
#include "Sensors.h"
#include "Output.h"
#include "EEPROM.h"

#define PACER_FREQUENCY 100

uint16_t SPI_C = 0; 
status_t status = {0, 0};
output_t out = {0, 0, 0, 0, 0, 0};

void setup() {
  //Initialise sensors and outputs
  pacer_init(PACER_FREQUENCY);
  sensor_init();
  output_init();
  SPI_init();
  wdt_disable();
  delay(3000);
  wdt_enable(WDTO_500MS);
  led_flash();
  SPI_send(status);
}

void loop() {
  //Updates sensors, checks against conditions, and updates outputs at a predefined frequency
  pacer_wait();
  if (SPI_C != 50) {
    updateSensor(&status);
    check_plug(status, &out);
    check_flow(status, &out);
    updateOutput(out);
  }
  if (SPI_C == 50) {
    SPI_send(status);
    SPI_C = 0;
  }
  SPI_C++;
  wdt_reset();
}
