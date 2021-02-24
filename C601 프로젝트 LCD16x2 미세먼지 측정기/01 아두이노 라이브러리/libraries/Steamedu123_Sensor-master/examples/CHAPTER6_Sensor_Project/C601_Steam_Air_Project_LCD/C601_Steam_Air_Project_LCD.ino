/*
   @타이틀 : 프로젝트 , 16x2 LCD + PMS7003 + DHT22 
*/


#include <C601_Steam_Air_LCD16X2.h>
#include <C202_Steam_Air_PMS7003_Dust.h>
#include <C301_Steam_Air_DHT22_TempHumidity.h>

SteamLCD16X2 lcd16x2;           // 16x2 LCD 인스턴스
SteamPMS7003 pms7003(2, 3);   // 미세먼지 센서 인스턴스, Rx(D2) 핀 번호를 입력한다.
SteamDHT22 dht22(A1, DHT22);  // 온도/습도 센서 인스턴스, 핀 번호(A1)와 DHT22타입을 입력한다.

void setup() {
  Serial.begin(9600);     // 9600bps의 속도로 시리얼 통신을 시작한다.

  lcd16x2.begin();            // (1) 16x2 lcd를 초기화 한다.
  pms7003.begin();        // (1) 미세먼지 센서를 초기화 한다.
  dht22.begin();          // (1) 온도/습도 센서를 초기화 한다.
}

void loop() {
  pms7003.read();       // (2) 미세먼지 센서의 값을 측정한다.
  dht22.read();         // (2) 온도/습도 센서의 값을 측정한다.

  pms7003.display();   // (3) 시리얼 미세먼지 출력
  dht22.display();     // (3) 시리얼 온도/습도 출력

  lcd16x2.display(pms7003.getPM2_5(), dht22.getTemp(), dht22.getHumidity());             // (4) lcd로 센서값을 표시한다.
}
