#include "DS1631.h"

#define START 0xEE
#define STOP 0x22
#define GET_TEMP 0xAA
#define CONFIG 0xAC

DS1631::DS1631() {
}

DS1631::DS1631(uint8_t A0, uint8_t A1, uint8_t A2) {
  _address = (0x48 | A2 << 2 | A1 << 1 | A0);
}

void DS1631::begin(){
  Wire.begin();
  Wire.beginTransmission(_address);
  Wire.write(STOP);
  Wire.endTransmission();
  Wire.beginTransmission(_address);
  Wire.write(CONFIG);
  Wire.write((0 << 6 | 0 << 5 | 0 << 4 | 0 << 1 | 1));
  Wire.endTransmission();
}

void DS1631::startConvert(){
  Wire.beginTransmission(_address);
  Wire.write(START);
  Wire.endTransmission();
}

uint8_t DS1631::finishedConvert(){
  uint8_t i = 0;

  Wire.beginTransmission(_address);
  Wire.write(CONFIG);
  Wire.endTransmission(false);
  Wire.requestFrom(_address, 1);
  while (Wire.available())
  {
      i = Wire.read() & 0x80;
  }

  return i;
}

float DS1631::getTempC() {
  uint8_t msb = 0;
  uint8_t lsb = 0;
  float t = 0.0;

  Wire.beginTransmission(_address);
  Wire.write(GET_TEMP);
  Wire.endTransmission(false);
  Wire.requestFrom(_address, 2);
  if (2 <= Wire.available()) {
      msb = Wire.read();
      lsb = Wire.read();
  }

  t = (float) msb;
  if (lsb & 0x80){
    t += 0.5;
  }
  if (msb & 0x80){
    t -= 256;
  }
  
  return t;  
}

float DS1631::getTempF() {
  uint8_t msb = 0;
  uint8_t lsb = 0;
  float t = 0.0;

  Wire.beginTransmission(_address);
  Wire.write(GET_TEMP);
  Wire.endTransmission(false);
  Wire.requestFrom(_address, 2);
  if (2 <= Wire.available()) {
      msb = Wire.read();
      lsb = Wire.read();
  }

  t = (float) msb;
  if (lsb & 0x80){
    t += 0.5;
  }
  if (msb & 0x80){
    t -= 256;
  }
  
  float tF = (t * 9/5) + 32;
  
  return tF;  
}
