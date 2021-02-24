/*
  CCS811(CJMCU-811) library
  STEMEDU123 license
  written by SteamLabs
  homepage: http://www.steamedu123.com   
  naver cafe : https://cafe.naver.com/arduinosensor/book5108749/54
  email : steamedu123@gmail.com
*/

#include "C304_Steam_Air_CCS811_TVOC.h"

/**
 * @함수명    : SteamCCS811
 * @설명      : 생성자
*/
SteamCCS811::SteamCCS811() {}

/**
 * @함수명    : begin
 * @설명      : 센서를 초기화 한다. 
*/
void SteamCCS811::begin()
{
  Serial.println("CCS811 Sensor");
  Serial.println("Ready.....");
  Serial.println("--------------------------------");

  _ccs811 = new Adafruit_CCS811();
  if (!_ccs811->begin())
  {
    Serial.println("Failed to start sensor! Please check your wiring.");
    while (1)
      ;
  }

  //calibrate temperature sensor
  while (!_ccs811->available())
    ;

  float temp = _ccs811->calculateTemperature();
  _ccs811->setTempOffset(temp - 25.0);
}

/**
 * @함수명    : read
 * @설명      : 센서의 값을 읽어온다
*/
void SteamCCS811::read()
{
  if (_ccs811->available())
  {
    _temp = _ccs811->calculateTemperature();

    if (!_ccs811->readData())
    {
      _eCo2 = _ccs811->geteCO2();
      _tvoc = _ccs811->getTVOC();
      _mg_m3 = _tvoc * 0.004546;
      // display();
    }
    else
    {
      Serial.println("ERROR!");
      while (1)
        ;
    }
  }
}

/**
 * @함수명    : display
 * @설명      : 센서의 값을 출력한다. 
*/
void SteamCCS811::display()
{
  //Serial.print("Temp: ");
  //Serial.print(_temp);

  //Serial.print("\t eCO2: ");
  //Serial.print(_eCo2);
  //Serial.print("ppm");

  Serial.print("TVOCs: ");
  Serial.print(_tvoc);
  Serial.print("ppb => ");
  _displayAirCondition_TVOC(_tvoc);

  Serial.print("\t TVOCs: ");
  Serial.print(_mg_m3, 3);
  Serial.println("mg/m3");
}

/**
 * @함수명    : _displayAirCondition_CO2
 * @설명      : 센서의 상태를 출력한다. 
 * 좋음(Good) : -130
 * 보통(Normal) : 131~261
 * 나쁨(Bad) : 262~522
 * 매우나쁨(Very Bad) : 523~
*/
void SteamCCS811::_displayAirCondition_TVOC(uint16_t ppb)
{
  if (ppb <= 130)
  {
    Serial.print("Good");
  }
  else if (ppb <= 261)
  {
    Serial.print("Normal");
  }
  else if (ppb <= 522)
  {
    Serial.print("Bad");
  }
  else
  {
    Serial.print("Very Bad");
  }
}
