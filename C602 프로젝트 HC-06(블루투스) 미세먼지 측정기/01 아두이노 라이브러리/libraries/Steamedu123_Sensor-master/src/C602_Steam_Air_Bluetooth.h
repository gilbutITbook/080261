#ifndef SteamBluetooth_H
#define SteamBluetooth_H

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <SoftwareSerial.h>

class SteamBluetooth
{
public:
  SteamBluetooth(uint8_t rxPin, uint8_t txPin);
  ~SteamBluetooth(){if (bt) delete bt;};

  unsigned long previousMillis = 0;       
  const long interval = 4000;           // 4초 주기	  
  
  void begin();
  void sendBT(int pm2_5, int temp, int humidity);

private:
  SoftwareSerial *bt;  
  uint8_t _rxPin, _txPin;
};

#endif
