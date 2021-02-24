 /*
   @타이틀 : 아황산가스(SO2) 센서
*/

#include <C405_Steam_Air_DGS-SO2_SO2.h> // 내부 라이브러리 헤더 파일

SteamDGSSO2 dgsSO2; // 인스턴스, 핀 번호를 입력한다.

void setup() {
  Serial.begin(9600);   // 9600bps의 속도로 시리얼 통신을 시작한다.
  dgsSO2.begin();       // (1) 센서를 초기화한다.
}

void loop() {
  dgsSO2.read();        // (2) 센서의 값을 측정한다.
  dgsSO2.display();     // (3) 센서의 값을 출력한다.
}
