/*
  DHT22 library
  STEMEDU123 license
  written by SteamLabs
*/


#include "C301_Steam_Air_DHT22_TempHumidity.h"


/**
 * @함수명    : SteamDHT22
 * @설명      : 생성자
*/
SteamDHT22::SteamDHT22(uint8_t pin, uint8_t type) {
  _pin = pin;
  _type = type;
} 


/**
 * @함수명    : begin
 * @설명      : DHT 객체를 생성한다. 
*/
void SteamDHT22::begin() {
  Serial.println("DHT22 Sensor");
  Serial.println("Ready.....");
  Serial.println("--------------------------------");  
  
  _dht22 = new DHT(_pin, _type);
  _dht22->begin();
}

/**
 * @함수명    : readHumidityTemperature
 * @설명      : DHT 센서로 부터 온도/습도 값을 읽어온다.
*/
bool SteamDHT22::read() {

  _humidity = _dht22->readHumidity();
  _temperature = _dht22->readTemperature();

  if (isnan(_humidity) || isnan(_temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return false;
  }
  //delay(1000);
  return true;
}



/**
 * @함수명    : display
 * @설명      : 시리얼로 온도, 습도를 출력한다. 
*/
void SteamDHT22::display() {
  Serial.print("Temperature: ");
  Serial.print(_temperature,1); 
  Serial.print(" *C => ");
  _displayAirCondition_Temp(_temperature);

  Serial.print("\t\t Humidity: ");
  Serial.print(_humidity,1); 
  Serial.print(" RH% => ");
  _displayAirCondition_Humidity(_humidity);

  Serial.println();
}


/**
 * @함수명    : _displayAirCondition_Temp
 * @설명      : 온도 상태를 표시한다. 
 * 좋음 : 22-26 ℃
 * 보통 : 20-22℃, 26-28℃
 * 나쁨 : 15-20℃, 28-31℃
 * 매우나쁨 : -15℃, 31℃-
*/
void SteamDHT22::_displayAirCondition_Temp(float temp){  
  if (temp < 15) {      
    Serial.print("Very Bad");    
  }  else if (temp < 20) {
    Serial.print("Bad");    
  }  else if (temp < 22){
    Serial.print("Normal");    
  }  else if (temp < 26) {
    Serial.print("Good");    
  }  else if (temp < 28) {
    Serial.print("Normal");    
  } else if (temp < 31) {
    Serial.print("Bad");    
  } else {
    Serial.print("Very Bad");    
  }
}

/**
 * @함수명    : _displayAirCondition_Humidity
 * @설명      : 습도 상태를 표시한다. 
 * 좋음 : 40-60%
 * 보통 : 30-40%, 60-70%
 * 나쁨 : 20-30%, 70-80%
 * 매우나쁨 : -20%, 80%-
*/
void SteamDHT22::_displayAirCondition_Humidity(float humidity){  
 if (humidity < 20) {      
    Serial.print("Very Bad");    
  } else if (humidity < 30) {
    Serial.print("Bad");    
  } else if (humidity < 40){
    Serial.print("Normal");    
  } else if (humidity < 60) {
    Serial.print("Good");    
  } else if (humidity < 70) {
    Serial.print("Normal");    
  } else if (humidity < 80) {
    Serial.print("Bad");    
  } else {
    Serial.print("Very Bad");    
  }
}

int SteamDHT22::getTemp(){
	return (int)_temperature;
}

int SteamDHT22::getHumidity(){
	return (int)_humidity;
}