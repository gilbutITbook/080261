#ifndef SteamGUVA12SD_H
#define SteamGUVA12SD_H

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class SteamGUVA12SD
{
public:
  SteamGUVA12SD(uint8_t pin);
  ~SteamGUVA12SD(){};

  void begin();   // 센서의 값을 초기화한다.
  void read();    // 센서의 값을 읽어온다.
  void display(); // 센서의 값을 출력한다.
  int getUVIndex();
  String getUVDangerOfExposure();

private:
  uint8_t _pin;

  //float workingVoltage = 5.0;  // 5v

  int sensorUVIndex;
  float sensorVoltage;
  float sensorValue;
};

#endif
