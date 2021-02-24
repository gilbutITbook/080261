/*
  NOVA SDS011 library
  STEMEDU123 license
  written by SteamLabs
*/ 

#include "C205_Steam_Air_NovaSDS011_Dust_PWM.h"


SteamNovaSDS011PWM::SteamNovaSDS011PWM(int pm2_5, int pm10)
{
  _pm25Pin = pm2_5; // pm2.5
  _pm10Pin = pm10;  // pm10
}

/**
 * @함수명    : begin
 * @설명      : 센서를 초기화 한다. 
*/
void SteamNovaSDS011PWM::begin()
{  
  //Serial.println("Nova SDS011 Sensor PWM");
  //Serial.println("Ready.....");
  //Serial.println("--------------------------------");  
  
  pinMode(_pm25Pin, INPUT);
  pinMode(_pm10Pin, INPUT);
}

/**
 * @함수명    : read
 * @설명      : 센서의 값을 읽어온다
*/
void SteamNovaSDS011PWM::read()
{
  pm25Pluse = pulseIn(_pm25Pin, HIGH, 1500000) ;
  pm10Pluse = pulseIn(_pm10Pin, HIGH, 1500000);

  pm25ugm3 = pulse2ugm3(pm25Pluse);
  pm10ugm3 = pulse2ugm3(pm10Pluse);
}

/**
 * @함수명    : display
 * @설명      : 센서의 값을 출력한다. 
*/
void SteamNovaSDS011PWM::display()
{

  Serial.print("PM2.5: ");
  Serial.print(pm25ugm3);
  Serial.print(" ug/m3");   
  
  Serial.print(" / PM10: ");
  Serial.print(pm10ugm3);
  Serial.println(" ug/m3"); 
}

int SteamNovaSDS011PWM::getPM2_5()
{
  return pm25ugm3;
}
 

unsigned long SteamNovaSDS011PWM::pulse2ugm3(unsigned long pulse){
  unsigned long value = pulse / 1000 - 2;
  if(value < 0 || value > 999){
    value = 0;
  }
  return value;
}

/**
 * @함수명    : _displayAirCondition_PM25
 * @설명      : 미세먼지 PM2.5 상태를 출력한다. 
*  좋음(Good) : 0-15
 * 보통(Normal) : 16-35
 * 나쁨(Bad) : 36-75
 * 매우나쁨(Very Bad) :76-
*/
void SteamNovaSDS011PWM::_displayAirCondition_PM25(unsigned int pm2_5){  
  if (pm2_5 <= 15) {      
    Serial.print("Good");    
  }  else if (pm2_5 <= 35) {
    Serial.print("Normal");    
  }  else if (pm2_5 <= 75){
    Serial.print("Bad");    
  }  else {
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
void SteamNovaSDS011PWM::_displayAirCondition_PM10(unsigned int pm10){  
  if (pm10 <= 30) {      
    Serial.print("Good");    
  }  else if (pm10 <= 80) {
    Serial.print("Normal");    
  }  else if (pm10 <= 150){
    Serial.print("Bad");    
  }  else {
    Serial.print("Very Bad");    
  }    
}