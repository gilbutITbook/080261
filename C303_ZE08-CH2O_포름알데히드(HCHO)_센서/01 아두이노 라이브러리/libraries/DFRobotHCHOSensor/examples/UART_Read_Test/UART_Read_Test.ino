/***************************************************
 DFRobot Gravity: HCHO Sensor
 <https://www.dfrobot.com/wiki/index.php/Gravity:_HCHO_Sensor_SKU:_SEN0231>
 
 ***************************************************
 This example reads the concentration of HCHO in air by UART mode.
 
 Created 2016-12-15
 By Jason <jason.ling@dfrobot.com@dfrobot.com>
 
 GNU Lesser General Public License.
 See <http://www.gnu.org/licenses/> for details.
 All above must be included in any redistribution
 ****************************************************/
 
 /***********Notice and Trouble shooting***************
 1. This code is tested on Arduino Uno with Arduino IDE 1.0.5 r2.
 2. In order to protect the sensor, do not touch the white sensor film on the sensor module, 
 and high concentration of Hydrogen sulfide, hydrogen, methanol, ethanol, carbon monoxide should be avoided. 
 3. Please do not use the modules in systems which related to human being’s safety.
 ****************************************************/

#include <DFRobotHCHOSensor.h>
#include <SoftwareSerial.h>

#define SensorSerialPin	10	//this pin read the uart signal from the HCHO sensor

SoftwareSerial sensorSerial(SensorSerialPin,SensorSerialPin);

DFRobotHCHOSensor hchoSensor(&sensorSerial);

void setup()
{  
    sensorSerial.begin(9600);	//the baudrate of HCHO is 9600
    sensorSerial.listen();
    Serial.begin(9600);
}

void loop()
{
    if(hchoSensor.available()>0)	
    {
      Serial.print(hchoSensor.uartReadPPM());
      Serial.println("ppm");
    }
}
