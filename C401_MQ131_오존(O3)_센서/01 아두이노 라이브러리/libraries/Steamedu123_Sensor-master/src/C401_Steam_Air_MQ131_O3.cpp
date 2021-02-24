/*
  MQ131 library
  STEMEDU123 license
  written by SteamLabs
  homepage: http://www.steamedu123.com   
  naver cafe : https://cafe.naver.com/arduinosensor/book5108749/56
  email : steamedu123@gmail.com
*/

#include <C401_Steam_Air_MQ131_O3.h>
#include <MQ131.h>

/**
 * @함수명    : SteamMQ131
 * @설명      : 생성자
*/
SteamMQ131::SteamMQ131(uint8_t aoutPin)
{
  _aoutPin = aoutPin;
}

/**
 * @함수명    : begin
 * @설명      : 센서를 초기화 한다. 
*/
void SteamMQ131::begin()
{
  Serial.println("MQ131 O3 Sensor");
  Serial.println("Ready.....");
  Serial.println("--------------------------------");

  // Init the sensor
  // - Heater control on pin 2
  // - Sensor analog read on pin A1
  // - Model LOW_CONCENTRATION
  // - Load resistance RL of 10KOhms (10000 Ohms)
  MQ131.begin(2, _aoutPin, LOW_CONCENTRATION, 10000);

  Serial.println("Calibration in progress...");
  MQ131.calibrate();

  Serial.println("Calibration done!");
  Serial.print("R0 = ");
  Serial.print(MQ131.getR0());
  Serial.println(" Ohms");
  Serial.print("Time to heat = ");
  Serial.print(MQ131.getTimeToRead());
  Serial.println(" s");
}

/**
 * @함수명    : read
 * @설명      : 센서의 값을 읽어온다
*/
void SteamMQ131::read(int _temp, int _humi)
{
  Serial.println("Sampling...");
  MQ131.sample();

  setTempHumi(_temp, _humi); // 온도, 습도

  _ppm = MQ131.getO3(PPM);
  _ppb = MQ131.getO3(PPB);
  _mg_m3 = MQ131.getO3(MG_M3);
  _ug_m3 = MQ131.getO3(UG_M3);
}

/**
 * @함수명    : display
 * @설명      : 센서의 값을 출력한다. 
*/
void SteamMQ131::display()
{
  Serial.print("Concentration O3 : ");
  Serial.print(_ppm);
  Serial.print(" ppm => ");
  _displayAirCondition_O3(_ppm);
  Serial.println();

  Serial.print("Concentration O3 : ");
  Serial.print(_ppb);
  Serial.println(" ppb");
  Serial.print("Concentration O3 : ");
  Serial.print(_mg_m3);
  Serial.println(" mg/m3");
  Serial.print("Concentration O3 : ");
  Serial.print(_ug_m3);
  Serial.println(" ug/m3");
}

/**
 * @함수명    : setTempHumi
 * @설명      : setEnv(int tempCels, int humPc) 
      The sensor is sensible to environmental variation (temperature and humidity). 
   If you want to have correct values, you should set the temperature and the humidity 
   before the call to getO3() function with the function setEnv(). 
   Temperature are in °C and humidity in %. 
   The values should come from another sensor like the DHT22.
*/
void SteamMQ131::setTempHumi(int _temp, int _humi)
{
  MQ131.setEnv(_temp, _humi);
}

/**
 * @함수명    : _displayAirCondition_O3
 * @설명      :  상태를 출력한다. 
*  좋음(Good) :         0~0.03
 * 보통(Normal) :       0.031~0.09
 * 나쁨(Bad) :          0.091~0.15
 * 매우나쁨(Very Bad) : 0.151~
*/
void SteamMQ131::_displayAirCondition_O3(float ppm)
{
  if (ppm <= 0.03)
  {
    Serial.print("Good");
  }
  else if (ppm <= 0.09)
  {
    Serial.print("Normal"); // MODERATE
  }
  else if (ppm <= 0.15)
  {
    Serial.print("Bad"); // POOR
  }
  else
  {
    Serial.print("Very Bad"); // UNHEALTHY
  }
}