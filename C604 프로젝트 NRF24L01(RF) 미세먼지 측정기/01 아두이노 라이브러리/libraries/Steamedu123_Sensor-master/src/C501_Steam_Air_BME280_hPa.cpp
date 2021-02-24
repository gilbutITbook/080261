/*
  BME280 library
  STEMEDU123 license
  written by SteamLabs
  homepage:  http://www.steamedu123.com 
*/

#include "C501_Steam_Air_BME280_hPa.h"

SteamBME280::SteamBME280() {}

/**
 * @함수명    : begin
 * @설명      : 센서를 초기화 한다. 
*/
void SteamBME280::begin()
{
  Serial.println("BME280(Barometer) Sensor");
  Serial.println("Ready.....");
  Serial.println("--------------------------------");
  
  if (!_bme280.init())
  {
    Serial.println("Device error!");
  }
}

/**
 * @함수명    : read
 * @설명      : 센서의 값을 읽어온다
*/
void SteamBME280::read()
{
  tremperature = _bme280.getTemperature();
  humidity = _bme280.getHumidity();

  pressure = _bme280.getPressure();
  calcAltitude = _bme280.calcAltitude(pressure);
}

/**
 * @함수명    : display
 * @설명      : 센서의 값을 출력한다. 
*/
void SteamBME280::display()
{

  //get and print atmospheric pressure data
  Serial.print("Pressure: ");
  Serial.print(pressure);
  Serial.println("Pa");

  //get and print altitude data
  Serial.print("Altitude: ");
  Serial.print(calcAltitude);
  Serial.println("m");
  
  //get and print temperatures
  Serial.print("Temp: ");
  Serial.print(tremperature);
  Serial.println("C"); //The unit for  Celsius because original arduino don't support special symbols

  //get and print humidity data
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println("%");  

  Serial.println("");
}

float SteamBME280::getTemp(){
  return tremperature;
}

uint32_t SteamBME280::getHumidity(){
  return humidity;
}

uint32_t SteamBME280::gethPa(){
  return pressure;
}
 
