#ifndef SteamMHZ19BPWM_H
#define SteamMHZ19BPWM_H

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <MHZ19PWM.h>

class SteamMHZ19BPWM
{
public:
  SteamMHZ19BPWM(int pwmPin);
  ~SteamMHZ19BPWM()
  {
    if (mhz19_pwm)
      delete mhz19_pwm;
  };

  void begin();   // 센서의 값을 초기화한다.
  void read();    // 센서의 값을 읽어온다.
  void display(); // 센서의 값을 출력한다.

  void _displayAirCondition_CO2(int CO2);

private:
  MHZ19PWM *mhz19_pwm;

  int _pwmPin;

  float _CO2;
  unsigned long _start;
  unsigned long _duration;
};

#endif
