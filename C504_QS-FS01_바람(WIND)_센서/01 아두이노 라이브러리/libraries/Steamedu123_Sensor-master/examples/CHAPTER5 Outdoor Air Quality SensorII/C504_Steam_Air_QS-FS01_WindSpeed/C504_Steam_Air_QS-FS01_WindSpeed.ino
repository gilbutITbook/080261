/*
   @타이틀 : 풍속 측정 센서 
*/

#include <C504_Steam_Air_QS-FS01_WindSpeed.h> // 내부 라이브러리 헤더파일
#define AoutPIN A1

SteamQSFS01 qsfs01(AoutPIN);  // 인스턴스, 핀 번호를 입력한다.

void setup() {
  Serial.begin(57600);        // 57600bps의 속도로 시리얼 통신을 시작한다.
  qsfs01.begin();             // (1) 센서를 초기화 한다.
}

void loop() {
  qsfs01.read();              // (2) 센서의 값을 측정한다.
  qsfs01.display();           // (3) 센서의 값을 출력한다.
  delay(1000);                 // 1초 동안 대기한다.
}
