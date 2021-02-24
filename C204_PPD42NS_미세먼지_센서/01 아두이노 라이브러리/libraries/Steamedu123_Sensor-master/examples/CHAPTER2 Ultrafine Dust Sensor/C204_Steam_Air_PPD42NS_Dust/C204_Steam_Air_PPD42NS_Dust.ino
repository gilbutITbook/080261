/*
   @타이틀 : PPD42NS 미세먼지 센서
*/

#include <C204_Steam_Air_PPD42NS_Dust.h>  // 내부 라이브러리 헤더파일
#define PIN 3

SteamPPD42NS ppd42ns(PIN);    // 인스턴스, 핀 번호를 입력한다.

void setup() {
  Serial.begin(9600);	  // 96000bps의 속도로 시리얼 통신을 시작한다.
  ppd42ns.begin();      // (1) 센서를 초기화 한다.
}

void loop() {
  ppd42ns.read();       // (2) 센서의 값을 측정한다.
  ppd42ns.display();    // (3) 센서의 값을 출력한다.
}
