#ifndef SteamLCD16X2_H
#define SteamLCD16X2_H

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

 #include <LiquidCrystal.h>
 


class SteamLCD16X2
{
public:
  SteamLCD16X2();
  ~SteamLCD16X2(){};

  void begin();
  void display(int pm, int temp, int humidity);
  
  void clearLCD(int row);
  LiquidCrystal *lcd;  
 
  
  byte SpecialChar1[8] = { B00100, B01010, B01010, B01010, B01110, B11111, B11111, B01110 }; // temp
  byte SpecialChar2[8] = { B01000, B10100, B01000, B00000, B00111, B01000, B01000, B00111 };   // C
  byte SpecialChar3[8] = { B00100, B00100, B01010, B01010, B10001, B10001, B10001, B01110 }; // humity
  
  unsigned long previousMillis = 0;       
  const long interval = 1000;           // 주기	
};

#endif
