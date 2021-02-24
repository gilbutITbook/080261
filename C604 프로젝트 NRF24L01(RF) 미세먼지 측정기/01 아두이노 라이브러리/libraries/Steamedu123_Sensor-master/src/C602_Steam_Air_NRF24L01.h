#ifndef SteamNRF24L01_H
#define SteamNRF24L01_H

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <nRF24L01.h>

class SteamNRF24L01
{
public:
  SteamNRF24L01();
  ~SteamNRF24L01()
  {
    if (Mirf)
      delete Mirf;
  };

  unsigned long previousMillis = 0;
  const long interval = 1000;

  void begin();
  void send(unsigned int pm2_5, float temp, uint32_t humidity, uint32_t hPa);
  void receive();

  byte value[6];

  byte getPm();
  byte getTemp();
  byte getHumi();
  String getPa();

private:
  Nrf24l *Mirf;

  void dataDebug();
};

#endif
