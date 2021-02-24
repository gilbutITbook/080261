/*
  ESP01 library
  STEMEDU123 license
  written by SteamLabs
*/


#include "C603_Steam_Air_ESP01.h"
#include <stdlib.h>
#define DEBUG true
 

/**
 * @함수명    : SteamESP01
 * @설명      : 생성자
*/
SteamESP01::SteamESP01(uint8_t rxPin, uint8_t txPin) {
  _rxPin = rxPin;
  _txPin = txPin;
 
} 

/**
 * @함수명    : begin
 * @설명      : 객체를 생성한다. 
*/
void SteamESP01::begin(String ssid, String pass, String key, long updatetime) {
  //Serial.println("esp01 Init");  
  //Serial.println("--------------------------------");  
      
  esp01 = new SoftwareSerial(_rxPin, _txPin);  
  esp01->begin(9600);
  
  /*AT Command 이용*/
  sendATcmd("AT+RST\r\n", 2000, DEBUG); //reset module
  sendATcmd("AT+CWMODE=1\r\n", 1000, DEBUG); //1 : Station Mode, WiFi 디바이스 기능  
  sendATcmd("AT+CWJAP=\"" + ssid + "\",\"" + pass + "\"\r\n", 3000, DEBUG);
  //sendData("AT+CIFSR\r\n", 5000, 1);
  
  apiKey = key;   // thingspeak apikey
  interval = updatetime; // inspeak.com 로 센서값 전송 주기, 15초
  
  pinMode(ledPin, OUTPUT);    
}
 

/**
 * @함수명    : sendData
 * @설명      : 인터벌 주기로 데이터를 네트워크로 보낸다. 
*/
void SteamESP01::sendData(int pm, int temp, int humidity) {
  digitalWrite(ledPin, LOW);
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    digitalWrite(ledPin, HIGH);
    sendToThinkspeak(pm, temp, humidity);  
  }  
}



/**
 * @함수명    : sendToThinkspeak
 * @설명      : Thinkspeak.com으로 데이터를 보낸다. 
*/
void SteamESP01::sendToThinkspeak(int pm, int temp, int humidity) {

  // String 변환
  char pmBuf[16];
  String strPM = dtostrf(pm, 4, 1, pmBuf);  
  char tempBuf[16];
  String strTemp = dtostrf(temp, 4, 1, tempBuf);
  char humidityBuf[16];
  String strHumidity = dtostrf(humidity, 4, 1, humidityBuf);


  Serial.print(strPM);
  Serial.print(strTemp);
  Serial.println(strHumidity);

  // TCP 연결
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += "184.106.153.149"; // api.thingspeak.com 접속 IP
  cmd += "\",80";           // api.thingspeak.com 접속 포트, 80
  esp01->println(cmd);

  if (esp01->find("Error")) {
    Serial.println("AT+CIPSTART error");
    return;
  }

  // GET 방식으로 보내기 위한 String, Data 설정
  String getStr = "GET /update?api_key=";
  getStr += apiKey;
  getStr += "&field1=";
  getStr += String(strPM);
  getStr += "&field2=";
  getStr += String(strTemp);
  getStr += "&field3=";
  getStr += String(strHumidity);
  getStr += "\r\n\r\n";

  // Send Data
  cmd = "AT+CIPSEND=";
  cmd += String(getStr.length());  
  esp01->println(cmd);


  if (esp01->find(">")) {
    esp01->print(getStr);
  }
  else {
    esp01->println("AT+CIPCLOSE");
    //alert user
    Serial.println("AT+CIPCLOSE");
  }

  // Thingspeak 최소 업로드 간격 15초를 맞추기 위한 delay
  //delay(16000);
}


/**
 * @함수명    : 
 * @설명      : esp01의 정보를 알아내고 설정하기 위한 함수 선언
*/
String SteamESP01::sendATcmd(String command, const int timeout, boolean debug) {
  String response = "";
  esp01->print(command); //command를 esp01에 보냄
  long int time = millis();

  while ((time + timeout) > millis()) {
    while (esp01->available()) {
      /*esp가 가진 데이터를 시리얼 모니터에 출력하기 위함*/
      char c = esp01->read(); //다음 문자를 읽어옴
      response += c;
    }
  }
  if (debug) {
    Serial.print(response);
  }

  return response;
}

