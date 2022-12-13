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

static double degree_toBits(void)
{
  double num;
  num = (THRESHOLD_ANGLE * 1024.0 / 360.0);
  return num;
}

double bits_toDegree(int n)
{
  double num;
  num = n * 360.0 / 1024.0;
  return num;
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
    out->light = true;
  }
}

void check_flow(status_t status, output_t* out)
{
  //From a status struct checks to see if the flow has exceded the threshold and updates the out struct
  if (status.error > degree_toBits()) {
    out->light = true;
  }
}


