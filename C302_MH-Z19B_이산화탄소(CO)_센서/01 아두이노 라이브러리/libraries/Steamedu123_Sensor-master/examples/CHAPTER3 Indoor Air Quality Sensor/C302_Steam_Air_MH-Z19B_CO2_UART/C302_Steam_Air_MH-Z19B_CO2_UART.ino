/*
   @타이틀 : 이산화탄소 센서 
*/

#include <C302_Steam_Air_MH-Z19B_CO2_UART.h> // 라이브러리 헤더
#define rxPin 3
#define txPin 2

SteamMHZ19B mhz19b_uart(rxPin, txPin);  // 인스턴스, 핀 번호를 입력한다

void setup() {
  Serial.begin(115200);     // 115200bps의 속도로 시리얼 통신을 시작한다.
  mhz19b_uart.begin();      // (1) 센서를 초기화 한다.
}

void loop() {
  mhz19b_uart.read();       // (2) 센서의 값을 측정한다.
  mhz19b_uart.display();    // (3) 센서의 값을 출력한다

  delay(5000);              // 5초 동안 대기한다.
}
