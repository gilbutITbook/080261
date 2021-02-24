/*
   @타이틀 : RF 프로젝트(송신부) 
*/

#include <C602_Steam_Air_NRF24L01.h>
#include <C202_Steam_Air_PMS7003_Dust.h>
#include <C501_Steam_Air_BME280_hPa.h>

SteamPMS7003 pms7003(4, 5);   // 미세먼지 센서 인스턴스, Rx(4), Tx(5)핀 번호를 입력한다.
SteamBME280 bme280;
SteamNRF24L01 rf;

byte value[4];

void setup() {
  Serial.begin(9600);     // 9600bps의 속도로 시리얼 통신을 시작한다.

  pms7003.begin();        // 미세먼지 센서를 초기화 한다.
  bme280.begin();          //온도/습도/기압 센서를 초기화 한다.
  rf.begin();
}

void loop() {

  bme280.read();
  pms7003.read();
  rf.send(pms7003.getPM2_5(), bme280.getTemp(), bme280.getHumidity(), bme280.gethPa());
}
