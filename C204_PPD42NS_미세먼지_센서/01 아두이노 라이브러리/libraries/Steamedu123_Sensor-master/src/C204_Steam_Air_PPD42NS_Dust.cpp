/*
  PPD42NS library
  STEMEDU123 license
  written by SteamLabs
  homepage:  http://www.steamedu123.com   
  naver cafe : https://cafe.naver.com/arduinosensor/book5108749/49
  email : steamedu123@gmail.com
*/

#include "C204_Steam_Air_PPD42NS_Dust.h"
#define COUNT_NUM 10

/**
 * @함수명    : SteamPPD42NS
 * @설명      : 생성자
*/
SteamPPD42NS::SteamPPD42NS(int pin)
{
  _ppdPin = pin;
}

/**
 * @함수명    : begin
 * @설명      : 센서를 초기화 한다. 
*/
void SteamPPD42NS::begin()
{
  Serial.println("PPD42NS Sensor");
  Serial.println("Ready.....");
  Serial.println("--------------------------------");

  pinMode(_ppdPin, INPUT);
  starttime = millis();

  // delay(5000);

  if (dustDensity == 0)
  {
    Serial.println("Analysing Sensor");
    Serial.println("................");
    lowpulseoccupancy = 0;
    starttime = millis();
  }

  cntPM = 0;
}

/**
 * @함수명    : read
 * @설명      : 센서의 값을 읽어온다
*/
void SteamPPD42NS::read()
{
  if (cntPM < COUNT_NUM)
  {
    getPM();
    avrDustDensity += dustDensity;
    cntPM++;
  }
  else
  {
    avrDustDensity = avrDustDensity / COUNT_NUM;
    cntPM = 0;
  }
}

/**
 * @함수명    : getPM
 * @설명      : 센서의 값을 변환한다.
*/
void SteamPPD42NS::getPM()
{
  duration = pulseIn(_ppdPin, LOW);
  lowpulseoccupancy = lowpulseoccupancy + duration;

  if ((millis() - starttime) >= sampletime_ms)
  {
    ratio = lowpulseoccupancy / (sampletime_ms * 10.0);
    concentration = 1.1 * pow(ratio, 3) - 3.8 * pow(ratio, 2) + 520 * ratio + 0.62;
    pcsPerCF = concentration * 100;
    dustDensity = pcsPerCF / 13000;
  }
}

/**
 * @함수명    : display
 * @설명      : 센서의 값을 출력한다. 
*/
void SteamPPD42NS::display()
{
  int pm25 = ceil(avrDustDensity);
  if (cntPM == 0)
  {
    Serial.print("PM2.5=> ");
    Serial.print(pm25);
    Serial.print(" ug/m3  ");
    _displayAirCondition(avrDustDensity);
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
void SteamPPD42NS::_displayAirCondition(unsigned int pm2_5)
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
