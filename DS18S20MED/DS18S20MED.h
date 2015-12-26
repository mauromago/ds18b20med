#ifndef DS18S20MED_H_INCLUDED
#define DS18S20MED_H_INCLUDED

#include "Arduino.h"

class DS18S20MED{

private:
int _sDelay, _sLoop, _letture;
	
public:
DS18S20MED (int sDelay, int sLoop, int letture);

void OneWireReset (int Pin);
void OneWireOutByte (int Pin, uint8_t d);
uint8_t OneWireInByte (int Pin);
int getCurrentTemp (int sensorPin);
void DataConv (int TReading2, char *temp);
int lettCycle(int SENSOR);

 };

#endif // PRIMALIB_H_INCLUDED
