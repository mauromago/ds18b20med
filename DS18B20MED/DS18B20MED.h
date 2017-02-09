#ifndef DS18B20MED_H_INCLUDED
#define DS18B20MED_H_INCLUDED

#include "Arduino.h"

class DS18B20MED{

private:
int  _sLoop, _letture; //int _sDelay, _sLoop, _letture;
	
public:
DS18B20MED (int sLoop, int letture); //DS18B20MED (int sDelay, int sLoop, int letture);

void OneWireReset (int Pin);
void OneWireOutByte (int Pin, uint8_t d);
uint8_t OneWireInByte (int Pin);
int getCurrentTemp (int sensorPin);
void DataConv (int TReading2, char *temp);
int lettCycle(int SENSOR);

 };

#endif // PRIMALIB_H_INCLUDED
