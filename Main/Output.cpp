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