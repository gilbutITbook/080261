/*
  NOVA SDS011 library
  STEMEDU123 license
  written by SteamLabs
  homepage:  http://www.steamedu123.com   
  naver cafe : https://cafe.naver.com/arduinosensor/book5108749/50
  email : steamedu123@gmail.com
*/

#include "C205_Steam_Air_NovaSDS011_Dust.h"

SteamNovaSDS011::SteamNovaSDS011(int rxPin, int txPin)
{
  _rxPin = rxPin;
  _txPin = txPin;
}

/**
 * @함수명    : begin
 * @설명      : 센서를 초기화 한다. 
*/
void SteamNovaSDS011::begin()
{
  Serial.println("Nova SDS011 Sensor");
  Serial.println("Ready.....");
  Serial.println("--------------------------------");

  _novasds011.begin(_rxPin, _txPin);
}

/**
 * @함수명    : read
 * @설명      : 센서의 값을 읽어온다
*/
void SteamNovaSDS011::read()
{
  error = _novasds011.read(&pm25, &pm10);
}

/**
 * @함수명    : display
 * @설명      : 센서의 값을 출력한다. 
*/
void SteamNovaSDS011::display()
{

  if (!error)
  {
    Serial.println(" ");
    Serial.print("PM2.5=> ");
    Serial.print(pm25);
    Serial.print(" ug/m3  ");
    _displayAirCondition_PM25(pm25);
    Serial.println(" ");

    Serial.print("PM10 => ");
    Serial.print(pm10);
    Serial.print(" ug/m3  ");
    _displayAirCondition_PM10(pm10);
    Serial.println(" ");
  }
}

/**
 * @함수명    : _displayAirCondition_PM25
 * @설명      : 미세먼지 PM2.5 상태를 출력한다. 
*  좋음(Good) : 0-15
 * 보통(Normal) : 16-35
 * 나쁨(Bad) : 36-75
 * 매우나쁨(Very Bad) :76-
*/
void SteamNovaSDS011::_displayAirCondition_PM25(unsigned int pm2_5)
{
  if (pm2_5 <= 15)
  {
    Serial.print("Good");
  }
  else if (pm2_5 <= 35)
  {
    Serial.print("Normal");
  }
  else if (pm2_5 <= 75)
  {
    Serial.print("Bad");
  }
  else
  {
    Serial.print("Very Bad");
  }
}

/**
 * @함수명    : _displayAirCondition_PM10
 * @설명      : 미세먼지 PM10 상태를 출력한다. 
*  좋음(Good) : 0-30
 * 보통(Normal) : 31-80
 * 나쁨(Bad) : 81-150
 * 매우나쁨(Very Bad) : 151-
*/
void SteamNovaSDS011::_displayAirCondition_PM10(unsigned int pm10)
{
  if (pm10 <= 30)
  {
    Serial.print("Good");
  }
  else if (pm10 <= 80)
  {
    Serial.print("Normal");
  }
  else if (pm10 <= 150)
  {
    Serial.print("Bad");
  }
  else
  {
    Serial.print("Very Bad");
  }
}