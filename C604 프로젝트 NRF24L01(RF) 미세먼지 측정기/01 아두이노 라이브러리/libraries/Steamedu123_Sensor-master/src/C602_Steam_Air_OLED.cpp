/*
  OLED library
  STEMEDU123 license
  written by SteamLabs 
*/

#include "C602_Steam_Air_OLED.h"
#include <U8glib.h>

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);
/**
 * @함수명    : SteamOLED
 * @설명      : 생성자
*/
SteamOLED::SteamOLED()
{
}

/**
 * @함수명    : begin
 * @설명      : 
*/
void SteamOLED::begin()
{
   
}

/**
 * @함수명    : display
 * @설명      :  센서의 값을 출력한다. 
*/
void SteamOLED::display(byte pm2_5, byte temp, byte humidity, String hPa)
{
    u8g.firstPage();
    do{

        u8g.setFont(u8g_font_unifont);
//        u8g.setPrintPos(5,10);
//        u8g.print("C604-NRF24L01");
        u8g.drawStr(5,10, "PM2.5:");
        u8g.setPrintPos(53,10); 
        u8g.print(pm2_5);
        u8g.drawStr(82,10, "um/m3");
        
        u8g.drawStr(5,25, "Temp:");
        u8g.setPrintPos(53,25); 
        u8g.print(temp);
        u8g.drawStr(102,25, "C");
        
        u8g.drawStr(5,40, "Humi:");
        u8g.setPrintPos(53,40); 
        u8g.print(humidity);
        u8g.drawStr(102,40, "%");

        u8g.drawStr(5,55, "Pa:");
        u8g.setPrintPos(53,55); 
        u8g.print(hPa);        
        u8g.drawStr(102,55, "Pa");
    }while(u8g.nextPage());
}

