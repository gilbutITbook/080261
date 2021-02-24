#ifndef SteamCCS811_H
#define SteamCCS811_H

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "Adafruit_CCS811.h"

class SteamCCS811
{
public:
  SteamCCS811();
  ~SteamCCS811()
  {
    if (_ccs811)
      delete _ccs811;
  };

  void begin();   // 센서의 값을 초기화한다.
  void read();    // 센서의 값을 읽어온다.
  void display(); // 센서의 값을 출력한다.

private:
  Adafruit_CCS811 *_ccs811;
  uint16_t _eCo2;

  uint16_t _tvoc; // ppb
  float _mg_m3;   // mg/m3

  float _temp;

  void _displayAirCondition_TVOC(uint16_t ppb);
};

#endif
