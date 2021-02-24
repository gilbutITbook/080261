/*
  MiCS-6814 library
  STEMEDU123 license
  written by SteamLabs
  homepage: http://www.steamedu123.com   
  naver cafe : https://cafe.naver.com/arduinosensor/book5108749/63
  email : steamedu123@gmail.com
*/

#include <C404_Steam_Air_MICS-6814_MOS.h>

/**
 * @함수명    : SteamMICS6814
 * @설명      : 생성자
*/
SteamMICS6814::SteamMICS6814()
{
  _nh3 = _co = _no2 = _c3h8 = _c4h10 = _ch4 = _h2 = _c2h5oh = 0;
}

/**
 * @함수명    : begin
 * @설명      : 센서를 초기화 한다. 
*/
void SteamMICS6814::begin()
{
  Serial.println("Grove - Multichannel Gas Sensor");
  Serial.println("Ready.....");
  Serial.println("--------------------------------");

  _sensor.begin(0x04); //the default I2C address of the slave is 0x04
  _sensor.powerOn();
}

/**
 * @함수명    : read
 * @설명      : 센서의 값을 읽어온다
*/
void SteamMICS6814::read()
{
  _co = _sensor.measure_CO();
  _no2 = _sensor.measure_NO2();
  _c2h5oh = _sensor.measure_C2H5OH();
  _h2 = _sensor.measure_H2();
  _nh3 = _sensor.measure_NH3();
  _ch4 = _sensor.measure_CH4();
  _c3h8 = _sensor.measure_C3H8();
  _c4h10 = _sensor.measure_C4H10();
}

/**
 * @함수명    : display
 * @설명      : 센서의 값을 출력한다. 
*/
void SteamMICS6814::display()
{
  displaySensor("NH3", _nh3);
  displaySensor("CO", _co);
  displaySensor("NO2", _no2);
  displaySensor("C2H5OH", _c2h5oh);
  displaySensor("H2", _h2);
  displaySensor("CH4", _ch4);
  displaySensor("C3H8", _c3h8);
  displaySensor("C4H10", _c4h10);
  Serial.println("---------------------------------");
}

/**
 * @함수명    : displaySensor
 * @설명      : 센서의 값을 출력한다. 
*/
void SteamMICS6814::displaySensor(String str, float c)
{
  // char buf[256];
  // sprintf(buf, "The concentration of %s is ", str);
  // Serial.print(buf);

  // if (c >= 0)
  // {
  //   Serial.print(c);
  // }
  // else
  // {
  //   Serial.print("invalid");
  // }
  Serial.print(str);
  Serial.print("\t");
  Serial.print(c);
  Serial.print(" ppm\t");

  if (str == "CO")
  {
    //_displayAirCondition_CO(c);
  }
  else if (str == "NO2")
  {
    //_displayAirCondition_NO2(c);
  }
  else if (str == "NH3")
  {
    _displayAirCondition_NH3(c);
  }

  Serial.println();
}

/**
 * @함수명    : _displayAirCondition_CO
 * @설명      : 
*/
void SteamMICS6814::_displayAirCondition_CO(float ppm)
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

/**
 * @함수명    : _displayAirCondition_NO2
 * @설명      : 
*/
void SteamMICS6814::_displayAirCondition_NO2(float ppm)
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

/**
 * @함수명    : _displayAirCondition_NH3
 * @설명      : 
*/

void SteamMICS6814::_displayAirCondition_NH3(float ppm)
{
  Serial.print(" => ");
  if (ppm <= 7)
  {
    Serial.print(" Good");
  }
  else if (ppm <= 25)
  {
    Serial.print("Normal");
  }
  else if (ppm <= 100)
  {
    Serial.print("Bad");
  }
  else
  {
    Serial.print("Very Bad");
  }
}