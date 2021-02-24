#include <SoftwareSerial.h>

SoftwareSerial esp01(2, 3); // RX, TX

void setup() {  
  Serial.begin(115200);
  esp01.begin(115200);
  Serial.print("ESP01 Serial Test");

}

void loop() {

  if (esp01.available()) {
    Serial.write(esp01.read());
  }
  if (Serial.available()) {
    esp01.write(Serial.read());
  }
}
