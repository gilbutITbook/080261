/*
   @타이틀 : 이산화질소(NO2) 측정 센서
*/

#include <C403_Steam_Air_MICS-4514_NO2.h>   // 내부 라이브러리 헤더 파일

SteamMICS4514 mics4514(3, A0, A1);    // 인스턴스, 핀 번호(pre, nox, red)를 입력받는다.

void setup() {
  Serial.begin(9600);       // 9600bps의 속도로 시리얼 통신을 시작한다.
  mics4514.begin();         // (1) 센서를 초기화한다.
}

void loop() {
  mics4514.read();          // (2) 센서의 값을 측정한다.
  mics4514.display();       // (3) 센서의 값을 출력한다.
  delay(1000);
}
