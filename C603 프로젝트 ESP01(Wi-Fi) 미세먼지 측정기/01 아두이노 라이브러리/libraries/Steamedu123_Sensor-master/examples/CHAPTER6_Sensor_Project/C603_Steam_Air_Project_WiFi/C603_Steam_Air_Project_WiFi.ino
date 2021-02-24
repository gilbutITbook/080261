
/*
   @타이틀 : WiFi + Nova SDS011 + DHT22 
*/

#include <C603_Steam_Air_ESP01.h>
#include <C301_Steam_Air_DHT22_TempHumidity.h>
#include <C205_Steam_Air_NovaSDS011_Dust_PWM.h>

SteamESP01 esp01(2, 3);       // RX/TX 설정, esp01 객체생성
SteamDHT22 dht22(A1, DHT22);  // 온도/습도 센서 인스턴스, 핀 번호(A1)와 DHT22타입을 입력한다.
SteamNovaSDS011PWM novasds011(4, 5); // pm2.5, pm1

String ssid = "iptime";              // 집에 사용하는 Wi-Fi 공유기 이름(SSID)
String pass = "qwerqwer";             // 집에 사용하는 Wi-Fi 비밀번호
String apiKey = "XJ61RWFSL0OJEDTG";   // thingspeak.com 채널의 Write API key 입력
const long interval = 4000;         // thingspeak.com 로 센서값 전송 주기, 4초

void setup() {
  Serial.begin(9600);       //소프트웨어 시리얼 시작
  Serial.println("C603 IoT Project Start(ESP01)");

  esp01.begin(ssid, pass, apiKey, interval); // Wi-Fi를 초기화 한다.
  dht22.begin();          // 온도/습도 센서를 초기화 한다.
  novasds011.begin();     // 미세먼지 센서를 초기화 한다.
}

void loop() {
  novasds011.read();      // 센서의 값을 측정한다.
  dht22.read();         //   온도/습도 센서의 값을 측정한다.

  esp01.sendData(novasds011.getPM2_5(), dht22.getTemp(), dht22.getHumidity());
}
