#ifndef SteamBME280_H
#define SteamBME280_H

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "Seeed_BME280.h"
#include <Wire.h>

class SteamBME280
{
public:
  SteamBME280();
  ~SteamBME280(){
  };

  void begin();
  void read();
  void display();

  float getTemp();
  uint32_t getHumidity();
  uint32_t gethPa();

private:
  BME280 _bme280;
  float tremperature;
  uint32_t humidity;

  uint32_t pressure;
  float calcAltitude;
};

#endif
