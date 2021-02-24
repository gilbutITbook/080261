/*
   @타이틀 : MQ-7 일산화탄소 센서
*/

#include <C402_Steam_Air_MQ7_CO.h>    // 내부 라이브러리 헤더파일
#define AoutPIN A1

SteamMQ7 mq7(AoutPIN);// 인스턴스, 핀 번호를 입력 받는다.

void setup() {
  Serial.begin(9600);   // 9600bps의 속도로 시리얼 통신을 시작한다.
  mq7.begin();          // (1) 센서를 초기화 한다.
}

void loop() {
  mq7.read();           // (2) 센서의 값을 측정한다.
  mq7.display();        // (3) 센서의 값을 출력한다.
  delay(1000);          // 1초 동안 대기한다.
}
