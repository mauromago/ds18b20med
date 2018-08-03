/*
===========================================
libreria per la lettura dei
sensori di temperatura ds18b20
===========================================
*/
#include <DS18B20MED.h>
#include "Arduino.h"

DS18B20MED::DS18B20MED(int sLoop, int letture) //DS18B20MED::DS18B20MED(int sDelay, int sLoop, int letture)
{
 //_sDelay = sDelay;
 _sLoop = sLoop;
 _letture = letture;

}

// Reset the 1-wire bus
void DS18B20MED::OneWireReset (int Pin) // reset.  Should improve to act as a presence pulse
{
  digitalWrite (Pin, LOW);
  pinMode (Pin, OUTPUT);        // bring low for 500 us
  delayMicroseconds (500);
  pinMode (Pin, INPUT);
  delayMicroseconds (500);
}

// Send data to a 1-wire device
void DS18B20MED::OneWireOutByte (int Pin, uint8_t d) // output byte d (least sig bit first).
{
  byte n;
  for (n=8; n!=0; n--)
  {
    if ((d & 0x01) == 1)  // test least sig bit
    {
      digitalWrite (Pin, LOW);
      pinMode (Pin, OUTPUT);
      delayMicroseconds (5);
      pinMode (Pin, INPUT);
      delayMicroseconds (60);
    }
    else
    {
      digitalWrite (Pin, LOW);
      pinMode (Pin, OUTPUT);
      delayMicroseconds (60);
      pinMode (Pin, INPUT);
    }

    d = d>>1; // now the next bit is in the least sig bit position.
  }
}

//Read data from a 1-wire device
uint8_t DS18B20MED::OneWireInByte (int Pin) // read byte, least sig byte first
{
  byte d, n, b;

  for (n=0; n<8; n++)
  {
    digitalWrite (Pin, LOW);
    pinMode (Pin, OUTPUT);
    delayMicroseconds (5);
    pinMode (Pin, INPUT);
    delayMicroseconds (5);
    b = digitalRead (Pin);
    delayMicroseconds (50);
    d = (d >> 1) | (b<<7); // shift d to right and insert b in most sig bit position
  }
  return (d);
}

// Read temperature from a DS18B20.
// int sensorPin: Arduino digital I/O pin connected to sensor
int DS18B20MED::getCurrentTemp (int sensorPin)
{
  int HighByte, LowByte, TReading;
  OneWireReset (sensorPin);
  OneWireOutByte (sensorPin, 0xcc);
  OneWireOutByte (sensorPin, 0x44); // Perform temperature conversion, strong pullup for one sec
  delay (750); //waiting for confersion
  OneWireReset (sensorPin);
  OneWireOutByte (sensorPin, 0xcc);
  OneWireOutByte (sensorPin, 0xbe);

  LowByte = OneWireInByte (sensorPin);
  HighByte = OneWireInByte (sensorPin);
  TReading = (HighByte << 8) + LowByte;
//TReading è il valore della lettura binaria della conversione
  return (TReading);
}

// funzione princale di letture. agisce su variabile esterna
void DS18B20MED::DataConv (int TReading2, char *temp) //converte il valore in centesimi di grado e poi in stringa di caratteri
{
  int Tc_100, whole, fract, sign;
sign = TReading2 & 0x8000;  // test most sig bit
  if (sign) // negative
  {
    TReading2 = (TReading2 ^ 0xffff) + 1; // 2's complement
  }
  Tc_100 = (6 * TReading2) + TReading2 / 4;    // multiply by (100 * 0.0625) or 6.25
  whole = Tc_100 / 100;  // separate off the whole and fractional portions
  fract = Tc_100 % 100;
  if (sign) {
    temp[0] = '-';
  } else {
    temp[0] = '+';
  }
  temp[1] = (whole-(whole/100)*100)/10 +'0' ;
  temp[2] = whole-(whole/10)*10 +'0';
  temp[3] = '.';
  temp[4] = fract/10 +'0';
  temp[5] = fract-(fract/10)*10 +'0';
  temp[6] = '\0';
}

// ciclo di lettura del sensore
int DS18B20MED::lettCycle(int SENSOR)
 {
long tempCalc = 0;
int M1 = -9999;
int M2 = -9999;
int m1 = 9999;
int m2 = 9999;
int som = 0;
  //getCurrentTemp(SENSOR);
  //delay (_sDelay);
  //getCurrentTemp(SENSOR); //fatte due letture a vuoto
  //delay (_sDelay);
for (int x = 0; x <_letture; x++) {
	 som = getCurrentTemp(SENSOR)*10;
	if (som>M2) {
		if (som>M1) {
			M2=M1;
			M1=som;
		} else {
			M2=som;
		}
	}
	if (som<m1) {
		if (som<m2) {
			m1=m2;
			m2=som;
		} else {
			m1=som;
		}
	}
	tempCalc = tempCalc + som;
         delay (_sLoop);
	}
  tempCalc =( (tempCalc -M1-M2-m1-m2)/(_letture-4)+5)/10;
        
return (tempCalc);
}

// chimare le funzioni nel seguente modo
//DataConv (lettCycle(sensore, loop corto, numero di letture), stringa passata per referenza su cui scrivere);
