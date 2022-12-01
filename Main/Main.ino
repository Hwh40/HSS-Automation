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
#include "Pacer.h"
#include "Sensors.h"
#include "Output.h"

#define PACER_FREQUENCY 10

status_t status = {0,0};
output_t out = {0,0,0,0,0,0};

void setup() 
{
  //Initialise sensors and outputs
  Serial.begin(9600);
  pacer_init(PACER_FREQUENCY);
  sensor_init();
  output_init();
}

void output_serial(void)
{
  //Outputs the sensor and output structs to the serial monitor
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
  //Updates sensors, checks against conditions, and updates outputs at a predefined frequency
  pacer_wait();
  updateSensor(&status);
  check_plug(status, &out);
  check_flow(status, &out);
  updateOutput(out);
  output_serial();  
}


