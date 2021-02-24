/*
   @타이틀 : GP2Y1010AU0F 미세먼지 센서
*/

#include <C203_Steam_Air_GP2Y1010AU0F_Dust.h>   // 내부 라이브러리 헤더파일
#define sharpLEDPin    3
#define sharpVoPin     A1

SteamGP2Y1010AU0F sensor(sharpLEDPin, sharpVoPin);    // 인스턴스, 핀 번호를 입력한다.

void setup() {
  Serial.begin(9600);   // 96000bps의 속도로 시리얼 통신을 시작한다.
  sensor.begin();       // (1) 센서를 초기화 한다.
}

void loop() {
  if (sensor.read()) {  // (2) 센서의 값을 측정한다.
    sensor.display();   // (3) 센서의 값을 출력한다.
  }
}
