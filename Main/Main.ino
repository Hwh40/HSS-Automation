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
#include <math.h>
#include <avr/wdt.h>
#include "Pacer.h"
#include "Sensors.h"
#include "Output.h"

#define PACER_FREQUENCY 100

status_t status = {0, 0};
output_t out = {0, 0, 0, 0, 0, 0};

void setup() {
  //Initialise sensors and outputs
  Serial.begin(9600);
  pacer_init(PACER_FREQUENCY);
  sensor_init();
  output_init();
  wdt_disable();
  
  delay(3000);
  wdt_enable(WDTO_250MS);
  //led_flash();
}

void loop() {
  //Updates sensors, checks against conditions, and updates outputs at a predefined frequency
  pacer_wait();
  updateSensor(&status);
  check_plug(status, &out);
  check_flow(status, &out);
  updateOutput(out);
  output_serial(out, status);
  wdt_reset();
}
