/*
   @타이틀 : DHT22 온도/습도 센서 
*/

#include <C301_Steam_Air_DHT22_TempHumidity.h>  // 내부 라이브러리 헤더파일
#define PIN 3

SteamDHT22 dht22(PIN, DHT22);  // 인스턴스, 핀 번호와 DHT22타입을 입력한다.

void setup() {
  Serial.begin(9600);     // 9600bps의 속도로 시리얼 통신을 시작한다.
  dht22.begin();          // (1) 센서를 초기화 한다.
}

void loop() {
  dht22.read();         // (2) 센서의 값을 측정한다.
  dht22.display();      // (3) 센서의 값을 출력한다.

  delay(1000);          // 1초 동안 대기한다.
}
