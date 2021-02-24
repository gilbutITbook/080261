/*
  DFRobotHCHOSensor.cpp - DFRobotHCHOSensor library
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

#include "DFRobotHCHOSensor.h"

DFRobotHCHOSensor::DFRobotHCHOSensor(HardwareSerial* Serial)	//read the uart signal by hardware uart,such as D0
{
    mySerial = Serial;
    receivedFlag = 0;
}

DFRobotHCHOSensor::DFRobotHCHOSensor(SoftwareSerial* Serial)	//read the uart signal by software uart,such as D10
{
    mySerial = Serial;
    receivedFlag = 0;
}
DFRobotHCHOSensor:: DFRobotHCHOSensor(int pin,float ref)//read the analog signal by analog input pin ,such as A2; ref:voltage on AREF pin
{
    _sensorPin = pin;
    _ref = ref;											//for arduino uno ,the ref should be 5.0V(Typical)
}

byte DFRobotHCHOSensor::checkSum(byte array[],byte length)	
{
    byte sum = 0;
    for(int i = 1; i < length-1; i ++)
    {
		sum += array[i];
    }
    sum = (~sum) + 1;
    return sum;
}

boolean DFRobotHCHOSensor::available()		//new data was recevied
{
    while(mySerial->available()>0)
    {
		for(byte index = 0; index < MAXLENGTH-1; index++)
		{
			receivedCommandStack[index] = receivedCommandStack[index+1];
		}
		receivedCommandStack[MAXLENGTH-1] = mySerial->read();

		byte sumNum = checkSum(receivedCommandStack,MAXLENGTH);
		if( (receivedCommandStack[0] == 0xFF) && (receivedCommandStack[1] == 0x17) && (receivedCommandStack[2] == 0x04) && (receivedCommandStack[MAXLENGTH-1] == sumNum) )	//head bit and sum are all right
		{
			receivedFlag = 1;			//new data received
			return receivedFlag;
		}else{
			receivedFlag = 0;			//data loss or error
			return receivedFlag;
		}  
    }
    return receivedFlag;
}

float DFRobotHCHOSensor::uartReadPPM()
{
    receivedFlag = 0;
    float ppb = (unsigned int)receivedCommandStack[4]<<8 | receivedCommandStack[5];		// bit 4: ppm high 8-bit; bit 5: ppm low 8-bit
    float ppm = ppb / 1000.0;	//1ppb = 1000ppm
    return ppm;
}
 
float DFRobotHCHOSensor::dacReadPPM()
{
   float analogVoltage = analogRead(_sensorPin) / 1024.0 * _ref;
   float ppm = 3.125 * analogVoltage - 1.25;	//linear relationship(0.4V for 0 ppm and 2V for 5ppm)
   if(ppm<0)
	   ppm=0;
   else if(ppm>5)
	   ppm = 5;
   return ppm;
}