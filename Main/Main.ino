/*
# File: HSS Automation.INO
# Author: Henry Hall
# Date: 30/11/2022
# Description: Provides processing and control of sensor data 
    from a proximity sensor and potentiometer in order to 
    detect faults in a Yardmaster Horizontal Screw Separator. 
*/

#include <stdint.h>
#include "Pacer.h"
#include "Sensors.h"
#include "Output.h"

#define PACER_FREQUENCY 500

int equilibrium;

status_t status;


void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  equilibrium = callibrate();
  pacer_init(PACER_FREQUENCY);
  sensor_init();
  output_init();
}

void sensor_serial(void)
{
  if (Serial.read() == '\n') {
    Serial.print(status.error);
    Serial.print("\n");
    Serial.print(status.is_doorShut);
    Serial.print("\n");
  }
}

void loop()
{
  // put your main code here, to run repeatedly:
  pacer_wait();
  status = update(status);
  sensor_serial();
  
}


