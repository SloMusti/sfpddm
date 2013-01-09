/*
  SFPddm.h - SFPddm library 
  
Copyright 2013 Luka Mustafa - Musti, musti@wlan-si.net

This file is part of the SFPddm library for Arduino

The SFPddm library is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by the
Free Software Foundation, either version 3 of the License, or (at your
option) any later version.

The SFPddm library is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with the SFPddm library. If not, see http://www.gnu.org/licenses/.

*/

// ensure this library description is only included once
#ifndef SFPddm_h
#define SFPddm_h

#include "Arduino.h"

// library interface description
class SFPddm
{
  // user-accessible "public" interface
  public:
    SFPddm(void);
    uint8_t begin(void);
    void getRawInfo(uint8_t addr, uint8_t *data);
    uint8_t getStatus();
    uint8_t getSupported();
    uint8_t readMeasurements();
    uint8_t getControl();
    void setControl(uint8_t data);
    int16_t getTemperature();
    uint16_t getVoltage();
    uint16_t getTXcurrent();
    uint16_t getTXpower();
    uint16_t getRXpower();
    uint16_t getAlarms();
    uint16_t getWarnings();

  // library-accessible "private" interface
  private:
    void getCalibrationData();
    uint16_t calibrateMeasurement(uint16_t rawdata, uint16_t slope, int16_t offset);
    int16_t calibrateTemperature(int16_t rawdata, uint16_t slope, int16_t offset);
    uint16_t calibrateRXpower(uint16_t rawdata, float *calibrationRX);
};

#endif

