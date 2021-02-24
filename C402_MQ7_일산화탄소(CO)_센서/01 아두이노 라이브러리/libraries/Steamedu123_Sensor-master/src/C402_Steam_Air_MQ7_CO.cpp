/*
  MQ-7 library
  STEMEDU123 license
  written by SteamLabs
  homepage: http://www.steamedu123.com   
  naver cafe : https://cafe.naver.com/arduinosensor/book5108749/57
  email : steamedu123@gmail.com
*/

#include "C402_Steam_Air_MQ7_CO.h"

/**
 * @함수명    : SteamMQ7
 * @설명      : 생성자
*/
SteamMQ7::SteamMQ7(uint8_t aoutPin)
{
  _aoutPin = aoutPin;
}

/**
 * @함수명    : begin
 * @설명      : 센서를 초기화 한다. 
*/
void SteamMQ7::begin()
{
  Serial.println("MQ-7 CO (Carbon Monoxide) Sensor");
  Serial.println("Ready.....");
  Serial.println("--------------------------------");

  mq7 = new MQ7(_aoutPin, 5.0);
}

/**
 * @함수명    : read
 * @설명      : 센서의 값을 읽어온다
*/
void SteamMQ7::read()
{
  _ppm = mq7->getPPM();
}

/**
 * @함수명    : display
 * @설명      : 센서의 값을 출력한다. 
*/
void SteamMQ7::display()
{
  Serial.print("CO: ");
  Serial.print(_ppm);
  Serial.print(" ppm\t");

  _displayAirCondition_CO(_ppm);

  Serial.println();
}

/**
 * @함수명    : _displayAirCondition_O3
 * @설명      :  상태를 출력한다. 
*  좋음(Good) :         0~2 ppm
 * 보통(Normal) :       <= 9
 * 나쁨(Bad) :           <= 15
 * 매우나쁨(Very Bad) : 15~
*/
void SteamMQ7::_displayAirCondition_CO(float ppm)
{
  if (ppm <= 2)
  {
    Serial.print("Good");
  }
  else if (ppm <= 9)
  {
    Serial.print("Normal");
  }
  else if (ppm <= 15)
  {
    Serial.print("Bad");
  }
  else
  {
    Serial.print("Very Bad");
  }
}
