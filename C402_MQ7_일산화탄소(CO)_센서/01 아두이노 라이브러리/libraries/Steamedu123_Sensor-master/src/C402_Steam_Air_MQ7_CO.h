#ifndef SteamMQ7_H
#define SteamMQ7_H

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "MQ7.h"

class SteamMQ7
{
public:
  SteamMQ7(uint8_t aoutPin);
  ~SteamMQ7()
  {
    if (mq7)
      delete mq7;
  };

  void begin();   // 센서의 값을 초기화한다.
  void read();    // 센서의 값을 읽어온다.
  void display(); // 센서의 값을 출력한다.

private:
  MQ7 *mq7;

  uint8_t _aoutPin;
  float _ppm;

  void _displayAirCondition_CO(float ppm);
};

#endif
