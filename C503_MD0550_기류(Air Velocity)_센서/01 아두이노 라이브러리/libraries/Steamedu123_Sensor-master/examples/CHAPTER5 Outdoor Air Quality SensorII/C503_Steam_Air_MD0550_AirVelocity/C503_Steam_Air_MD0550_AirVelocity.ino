/*
   @타이틀 : 기류 측정 센서
*/
 
#include <C503_Steam_Air_MD0550_AirVelocity.h>  // 내부 라이브러리 헤더 파일
#define RvPIN  A2
#define TmpPIN A1

SteamMD0550 md0550(RvPIN, TmpPIN);    // 인스턴스, 핀 번호를 입력한다.

void setup() {
  Serial.begin(57600);    // 57600bps의 속도로 시리얼 통신을 시작한다.
  md0550.begin();         // (1) 센서를 초기화한다.
}

void loop() {
  md0550.read();          // (2) 센서의 값을 측정한다.
  md0550.display();       // (3) 센서의 값을 출력한다.
  delay(1000);            // 1초 동안 대기한다.
}
