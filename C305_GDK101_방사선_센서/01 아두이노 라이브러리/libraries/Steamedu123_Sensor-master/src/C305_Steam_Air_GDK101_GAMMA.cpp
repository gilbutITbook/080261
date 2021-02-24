/*
  GDK101 library
  STEMEDU123 license
  written by SteamLabs
  homepage: http://www.steamedu123.com   
  naver cafe : https://cafe.naver.com/arduinosensor/book5108749/55
  email : steamedu123@gmail.com
*/

#include "C305_Steam_Air_GDK101_GAMMA.h"

#define DEF_ADDR 0x18

/**
 * @함수명    : begin
 * @설명      : 센서를 초기화 한다. 
*/
void SteamGDK101::begin()
{
  Serial.println("GDK101 Gamma Radiation Sensor Module");
  Serial.println("Ready.....");
  Serial.println("--------------------------------");

  _gdk101.begin(DEF_ADDR);
  //_gdk101.reset();
  fw_vers = _gdk101.get_fw_version();
}

/**
 * @함수명    : read
 * @설명      : 센서의 값을 읽어온다
*/
void SteamGDK101::read()
{
  avg10min = _gdk101.get_10min_avg();
  avg1min = _gdk101.get_1min_avg();
  mea_min = _gdk101.get_measuring_time_min();
  mea_sec = _gdk101.get_measuring_time_sec();
  _status = _gdk101.get_status();
  vibration = _gdk101.get_vib();
}

/**
 * @함수명    : display
 * @설명      : 센서의 값을 출력한다. 
*/
void SteamGDK101::display()
{
  Serial.println("Gamma Sensor Sensing Start");
  Serial.print("FW verwion : \t\t\t");
  Serial.println(fw_vers);

  Serial.println("===========================================");
  displayStatus(_status);
  displayVibration(vibration);

  sprintf(out_buff, "Measuring Time: \t\t%i:%i", mea_min, mea_sec);
  Serial.println(out_buff);

  Serial.print("Measuring Value(10min Avg) \t");
  Serial.print(avg10min);
  Serial.println(" uSv/hr");

  float uSvTomSV = avg10min * 0.001;
  Serial.print("\t\t\t\t");
  Serial.print(uSvTomSV, 6);
  Serial.println(" mSv/hr");

  Serial.print("\t\t\t\t");
  _displayAirCondition_RN(avg10min);
  Serial.println();

  Serial.print("Measuring Value(1min Avg) \t");
  Serial.print(avg1min);
  Serial.println(" uSv/hr");

  uSvTomSV = avg1min * 0.001;
  Serial.print("\t\t\t\t");
  Serial.print(uSvTomSV, 6);
  Serial.println(" mSv/hr");

  Serial.print("\t\t\t\t");
  _displayAirCondition_RN(avg1min);
  Serial.println();

  Serial.println();
}

float SteamGDK101::convert_uSvTomSv(float sv)
{
  return sv * (1 / 1000);
}

void SteamGDK101::displayReset(bool s)
{
  Serial.print("Reset Response\t\t\t");

  if (s == 1)
  {
    Serial.println("Reset Success.");
  }
  else
  {
    Serial.println("Reset Fail(Status - Ready");
  }
}

void SteamGDK101::displayStatus(int s)
{
  Serial.print("Status: ");

  switch (s)
  {
  case 0:
    Serial.println("\t\t\tReady");
    break;
  case 1:
    Serial.println("\t\t\t10min Waiting");
    break;
  case 2:
    Serial.println("\t\t\tNormal");
    break;
  }
}

void SteamGDK101::displayVibration(bool s)
{
  Serial.print("VIB Status\t\t\t");
  switch (s)
  {
  case 0:
    Serial.println("OFF");
    break;
  case 1:
    Serial.println("ON");
    break;
  }
}

/**
 * @함수명    : _displayAirCondition_RN
 * @설명      : 라돈의 상태를 출력한다. 
 * 안전(Good) :     0~0.4 uSv/h
 * 경고(Normal) :   0.4~30 uSv/h
 * 위험(Bad) :      30~ uSv/h
*/
void SteamGDK101::_displayAirCondition_RN(float uSv)
{
  if (uSv <= 0.4)
  {
    Serial.print("SAFETY");
  }
  else if (uSv <= 30)
  {
    Serial.print("WARNING!");
  }
  else
  {
    Serial.print("DANGER!!");
  }
}