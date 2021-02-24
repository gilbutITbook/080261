/*
  MiCS-4514 library
  STEMEDU123 license
  written by SteamLabs
  homepage: http://www.steamedu123.com   
  naver cafe : https://cafe.naver.com/arduinosensor/book5108749/62
  email : steamedu123@gmail.com
*/

#include <C403_Steam_Air_MICS-4514_NO2.h>

#define PRE_HEAT_SECONDS 10

/**
 * @함수명    : SteamMICS4514
 * @설명      : 생성자
*/
SteamMICS4514::SteamMICS4514(uint8_t prePin, uint8_t vnoxPin, uint8_t vredPin)
{
  _prePin = prePin;
  _vnoxPin = vnoxPin;
  _vredPin = vredPin;
}

/**
 * @함수명    : begin
 * @설명      : 센서를 초기화 한다. 
*/
void SteamMICS4514::begin()
{
  Serial.println("MiCS-4514 NO2 Sensor");
  Serial.println("Preheating...");
  Serial.println("--------------------------------");

  // 예열
  digitalWrite(_prePin, 1);
  delay(PRE_HEAT_SECONDS * 1000);
  digitalWrite(_prePin, 0);
  Serial.println("Done");
}

/**
 * @함수명    : read
 * @설명      : 센서의 값을 읽어온다
*/

void SteamMICS4514::read()
{
  _readNO2();
}

void SteamMICS4514::_readNO2()
{
  // read NO2 sensor:
  vnox_value = analogRead(_vnoxPin);
  vout_no2 = analogRead(_vnoxPin) / 409.2;   // adc 값을 전압으로 변환
  Rs_no2 = Rload_no2 / ((5 / vout_no2) - 1); // 5V 입력 및 22kOhm 부하 저항을 사용하여 Vout에서 센서 저항 찾기
  ppmNO2 = (.000008 * Rs_no2 - .0194);       //Rs를 ppm 농도 NO2로 변환
}

void SteamMICS4514::_readCO()
{
  // read CO sensor:
  //vred_value = analogRead(_vredPin);
  //  vout_co = vred_value /409.2; // adc 값을 전압으로 변환
  //  Rs_co = Rload_co /((5/vout_co) - 1);   // 5V 입력 및  470kOhm 부하 저항을 사용하여 Vout에서 센서 저항 찾기
  //  ppmCO = 911.19*pow(2.71828,(-8.577*Rs_co/100000));    //Rs를 ppm 농도 CO로 변환
}
/**
 * @함수명    : display
 * @설명      : 센서의 값을 출력한다. 
*/
void SteamMICS4514::display()
{
  displaySensor("  NO2: ", ppmNO2);
}

/**
 * @함수명    : displaySensor
 * @설명      : 센서의 값을 출력한다. 
*/
void SteamMICS4514::displaySensor(String str, float c)
{
  Serial.print("Vnox: ");
  Serial.print(vnox_value, DEC);

  Serial.print(str);
  Serial.print(c);
  Serial.print(" ppm => ");

  _displayAirCondition_NO2(c);

  Serial.println();
}

void SteamMICS4514::_displayAirCondition_NO2(float ppm)
{
  if (ppm <= 0.03)
  {
    Serial.print("Good");
  }
  else if (ppm <= 0.06)
  {
    Serial.print("Normal");
  }
  else if (ppm <= 0.2)
  {
    Serial.print("Bad");
  }
  else
  {
    Serial.print("Very Bad");
  }
}
