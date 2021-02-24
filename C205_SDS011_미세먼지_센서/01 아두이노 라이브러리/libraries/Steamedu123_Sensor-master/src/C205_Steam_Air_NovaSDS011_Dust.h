#ifndef SteamNovaSDS011_H
#define SteamNovaSDS011_H

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <SDS011.h>

class SteamNovaSDS011
{
public:
  SteamNovaSDS011(int rxPin, int txPin);
  ~SteamNovaSDS011(){};

  void begin();
  void read();
  void display();

  void _displayAirCondition_PM25(unsigned int pm2_5);
  void _displayAirCondition_PM10(unsigned int pm10);

private:
  int _rxPin;
  int _txPin;

  float pm10, pm25;
  int error;

  SDS011 _novasds011;
};

#endif
