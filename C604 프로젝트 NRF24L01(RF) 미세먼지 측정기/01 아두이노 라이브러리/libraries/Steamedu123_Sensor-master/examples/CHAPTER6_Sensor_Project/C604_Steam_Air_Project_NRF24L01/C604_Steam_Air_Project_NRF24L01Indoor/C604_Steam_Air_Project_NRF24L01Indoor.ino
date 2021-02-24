/*
   @타이틀 : RF 프로젝트(수신부)
*/

#include <C602_Steam_Air_NRF24L01.h>
#include <C602_Steam_Air_OLED.h>

SteamNRF24L01 rf;
SteamOLED oled;

void setup() {
  Serial.begin(9600);     // 9600bps의 속도로 시리얼 통신을 시작한다.
  rf.begin();             // rf 초기화 한다
  Serial.println("Listening...");  // 데이터 수신 대기
}

void loop() {
  rf.receive();            // 센서 데이터를 수신한다.

  // OLED 에 센서데이터를 출력한다.
  oled.display(rf.getPm(), rf.getTemp(), rf.getHumi(), rf.getPa());
}
