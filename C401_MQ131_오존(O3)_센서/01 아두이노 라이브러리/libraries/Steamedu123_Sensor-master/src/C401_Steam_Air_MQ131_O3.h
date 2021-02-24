#ifndef SteamMQ131_H
#define SteamMQ131_H

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class SteamMQ131
{
public:
  SteamMQ131(uint8_t aoutPin);
  ~SteamMQ131(){

  };

  void begin();                    // 센서의 값을 초기화한다.
  void read(int _temp, int _humi); // 센서의 값을 읽어온다.
  void display();                  // 센서의 값을 출력한다.

  void setTempHumi(int _temp, int _humi);

private:
  uint8_t _aoutPin;
  float _ppm;
  float _ppb;
  float _mg_m3;
  float _ug_m3;

  void _displayAirCondition_O3(float ppm);
};

#endif
