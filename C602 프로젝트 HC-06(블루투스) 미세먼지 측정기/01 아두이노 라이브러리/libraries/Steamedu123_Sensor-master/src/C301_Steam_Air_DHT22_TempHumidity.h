#ifndef SteamDHT22_H
#define SteamDHT22_H

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <DHT.h>

class SteamDHT22
{
public:
  SteamDHT22(uint8_t pin, uint8_t type);
  ~SteamDHT22()
  {
    if (_dht22)
      delete _dht22;
  };

  void begin();   // ������ ���� �ʱ�ȭ�Ѵ�.
  bool read();    // ������ ���� �о�´�. 
  void display(); // ������ ���� ����Ѵ�.
  
  int getTemp();
  int getHumidity();
	

private:
  DHT *_dht22;
  uint8_t _pin, _type;

  float _humidity = 0;
  float _temperature = 0;

  void _displayAirCondition_Temp(float temp);
  void _displayAirCondition_Humidity(float humidity);
};

#endif
