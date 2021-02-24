#ifndef SteamMICS6814_H
#define SteamMICS6814_H

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <Wire.h>
#include <MutichannelGasSensor.h>

class SteamMICS6814
{
public:
  SteamMICS6814();
  ~SteamMICS6814()
  {  
  };

  void begin();   // 센서의 값을 초기화한다.
  void read();    // 센서의 값을 읽어온다. 
  void display(); // 센서의 값을 출력한다.

  void displaySensor(String str, float c);

private:
  MutichannelGasSensor _sensor;

  float _co;     // Carbon monoxide CO 1 – 1000ppm
  float _no2;    // Nitrogen dioxide NO2 0.05 – 10ppm
  float _c2h5oh; // Ethanol C2H6OH 10 – 500ppm
  float _h2;     // Hydrogen H2 1 – 1000ppm
  float _nh3;    // Ammonia NH3 1 – 500ppm
  float _ch4;    // Methane CH4 >1000ppm
  float _c3h8;   // Propane C3H8 >1000ppm
  float _c4h10;  // Iso-butane C4H10 >1000ppm


  void _displayAirCondition_CO(float ppm);
  void _displayAirCondition_NH3(float ppm);
  void _displayAirCondition_NO2(float ppm);

};

#endif