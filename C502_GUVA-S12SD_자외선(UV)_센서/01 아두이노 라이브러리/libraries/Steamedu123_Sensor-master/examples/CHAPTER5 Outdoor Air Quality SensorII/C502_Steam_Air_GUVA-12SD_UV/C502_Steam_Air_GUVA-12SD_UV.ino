/*
   @타이틀 : 자외선(UV) 측정 센서
*/

#include <C502_Steam_Air_GUVA-12SD_UV.h>    // 내부 라이브러리 헤더파일
#define AoutPIN A1

SteamGUVA12SD uv(AoutPIN);    // 인스턴스, 핀 번호를 입력한다.

void setup() {
  Serial.begin(9600);     // 9600bps의 속도로 시리얼 통신을 시작한다.
  uv.begin();     // (1) 센서를 초기화 한다.
}

void loop() {
  uv.read();      // (2) 센서의 값을 측정한다.
  uv.display();   // (3) 센서의 값을 출력한다.
  delay(1000);            // 1초 동안 대기한다.
}
