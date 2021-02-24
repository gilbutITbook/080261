#ifndef SteamNovaSDS011PWM_H
#define SteamNovaSDS011PWM_H

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif


class SteamNovaSDS011PWM
{
public:
  SteamNovaSDS011PWM(int pm2_5, int pm10);
  ~SteamNovaSDS011PWM() {};

  void begin();
  void read();
  void display();
  
  void _displayAirCondition_PM25(unsigned int pm2_5);
  void _displayAirCondition_PM10(unsigned int pm10);

  unsigned long pulse2ugm3(unsigned long pulse);
  
  int getPM2_5();

private:
  

  int _pm25Pin;
  int _pm10Pin;  

  int pm10 = 0, pm25 = 0;  

  unsigned long  pm25Pluse = 0 ;
  unsigned long  pm10Pluse = 0;

  unsigned long pm25ugm3 = 0;
  unsigned long pm10ugm3 = 0;
  
};

#endif
