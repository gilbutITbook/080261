/*
  DGS_25SEP17.cpp - Library for reading KWJ Engineering with SPEC Sensors on Digital SDK with firmware date 25SEP17.
  Created by David E. Peaslee, Mar 29, 2018.
*/

#include "DGS.h"

DGS::DGS() {
}

DGS::DGS(Stream *mySerial) : _mySerial(mySerial) {
}

DGS::DGS(Stream &mySerial) : _mySerial(&mySerial) {
}

void DGS::begin(int rx, int tx){

}

void DGS::DEBUG_PRINTLN(long x) {
	delay(10);
	if (DEBUG) {
		Serial.println(x);
	}
}

void DGS::DEBUG_PRINTLN(String x) {
	delay(10);
	if (DEBUG) {
		Serial.println(x);
	}
}

void DGS::DEBUG_PRINTLN(float x) {
	delay(10);
	if (DEBUG) {
		Serial.println(x);
	}
}

void DGS::DEBUG_PRINT(long x) {
	delay(10);
	if (DEBUG) {
		Serial.print(x);
	}
}

void DGS::DEBUG_PRINT(float x) {
	delay(10);
	if (DEBUG) {
		Serial.print(x);
	}
}

void DGS::DEBUG_PRINT(String x) {
	delay(10);
	if (DEBUG) {
		Serial.print(x);
	}
}

int DGS::getData(char c) {
	delay(500);
	String dataString;

	while (_mySerial->available())
		_mySerial->read();
	_mySerial->write(c);

	while (!_mySerial->available()) {
	}

	dataString = _mySerial->readStringUntil('\n');
	for (int i = 0; i < 11; i++) {
		String subS = dataString.substring(0, dataString.indexOf(','));
		if (subS.length() == 0) return 0;
		dataArray[i] = subS.toInt();
		dataString = dataString.substring(dataString.indexOf(',') + 2);
	}
	return 1;
}

int DGS::setToff(float offset) {
	String commandString;
	DEBUG_PRINTLN("Starting T Offset");
	while (_mySerial->available()) _mySerial->read();
	_mySerial->write('T');
	//getData('T');
	while (!_mySerial->available()) {
	}
	commandString = _mySerial->readString();
	DEBUG_PRINT(commandString);
	delay(10);

	if (commandString == "\r\nEnter Temperature_Offset: ") {
		_mySerial->print(offset);
		_mySerial->write('\r');
	} else {
		DEBUG_PRINTLN("Failed Entering Temperature");
		delay(2000);
		while (_mySerial->available()) _mySerial->read();
		return 0;
	}

	while (!_mySerial->available()) {
	}
	commandString = _mySerial->readString();
	DEBUG_PRINTLN(commandString);
	if (commandString.toFloat() == offset) {
		DEBUG_PRINTLN("Success");
		// getData('\r');
		return 1;
	} else {
		// getData('\r');
		delay(3000);
		return 0;
	}
}

int DGS::setBC(String BC) {
	String commandString;
	DEBUG_PRINTLN("Starting BC Setup");
	while (_mySerial->available()) _mySerial->readString();
	_mySerial->write('B');
	//getData('B');

	while (!_mySerial->available()) {
	}
	commandString = _mySerial->readString();
	DEBUG_PRINTLN(commandString);

	delay(10);
	if (commandString == "\r\nRemove Sensor and Scan: ") {  //": "
		for (int i = 0; i < BC.length() + 1; i++) {
			_mySerial->write(BC.charAt(i));
			delay(10);
		}
		_mySerial->write('\r');
	} else {
		DEBUG_PRINTLN("Failed Entering BC");
		DEBUG_PRINTLN(commandString);

		return 0;
	}

	while (!_mySerial->available()) {
	}
	commandString = _mySerial->readStringUntil('\r');
	commandString.setCharAt(commandString.length() - 1, '\r');
	DEBUG_PRINTLN(commandString);

	while (!_mySerial->available()) {
	}
	commandString = _mySerial->readString();
	DEBUG_PRINTLN(commandString);

	if (commandString == "\r\nSetting OC...done\r\nSetting zero...done\r\n") {
		delay(2000);
		DEBUG_PRINTLN("Success");
		return 1;
	}
	delay(2000);
	DEBUG_PRINTLN("Failed Setting Barcode");
	return 0;
}

void DGS::getEEPROM(void) {
	DEBUG_PRINTLN("Starting EEPROM Read");
	while (_mySerial->available()) _mySerial->read();
	_mySerial->write('e');
	//getData('e');

	while (!_mySerial->available()) {
	}
	String data = _mySerial->readStringUntil('\n');  //Read Header

	while (!_mySerial->available()) {
	}

	for (int i = 1; i < 14; i++) {
		data = _mySerial->readStringUntil('\n');
		String subS1 = data.substring(0, data.indexOf('='));
		String subS2 = data.substring(data.indexOf('=') + 2);
		eepromInt[i] = subS2.toInt();
		DEBUG_PRINT(subS1);
		DEBUG_PRINT("= ");
		DEBUG_PRINTLN(eepromInt[i]);
	}

	for (int i = 14; i < 19; i++) {
		data = _mySerial->readStringUntil('\n');
		String subS1 = data.substring(0, data.indexOf('='));
		String subS2 = data.substring(data.indexOf('=') + 2);
		eepromStr[i - 14] = subS2;
		DEBUG_PRINT(subS1);
		DEBUG_PRINT("= ");
		DEBUG_PRINTLN(eepromStr[i - 14]);
	}

	data = _mySerial->readStringUntil('\n');
	String subS1 = data.substring(0, data.indexOf('='));
	String subS2 = data.substring(data.indexOf('=') + 2);
	Sensitivity_Code = subS2.toFloat();
	DEBUG_PRINT(subS1);
	DEBUG_PRINT("= ");
	DEBUG_PRINTLN(Sensitivity_Code);

	_barcode = eepromStr[0];
	_gasname = eepromStr[3].substring(0, eepromStr[3].length()-1);
}

String DGS::getFW(void) {
	String dataString;
	while (_mySerial->available()) _mySerial->read();
	_mySerial->write('f');
	//getData('f');

	while (!_mySerial->available()) {
	}
	dataString = _mySerial->readStringUntil('\r');
	_mySerial->flush();
	while (_mySerial->available()) _mySerial->read();

	return dataString;
}

int DGS::setLMP(int R1, int R2, int R3) {
	String commandString;
	DEBUG_PRINTLN("");

	DEBUG_PRINTLN("Setting LMP Registers");
	while (_mySerial->available()) _mySerial->read();
	_mySerial->write('L');
	//getData('L');

	while (!_mySerial->available()) {
	}
	commandString = _mySerial->readString();
	DEBUG_PRINT(commandString);
	if (commandString == "\r\nEnter LMP91000 Register 0x10: ") {
		_mySerial->print(R1);
		_mySerial->write('\r');
	} else {
		DEBUG_PRINTLN("Setting Failed");
		return 0;
	}
	while (!_mySerial->available()) {
	}
	commandString = _mySerial->readStringUntil('\n');
	DEBUG_PRINTLN(commandString);
	if (commandString.toInt() != R1) {
		DEBUG_PRINTLN("Failure");
		return 0;
	}

	while (!_mySerial->available()) {
	}
	commandString = _mySerial->readString();
	DEBUG_PRINT(commandString);
	if (commandString == "Enter LMP91000 Register 0x11: ") {
		_mySerial->print(R2);
		_mySerial->write('\r');
	} else {
		DEBUG_PRINTLN("Setting Failed");
		return 0;
	}
	while (!_mySerial->available()) {
	}
	commandString = _mySerial->readStringUntil('\n');
	DEBUG_PRINTLN(commandString);
	if (commandString.toInt() != R2) {
		DEBUG_PRINTLN("Failure");
		return 0;
	}

	while (!_mySerial->available()) {
	}
	commandString = _mySerial->readString();
	DEBUG_PRINT(commandString);
	if (commandString == "Enter LMP91000 Register 0x12: ") {
		_mySerial->print(R3);
		_mySerial->write('\r');
	} else {
		DEBUG_PRINTLN("Setting Failed");
		return 0;
	}
	while (!_mySerial->available()) {
	}
	commandString = _mySerial->readStringUntil('\n');
	DEBUG_PRINTLN(commandString);
	if (commandString.toInt() != R3) {
		DEBUG_PRINTLN("Failure");
		delay(2000);
		return 0;
	} else {
		DEBUG_PRINTLN("Success");
		delay(2000);
		return 1;
	}
}

int DGS::getLMP(void) {
	String dataString;
	DEBUG_PRINTLN("Getting LMP Registers");
	while (_mySerial->available()) _mySerial->read();
	_mySerial->write('l');
	//getData('l');

	while (!_mySerial->available()) {
	}
	dataString = _mySerial->readStringUntil('\n');
	for (int i = 0; i < 3; i++) {
		dataString = _mySerial->readStringUntil('\n');
		String subS = dataString.substring(dataString.indexOf('=') + 1, dataString.length());
		LMP[i] = subS.toInt();
		DEBUG_PRINT("LMP R");
		DEBUG_PRINT((long)i);
		DEBUG_PRINT(" = ");
		DEBUG_PRINTLN((long)LMP[i]);
		if (LMP[i] < 3 || LMP[i] > 200) return 0;
	}
	return 1;
}

int DGS::zero(void) {
	String commandString;
	DEBUG_PRINTLN("Starting Zero");
	while (_mySerial->available()) _mySerial->read();
	_mySerial->write('Z');
	//getData('Z');

	while (!_mySerial->available()) {
	}
	commandString = _mySerial->readString();
	//DEBUG_PRINT(commandString);
	commandString.remove(commandString.length() - 2);

	if (commandString == "\r\nSetting zero...done") {
		DEBUG_PRINTLN("Success");
		return 1;
	} else
		DEBUG_PRINTLN("Failed Zero");

	return 0;
}

int DGS::setXSpan(float X) {
	if (getFW() != "15SEP17") {
		DEBUG_PRINTLN("Only checked with firmware [15SEP17]");
		return 0;
	}

	String commandString;
	String inSf;
	DEBUG_PRINT("Starting Span Setup");
	while (_mySerial->available()) _mySerial->read();
	_mySerial->write('S');
	//getData('S');

	while (!_mySerial->available()) {
	}

	commandString = _mySerial->readString();
	DEBUG_PRINT(commandString);
	delay(10);
	if (commandString == "\r\nEnter span gas value in PPM: ") {
		_mySerial->print(X);
		_mySerial->write('\r');
	} else {
		DEBUG_PRINT("Failed Span");
		while (_mySerial->available()) _mySerial->read();
		return 0;
	}

	while (!_mySerial->available()) {
	}

	inSf = _mySerial->readString();
	DEBUG_PRINT(inSf);
	if (inSf.toFloat() == X) {
		DEBUG_PRINTLN("Success. Please wait, be patient..");
		getData('\r');
		return 1;
	} else {
		DEBUG_PRINTLN("Failed Span");
		getData('\r');
		return 0;
	}
}

long DGS::getConc(char x) {
	if (x == 'p')
		return dataArray[1];
	else
		return dataArray[4];
}

long DGS::getTemp(char t) {
	if (t == 'F')
		return dataArray[2] * 9 / 5 + 32;
	else if (t == 'C')
		return dataArray[2];
	else
		return dataArray[5];
}

long DGS::getRh(char r) {
	if (r == 'r')
		return dataArray[3];
	else
		return dataArray[6];
}

String paddingZero(String cadena, String cPad, unsigned int totalLength, bool left) {
	if (cadena.length() < totalLength) {
		for (unsigned int t = 0; t < (cadena.length() - totalLength); t++) {
			if (left) cadena = cPad + cadena;
			if (!left) cadena = cadena + cPad;
		}
	}
	return cadena;
}

String DGS::getTimeRunning() {
	String temp;
	return String(dataArray[7]) + "d " +
	       paddingZero(String(dataArray[8]), "0", 2, true) + ":" +
	       paddingZero(String(dataArray[9]), "0", 2, true) + ":" +
	       paddingZero(String(dataArray[10]), "0", 2, true);
}

String DGS::getBarcode() {
	// DEBUG = false;
	// getEEPROM();
	// DEBUG = true;
	return _barcode;
}

String DGS::getGasName() {
	// DEBUG = false;
	// getEEPROM();
	// DEBUG = true;
	return _gasname;
}

void DGS::resetModule() {
	String commandString;
	DEBUG_PRINTLN("Resetting module...");
	while (_mySerial->available()) _mySerial->read();

	_mySerial->write('r');
}