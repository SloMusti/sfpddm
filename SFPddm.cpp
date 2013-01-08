/*
  SFPddm.cpp - SFPddm library
*/

// Includes

#include "Arduino.h"
#include "SFPddm.h"
#include "inttypes.h"
#include "I2C.h"

// Definitions

#define INFOADDR    0x50 // addr A0/1
#define DDMADDR     0x51 // addr A2/3


// Private variables

// error variable
uint8_t error;
// calibration data variables
uint8_t cal_general[4]; 
float cal_rxpower[5]; 
//raw measurement buffer
uint8_t raw_buffer[];
//measurement values
int16_t temperature;
uint16_t voltage;
uint16_t TXcurrent;
uint16_t TXpower;
uint16_t RXpower;
uint16_t alarms;
uint16_t warnings;
//supported modes flags
uint8_t supported;
//contains register A0/92




// Constructor /////////////////////////////////////////////////////////////////

SFPddm::SFPddm()
{
    //reset error code
    error=0x00;
}

// Public Methods //////////////////////////////////////////////////////////////

// The function initializes the communication, checks if the module is present, retrieves necessary information
uint8_t SFPddm::begin(void){
  I2c.begin();
  I2c.pullup(true);
  // enable timeout
  
  // test if device is present and read modes
  error|=I2c.read(INFOADDR,92, 1, (uint8_t*)&supported); 
  // stop if not present
  if(error){
    return error;
  }
  // if DDM mode is supported and externally callibrated
  if(supported&0x08){
    getCalibrationData();
  }
  
  return error;
}

// The function returns the 128 bytes of information at address 0xA0
void SFPddm::getRawInfo(uint8_t addr, uint8_t *data){
//implement when required
}


// The function returns an OR or all error codes detected, should be 0x00 if data is to be valid
// Can be used to check if the module is present
uint8_t SFPddm::getStatus(){
  // Do a test write to register pointer.
  error|=I2c.write(INFOADDR, 0x00);
  return error;
}

// The function acquires the measurements and returns an error code if sth went wrong, 0x00 is OK
uint8_t SFPddm::getMeasurements(){
  int i;
  //store measurements
  byte *pMeas = (byte*)&raw_meas;
  //read diagnostic measurements registers 96-105 of 0xA2
  error|=I2c.read(DDMADDR, 96, 10, pMeas);
  
  //calibration if external data
  if(supported&0x08){
    //calibrate measurements
    for(i=0;i<4;i++){
        //data[i]=calibrateMeasurement(meas[i], meascal[2*i], meascal[2*i+1]);
    }
    //calibrate RX power separately
    //data[4]=calibrateRXpower(meas[4], &rxpowercal[0]);
  
  }
  else{
    //return data
  }
  
return error;
}

// The function gets the value of the control register (0xA2 memory, register 110)
uint8_t SFPddm::getControl(){
  uint8_t status;
  // read A3/110
  error|=I2c.read(DDMADDR,110, 1, &status);
  return status;
}
// The function sets the value of the control register (0xA2 memory, register 110)
void SFPddm::setControl(uint8_t data){
  //write the byte (not all bits are writable!)
  error|=I2c.write(DDMADDR,110, data&0xFF);
}

// The function returns the temperature , signed
int16_t SFPddm::getTemperature(){
  return temperature;
}

// The function returns the supply voltage , unsigned
uint16_t SFPddm::getVoltage(){
  return voltage;
}

// The function returns the supply current , unsigned
uint16_t SFPddm::getTXcurrent(){
 return TXcurrent;
}

// The function returns the TX power , unsigned
uint16_t SFPddm::getTXpower(){
  return TXpower;
}

// The function returns the RX power , unsigned
uint16_t SFPddm::getRXpower(){
  return RXpower;
}

// Private Methods /////////////////////////////////////////////////////////////

// The function retrieves callibration values
void SFPddm::getCalibrationData(){
  // buffer for data
  uint8_t calData[36];
  
  //read data
  error|=I2c.read(DDMADDR, 56, 36, &calData[0]);
  //loop variable
  int i;
  
  //writing binary to the float register using pointers
  byte *pRXcal = (byte*)&cal_rxpower;
  
  for(i=0;i<20;i++){
    //this goes from 0xA2 SFP bytes 56-75
    //write data to pointer location and decrement pointer
    //beware, low byte is LSB in Arduino
    *pRXcal =calData[19-i];
    pRXcal++;
  }
   
  //writing to uint16_t register using pointers
  //creating a pointer
  byte *pCal = (byte*)&cal_general;
   
  for(i=20;i<36;i+=2){
  //this goes from 0xA2 SFP bytes 76-91
  //write data to pointer location and increment pointer
    *pCal++ =calData[i+1];
    *pCal++ =calData[i];
  }
}

// This function calibrates all values except RX power and temperature
int16_t SFPddm::calibrateMeasurement(int16_t rawdata, uint16_t slope, int16_t offset)
{
  int32_t temporary = slope;
  temporary *= rawdata;
  //safe to use signed for all function, values do not overflow
  int16_t result = (temporary>>8 + offset);
  
  return result;
}

uint16_t SFPddm::calibrateRXpower(uint16_t rawdata, float *calibrationRX)
{
  uint16_t result;
  float temporary;
  
  temporary = calibrationRX[4] * rawdata;
  temporary += calibrationRX[3] * rawdata;
  temporary += calibrationRX[2] * rawdata;
  temporary += calibrationRX[1] * rawdata;
  temporary += calibrationRX[0]; //offset
  
  //Serial.print("RXcalibrated: ");
  //Serial.println(temporary);

  return (int16_t)temporary;
}
