#ifndef SteamPMS7003_H
#define SteamPMS7003_H

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <SoftwareSerial.h>

#define COUNT_NUM 5 // 센서값을 5번 누적해서 평균값을 구할 때 사용한다. 실시간 센서값을 원할 때는 1로 변경해서 사용하면 된다.
#define MAX_FRAME_LEN 64

class SteamPMS7003
{
public:
  SteamPMS7003(uint8_t rxPin, uint8_t txPin); // 생성자
  ~SteamPMS7003()                             // 소멸자
  {
    if (_pms7003)
      delete _pms7003;
  };

  void begin();   // 센서의 값을 초기화한다.
  bool read();    // 센서의 값을 읽어온다.
  void display(); // 센서의 값을 출력한다.

  void _getSensor();
  bool _getSensorPacket();
  void _getSensorAverageValue();
  void _displayAirCondition_PM25(unsigned int pm2_5); // 미세먼지 PM2.5 상태를 출력한다.
  void _displayAirCondition_PM10(unsigned int pm10);  // 미세먼지 PM10 상태를 출력한다.

  unsigned int getPM2_5();  // PM2.5의 값을 리턴한다.
  unsigned int getPM10_0(); // PM10의 값을 리턴한다.

private:
  uint8_t _txPin;
  uint8_t _rxPin;

  SoftwareSerial *_pms7003;

  uint32_t incomingByte;
  uint32_t detectOff = 0;
  uint32_t frameLen = MAX_FRAME_LEN;
  uint32_t d1, d2, d3;
  unsigned int calcChecksum = 0;
  unsigned int pm2_5 = 0, pm10_0 = 0;
  unsigned int avrPM2_5 = 0, avrPM10_0 = 0;
  uint32_t cnt = 0;

  bool inFrame = false;
  char printbuf[256];
  char frameBuf[MAX_FRAME_LEN];

  struct PMS7003_framestruct // 측정된 센서의 값을 저장하는 구조체
  {
    byte frameHeader[2];
    uint32_t frameLen = MAX_FRAME_LEN;
    uint32_t concPM2_5_CF1;
    uint32_t concPM10_0_CF1;
    uint32_t checksum;
  } thisFrame;
};

#endif
