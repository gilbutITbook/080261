/*
  CCS811 (CJMCU-8128) library
  STEMEDU123 license
  written by SteamLabs
  homepage: http://www.steamedu123.com   
  naver cafe : https://cafe.naver.com/arduinosensor/book5108749/54
  email : steamedu123@gmail.com
*/


#include "C304_Steam_Air_CCS811_TVOC_CJMCU-8128.h"

#define BMP_SCK  (13)
#define BMP_MISO (12)
#define BMP_MOSI (11)
#define BMP_CS   (10)

/**
 * @함수명    : SteamCJMCU8128
 * @설명      : 생성자
*/
SteamCJMCU8128::SteamCJMCU8128() {}

/**
 * @함수명    : begin
 * @설명      : 센서를 초기화 한다. 
*/
void SteamCJMCU8128::begin()
{
  Serial.println("CJMCU-8128 CCS811 + SI7021 + BMP280 Sensor");
  Serial.println("Ready.....");
  Serial.println("--------------------------------");  

  _begin_CCS811();
  _begin_SI7021();
  _begin_BMP280();
  delay(100);
}


/**
 * @함수명    : read
 * @설명      : 센서의 값을 읽어온다
*/
void SteamCJMCU8128::read()
{  
  _read_CCS811();
  _read_SI7021();
  _read_BMP280();
}

/**
 * @함수명    : display
 * @설명      : 센서의 값을 출력한다. 
*/
void SteamCJMCU8128::display()
{
  _display_CCS811(); 
  _display_SI7021();
  _display_BMP280();

  //setEnvironmentalData(uint8_t humidity, double temperature)  
  ccs.setEnvironmentalData(_si7021Temp, _si7021Temp);
}


void SteamCJMCU8128::_begin_CCS811(){
   if (!ccs.begin()) {
    Serial.println("Failed to start sensor! Please check your wiring.");
    while (1);
  }

    //calibrate temperature sensor
  while (!ccs.available());
  float temp = ccs.calculateTemperature();
  ccs.setTempOffset(temp - 25.0);

  Serial.println("CCS811 Begin...........");
}

void SteamCJMCU8128::_read_CCS811(){
  if (ccs.available()) {
    _tempCCS811 = ccs.calculateTemperature();
    _eCO2 = ccs.geteCO2();
    _tvoc = ccs.getTVOC();
  }
}

void SteamCJMCU8128::_display_CCS811(){    
    if (!ccs.readData()) {
      Serial.print("CCS811 \tTemperature: ");
      Serial.print(_tempCCS811);
      Serial.print(" *C");

      Serial.print("  CO2: ");
      Serial.print(_eCO2);
      Serial.print("ppm ");

      Serial.print("TVOC: ");
      Serial.print(_tvoc);
      Serial.print("ppb => ");
      _displayAirCondition_TVOC(_tvoc);

      Serial.println();
      
    }
    else {
      Serial.println("ERROR!");
      while (1);
    }  
}



void SteamCJMCU8128::_begin_SI7021(){
  si7021 = Adafruit_Si7021();
   // wait for serial port to open
  while (!Serial) {
    delay(10);
  }

  Serial.println("Si7021 Begin...........");

  
  if (!si7021.begin()) {
    Serial.println("Did not find Si7021 sensor!");
    while (true)
      ;
  }

  Serial.print("\tFound model ");
  switch(si7021.getModel()) {
    case SI_Engineering_Samples:
      Serial.print("SI engineering samples"); break;
    case SI_7013:
      Serial.print("Si7013"); break;
    case SI_7020:
      Serial.print("Si7020"); break;
    case SI_7021:
      Serial.print("Si7021"); break;
    case SI_UNKNOWN:
    default:
      Serial.print("Unknown");
  }

  Serial.println();

  // Serial.print(" Rev(");
  // Serial.print(si7021.getRevision());
  // Serial.print(")");
  // Serial.print(" Serial #"); Serial.print(si7021.sernum_a, HEX); Serial.println(sensor.sernum_b, HEX);

}

void SteamCJMCU8128::_read_SI7021(){
  _si7021Temp = si7021.readTemperature();
  _si7021Humi = si7021.readHumidity();
}

void SteamCJMCU8128::_display_SI7021(){
  Serial.print("SI7021 \tTemperature: ");
  Serial.print(_si7021Temp, 2);
  Serial.print(" *C");

  Serial.print("  Humidity: ");
  Serial.print(_si7021Humi, 2);  
  Serial.println(" %");
}

void SteamCJMCU8128::_begin_BMP280(){
  Serial.println("BMP280 Begin...........");
  
  if (!bmp.begin(0X76)) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    while (1);
  }

  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
  
  Serial.println();
}

void SteamCJMCU8128::_read_BMP280(){
  _bmpTemp = bmp.readTemperature();
  _bmpPressure = bmp.readPressure() / 100;
  _bmpAltitude = bmp.readAltitude(1026.25);
}

void SteamCJMCU8128::_display_BMP280(){
    Serial.print(F("BMP280 \tTemperature: "));
    Serial.print(_bmpTemp);
    Serial.println(" *C");

    Serial.print(F("\tPressure = "));
    Serial.print(_bmpPressure);
    Serial.println(" hPa");

    Serial.print(F("\tApprox altitude = "));
    //Serial.print(bmp.readAltitude(1013.25)); /* Adjusted to local forecast! */
    Serial.print(_bmpAltitude); /* Adjusted to local forecast! */
    Serial.println(" m");

    Serial.println();
}


/**
 * @함수명    : _displayAirCondition_TVOC
 * @설명      : 센서의 상태를 출력한다. 
 * 좋음(Good) :           0-300 ppb
 * 보통(Normal) :       301~500 ppb
 * 나쁨(Bad) :          501~1000 ppb
 * 매우나쁨(Very Bad) : 1001~ ppb
*/ 
void SteamCJMCU8128::_displayAirCondition_TVOC(uint16_t ppb){  
  if (ppb <= 300) {      
    Serial.print("Good");    
  }  else if (ppb <= 500) {
    Serial.print("Normal");    
  }  else if (ppb <= 1000){
    Serial.print("Bad");    
  }  else {
    Serial.print("Very Bad");    
  }  
  
}

