/*
# File: Sensors.cpp
# Author: Henry Hall
# Date: 30/11/2022
# Description: Reads and proccesses the sensor data
  from a proximity sensor and a potentiometer. 
*/

#include "Sensors.h"
#include "Output.h"
#include <stdint.h>

static int equilibrium;
static int PROX = 3;
static int POT = 15;
static int ADJ = 14;
static int D3 = 7;
static bool is_on = false;

static void callibrate(void)
{
  //Finds the initial equilibrium angle of the paddle
  equilibrium = analogRead(POT);
}

static uint16_t error(void)
{
  //Finds the error between the current paddle position and the equilibrium
  return abs(equilibrium - analogRead(POT));
}

static bool doors_shut(void)
{
  //Returns true if the doors are shut
  return (digitalRead(PROX) == HIGH);
}

void sensor_init(void)
{
  //Initialises the pins and callibrates the sensors
  pinMode(PROX, INPUT);
  pinMode(POT, INPUT);
  pinMode(D3, INPUT);
  pinMode(ADJ, INPUT);
  callibrate();
}

void updateSensor(status_t* status)
{
  //Updates a status struct using static functions
  status->error = error();
  status->is_doorShut = doors_shut();
}

void check_plug(status_t status, output_t* out)
{
  //From a status struct checks to see if the plug has blown and updates the out struct
  if (status.is_doorShut == false && !is_on) {
    is_on = true;
  }
  if (status.is_doorShut == true && is_on) {
    out->relay1 = true;
  }
}

void check_flow(status_t status, output_t* out)
{
  //From a status struct checks to see if the flow has exceded the threshold and updates the out struct
  if (status.error > ((1024.0 / 360.0) * THRESHOLD_ANGLE)) {
    out->relay2 = true;
  }
}

void output_serial(output_t  out, status_t status)
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
    Serial.print(equilibrium);
    Serial.print("\n");
  }
}
