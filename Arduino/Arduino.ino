/*
# File: HSS Automation.INO
# Author: Henry Hall
# Date: 30/11/2022
# Description: Provides processing and control of sensor data 
    from a proximity sensor and potentiometer in order to 
    detect faults in a Yardmaster Horizontal Screw Separator. 
*/

#include <stdint.h>
#include "Pacer.h"

int R1 = 0;
int R2 = 1;
int R3 = 2;
int D1 = 6;
int D2 = 10;
int D3 = 7;
int PROX = 3;
int POT = 15;
int LIGHT = 4;
int ADJ = 14;

static int equilibrium;

#define PACER_FREQUENCY 500


void callibrate(void)
{
  //Finds the initial equilibrium angle of the paddle
  equilibrium = analogRead(POT);
}

int error(void)
{
  return abs(equilibrium - analogRead(POT));
}

bool doors_shut(void)
{
  return (digitalRead(PROX) == HIGH);
}

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(R3, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(LIGHT, OUTPUT);
  pinMode(D3, INPUT);
  pinMode(PROX, INPUT);
  pinMode(POT, INPUT);
  pinMode(ADJ, INPUT);
  callibrate();
  pacer_init(PACER_FREQUENCY);
}

void loop()
{
  // put your main code here, to run repeatedly:
  pacer_wait();

}
