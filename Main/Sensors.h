#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>
#include <stdint.h>
#include <stdbool.h>
#include "Output.h"

#define THRESHOLD_ANGLE 22.5

typedef struct {
  uint16_t error;
  bool is_doorShut;
} status_t;

void sensor_init(void);


void updateSensor(status_t*);

void check_plug(status_t status, output_t* out);

void check_flow(status_t status, output_t* out);

#endif