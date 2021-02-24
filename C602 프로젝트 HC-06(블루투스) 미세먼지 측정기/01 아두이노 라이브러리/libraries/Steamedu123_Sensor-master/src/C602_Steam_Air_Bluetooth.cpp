/*
  HC-06 Bluetooth library
  STEMEDU123 license
  written by SteamLabs
*/


#include "C602_Steam_Air_Bluetooth.h"


/**
 * @함수명    : SteamBluetooth
 * @설명      : 생성자
*/
SteamBluetooth::SteamBluetooth(uint8_t rxPin, uint8_t txPin) {
  _rxPin = rxPin;
  _txPin = txPin;
} 

/**
 * @함수명    : begin
 * @설명      :  블루투스 객체를 생성한다. 
*/
void SteamBluetooth::begin() {
  Serial.println("Bluetooth Init");  
  Serial.println("--------------------------------");  
  
  bt = new SoftwareSerial(_rxPin, _txPin);  
  bt->begin(9600);
  
  pinMode(13, OUTPUT); // 내장 13번 LED
}
  
 
 /**
 * @함수명    : sendBT
 * @설명      : 스마트폰으로 데이터를 전송한다. 
*/
 void SteamBluetooth::sendBT(int pm2_5, int temp, int humidity){
  unsigned long currentMillis = millis();
  digitalWrite(13, LOW); // 내장 13번 LED 끄기
  
  if (currentMillis - previousMillis >= interval) {    // 인터발 주기(4초) 로 데이터 전송
    previousMillis = currentMillis;    
	digitalWrite(13, HIGH);  // 내장 13번 LED 켜기

    
    // BT 데이터 전송
    // 예: 999, 10, 25, 60, 888
    //bt->print("999");  // 블루투스 데이터가 한번에 많이 도착하거나 적게 도착하였을 때 데이터의 처음과 끝을 정해 제대로 된 데이터가 왔는지 확인
    //bt->print(", ");
	
	char buf[10];
	if(pm2_5 < 10) sprintf(buf, "0%d", pm2_5);
	else if(pm2_5 > 100) sprintf(buf, "%d", 99);
	//Serial.println(buf);
	
    bt->print(buf); // 블루투스로 미세먼지 값을 전송한다.    
    //bt->print(", ");
    bt->print(temp);     // 블루투스로 온도 값을 전송한다.
    //bt->print(", ");
    bt->print(humidity); // 블루투스로 습도 값을 전송한다.   
    //bt->print(", ");
    //bt->print("888"); // 블루투스 데이터가 한번에 많이 도착하거나 적게 도착하였을 때 데이터의 처음과 끝을 정해 제대로 된 데이터가 왔는지 확인
	
	char ch[10];
	sprintf(ch, "%s%d%d", buf, temp, humidity);
	Serial.println(ch);
	
  }    
}
