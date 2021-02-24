/*
   @타이틀 : ZE08-CH2O 포름알데히드 측정 센서 
*/

#include <C303_Steam_Air_ZE08-CH2O_HCHO.h>    // 내부 라이브러리 헤더파일

SteamZE08CH2O hcho(A1);          // dac::인스턴스, 핀 번호를 입력한다.

void setup() {
  Serial.begin(9600);   // 9600bps의 속도로 시리얼 통신을 시작한다.
  hcho.begin();         // (1) 센서를 초기화 한다.
}

void loop() {
  hcho.read();          // (2) 센서의 값을 측정한다.
  hcho.display();       // (3) 센서의 값을 출력한다
  delay(1000);          // 1초 동안 대기한다.
}
