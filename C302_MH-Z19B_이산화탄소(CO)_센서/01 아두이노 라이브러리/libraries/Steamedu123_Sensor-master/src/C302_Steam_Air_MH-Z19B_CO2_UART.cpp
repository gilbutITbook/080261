/*
  MH-Z19B library
  STEMEDU123 license
  written by SteamLabs
  homepage: http://www.steamedu123.com   
  naver cafe : https://cafe.naver.com/arduinosensor/book5108749/52
  email : steamedu123@gmail.com
*/

#include "C302_Steam_Air_MH-Z19B_CO2_UART.h"

/**
 * @함수명    : SteamMHZ19B
 * @설명      : 생성자
*/
SteamMHZ19B::SteamMHZ19B(int rxPin, int txPin)
{
  _rxPin = rxPin;
  _txPin = txPin;
}

/**
 * @함수명    : begin
 * @설명      : 센서를 초기화 한다. 
*/
void SteamMHZ19B::begin()
{
  Serial.println("MH-Z19B CO2 Sensor - UART");
  Serial.println("Ready.....");
  Serial.println("--------------------------------");

  mhz19_uart = new MHZ19(_rxPin, _txPin);

  mhz19_uart->begin(_rxPin, _txPin);
}

/**
 * @함수명    : read
 * @설명      : 센서의 값을 읽어온다
*/
void SteamMHZ19B::read()
{
  response = mhz19_uart->retrieveData();

  _CO2 = mhz19_uart->getCO2();
  _miniCO2 = mhz19_uart->getMinCO2();
  _temperature = mhz19_uart->getTemperature();
  _Accuracy = mhz19_uart->getAccuracy();
}

/**
 * @함수명    : display
 * @설명      : 센서의 값을 출력한다. 
*/
void SteamMHZ19B::display()
{
  if (response == MHZ19_RESULT_OK)
  {
    Serial.print(F("CO2: "));
    Serial.print(_CO2);

    Serial.print(" ==> ");
    _displayAirCondition_CO2(_CO2);
    Serial.println(" ");

    Serial.print(F("\tMin CO2: "));
    Serial.println(_miniCO2);
    Serial.print(F("\tTemperature: "));
    Serial.println(_temperature);
    Serial.print(F("\tAccuracy: "));
    Serial.println(_Accuracy);
    Serial.println(" ");
  }
  else
  {
    Serial.print(F("Error, code: "));
    Serial.println(response);
  }
}

/**
 * @함수명    : _displayAirCondition_CO2
 * @설명      : 센서의 상태를 출력한다. 
 * 좋음(Good) : 
 * 보통(Normal) : 
 * 나쁨(Bad) : 
 * 매우나쁨(Very Bad) : 
*/
void SteamMHZ19B::_displayAirCondition_CO2(int CO2)
{
  if (CO2 <= 700)
  {
    Serial.print("Good");
  }
  else if (CO2 <= 1000)
  {
    Serial.print("Normal"); // MODERATE
  }
  else if (CO2 <= 2000)
  {
    Serial.print("Bad"); // POOR
  }
  else
  {
    Serial.print("Very Bad"); // UNHEALTHY
  }
}