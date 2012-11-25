/*
  SFPddm.cpp - SFPddm library for Wiring - implementation
  Copyright (c) 2006 John Doe.  All right reserved.
*/

#include "Arduino.h"
#include "SFPddm.h"
#include "inttypes.h"
#include "I2C.h"

#define INFOADDR    0x50
#define DDMADDR     0x51  

uint8_t error;
boolean addrMode;
// Constructor /////////////////////////////////////////////////////////////////

SFPddm::SFPddm()
{
    //reset error code
    error=0x00;
}

// Public Methods //////////////////////////////////////////////////////////////
void SFPddm::begin(void)
{
  I2c.begin();
  I2c.pullup(true);
  Serial.println("SFPddm lib init.");
  //I2c.scan();
}

// Method to test is SFP is present
uint8_t SFPddm::checkSFP(void)
{
  Serial.print("Checking for SFP.");
  error|=I2c.write(INFOADDR, 0x00);
  return error;
}

// Method to check for errors, run after all other
uint8_t SFPddm::errorcheck(void)
{
  Serial.print("Printing errors.");
  return error;
}

// Method to read 0xA0 memory register 92 for info on DDM
// Diagnostic Monitor Type
uint8_t SFPddm::readDMT(void)
{
  uint8_t data;
  error|=I2c.read(INFOADDR,92, 1, &data);
  addrMode=(data>>2)&0x01;
  Serial.print("REG92:");
  Serial.println(data,HEX);
  return data;
}

// Method to control and read 0xA2 memory register 110
// Optional Status/Control Bits
void SFPddm::setControlSFP(uint8_t control)
{
  //write control
  error|=I2c.write(DDMADDR,110, control&0xFF);
  
  Serial.print("setDdmREG110:");
  Serial.println(control,HEX);
}

uint8_t SFPddm::getControlSFP(void){
  uint8_t status;
  //read back to get other bits
  error|=I2c.read(DDMADDR,110, 1, &status);
  // add optional validation of write
  
  Serial.print("getDdmREG110:");
  Serial.println(status,HEX);
  
  return status;
}

void SFPddm::getMeasurementsSFP(uint8_t *data){
  int i;
  //local buffer
  uint8_t measurements[10];
  //read diagnostic measurements registers 96-105 of 0xA2
  error|=I2c.read(DDMADDR, 96, 10, &measurements[0]);
  // do processing if required
  
  // return data
  Serial.print("rawmeas:");
  for(i=0;i<10;i++){
    data[i]=measurements[i];
    Serial.print(data[i],HEX);
    Serial.print(",");
  }
  Serial.println("");
  // return status
}

void SFPddm::getAlarmsSFP(uint8_t *abuffer){
  //read alarms from 112,113 of 0xA2
  error|=I2c.read(DDMADDR, 112, 2, &abuffer[0]);
  
  Serial.print("rawalarms:");
  Serial.print(abuffer[0],HEX);
  Serial.print(",");
  Serial.println(abuffer[1],HEX);
}

void SFPddm::getWarningsSFP(uint8_t *wbuffer){
  //read warnings from 116,117 of 0xA2
  error|=I2c.read(DDMADDR, 116, 2, &wbuffer[0]);
  
  Serial.print("rawwarnings:");
  Serial.print(wbuffer[0],HEX);
  Serial.print(",");
  Serial.println(wbuffer[1],HEX);
}


// Private Methods /////////////////////////////////////////////////////////////

void SFPddm::processing(void)
{
}

