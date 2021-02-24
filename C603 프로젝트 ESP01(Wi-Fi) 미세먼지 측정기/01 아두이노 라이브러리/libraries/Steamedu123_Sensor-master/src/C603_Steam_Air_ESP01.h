#ifndef SteamESP01_H
#define SteamESP01_H

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <SoftwareSerial.h>

class SteamESP01
{
public:
  SteamESP01(uint8_t rxPin, uint8_t txPin);
  ~SteamESP01(){if (esp01) delete esp01;};

  void begin(String ssid, String pass, String key, long updatetime); 
  void sendData(int pm, int temp, int humidity);

private:
  SoftwareSerial *esp01;  
  uint8_t _rxPin, _txPin;
  
  int ledPin = 13; // 업로드 알림 LED 설정 (아두이노 우노 Board LED)
  String apiKey;
  
  unsigned long previousMillis = 0;        // will store last time LED was updated
  long interval = 15000;           // interval at which to blink (milliseconds)

  void sendToThinkspeak(int pm, int temp, int humidity);
  String sendATcmd(String command, const int timeout, boolean debug);
};

#endif
