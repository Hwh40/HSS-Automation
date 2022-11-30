/*
# File: HSS Automation.INO
# Author: Henry Hall
# Date: 30/11/2022
# Description: Provides processing and control of sensor data 
    from a proximity sensor and potentiometer in order to 
    detect faults in a Yardmaster Horizontal Screw Separator. 
*/

#include <stdint.h>
#include <stdbool.h>
#include "Pacer.h"
#include "Sensors.h"
#include "Output.h"

#define PACER_FREQUENCY 500

int equilibrium;

status_t status;
output_t out = {0,0,0,0,0,0};


void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  equilibrium = callibrate();
  pacer_init(PACER_FREQUENCY);
  sensor_init();
  output_init();
}

void output_serial(void)
{
  if (Serial.read() == '\n') {
    Serial.print("Outputs:\n");
    Serial.print(out.relay1);
    Serial.print("\n");
    Serial.print(out.relay2);
    Serial.print("\n");
    Serial.print(out.relay3);
    Serial.print("\n");
    Serial.print(out.digital1);
    Serial.print("\n");
    Serial.print(out.digital2);
    Serial.print("\n");
    Serial.print(out.light);
    Serial.print("\n");
    Serial.print("Sensors:\n");
    Serial.print(status.error);
    Serial.print("\n");
    Serial.print(status.is_doorShut);
    Serial.print("\n");
    Serial.print("\n");
  }
}

void loop()
{
  // put your main code here, to run repeatedly:
  pacer_wait();
  status = updateSensor(status);
  if (status.is_doorShut == true) {
    out.relay1 = true;
  }
  updateOutput(out);
  output_serial();

  
}


