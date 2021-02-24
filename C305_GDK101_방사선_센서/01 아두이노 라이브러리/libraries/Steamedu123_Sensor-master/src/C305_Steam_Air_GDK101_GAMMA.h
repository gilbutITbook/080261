#ifndef SteamGDK101_H
#define SteamGDK101_H

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "gdk101_i2c.h"

class SteamGDK101
{

public:
  SteamGDK101(void){};
  ~SteamGDK101(void){};

  void begin();
  void read();
  void display();

private:
  GDK101_I2C _gdk101;

  float avg10min;
  float avg1min;
  float fw_vers;
  int _status;

  bool vibration;
  byte mea_min;
  byte mea_sec;

  //output
  char out_buff[48];

  void displayReset(bool s);
  void displayStatus(int s);
  void displayVibration(bool s);

  float convert_uSvTomSv(float sv);
  void _displayAirCondition_RN(float uSv);
};

#endif
