#include "Sensors.h"
#include "Output.h"
#include <stdint.h>

static int equilibrium;
static int PROX = 3;
static int POT = 15;
static int ADJ = 14;
static int D3 = 7;
static bool is_on = false;

void sensor_init(void)
{
  pinMode(PROX, INPUT);
  pinMode(POT, INPUT);
  pinMode(D3, INPUT);
  pinMode(ADJ, INPUT);
}

void callibrate(void)
{
  //Finds the initial equilibrium angle of the paddle
  equilibrium = analogRead(POT);
}

static uint16_t error(void)
{
  return abs(equilibrium - analogRead(POT));
}

static bool doors_shut(void)
{
  return (digitalRead(PROX) == HIGH);
}

status_t updateSensor(status_t status)
{
  status.error = error();
  status.is_doorShut = doors_shut();
  return status;
}

void check_plug(status_t status, output_t* out)
{
  if (status.is_doorShut == false && !is_on) {
    is_on = true;
  }
  if (status.is_doorShut == true && is_on) {
    out->relay1 = true;
  }
}

void check_flow(status_t status, output_t* out)
{
  if (status.error > ((1024.0 / 360.0) * THRESHOLD_ANGLE)) {
    out->relay2 = true;
  }
}
