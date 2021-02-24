#ifndef SteamQSFS01_H
#define SteamQSFS01_H

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class SteamQSFS01
{
public:
  SteamQSFS01(uint8_t _pin);
  ~SteamQSFS01(){};

  void begin();   // 센서의 값을 초기화한다.
  void read();    // 센서의 값을 읽어온다.
  void display(); // 센서의 값을 출력한다.

private:
  uint8_t _pin;

  int sensorValue;
  float outvoltage;
  float ms;
  int level;

  void _displayAirCondition(float speed);
};

#endif
