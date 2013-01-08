/*
  SFPddm.h - SFPddm library 
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
    uint8_t getMeasurements();
    uint8_t getControl();
    void setControl(uint8_t data);
    int16_t getTemperature();
    uint16_t getVoltage();
    uint16_t getTXcurrent();
    uint16_t getTXpower();
    uint16_t getRXpower();
    
    
    uint8_t checkSFP(void);
    uint8_t errorcheck(void);
    uint8_t readDMT(void);
    void setControlSFP(uint8_t control);
    uint8_t getControlSFP(void);
    void getMeasurementsSFP(uint16_t *data);
    void getAlarmsSFP(uint8_t *abuffer);
    void getWarningsSFP(uint8_t *wbuffer);

  // library-accessible "private" interface
  private:
    void getCalibrationData();
    int16_t calibrateMeasurement(int16_t rawdata, uint16_t slope, int16_t offset);
    uint16_t calibrateRXpower(uint16_t rawdata, float *calibrationRX);
};

#endif

