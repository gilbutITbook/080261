/*
  QS-FS01 library
  STEMEDU123 license
  written by SteamLabs
  homepage: http://www.steamedu123.com   
  naver cafe : https://cafe.naver.com/arduinosensor/book5108749/61
  email : steamedu123@gmail.com
*/

#include "C504_Steam_Air_QS-FS01_WindSpeed.h"

/**
 * @함수명    : SteamQSFS01
 * @설명      : 생성자
*/
SteamQSFS01::SteamQSFS01(uint8_t pin)
{
  _pin = pin;
}

/**
 * @함수명    : begin
 * @설명      : 센서를 초기화 한다. 
*/
void SteamQSFS01::begin()
{
  Serial.println("QS-FS01 Wind speed Sensor");
  Serial.println("Ready.....");
  Serial.println("--------------------------------");
}

/**
 * @함수명    : read
 * @설명      : 센서의 값을 읽어온다
*/
void SteamQSFS01::read()
{
  sensorValue = analogRead(_pin);
  outvoltage = sensorValue * (5.0 / 1023.0);

  if (outvoltage >= 0.4)
  {
    ms = (outvoltage - 0.4) / 1.6 * 32.4;
  }
  else
  {
    ms = 0;
  }

  level = 6 * outvoltage;
}

/**
 * @함수명    : display
 * @설명      : 센서의 값을 출력한다. 
*/
void SteamQSFS01::display()
{

  Serial.print("Vol=");
  Serial.print(outvoltage);
  Serial.print("v ");

  Serial.print(ms);
  Serial.print("m/s ");

  //Serial.print(" Level ");
  //Serial.println(level);

  Serial.print(" => ");
  _displayAirCondition(ms);
  Serial.println("");
}

/**
 * @함수명    : display
 * @설명      : 풍속 4단계 상태를 출력한다. 
*/
void SteamQSFS01::_displayAirCondition(float speed)
{
  if (speed < 4)
  {
    Serial.print("Good");
  }
  else if (speed < 9)
  {
    Serial.print("Normal");
  }
  else if (speed < 14)
  {
    Serial.print("Bad");
  }
  else
  {
    Serial.print("Very Bad");
  }
}