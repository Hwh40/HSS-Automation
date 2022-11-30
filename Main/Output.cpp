#include "Output.h"

static int R1 = 0;
static int R2 = 1;
static int R3 = 2;
static int D1 = 6;
static int D2 = 10;
static int LIGHT = 4;

void output_init(void)
{
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(R3, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(LIGHT, OUTPUT);
}

void light_on(void)
{
  digitalWrite(LIGHT, HIGH);
}

void light_off(void)
{
  digitalWrite(LIGHT, LOW);
}

void updateOutput(output_t out)
{
  digitalWrite(R1, out.relay1);
  digitalWrite(R2, out.relay2);
  digitalWrite(R3, out.relay3);
  digitalWrite(D1, out.digital1);
  digitalWrite(D2, out.digital2);
  digitalWrite(LIGHT, out.light);
}