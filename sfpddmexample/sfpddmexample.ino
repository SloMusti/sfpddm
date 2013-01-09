/*
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
#include "Arduino.h"
#include <SFPddm.h>
#include "I2C.h"

// Creating an object of SFP DDM library
SFPddm sfp;

byte supp;

// Setup
void setup()
{
  Serial.begin(9600);
  
  //initialize
  Serial.print("Initialized 0x");
  byte err = sfp.begin();
  Serial.println(err,HEX);
  
  //get supported operations
  supp = sfp.getSupported();
  Serial.print("Supported 0x");
  Serial.println(supp,HEX);
  
  
}

// Main operation loop
void loop(){

  if(supp&0x40){
    //readMeasurements from the SFP
    sfp.readMeasurements();
    
    Serial.print("Temperature: ");
    Serial.print(sfp.getTemperature()/256,DEC);
    Serial.println(" C");
    
    Serial.print("Voltage: ");
    Serial.print(sfp.getVoltage(),DEC);
    Serial.println(" uV");
    
    Serial.print("TX current: ");
    Serial.print(sfp.getTXcurrent(),DEC);
    Serial.println(" uA");
    
    Serial.print("TX power: ");
    Serial.print(sfp.getTXpower(),DEC);
    Serial.println(" uW");
    
    Serial.print("RX power: ");
    Serial.print(sfp.getRXpower(),DEC);
    Serial.println(" uW");
  }
  delay(1000);
}
