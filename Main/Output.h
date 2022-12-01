/*
# File: Output.h
# Author: Henry Hall
# Date: 30/11/2022
# Description: The header file for the output source file.
*/

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

void updateOutput(output_t out);

#endif