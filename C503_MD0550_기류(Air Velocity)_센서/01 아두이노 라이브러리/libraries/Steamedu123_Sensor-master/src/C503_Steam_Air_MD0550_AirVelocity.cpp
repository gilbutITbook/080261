/*
  MD0550 library
  STEMEDU123 license
  written by SteamLabs
  homepage: http://www.steamedu123.com   
  naver cafe : https://cafe.naver.com/arduinosensor/book5108749/60
  email : steamedu123@gmail.com
*/

#include "C503_Steam_Air_MD0550_AirVelocity.h"

#define CALM 0            // Smoke rises vertically
#define LIGHT_AIR 1       // Smoke drifts with air, weather vanes inactive
#define LIGHT_BREEZE 2    // Weather vanes active, wind felt on face, leaves rustle
#define GENTLE_BREEZE 3   // Leaves & small twigs move, light flags extend
#define MODERATE_BREEZE 4 // Small branches sway, dust & loose paper blows about
#define FRESH_BREEZE 5    // Small trees sway, waves break on inland waters
#define STRONG_BREEZE 6   // Large branches sway, umbrellas difficult to use
#define MODERATE_GALE 7   // Whole trees sway, difficult to walk against wind
#define FRESH_GALE 8      // Twigs broken off trees, walking against wind very difficult
#define STRONG_GALE 9     // Slight damage to buildings, shingles blown off roof
#define WHOLE_GALE 10     // Trees uprooted, considerable damage to buildings
#define STORM 11          //Widespread damage, very rare occurrence
#define HURRICANE 12      // Violent destruction

String WIND[] = {"CALM", "LIGHT_AIR",
                 "LIGHT_BREEZE", "GENTLE_BREEZE",
                 "MODERATE_BREEZE", "FRESH_BREEZE",
                 "STRONG_BREEZE", "MODERATE_GALE",
                 "FRESH_GALE", "STRONG_GALE",
                 "WHOLE_GALE", "STORM", "HURRICANE"};

/**
 * @함수명    : SteamMD0550
 * @설명      : 생성자
*/
SteamMD0550::SteamMD0550(uint8_t rvPin, uint8_t tmpPin)
{
  _rvPin = rvPin;
  _tmpPin = tmpPin;
}

/**
 * @함수명    : begin
 * @설명      : 센서를 초기화 한다. 
*/
void SteamMD0550::begin()
{
  Serial.println("MD0550 Thermal Anememoter Sensor");
  Serial.println("Ready.....");
  Serial.println("--------------------------------");
}

/**
 * @함수명    : read
 * @설명      : 센서의 값을 읽어온다
*/
void SteamMD0550::read()
{

  if (millis() - lastMillis > 200)
  {

    TMP_Therm_ADunits = analogRead(_tmpPin);
    RV_Wind_ADunits = analogRead(_rvPin);
    RV_Wind_Volts = (RV_Wind_ADunits * 0.0048828125);

    TempCtimes100 = (0.005 * ((float)TMP_Therm_ADunits * (float)TMP_Therm_ADunits)) - (16.862 * (float)TMP_Therm_ADunits) + 9075.4;
    zeroWind_ADunits = -0.0006 * ((float)TMP_Therm_ADunits * (float)TMP_Therm_ADunits) + 1.0727 * (float)TMP_Therm_ADunits + 47.172;

    zeroWind_volts = (zeroWind_ADunits * 0.0048828125) - zeroWindAdjustment;

    WindSpeed_MPH = pow(((RV_Wind_Volts - zeroWind_volts) / .2300), 2.7265);

    //display();

    lastMillis = millis();
  }
}

/**
 * @함수명    : display
 * @설명      : 센서의 값을 출력한다. 
*/
void SteamMD0550::display()
{
  float ms = WindSpeed_MPH * 0.44704;
  Serial.print("WindSpeed ");
  Serial.print(ms);
  Serial.print("m/s");

  Serial.print(" => ");
  _displayAirCondition(ms);
  //int index =  BeaufortWindScale();
  //Serial.print("  BeauforWindScale:");
  //Serial.println(WIND[index]);

  Serial.print("--- TMP(v):");
  Serial.print(TMP_Therm_ADunits * 0.0048828125);

  Serial.print(" RV(V):");
  Serial.print((float)RV_Wind_Volts);

  Serial.print(" TempC*100:");
  Serial.print(TempCtimes100);

  Serial.print(" ZeroWind volts:");
  Serial.println(zeroWind_volts);
}

/**
 * @함수명    : display
 * @설명      : 풍속 4단계 상태를 출력한다. 
*/
void SteamMD0550::_displayAirCondition(float speed)
{
  if (speed < 0.5)
  {
    Serial.print("Good");
  }
  else if (speed < 1)
  {
    Serial.print("Normal");
  }
  else if (speed < 1.5)
  {
    Serial.print("Bad");
  }
  else
  {
    Serial.print("Very Bad");
  }
}

/**
 * @함수명    : BeaufortWindScale
 * @설명      : 보퍼트(beaufort) 풍력계급표 기준 상태 값을 리턴한다. 
*/
int SteamMD0550::BeaufortWindScale()
{
  float wind = (float)WindSpeed_MPH;
  if (wind < 1)
  {
    return CALM;
  }
  else if (wind <= 3)
  { // 1~3 mph
    return LIGHT_AIR;
  }
  else if (wind <= 7)
  { // 3~7
    return LIGHT_BREEZE;
  }
  else if (wind <= 12)
  { // 8~12
    return GENTLE_BREEZE;
  }
  else if (wind <= 17)
  { // 13~17
    return MODERATE_BREEZE;
  }
  else if (wind <= 24)
  { // 18~24
    return FRESH_BREEZE;
  }
  else if (wind <= 30)
  { // 25~30
    return STRONG_BREEZE;
  }
  else if (wind <= 38)
  { // 31~38
    return MODERATE_GALE;
  }
  else if (wind <= 46)
  { // 39~46
    return FRESH_GALE;
  }
  else if (wind <= 54)
  { // 47~54
    return STRONG_GALE;
  }
  else if (wind <= 63)
  { // 55~63
    return WHOLE_GALE;
  }
  else if (wind <= 72)
  { // 64~72
    return STORM;
  }
  else
  { // 73~82
    return HURRICANE;
  }
}
