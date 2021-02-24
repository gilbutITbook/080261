#ifndef SteamMD0550_H
#define SteamMD0550_H

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class SteamMD0550
{
public:
  SteamMD0550(uint8_t rvPin, uint8_t tmpPin);
  ~SteamMD0550(){};

  void begin();   // 센서의 값을 초기화한다.
  void read();    // 센서의 값을 읽어온다.
  void display(); // 센서의 값을 출력한다.

  int BeaufortWindScale();
  void _displayAirCondition(float speed);

private:
  uint8_t _rvPin, _tmpPin;

  const float zeroWindAdjustment = .2;

  int TMP_Therm_ADunits;
  float RV_Wind_ADunits;

  float RV_Wind_Volts;
  unsigned long lastMillis;
  int TempCtimes100;
  float zeroWind_ADunits;
  float zeroWind_volts;
  float WindSpeed_MPH;
};

#endif
