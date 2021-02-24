/*
   @타이틀 : MiCS-6814 암모니아(NH3) 측정 센서
*/

#include <C404_Steam_Air_MICS-6814_MOS.h>   // 내부 라이브러리 헤더파일

SteamMICS6814 mics6814;     // 인스턴스

void setup() {
  Serial.begin(115200);     // 115200bps의 속도로 시리얼 통신을 시작한다.
  mics6814.begin();         // (1) 센서를 초기화 한다.
}

void loop() {
  mics6814.read();          // (2) 센서의 값을 측정한다.
  mics6814.display();       // (3) 센서의 값을 출력한다.
  delay(3000);              // 1초 동안 대기한다.
}
