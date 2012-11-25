/*
  SFPddm.h - SFPddm library for Wiring - description
  Copyright (c) 2006 John Doe.  All right reserved.
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
    void begin(void);
    uint8_t checkSFP(void);
    uint8_t errorcheck(void);
    uint8_t readDMT(void);
    void setControlSFP(uint8_t control);
    uint8_t getControlSFP(void);
    void getMeasurementsSFP(uint8_t *data);
    void getAlarmsSFP(uint8_t *abuffer);
    void getWarningsSFP(uint8_t *wbuffer);

  // library-accessible "private" interface
  private:
    void processing(void);
};

#endif

