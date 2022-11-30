#ifndef OUTPUT_H
#define OUTPUT_H

#include <Arduino.h>

typedef struct {
  bool relay1;
  bool relay2;
  bool relay3;
  bool digital1;
  bool digital2;
  bool light;
} output_t;

void output_init(void);

void light_on(void);

void light_off(void);

void updateOutput(output_t out);

#endif