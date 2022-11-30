#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>
#include <stdint.h>

typedef struct {
  uint16_t error;
  bool is_doorShut;
} status_t;

void sensor_init(void);

int callibrate(void);

status_t update(status_t);

#endif