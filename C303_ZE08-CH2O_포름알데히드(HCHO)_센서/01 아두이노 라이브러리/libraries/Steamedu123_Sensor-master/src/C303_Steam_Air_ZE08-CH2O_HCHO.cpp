/*
  ZE08-CH2O library
  STEMEDU123 license
  written by SteamLabs
  homepage:  http://www.steamedu123.com   
  naver cafe : https://cafe.naver.com/arduinosensor/book5108749/51
  email : steamedu123@gmail.com
*/

#include "C303_Steam_Air_ZE08-CH2O_HCHO.h"
#define VREF 5.0 //voltage on AREF pin

/**
 * @함수명    : SteamZE08CH2O
 * @설명      : 생성자
*/
SteamZE08CH2O::SteamZE08CH2O(uint8_t pin)
{
  this->_pin = pin;
}

/**
 * @함수명    : begin
 * @설명      : 센서를 초기화 한다. 
*/
void SteamZE08CH2O::begin()
{
  Serial.println("ZE08-CH2O HCHO Sensor");
  Serial.println("Ready.....");
  Serial.println("--------------------------------");

  _hcho = new DFRobotHCHOSensor(_pin, VREF);
}

/**
 * @함수명    : read
 * @설명      : 센서의 값을 읽어온다
*/
void SteamZE08CH2O::read()
{
  dacHchoPPM = _hcho->dacReadPPM();
}

/**
 * @함수명    : display
 * @설명      : 센서의 값을 출력한다. 
*/
void SteamZE08CH2O::display()
{
  Serial.print(F("HCHO: "));
  Serial.print(dacHchoPPM);
  Serial.print("ppm ");

  Serial.print(" ==> ");
  _displayAirCondition_HCHO(dacHchoPPM);
  Serial.println();
}

/**
 * @함수명    : _displayAirCondition_HCHO
 * @설명      : 센서의 상태를 출력한다. 
 * 좋음(Good) :         0~0.08    ppm
 * 보통(Normal) :       0.08~0.16 ppm
 * 나쁨(Bad)  :         0.16~0.81 ppm
 * 매우나쁨(Very Bad) :  0.81~     ppm
*/
void SteamZE08CH2O::_displayAirCondition_HCHO(float hcho)
{
  if (hcho <= 0.08)
  {
    Serial.print("Good");
  }
  else if (hcho <= 0.16)
  {
    Serial.print("Normal");
  }
  else if (hcho <= 0.81)
  {
    Serial.print("Bad");
  }
  else
  {
    Serial.print("Very Bad");
  }
}