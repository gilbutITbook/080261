/******************************************************************************
 * Arduino-MQ131-driver                                                       *
 * --------------------                                                       *
 * Arduino driver for gas sensor MQ131 (O3)                                   *
 * Author: Olivier Staquet                                                    *
 * Last version available on https://github.com/ostaquet/Arduino-MQ131-driver *
 ******************************************************************************/

 #include "MQ131.h"

/**
 * Constructor, nothing special to do
 */
MQ131Class::MQ131Class(int _RL) {
  valueRL = _RL;
}

/**
 * Destructor, nothing special to do
 */
MQ131Class::~MQ131Class() {
}

/**
 * Init core variables
 */
 void MQ131Class::begin(int _pinPower, int _pinSensor, MQ131Model _model, int _RL) {
 	// Setup the model
 	model = _model;

 	// Store the circuit info (pin and load resistance)
 	pinPower = _pinPower;
 	pinSensor = _pinSensor;
 	valueRL = _RL;

  // Setup default calibration value
  switch(model) {
    case LOW_CONCENTRATION :
      setR0(MQ131_DEFAULT_LO_CONCENTRATION_R0);
      setTimeToRead(MQ131_DEFAULT_LO_CONCENTRATION_TIME2READ);
      break;
    case HIGH_CONCENTRATION :
      setR0(MQ131_DEFAULT_HI_CONCENTRATION_R0);
      setTimeToRead(MQ131_DEFAULT_HI_CONCENTRATION_TIME2READ);
      break;
  }

 	// Setup pin mode
 	pinMode(pinPower, OUTPUT);
 	pinMode(pinSensor, INPUT);

  // Switch off the heater as default status
  digitalWrite(pinPower, LOW);
 }

/**
 * Do a full cycle (heater, reading, stop heater)
 * The function gives back the hand only at the end
 * of the read cycle!
 */
 void MQ131Class::sample() {
 	startHeater();
 	while(!isTimeToRead()) {
 		delay(1000);
 	}
 	lastValueRs = readRs();
 	stopHeater();
 }

/**
 * Start the heater
 */
 void MQ131Class::startHeater() {
 	digitalWrite(pinPower, HIGH);
 	secLastStart = millis()/1000;
 }

/**
 * Check if it is the right time to read the Rs value
 */
 bool MQ131Class::isTimeToRead() {
 	// Check if the heater has been started...
 	if(secLastStart < 0) {
 		return false;
 	}
 	// OK, check if it's the time to read based on calibration parameters
 	if(millis()/1000 >= secLastStart + getTimeToRead()) {
 		return true;
 	}
 	return false;
 } 

/**
 * Stop the heater
 */
 void MQ131Class::stopHeater() {
 	digitalWrite(pinPower, LOW);
 	secLastStart = -1;
 }

/**
 * Get parameter time to read
 */
 long MQ131Class::getTimeToRead() {
 	return secToRead;
 }

/**
 * Set parameter time to read (for calibration or to recall
 * calibration from previous run)
 */
 void MQ131Class::setTimeToRead(long sec) {
 	secToRead = sec;
 }

/**
 * Read Rs value
 */
 float MQ131Class::readRs() {
 	// Read the value
 	int valueSensor = analogRead(pinSensor);
 	// Compute the voltage on load resistance (for 5V Arduino)
 	float vRL = ((float)valueSensor) / 1024.0 * 5.0;
 	// Compute the resistance of the sensor (for 5V Arduino)
 	float rS = (5.0 / vRL - 1.0) * valueRL;
 	return rS;
 }

/**
 * Set environmental values
 */
 void MQ131Class::setEnv(int tempCels, int humPc) {
 	temperatureCelsuis = tempCels;
 	humidityPercent = humPc;
 }

/**
 * Get correction to apply on Rs depending on environmental
 * conditions
 */
 float MQ131Class::getEnvCorrectRatio() {
 	// Select the right equation based on humidity
 	// If default value, ignore correction ratio
 	if(humidityPercent == 60 && temperatureCelsuis == 20) {
 		return 1.0;
 	}
 	// For humidity > 75%, use the 85% curve
 	if(humidityPercent > 75) {
 		// R^2 = 0.9986
 		return -0.0141 * temperatureCelsuis + 1.5623;
 	}
 	// For humidity > 50%, use the 60% curve
 	if(humidityPercent > 50) {
 		// R^2 = 0.9976
 		return -0.0119 * temperatureCelsuis + 1.3261;
 	}

 	// Humidity < 50%, use the 30% curve
 	// R^2 = 0.996
 	return -0.0103 * temperatureCelsuis + 1.1507;
 }

 /**
 * Get gas concentration for O3 in ppm
 */
 float MQ131Class::getO3(MQ131Unit unit) {
 	// If no value Rs read, return 0.0
 	if(lastValueRs < 0) {
 		return 0.0;
 	}

  float ratio = 0.0;

 	switch(model) {
 		case LOW_CONCENTRATION :
 			// Use the equation to compute the O3 concentration in ppm
 			// R^2 = 0.9987
      // Compute the ratio Rs/R0 and apply the environmental correction
      ratio = lastValueRs / valueR0 * getEnvCorrectRatio();
      return convert(9.4783 * pow(ratio, 2.3348), PPB, unit);
 		case HIGH_CONCENTRATION :
 			// Use the equation to compute the O3 concentration in ppm
 			// R^2 = 0.99
      // Compute the ratio Rs/R0 and apply the environmental correction
      ratio = lastValueRs / valueR0 * getEnvCorrectRatio();
      return convert(8.1399 * pow(ratio, 2.3297), PPM, unit);
 		default :
 			return 0.0;
  }
}

 /**
  * Convert gas unit of gas concentration
  */
 float MQ131Class::convert(float input, MQ131Unit unitIn, MQ131Unit unitOut) {
  if(unitIn == unitOut) {
    return input;
  }

  float concentration = 0;

  switch(unitOut) {
    case PPM :
      // We assume that the unit IN is PPB as the sensor provide only in PPB and PPM
      // depending on the type of sensor (METAL or BLACK_BAKELITE)
      // So, convert PPB to PPM
      return input / 1000.0;
    case PPB :
      // We assume that the unit IN is PPM as the sensor provide only in PPB and PPM
      // depending on the type of sensor (METAL or BLACK_BAKELITE)
      // So, convert PPM to PPB
      return input * 1000.0;
    case MG_M3 :
      if(unitIn == PPM) {
        concentration = input;
      } else {
        concentration = input / 1000.0;
      }
      return concentration * 48.0 / 22.71108;
    case UG_M3 :
      if(unitIn == PPB) {
        concentration = input;
      } else {
        concentration = input * 1000.0;
      }
      return concentration * 48.0 / 22.71108;
    default :
      return input;
  }
}

 /**
  * Calibrate the basic values (R0 and time to read)
  */
void MQ131Class::calibrate() {
  // Take care of the last Rs value read on the sensor
  // (forget the decimals)
  float lastRsValue = 0;
  // Count how many time we keep the same Rs value in a row
  int countReadInRow = 0;
  // Count how long we have to wait to have consistent value
  int count = 0;

  // Start heater
  startHeater();

  int timeToReadConsistency = MQ131_DEFAULT_STABLE_CYCLE;

  while(countReadInRow <= timeToReadConsistency) {
    float value = readRs();

    Serial.println(value);
    
    if((int)lastRsValue != (int)value) {
      lastRsValue = value;
      countReadInRow = 0;
    } else {
      countReadInRow++;
    }
    count++;
    delay(1000);
  }

  // Stop heater
  stopHeater();

  // We have our R0 and our time to read
  setR0(lastRsValue);
  setTimeToRead(count);
}

 /**
  * Store R0 value (come from calibration or set by user)
  */
  void MQ131Class::setR0(float _valueR0) {
  	valueR0 = _valueR0;
  }

 /**
 * Get R0 value
 */
 float MQ131Class::getR0() {
 	return valueR0;
 }

MQ131Class MQ131(MQ131_DEFAULT_RL);
