/*
  LCD 16X2 library
  STEMEDU123 license
  written by SteamLabs 
*/


#include "C601_Steam_Air_LCD16X2.h"


  
/**
 * @함수명    : SteamLCD16X2
 * @설명      : 생성자
*/
SteamLCD16X2::SteamLCD16X2() {  
} 

/**
 * @함수명    : begin
 * @설명      : DHT 객체를 생성한다. 
*/
void SteamLCD16X2::begin() {
	lcd = new LiquidCrystal(8, 9, 4, 5, 6, 7);  
	lcd->begin(16, 2);
	// Print a message to the LCD.
	lcd->print("Init....");
	delay(1000);
  
    //lcd->setCursor(0, 0);
	
    lcd->createChar(0, SpecialChar1);
    lcd->createChar(1, SpecialChar2);
    lcd->createChar(2, SpecialChar3);    
}
  
void SteamLCD16X2::display(int pm, int temp, int humidity) {
	unsigned long currentMillis = millis();
  
  
    if (currentMillis - previousMillis >= interval) {    // 인터발 주기(4초) 로 데이터 전송
    previousMillis = currentMillis;    
	
    char buf[256];
    //sprintf(buf, "%02x:%02x:%02x ug/m3", avrPM1_0, avrPM2_5, avrPM10_0);
    sprintf(buf, "%02d ug/m3", pm);
  
    //lcd->clear();
    //clearLCD(0);
    lcd->setCursor(0, 0);
    lcd->print(buf);     // 미세먼지 값
	
	//lcd->clear();   
    lcd->setCursor(0, 1);    
    lcd->write(byte(0));
    lcd->print(" ");
    lcd->print(temp, 1); // 온도값
    lcd->write(byte(1));
    lcd->print("  ");
    lcd->write(byte(2));
    lcd->print(" ");
    lcd->print(humidity, 1);   // 습도값
    lcd->print("%");
	}
}


void SteamLCD16X2::clearLCD(int row){  
  for(int i=0; i<16;i++){
    lcd->print(" ");
    lcd->setCursor(i,row);
  }
  lcd->setCursor(0, 0);
}

