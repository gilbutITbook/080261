/*
  nRF24L01 library
  STEMEDU123 license
  written by SteamLabs
*/

#include "C602_Steam_Air_NRF24L01.h"

/**
 * @함수명    : SteamNRF24L01
 * @설명      : 생성자
*/
SteamNRF24L01::SteamNRF24L01()
{
}

/**
 * @함수명    : begin
 * @설명      : DHT 객체를 생성한다. 
*/
void SteamNRF24L01::begin()
{
  Serial.println("NRF24L01 Init");
  Serial.println("--------------------------------");

  Mirf = new Nrf24l(10, 9);

  pinMode(13, OUTPUT); // 내장 13번 LED

  Mirf->spi = &MirfHardwareSpi;
  Mirf->init();
  Mirf->setRADDR((byte *)"steamedu123"); //Set your own address (receiver address) using 5 characters
  Mirf->payload = sizeof(value);
  Mirf->channel = 90; //Set the used channel
  Mirf->config();
}

/**
 * @함수명    : sendBT
 * @설명      : 스마트폰으로 데이터를 전송한다. 
*/
void SteamNRF24L01::send(unsigned int pm2_5, float temp, uint32_t humidity, uint32_t hPa)
{
  unsigned long currentMillis = millis();
  digitalWrite(13, LOW); // 내장 13번 LED 끄기

  uint32_t hPa1, hPa2, hPa3;
  hPa1 = hPa / 10000;
  hPa3 = hPa % 100;
  hPa2 = (hPa % 10000 - hPa3) / 100;

  // Serial.println(hPa);
  // Serial.println(hPa1);
  // Serial.println(hPa2);
  // Serial.println(hPa3);

  value[0] = pm2_5;    // 미세먼지(pm2.5)
  value[1] = temp;     // 온도
  value[2] = humidity; // 습도
  value[3] = hPa1;     // 기압 앞자리 예:) 101511hPa 이면 10
  value[4] = hPa2;     // 기압 가운데 2자리 예:) 101511hPa 이면 15
  value[5] = hPa3;     // 기압 뒤 2자리 예:) 101511hPa 이면 11

  if (currentMillis - previousMillis >= interval) // 인터발 주기(4초) 로 데이터 전송
  {
    previousMillis = currentMillis;
    digitalWrite(13, HIGH); // 내장 13번 LED 켜기

    Mirf->send(value); //Send instructions, send data value
    Serial.print("Wait for sending.....");
    while (Mirf->isSending()) //Until you send successfully, exit the loop
      delay(1);
    Serial.print("Send success: ");
    dataDebug();
  } 
}

void SteamNRF24L01::receive()
{
  digitalWrite(13, LOW); // 내장 13번 LED 끄기
  while (Mirf->dataReady())
  {                         //When the program is received, the received data is output from the serial port
    digitalWrite(13, HIGH); // 내장 13번 LED 켜기
    Mirf->getData(value);
    Serial.print("Remote: ");
    dataDebug();
  }
}

void SteamNRF24L01::dataDebug()
{
  Serial.print(value[0]);
  Serial.print("㎛/㎥ ");
  Serial.print(value[1]);
  Serial.print("℃ ");
  Serial.print(value[2]);
  Serial.print("% ");
  Serial.print(value[3]);
  Serial.print(value[4]);
  Serial.print(value[5]);
  Serial.println("Pa");
}

byte SteamNRF24L01::getPm()
{
  return value[0];
}

byte SteamNRF24L01::getTemp()
{
  return value[1];
}

byte SteamNRF24L01::getHumi()
{
  return value[2];
}

String SteamNRF24L01::getPa()
{
  char str[256];
  sprintf(str, "%2d%2d%2d", value[3], value[4], value[5]);
  //Serial.println(str);
  return str;
}