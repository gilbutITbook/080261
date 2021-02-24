#ifndef SteamPPD42NS_H
#define SteamPPD42NS_H

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class SteamPPD42NS
{
public:
  SteamPPD42NS(int pin);
  ~SteamPPD42NS(){
      // if (_sensor)
      //   delete _sensor;
  };

  void begin();   // 센서의 값을 초기화한다.
  void read();    // 센서의 값을 읽어온다.
  void display(); // 센서의 값을 출력한다.
  void getPM();

  void _displayAirCondition(unsigned int pm2_5);

private:
  int _ppdPin;
  unsigned long duration;
  unsigned long starttime;
  unsigned long sampletime_ms = 30000;
  unsigned long lowpulseoccupancy = 0;
  float ratio = 0;
  float concentration = 0;
  float pcsPerCF = 0;

  float dustDensity = 0;
  int cntPM;
  float avrDustDensity;
};

#endif
