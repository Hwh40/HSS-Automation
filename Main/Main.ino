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
#include <math.h>
#include "Pacer.h"
#include "Sensors.h"
#include "Output.h"

#define PACER_FREQUENCY 10
#define THRESHOLD_ANGLE 22.5

bool is_on;
status_t status = {0,0};
output_t out = {0,0,0,0,0,0};


void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  callibrate();
  pacer_init(PACER_FREQUENCY);
  sensor_init();
  output_init();
  is_on = false;
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

void check_plug(void)
{
  if (status.is_doorShut == false && !is_on) {
    is_on = true;
  }
  if (status.is_doorShut == true && is_on) {
    out.relay1 = true;
  }
}

void check_flow(void)
{
  if (status.error > ((1024.0 / 360.0) * THRESHOLD_ANGLE)) {
    out.relay2 = true;
  }
}

void loop()
{
  // put your main code here, to run repeatedly:
  pacer_wait();
  status = updateSensor(status);
  check_plug();
  check_flow();
  updateOutput(out);
  output_serial();  
}


