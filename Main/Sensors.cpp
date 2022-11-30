#include "Sensors.h"

static int equilibrium;
static int PROX = 3;
static int POT = 15;
static int ADJ = 14;
static int D3 = 7;

void sensor_init(void)
{
  pinMode(PROX, INPUT);
  pinMode(POT, INPUT);
  pinMode(D3, INPUT);
  pinMode(ADJ, INPUT);
}

int callibrate(void)
{
  //Finds the initial equilibrium angle of the paddle
  equilibrium = analogRead(POT);
  return equilibrium;
}

static int error(void)
{
  return abs(equilibrium - analogRead(POT));
}

static bool doors_shut(void)
{
  return (digitalRead(PROX) == HIGH);
}

void update(status_t status)
{
  status.error = error();
  status.is_doorShut = doors_shut();
}



