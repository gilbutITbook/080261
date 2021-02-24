#ifndef SteamOLED_H
#define SteamOLED_H

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif



class SteamOLED
{
public:
  SteamOLED();
  ~SteamOLED(){};

  void begin();
  void display(byte pm2_5, byte temp, byte humidity, String hPa);
  
  
private:
  
};

#endif
