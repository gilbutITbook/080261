/*
   @타이틀 : Nova SDS011 미세먼지 센서
*/

#include <C205_Steam_Air_NovaSDS011_Dust.h>    // 내부 라이브러리 헤더파일

#define RxPIN 3
#define TxPIN 2

SteamNovaSDS011 novasds011(RxPIN, TxPIN); // 인스턴스, 핀 번호를 입력한다.

void setup() {
  Serial.begin(9600);     // 9600bps의 속도로 시리얼 통신을 시작한다.
  novasds011.begin();     // (1) 센서를 초기화 한다.
}

void loop() {
  novasds011.read();      // (2) 센서의 값을 측정한다.
  novasds011.display();   // (3) 센서의 값을 출력한다
}
