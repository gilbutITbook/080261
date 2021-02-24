/*
  BME280 library
  STEMEDU123 license
  written by SteamLabs
  homepage: http://www.steamedu123.com   
  naver cafe : https://cafe.naver.com/arduinosensor/book5108749/58
  email : steamedu123@gmail.com
*/

#include "C501_Steam_Air_BME280_hPa.h"

/**
 * @함수명    : SteamBME280
 * @설명      : 생성자
*/
SteamBME280::SteamBME280() {}

/**
 * @함수명    : begin
 * @설명      : 센서를 초기화 한다. 
*/
void SteamBME280::begin()
{
  Serial.println("BME280(Barometer) Sensor");
  Serial.println("Ready.....");
  Serial.println("--------------------------------");

  unsigned status;

  // default settings
  status = bme.begin(0x76);
  // You can also pass in a Wire library object like &Wire2
  // status = bme.begin(0x76, &Wire2)
  if (!status)
  {
    Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
    Serial.print("SensorID was: 0x");
    Serial.println(bme.sensorID(), 16);
    Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
    Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
    Serial.print("        ID of 0x60 represents a BME 280.\n");
    Serial.print("        ID of 0x61 represents a BME 680.\n");
    while (1)
      delay(10);
  }

  Serial.println();
}

/**
 * @함수명    : read
 * @설명      : 센서의 값을 읽어온다
*/
void SteamBME280::read()
{
  tremperature = bme.readTemperature();
  humidity = bme.readHumidity();

  pressure = bme.readPressure() / 100.0F;
  calcAltitude = bme.readAltitude(SEALEVELPRESSURE_HPA);
}

/**
 * @함수명    : display
 * @설명      : 센서의 값을 출력한다. 
*/
void SteamBME280::display()
{

  //get and print atmospheric pressure data
  Serial.print("Pressure: ");
  Serial.print(pressure);
  Serial.println("hPa");

  //get and print altitude data
  Serial.print("Altitude: ");
  Serial.print(calcAltitude);
  Serial.println("m");

  //get and print temperatures
  Serial.print("Temp: ");
  Serial.print(tremperature);
  Serial.println("C");

  //get and print humidity data
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println("%");

  Serial.println("");
}
