#ifndef SteamBME280_H
#define SteamBME280_H

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Wire.h>
#include <SPI.h>

// 서울 : 1028.3
// 대구 : 1028.9
// 부산 : 1028.0
#define SEALEVELPRESSURE_HPA (1028.3) // 해면 기압 : http://www.weather.go.kr/weather/observation/currentweather.jsp


class SteamBME280
{
public:
  SteamBME280();
  ~SteamBME280(){

  };

  void begin();   // 센서의 값을 초기화한다.
  void read();    // 센서의 값을 읽어온다.
  void display(); // 센서의 값을 출력한다.

private:
  Adafruit_BME280 bme;
  float tremperature;
  uint32_t humidity;

  float pressure;
  float calcAltitude;
};

#endif
