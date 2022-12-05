/*
# File: Output.cpp
# Author: Henry Hall
# Date: 30/11/2022
# Description: Affects the output pins dependant on various inputs.
  Outputs include 3 relays, 2 digital outputs, and an on PCB LED. 
*/

#include "Output.h"
#include "Sensors.h"
#include <avr/wdt.h>

static int R1 = 0;
static int R2 = 1;
static int R3 = 2;
static int D1 = 6;
static int D2 = 10;
static int LIGHT = 4;

void output_init(void)
{
  //Initialises output pins
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(R3, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(LIGHT, OUTPUT);
}

void updateOutput(output_t out)
{
  //Updates pins based on an output struct
  digitalWrite(R1, out.relay1);
  digitalWrite(R2, out.relay2);
  digitalWrite(R3, out.relay3);
  digitalWrite(D1, out.digital1);
  digitalWrite(D2, out.digital2);
  digitalWrite(LIGHT, out.light);
}

void led_flash(void)
{
  for (size_t i = 0; i < 5; i++) {
    wdt_reset();
    digitalWrite(LIGHT, HIGH);
    Serial.print("...\n");
    delay(100);
    digitalWrite(LIGHT, LOW);
    delay(100);
  }
}


