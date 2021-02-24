/*
  MH-Z19B library
  STEMEDU123 license
  written by SteamLabs
  homepage: http://www.steamedu123.com   
  naver cafe : https://cafe.naver.com/arduinosensor/book5108749/52
  email : steamedu123@gmail.com
*/

#include "C302_Steam_Air_MH-Z19B_CO2_PWM.h"

/**
 * @함수명    : SteamMHZ19BPWM
 * @설명      : 생성자
*/
SteamMHZ19BPWM::SteamMHZ19BPWM(int pwmPin)
{
  _pwmPin = pwmPin;
}

/**
 * @함수명    : begin
 * @설명      : 센서를 초기화 한다. 
*/
void SteamMHZ19BPWM::begin()
{
  Serial.println("MH-Z19B CO2 Sensor - PWM");
  Serial.println("Ready.....");
  Serial.println("--------------------------------");

  mhz19_pwm = new MHZ19PWM(_pwmPin, MHZ_CONTINUOUS_MODE);
  mhz19_pwm->useLimit(5000);
}

/**
 * @함수명    : read
 * @설명      : 센서의 값을 읽어온다
*/
void SteamMHZ19BPWM::read()
{
  _start = millis();
  _CO2 = mhz19_pwm->getCO2();
  _duration = millis() - _start;
}

/**
 * @함수명    : display
 * @설명      : 센서의 값을 출력한다. 
*/
void SteamMHZ19BPWM::display()
{
  Serial.print(F("CO2: "));
  Serial.print(_CO2);

  Serial.print(" ==> ");
  _displayAirCondition_CO2(_CO2);
  //Serial.print(" ");

  Serial.print(F("\tDuration: "));
  Serial.println(_duration);
}

/**
 * @함수명    : _displayAirCondition_CO2
 * @설명      : 센서의 상태를 출력한다. 
 * 좋음(Good) :       0~700   ppm
 * 보통(Normal) :   700~1000 ppm
 * 나쁨(Bad) :      1000~2000 ppm
 * 매우나쁨(Very Bad) :  2000~
*/
void SteamMHZ19BPWM::_displayAirCondition_CO2(int CO2)
{
  if (CO2 <= 700)
  {
    Serial.print("Good");
  }
  else if (CO2 <= 1000)
  {
    Serial.print("Normal");
  }
  else if (CO2 <= 2000)
  {
    Serial.print("Bad");
  }
  else
  {
    Serial.print("Very Bad");
  }
}