/*
# File: EEPROM.h
# Author: Henry Hall
# Date: 30/11/2022
# Description: Header file for the EEPROM source file. 
*/

#ifndef EEPROM_H
#define EEPROM_H

#include <Arduino.h>
#include <stdint.h>
#include "Output.h"
#include "Sensors.h"

void Sensor_toEEPROM(status_t);

void SPI_send(status_t);  

void SPI_init(void);

#endif