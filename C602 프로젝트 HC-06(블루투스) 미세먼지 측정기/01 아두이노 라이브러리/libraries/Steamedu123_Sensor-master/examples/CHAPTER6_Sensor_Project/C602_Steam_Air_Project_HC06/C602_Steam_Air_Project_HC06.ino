/*
   @타이틀 : 블루투스 + PMS7003 + DHT22 
*/

#include <C602_Steam_Air_Bluetooth.h>
#include <C202_Steam_Air_PMS7003_Dust.h>
#include <C301_Steam_Air_DHT22_TempHumidity.h>

SteamBluetooth bt(2, 3);       // 블루투스 Rx(2), Tx(3) 핀 번호를 입력한다.
SteamPMS7003 pms7003(4, 5);   // 미세먼지 센서 인스턴스, Rx(4), Tx(5)핀 번호를 입력한다.
SteamDHT22 dht22(A1, DHT22);  // 온도/습도 센서 인스턴스, 핀 번호(A1)와 DHT22타입을 입력한다.


void setup() {
  Serial.begin(9600);     // 9600bps의 속도로 시리얼 통신을 시작한다.

  bt.begin();             // (1) 블루투스를 초기화 한다.
  pms7003.begin();        // (1) 미세먼지 센서를 초기화 한다.
  dht22.begin();          // (1) 온도/습도 센서를 초기화 한다.
}

void loop() {
  pms7003.read();       // (2) 미세먼지 센서의 값을 측정한다.
  dht22.read();         // (2) 온도/습도 센서의 값을 측정한다.

  bt.sendBT(pms7003.getPM2_5(), dht22.getTemp(), dht22.getHumidity());             // (3) 블루투스로 센서값을 전송한다.
}
