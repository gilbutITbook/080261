/*
   @타이틀 : PMS7003 미세먼지 센서
*/

#include <C202_Steam_Air_PMS7003_Dust.h>    // 내부 라이브러리 헤더파일
#define RxPIN 3
#define TxPIN 2

SteamPMS7003 pms7003(RxPIN, TxPIN);   // 인스턴스, RX/TX핀 번호를 입력한다.

void setup() {
  Serial.begin(9600);     // 9600bps의 속도로 시리얼 통신을 시작한다.
  pms7003.begin();        // (1) 센서를 초기화 한다.
}

void loop() {
  if (pms7003.read()) {   // (2) 센서의 값을 측정한다.
    pms7003.display();    // (3) 센서의 값을 출력한다.
  }
}
