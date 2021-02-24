/*
  GP2Y1010AU0F library
  STEMEDU123 license
  written by SteamLabs
  homepage:  http://www.steamedu123.com   
  naver cafe : https://cafe.naver.com/arduinosensor/book5108749/48
  email : steamedu123@gmail.com
*/

#include "C203_Steam_Air_GP2Y1010AU0F_Dust.h"

#define COUNT_NUM 100

static unsigned long VoRawTotal = 0;
static int VoRawCount = 0;
// Set the typical output voltage in Volts when there is zero dust.
static float Voc = 0.6;
// Use the typical sensitivity in units of V per 100ug/m3.
const float K = 0.5;

/**
 * @함수명    : SteamGP2Y1010AU0F
 * @설명      : 생성자
*/
SteamGP2Y1010AU0F::SteamGP2Y1010AU0F(uint8_t sharpLEDPin, uint8_t sharpVoPin)
{
  _sharpLEDPin = sharpLEDPin; // Connect dust sensor LED pin to Arduino pin Digital
  _sharpVoPin = sharpVoPin;   // Connect dust sensor analog measure pin to Arduino A0 pin
}

/**
 * @함수명    : begin
 * @설명      : 센서를 초기화 한다. 
*/
void SteamGP2Y1010AU0F::begin()
{
  Serial.println("Sharp dust sensor GP2Y1010AU0F");
  Serial.println("Ready.....");
  Serial.println("--------------------------------");

  pinMode(_sharpLEDPin, OUTPUT);
  //delay(2000);
}

/**
 * @함수명    : read
 * @설명      : 센서의 값을 읽어온다
*/
bool SteamGP2Y1010AU0F::read()
{
  digitalWrite(_sharpLEDPin, LOW);     // Turn on the dust sensor LED by setting digital pin LOW.
  delayMicroseconds(_samplingTime);    // 280(0.28ms)
  int VoRaw = analogRead(_sharpVoPin); // Record the output voltage. This operation takes around 100 microseconds.
  //delayMicroseconds(_deltaTime);
  digitalWrite(_sharpLEDPin, HIGH); // Turn the dust sensor LED off by setting digital pin HIGH.
  delayMicroseconds(_sleepTime);    // 10ms

  // Use averaging if needed.
  float Vo = VoRaw;

  VoRawTotal += VoRaw;
  VoRawCount++;

  if (VoRawCount >= COUNT_NUM)
  {
    Vo = 1.0 * VoRawTotal / COUNT_NUM;
    VoRawCount = 0;
    VoRawTotal = 0;

    Vo = Vo / 1024.0 * 5.0;

    _calcVoltage(Vo);
    _calcDustDensity(Vo);
    return true;
  }
  else
  {
    return false;
  }
}

/**
 * @함수명    : _calcVoltage
 * @설명      : Compute the output voltage in Volts.
*/
void SteamGP2Y1010AU0F::_calcVoltage(float Vo)
{
  outVoltage = Vo * 1000.0;
  //printFValue("Vo", Vo*1000.0, "mV");
}

/**
 * @함수명    : _calcDustDensity
 * @설명      : Convert to Dust Density in units of ug/m3.
*/
void SteamGP2Y1010AU0F::_calcDustDensity(float Vo)
{
  float dV = Vo - Voc;
  if (dV < 0)
  {
    dV = 0;
    Voc = Vo;
  }

  dustDensity = dV / K * 100.0;
  //printFValue("DustDensity", dustDensity, "ug/m3", true);
}

/**
 * @함수명    : display
 * @설명      : 센서의 값을 출력한다. 
*/
void SteamGP2Y1010AU0F::display()
{
  Serial.print("Vo=");
  Serial.print(outVoltage);
  Serial.print("mV ");

  Serial.print("PM2.5=");
  Serial.print(dustDensity);
  Serial.print("ug/m3 ");

  _displayAirCondition_PM25(dustDensity);
  Serial.println(" ");
}

/**
 * @함수명    : _displayAirCondition_PM25
 * @설명      : 미세먼지 PM2.5 상태를 출력한다. 
*  좋음(Good) : 0-15
 * 보통(Normal) : 16-35
 * 나쁨(Bad) : 36-75
 * 매우나쁨(Very Bad) :76-
*/
void SteamGP2Y1010AU0F::_displayAirCondition_PM25(unsigned int pm2_5)
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
