#ifndef SteamMICS4514_H
#define SteamMICS4514_H

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class SteamMICS4514
{
public:
  SteamMICS4514(uint8_t prePin, uint8_t vnoxPin, uint8_t vredPin);
  ~SteamMICS4514(){};

  void begin(); // 센서의 값을 초기화한다.
  void read();  // 센서의 값을 읽어온다.
  void _readNO2();
  void _readCO();
  void display(); // 센서의 값을 출력한다.

  void displaySensor(String str, float c);

private:
  int vnox_value = 0;
  int vred_value = 0;

  float ppmNO2 = 0; //ppb NO2
  float ppmCO = 0;  //ppm CO

  int Rload_no2 = 22000; // 저항
  int Rload_co = 47000;  // 저항

  float vout_no2 = 0; //output voltage
  float vout_co = 0;  //output voltage
  float Rs_no2 = 0;   //Sensor Resistance
  float Rs_co = 0;    //Sensor Resistance

  uint8_t _prePin;
  uint8_t _vnoxPin;
  uint8_t _vredPin;

  void _displayAirCondition_CO(float ppm);
  void _displayAirCondition_NO2(float ppm);
};

#endif