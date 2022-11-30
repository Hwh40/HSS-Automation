#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>

void sensor_init(void);

void callibrate(void);

int error(void);

bool doors_shut(void);

#endif