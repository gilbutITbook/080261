/*
  DGS-SO2 library
  STEMEDU123 license
  written by SteamLabs
  homepage: http://www.steamedu123.com   
  naver cafe : https://cafe.naver.com/arduinosensor/book5108749/64
  email : steamedu123@gmail.com
*/

#include <DGS.h>
#include "C405_Steam_Air_DGS-SO2_SO2.h"
#include "SoftwareSerial.h"

//SoftwareSerial Serial1(10, 11); // !!! RX, TX Must be on 3.3 volt communication, or using level shifters to get to 3.3V UART!!!
SoftwareSerial Serial1(3, 2);  //RX, TX
DGS dgs(&Serial1);

/**
 * @함수명    : SteamDGSSO2
 * @설명      : 생성자
*/
SteamDGSSO2::SteamDGSSO2()
{
}

/**
 * @함수명    : begin
 * @설명      : 센서를 초기화 한다. 
*/
void SteamDGSSO2::begin()
{
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial.flush();
  Serial1.flush();
  Serial.println(F("SPEC Sensors' Digital DGS-SO2 Sensor"));
  Serial.println(F("Ready....."));
  Serial.println(F("--------------------------------"));

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, 1);
  delay(10000); // Important!!! Need 10s for get EEPROM data

  dgs.DEBUG = false;
  dgs.getEEPROM();
  dgs.DEBUG = true;
  delay(2000);

  // Checked compatibility with firmware 15SEP17 and 25SEP17
  Serial.println("Firmware: " + dgs.getFW());
  Serial.println("Barcode: " + dgs.getBarcode());

  if (setupSensor)
  {
    Serial.println("Setup...");
    // Enter your barcode string. Returns 1/0
    dgs.setBC(setupBarcode);

    // Loads LMP values into variable returns 1/0
    if (dgs.getLMP())
    {
      Serial.print(F("LMP91000 Values loaded into array"));
      if (dgs.setLMP(dgs.LMP[0], dgs.LMP[1], dgs.LMP[2]))
        Serial.println("Finished Setting New Values For LMP"); //Sets LMP variables into register returns 1/0
    }

    // Set T offset in deg C returns 1/0. Podemos subir/bajar la temperatura. Hay que pasar el valor a subir ej "1.2" o a bajar "-2.2"
    // if (dgs.setToff(0.0)) Serial.println("Finished Setting T Offset");
  }

  Serial.println("");
}

void SteamDGSSO2::blinkLed()
{
  digitalWrite(LED_BUILTIN, 1);
  delay(10);
  digitalWrite(LED_BUILTIN, 0);
}

/**
 * @함수명    : read
 * @설명      : 센서의 값을 읽어온다
*/
void SteamDGSSO2::read()
{
}

/**
 * @함수명    : display
 * @설명      : 센서의 값을 출력한다. 
  * so2 = 1ppb = 2.62ug/m3
               = 0.001ppm
*/
void SteamDGSSO2::display()
{
  dgs.getData('\r');

  if (!calibratedZero)
    blinkLed(); // blink while not calibrateds

  //dgs.getData('\r');
  ppb = dgs.getConc();
  ppm = ppb / 1000;
  temp = dgs.getTemp('C');
  rh = dgs.getRh();
  timeRunning = dgs.getTimeRunning();

  Serial.print(dgs.getGasName() + " " + String(ppb) + " ppb "); // default is 'p' for temperature compensated ppb, any other cahracter for raw counts
  //Serial.print(" " + String(ppm) + "ppm");
  //Serial.print(" | T " + String(temp));         // 'F' or 'C' for units of temperature, default is 'C'
  //Serial.print(" | H " + String(rh));
  Serial.print(" | " + String(dgs.getTimeRunning()));
  Serial.print(" => ");
  _displayAirCondition_SO2(ppb);

  if ((dgs.getTimeRunning() == "0d 08:00:00") ||
      (dgs.getTimeRunning() == "0d 08:00:01"))
  {
    // Auto Zero al time
    if (dgs.zero())
      Serial.println("Finished Setting Zero"); //zeros returns 1/0
    calibratedZero = true;
  }

  if (Serial.available())
  {
    char U = Serial.read();

    if (U == 'Z')
      if (dgs.zero())
        Serial.println(F("Finished Setting Zero")); //zeros returns 1/0

    if ((U == 'r') || (U == 'R'))
      dgs.resetModule();

    if (U == 'f')
      Serial.println("My firmware: " + dgs.getFW());

    if (U == 'e')
    {
      dgs.DEBUG = true;
      dgs.getEEPROM();
    }

    if (U == 'S')
    {
      // No siempre funciona bien, algunas veces tarda hasta 5min en ejecutarse
      Serial.print(F("Enter span value in PPM (ex 10.2): "));
      delay(200);

      String cadena = "";
      while (true)
      {
        while (!Serial.available())
        {
        }
        char val = Serial.read();
        Serial.print(val);

        if (val == '\n')
          break;

        cadena = cadena + val;
      }
      dgs.setXSpan(cadena.toFloat());
    }
  }
}

void SteamDGSSO2::_displayAirCondition_SO2(float ppb)
{
  if (ppb <= 20)
  {
    Serial.print("Good");
  }
  else if (ppb <= 50)
  {
    Serial.print("Normal");
  }
  else if (ppb <= 150)
  {
    Serial.print("Bad");
  }
  else
  {
    Serial.print("Very Bad");
  }
  Serial.println("");
}