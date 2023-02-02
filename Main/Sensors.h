/*
# File: Sensors.h
# Author: Henry Hall
# Date: 30/11/2022
# Description: Header file for the sensors source file. 
*/

#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>
#include <stdint.h>
#include <stdbool.h>
#include "Output.h"

typedef struct {
  uint16_t error;
  bool is_doorShut;
  uint16_t sensitivity;
} status_t;

void sensor_init(void);

void updateSensor(status_t*);

void check_plug(status_t, output_t*);

void check_flow(status_t, output_t*, uint16_t, uint16_t);

#endif