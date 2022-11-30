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


void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  equilibrium = callibrate();
  pacer_init(PACER_FREQUENCY);
  sensor_init();
  output_init();
}

void loop()
{
  // put your main code here, to run repeatedly:
  pacer_wait();
  light_on();
  Serial.write(equilibrium);
}
