/*
    Arduino library for DS1631

    Reference Datasheet: https://datasheets.maximintegrated.com/en/ds/DS1631-DS1731.pdf

    Author: DJMarlow - https://github.com/DJMarlow
    Date: 2020-7-18
*/

#ifndef DS1631_H
#define DS1631_H

#include <Arduino.h>
#include <Wire.h>

class DS1631 {
public:

  DS1631();
  DS1631(uint8_t A0, uint8_t A1, uint8_t A2);

  void begin();
  void startConvert();
  uint8_t finishedConvert();
  float getTempC();
  float getTempF();

private:
  //I2C address
  int _address;
};

#endif
