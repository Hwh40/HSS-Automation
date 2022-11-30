#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>

typedef struct {
  uint8_t error;
  bool is_doorShut;
} status_t;

void sensor_init(void);

int callibrate(void);


#endif