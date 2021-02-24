/*
  DFRobotHCHOSensor.h - DFRobotHCHOSensor library
  Developed by Jason - 2016/12/15

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

Gravity: HCHO Sensor info found at
http://www.dfrobot.com/

Version 1.0: 15 Dec 2016 by Jason<jason.ling@dfrobot.com@dfrobot.com>
- Updated to build against Arduino 1.0.6
- Made accessors inline in the header so they can be optimized away
*/


#ifndef __DFRobotHCHOSensor_H_
#define __DFRobotHCHOSensor_H_

#include <SoftwareSerial.h>
#include <arduino.h>

#define MAXLENGTH  9

class DFRobotHCHOSensor
{
  public:
  DFRobotHCHOSensor(HardwareSerial* Serial);	//read the uart signal by hardware uart,such as D0
  DFRobotHCHOSensor(SoftwareSerial* Serial);	//read the uart signal by software uart,such as D10
  DFRobotHCHOSensor(int pin,float ref);			//read the analog signal by analog input pin ,such as A2; ref:voltage on AREF pin
  boolean available();		//new data was recevied
  float uartReadPPM();		//get the concentration(ppm) by uart signal
  float dacReadPPM();		//get the concentration(ppm) by analog signal

  private:
  Stream *mySerial;
  byte receivedCommandStack[MAXLENGTH];
  byte checkSum(byte array[],byte length);
  boolean receivedFlag;
  byte _sensorPin;
  float _ref;
};

#endif