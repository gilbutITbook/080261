#ifndef SteamDGSSO2_H
#define SteamDGSSO2_H

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif


class SteamDGSSO2
{
public:
  SteamDGSSO2();
  ~SteamDGSSO2(){
      // if (_sensor)
      //   delete _sensor;
  };

  void begin();   // 센서의 값을 초기화한다.
  void read();    // 센서의 값을 읽어온다. 
  void display(); // 센서의 값을 출력한다.

  void blinkLed();

private:
  
  bool const setupSensor = false;
  String const setupBarcode = "042418010239 110601 SO2 1805 29.32";
  bool calibratedZero = false;

  long ppb;
  float ppm;
  long temp;
  long rh;
  String timeRunning;  
  void _displayAirCondition_SO2(float ppb);

  //int _rxPin, _txPin;  
};

#endif
