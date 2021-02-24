/*
   @타이틀 : GDK101 방사선(감마) 측정 센서 
*/

#include <C305_Steam_Air_GDK101_GAMMA.h>    // 내부 라이브러리 헤더 파일

SteamGDK101 gdk101; // 인스턴스

void setup() {
  Serial.begin(115200);   // 115200bps의 속도로 시리얼 통신을 시작한다.
  gdk101.begin();         // (1) 센서를 초기화한다.
}

void loop() {
  gdk101.read();          // (2) 센서의 값을 측정한다.
  gdk101.display();       // (3) 센서의 값을 출력한다
  delay(2000);            // 2초 동안 대기한다.
}
