/*
   @타이틀 : MH-Z19B 이산화탄소(CO2) 측정센서 
*/

#include <C302_Steam_Air_MH-Z19B_CO2_PWM.h>   // 내부 라이브러리 헤더파일

#define pwmPin 3

SteamMHZ19BPWM mhz19b_pwm(pwmPin);    // 인스턴스, 핀 번호를 입력한다.

void setup() {
  Serial.begin(115200);       // 115200bps의 속도로 시리얼 통신을 시작한다.
  mhz19b_pwm.begin();         // (1) 센서를 초기화 한다.
}

void loop() {
  mhz19b_pwm.read();        // (2) 센서의 값을 측정한다.
  mhz19b_pwm.display();     // (3) 센서의 값을 출력한다.
  delay(5000);              // 5초 동안 대기한다.
}
