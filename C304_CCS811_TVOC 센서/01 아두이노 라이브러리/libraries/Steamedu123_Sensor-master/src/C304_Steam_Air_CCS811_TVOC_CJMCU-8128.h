#ifndef SteamCJMCU8128_H
#define SteamCJMCU8128_H

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <Wire.h>
#include <SPI.h>

#include <Adafruit_BMP280.h>
#include "Adafruit_CCS811.h"
#include "Adafruit_Si7021.h"

class SteamCJMCU8128
{
public:
  SteamCJMCU8128();
  ~SteamCJMCU8128(){};

  void begin();   // 센서의 값을 초기화한다.
  void read();    // 센서의 값을 읽어온다.
  void display(); // 센서의 값을 출력한다.

private:
  Adafruit_CCS811 ccs;
  Adafruit_Si7021 si7021;
  Adafruit_BMP280 bmp; // I2C
  //Adafruit_BMP280 bmp(BMP_CS); // hardware SPI
  //Adafruit_BMP280 bmp(BMP_CS, BMP_MOSI, BMP_MISO,  BMP_SCK);

  float _tempCCS811;
  uint16_t _eCO2;
  uint16_t _tvoc;

  float _bmpTemp;
  float _bmpPressure;
  float _bmpAltitude;

  float _si7021Temp;
  float _si7021Humi;

  void _begin_CCS811();
  void _read_CCS811();
  void _display_CCS811();

  void _begin_SI7021();
  void _read_SI7021();
  void _display_SI7021();

  void _begin_BMP280();
  void _read_BMP280();
  void _display_BMP280();

  void _displayAirCondition_TVOC(uint16_t ppb);
};

#endif
