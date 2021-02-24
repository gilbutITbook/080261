/*
  GUVA-12SD library
  STEMEDU123 license
  written by SteamLabs
  homepage: http://www.steamedu123.com   
  naver cafe : https://cafe.naver.com/arduinosensor/book5108749/59
  email : steamedu123@gmail.com
*/

#include "C502_Steam_Air_GUVA-12SD_UV.h"

/**
 * @함수명    : SteamGUVA12SD
 * @설명      : 생성자
*/
SteamGUVA12SD::SteamGUVA12SD(uint8_t pin)
{
  _pin = pin;
}

/**
 * @함수명    : begin
 * @설명      : 센서를 초기화 한다. 
*/
void SteamGUVA12SD::begin()
{
  Serial.println("GUVA-S12SD (UV Detection Sensor)");
  Serial.println("Ready.....");
  Serial.println("--------------------------------");
}

/**
 * @함수명    : read
 * @설명      : 센서의 값을 읽어온다
*/
void SteamGUVA12SD::read()
{
  sensorValue = analogRead(_pin);
  sensorVoltage = sensorValue / 1024 * 5.0;
  sensorUVIndex = getUVIndex();
}

/**
 * @함수명    : display
 * @설명      : 센서의 값을 출력한다. 
*/
void SteamGUVA12SD::display()
{
  //Get the UV Index, from 0 to 11
  Serial.print("UV Index = ");
  Serial.print(sensorUVIndex);
  Serial.print(" Level: ");
  Serial.println(getUVDangerOfExposure());

  //Sensor Voltage
  Serial.print("Sensor Voltage = ");
  Serial.print(sensorVoltage * 1000);
  Serial.println(" mV");

  //Sensor Value
  Serial.print("Sensor Value = ");
  Serial.println(sensorValue);

  //Empty
  Serial.println();
}

/**
 * @함수명    : getUVDangerOfExposure
 * @설명      : 자외선 강도의 값을 가져온다.  
 * 
 * LOW(0~2) : Cover head and / or eyes
 * MODERATE(3~5) : Cover head and eyes and use low SPF sunscreen
 * HIGH(6~7) : Cover head, eyes, body, and use strong SPF or do not spend time outdoors
 * VERY HIGH(7~10) : Cover head, eyes, body, and use strong SPF or do not spend time outdoors
 * EXTREME HIGH(11~) : Do not go outdoors
*/
String SteamGUVA12SD::getUVDangerOfExposure()
{
  int uv = getUVIndex();
  if (uv <= 2)
  {
    return "GOOD"; //LOW
  }
  else if (uv <= 5)
  {                  // 3~5
    return "NORMAL"; // MODERATE
  }
  else if (uv <= 7)
  {               // 6~7
    return "BAD"; // HIGH
  }
  else if (uv <= 10)
  {                    // 7~10
    return "VERY BAD"; // VERY HIGH
  }
  else
  {
    return "EXTREME HIGH";
  }
}

/**
 * @함수명    : display
 * @설명      : 센서의 값을 출력한다. 
*/
int SteamGUVA12SD::getUVIndex()
{
  int volt = sensorVoltage * 1000;
  if (volt < 50)
  {
    return 0;
  }
  else if (volt < 227)
  {
    return 1;
  }
  else if (volt < 318)
  {
    return 2;
  }
  else if (volt < 408)
  {
    return 3;
  }
  else if (volt < 503)
  {
    return 4;
  }
  else if (volt < 606)
  {
    return 5;
  }
  else if (volt < 696)
  {
    return 6;
  }
  else if (volt < 795)
  {
    return 7;
  }
  else if (volt < 881)
  {
    return 8;
  }
  else if (volt < 976)
  {
    return 9;
  }
  else if (volt < 1079)
  {
    return 10;
  }
  else
  {
    return 11;
  }
}