/*
   @타이틀 : MQ131 오존 센서 
*/

#include <C401_Steam_Air_MQ131_O3.h>    // 내부 라이브러리 헤더파일
#define AoutPIN A1
#define TEMP 24 // °C
#define HUMI 40 //  %

SteamMQ131 mq131(AoutPIN);    // 인스턴스, 핀 번호를 입력한다.

void setup() {
  Serial.begin(115200);       // 115200bps의 속도로 시리얼 통신을 시작한다.
  mq131.begin();              // (1) 센서를 초기화 한다.
}

void loop() {
  mq131.read(TEMP, HUMI);     // (2) 센서의 값을 측정한다.
  mq131.display();            // (3) 센서의 값을 출력한다

  delay(6000);                // 6초 동안 대기한다.
}
