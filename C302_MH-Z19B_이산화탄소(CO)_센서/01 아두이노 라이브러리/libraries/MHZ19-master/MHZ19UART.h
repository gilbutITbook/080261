#pragma once
#include <Arduino.h>
#include "SoftwareSerial.h"

#define SERIAL_TIMEOUT 500


enum MHZ19_RESULT {
	MHZ19_RESULT_OK,
	MHZ19_RESULT_ERR_UNKNOWN,
	MHZ19_RESULT_ERR_FB,
	MHZ19_RESULT_ERR_SB,
	MHZ19_RESULT_ERR_CRC,
	MHZ19_RESULT_ERR_TIMEOUT
};
enum MHZ19_RANGE {
	MHZ19_RANGE_1000,
	MHZ19_RANGE_2000,
	MHZ19_RANGE_3000,
	MHZ19_RANGE_5000,
	MHZ19_RANGE_10000
};

class MHZ19
{
public:
	//MHZ19(Stream * stream);
	MHZ19(int rx, int tx);
	MHZ19(int pwm);	
	~MHZ19();
	
	void begin(int rx, int tx);
	void begin(int pwm);
	
	// Call retrieveData to retrieve values from the sensor and check return code
	MHZ19_RESULT retrieveData();
	int getCO2();
	// It isn't ready to use minimum CO2 value, additional calculations have to be applied
	int getMinCO2();
	int getTemperature();
	int getAccuracy();

	MHZ19_RESULT setRange(MHZ19_RANGE range);
	void calibrateZero();
	void calibrateSpan(int span);
	void setAutoCalibration(bool mode);	
	
	void sendCommand(byte command, byte b3 = 0, byte b4 = 0, byte b5 = 0, byte b6 = 0, byte b7 = 0);
	MHZ19_RESULT receiveResponse(byte cmd[9]);	
private:
	// Serial Pins
	int _rx_pin = -1;
	int _tx_pin = -1;

	// Pwm Pin
	int _pwm_pin;
	
	SoftwareSerial * _serial = nullptr;
	byte _cmd = 0;
	byte _response[9];
	MHZ19_RESULT _result;

	void write(byte *data, byte len);
	int bytes2int(byte h, byte l);
	byte calcCRC(byte *data);
};

