/*
  PMS7003 library
  STEMEDU123 license
  written by SteamLabs
  homepage:  http://www.steamedu123.com   
  naver cafe : https://cafe.naver.com/arduinosensor/book5108749/47
  email : steamedu123@gmail.com
*/

#include "C202_Steam_Air_PMS7003_Dust.h"

/**
 * @함수명    : SteamPMS7003
 * @설명      : 생성자
*/
SteamPMS7003::SteamPMS7003(uint8_t rxPin, uint8_t txPin)
{
  _rxPin = rxPin;
  _txPin = txPin;
}

/**
 * @함수명    : begin
 * @설명      : 센서를 초기화 한다. 
*/
void SteamPMS7003::begin()
{
  Serial.println("PMS7003 Sensor");
  Serial.println("Ready.....");
  Serial.println("--------------------------------");

  _pms7003 = new SoftwareSerial(_rxPin, _txPin);
}

/**
 * @함수명    : read
 * @설명      : 센서의 값을 읽어온다
*/
bool SteamPMS7003::read()
{
  _getSensor();

  if (cnt == COUNT_NUM)
  { // cnt 회수 만큼 센서의 값을 측정
    _getSensorAverageValue();

    pm2_5 = pm10_0 = cnt = 0;
    return true;
  }

  return false;
}

/**
 * @함수명    : display
 * @설명      : 센서의 값을 출력한다. 
*/
void SteamPMS7003::display()
{
  Serial.println(" ");
  Serial.print("PM2.5=> ");
  Serial.print(avrPM2_5);
  Serial.print(" ug/m3  ");
  _displayAirCondition_PM25(avrPM2_5);
  Serial.println(" ");

  Serial.print("PM10 => ");
  Serial.print(avrPM10_0);
  Serial.print(" ug/m3  ");
  _displayAirCondition_PM10(avrPM10_0);
  Serial.println(" ");
}

/**
 * @함수명    : getSensorValue
 * @설명      : 센서의 값을 cnt 회수 만큼 반복해서 읽어온다. 
*/
void SteamPMS7003::_getSensor()
{
  if (_getSensorPacket())
  {

    pm2_5 += thisFrame.concPM2_5_CF1;
    pm10_0 += thisFrame.concPM10_0_CF1;
    cnt++;

    Serial.print(cnt);
  }
  else
  {
    Serial.print("*");
  }
}

/**
 * @함수명    : getSensorPacket
 * @설명     : 센서의 값을 읽어온다. 
 * @리턴값    : bool  
*/
bool SteamPMS7003::_getSensorPacket()
{
  _pms7003->begin(9600);
  bool packetReceived = false;
  calcChecksum = 0;

  while (!packetReceived)
  {
    if (_pms7003->available() > 32)
    {
      int drain = _pms7003->available();

      for (int i = drain; i > 0; i--)
      {
        _pms7003->read();
      }
    }

    if (_pms7003->available() > 0)
    {
      incomingByte = _pms7003->read();

      if (!inFrame)
      {
        if (incomingByte == 0x42 && detectOff == 0)
        {
          frameBuf[detectOff] = incomingByte;
          thisFrame.frameHeader[0] = incomingByte;
          calcChecksum = incomingByte; // Checksum init!
          detectOff++;
        }
        else if (incomingByte == 0x4D && detectOff == 1)
        {
          frameBuf[detectOff] = incomingByte;
          thisFrame.frameHeader[1] = incomingByte;
          calcChecksum += incomingByte;
          inFrame = true;
          detectOff++;
        }
        else
        {
          Serial.print("----- Frame syncing... -----");
          Serial.print(incomingByte, HEX);
          Serial.println();
        }
      }
      else
      {
        frameBuf[detectOff] = incomingByte;
        calcChecksum += incomingByte;
        detectOff++;
        unsigned int val = (frameBuf[detectOff - 1] & 0xff) + (frameBuf[detectOff - 2] << 8);

        switch (detectOff)
        {
        case 4:
          thisFrame.frameLen = val;
          frameLen = val + detectOff;
          break;

        case 8:
          thisFrame.concPM2_5_CF1 = val;
          break;
        case 10:
          thisFrame.concPM10_0_CF1 = val;
          break;

        case 32:
          thisFrame.checksum = val;
          calcChecksum -= ((val >> 8) + (val & 0xFF));
          break;
        default:
          break;
        }

        if (detectOff >= frameLen)
        {
          packetReceived = true;
          detectOff = 0;
          inFrame = false;
        }
      }
    }
  }

  _pms7003->end();
  return (calcChecksum == thisFrame.checksum);
}

/**
 * @함수명    : getSensorResult
 * @설명      : 평균 센서값을 계산한다.
*/
void SteamPMS7003::_getSensorAverageValue()
{
  avrPM2_5 = pm2_5 / COUNT_NUM;
  avrPM10_0 = pm10_0 / COUNT_NUM;
}

/**
 * @함수명    : getPM2_5
 * @설명      : pm2.5 값을 리턴한다.
*/
unsigned int SteamPMS7003::getPM2_5()
{
  return avrPM2_5;
}

/**
 * @함수명    : getPM10_0
 * @설명      : pm10 값을 리턴한다.
*/
unsigned int SteamPMS7003::getPM10_0()
{
  return avrPM10_0;
}

/**
 * @함수명    : _displayAirCondition_PM25
 * @설명      : 미세먼지 PM2.5 상태를 출력한다. 
*  좋음(Good) : 0-15
 * 보통(Normal) : 16-35
 * 나쁨(Bad) : 36-75
 * 매우나쁨(Very Bad) :76-
*/
void SteamPMS7003::_displayAirCondition_PM25(unsigned int pm2_5)
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

/**
 * @함수명    : _displayAirCondition_PM10
 * @설명      : 미세먼지 PM10 상태를 출력한다. 
*  좋음(Good) : 0-30
 * 보통(Normal) : 31-80
 * 나쁨(Bad) : 81-150
 * 매우나쁨(Very Bad) : 151-
*/
void SteamPMS7003::_displayAirCondition_PM10(unsigned int pm10)
{
  if (pm10 <= 30)
  {
    Serial.print("Good");
  }
  else if (pm10 <= 80)
  {
    Serial.print("Normal");
  }
  else if (pm10 <= 150)
  {
    Serial.print("Bad");
  }
  else
  {
    Serial.print("Very Bad");
  }
}