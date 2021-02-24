
#include "gdk101_i2c.h"

//A0 Short, A1 Short : 0x18
//A0 Open,  A1 Short : 0x19
//A0 Short, A1 Open  : 0x1A
//A0 Open,  A1 Open  : 0x1B

#define DEF_ADDR 0x18

GDK101_I2C gdk101(DEF_ADDR);

float avg10min;
float avg1min;
float fw_vers;
int _status;

bool vibration;
byte mea_min;
byte mea_sec;

//output
char out_buff[48];

void setup() {
  Serial.begin(115200);
  gdk101.init();
  //gdk101.reset();
  fw_vers = gdk101.get_fw_version();
}

void loop() {
  avg10min = gdk101.get_10min_avg();
  avg1min = gdk101.get_1min_avg();
  mea_min = gdk101.get_measuring_time_min();
  mea_sec = gdk101.get_measuring_time_sec();
  _status = gdk101.get_status();
  vibration = gdk101.get_vib();

  Serial.println("Gamma Sensor Sensing Start");
  Serial.print("FW verwion : \t\t\t");
  Serial.println(fw_vers);
    
  Serial.println("===========================================");
  displayStatus(_status);  
  displayVibration(vibration);  
  
  sprintf(out_buff, "Measuring Time: \t\t%i:%i", mea_min, mea_sec);
  Serial.println(out_buff);  
  
  Serial.print("Measuring Value(10min Avg) \t");
  Serial.print(avg10min);
  Serial.println(" uSv/hr");
  
  Serial.print("Measuring Value(1min Avg) \t");
  Serial.print(avg1min);
  Serial.println(" uSv/hr");
  
  Serial.println();
  
    
  delay(2000);
}


void displayReset(bool s){
  Serial.print("Reset Response\t\t\t");
  
  if(s == 1){
    Serial.println("Reset Success.");   
  } else{
    Serial.println("Reset Fail(Status - Ready");
  }
}


void displayStatus(int s){
  Serial.print("Status: ");
  
  switch(s){
    case 0: Serial.println("\t\t\tReady");break;
    case 1: Serial.println("\t\t\t10min Waiting"); break;
    case 2: Serial.println("\t\t\tNormal"); break;
  }
}

void displayVibration(bool s){
  Serial.print("VIB Status\t\t\t");
  switch(s){
    case 0: Serial.println("OFF"); break;
    case 1: Serial.println("ON"); break;
  }
}
