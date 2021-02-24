#ifndef SteamGP2Y1010AU0F_H
#define SteamGP2Y1010AU0F_H

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class SteamGP2Y1010AU0F
{
public:
  SteamGP2Y1010AU0F(uint8_t sharpLEDPin, uint8_t sharpVoPin);
  ~SteamGP2Y1010AU0F(){};

  void begin();   // 센서의 값을 초기화한다.
  bool read();    // 센서의 값을 읽어온다.
  void display(); // 센서의 값을 출력한다.

  void _calcVoltage(float Vo);
  void _calcDustDensity(float Vo);

  void _displayAirCondition_PM25(unsigned int pm2_5);

private:
  float dustDensity = 0;

  uint8_t _sharpLEDPin;
  uint8_t _sharpVoPin;

  int _samplingTime = 280; // Wait 0.28ms before taking a reading of the output voltage as per spec.
  int _sleepTime = 9680;   // Wait for remainder of the 10ms cycle = 10000 - 280 - 100 microseconds.
  int _deltaTime = 40;
  float _VCC = 5.0;

  float outVoltage;
};

#endif
