#ifndef SteamMHZ19B_H
#define SteamMHZ19B_H

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <MHZ19UART.h>

class SteamMHZ19B
{
public:
  SteamMHZ19B(int rxPin, int txPin);
  ~SteamMHZ19B()
  {
    if (mhz19_uart)
      delete mhz19_uart;
  };

  void begin();   // 센서의 값을 초기화한다.
  void read();    // 센서의 값을 읽어온다.
  void display(); // 센서의 값을 출력한다.

  void _displayAirCondition_CO2(int CO2);

private:
  MHZ19 *mhz19_uart;
  int _rxPin, _txPin;

  MHZ19_RESULT response;

  int _CO2;
  int _miniCO2;
  int _temperature;
  int _Accuracy;
};

#endif
