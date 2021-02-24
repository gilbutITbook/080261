#ifndef SteamZE08CH2O_H
#define SteamZE08CH2O_H

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <SoftwareSerial.h>
#include <DFRobotHCHOSensor.h>

class SteamZE08CH2O
{
public:
  SteamZE08CH2O(uint8_t pin);
  ~SteamZE08CH2O()
  {
    if (_hcho)
      delete _hcho;
  };

  void begin();   // 센서의 값을 초기화한다.
  void read();    // 센서의 값을 읽어온다.
  void display(); // 센서의 값을 출력한다.

  void _displayAirCondition_HCHO(float hcho);

private:
  DFRobotHCHOSensor *_hcho;

  uint8_t _pin;
  float dacHchoPPM;
};

#endif
