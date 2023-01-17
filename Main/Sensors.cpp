/*
# File: Sensors.cpp
# Author: Henry Hall
# Date: 30/11/2022
# Description: Reads and proccesses the sensor data
  from a proximity sensor and a potentiometer. 
*/

#include "Sensors.h"
#include "Output.h"
#include <math.h>
#include <stdint.h>

#define ANGLE_LOW 30
#define ANGLE_HIGH 60
#define THRESHOLD 1000

static double equilibrium;
static uint16_t period = 0;
static int PROX = 3;
static int S1 = 15;
static int S2 = 14;
static int D3 = 7;
static bool is_on = false;

static double sensor_read(void)
{
  //Reads two hall effect sensors and calculates the angle travelled 
  double tesla1;
  double tesla2;
  tesla1 = analogRead(S1);
  tesla2 = analogRead(S2);
  tesla1 = (tesla1 - 310) * 100 / 310;
  tesla2 = (tesla2 - 310) * 100 / 310;
  double angle = atan2(tesla2, tesla1);
  return (angle * 180 / 3.14159);
}

static void callibrate(void)
{
  //Finds the initial equilibrium angle of the paddle
  equilibrium = sensor_read();
}

static uint16_t error(void)
{
  //Finds the error between the current paddle position and the equilibrium
  return abs(equilibrium - sensor_read());
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
  pinMode(S1, INPUT);
  pinMode(S1, INPUT);
  pinMode(D3, INPUT);
  period = 0;
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
    out->light = true;
  }
}

void check_flow(status_t status, output_t* out)
{
  //From a status struct checks to see if the flow has exceded the threshold and updates the out struct
  if (status.error > ANGLE_HIGH) {
    out->relay3 = true;
    out->light = true;
  }
  if (period > THRESHOLD) {
    out->relay2 = true;
    out->light = true;
  }
  if (status.error > ANGLE_LOW && status.error < ANGLE_HIGH) {
    period++;
  } else if (status.error <= ANGLE_LOW) {
    period = 0;
  }
}


