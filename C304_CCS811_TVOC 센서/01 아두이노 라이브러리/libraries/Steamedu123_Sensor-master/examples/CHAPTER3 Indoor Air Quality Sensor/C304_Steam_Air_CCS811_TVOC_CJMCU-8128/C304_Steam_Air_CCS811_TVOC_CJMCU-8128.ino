/*
   @타이틀 : CJMCU-8128 CCS811 TVOC 센서  (CCS811+SI7021_BMP280)
   @AliExpress : https://aliexpi.com/Qyvr 
*/

#include <C304_Steam_Air_CCS811_TVOC_CJMCU-8128.h> // 내부 라이브러리 헤더 파일

SteamCJMCU8128 cjmcu8128; // 인스턴스

void setup() {
  Serial.begin(9600); // 9600bps의 속도로 시리얼 통신을 시작한다.
  cjmcu8128.begin();  // (1) 센서를 초기화한다.
}

void loop() {
  cjmcu8128.read();    // (2) 센서의 값을 측정한다.
  cjmcu8128.display(); // (3) 센서의 값을 출력한다
  delay(1000);          // 1초 동안 대기한다.
}
