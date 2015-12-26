#include <DS18S20MED.h>

#define SENSOR_A  6 
//#define SENSOR_B  8 //required if more sensor are used
//#define SENSOR_C  7 

char temp_string_a[7];
//char temp_string_b[7]; //required if more sensor are used
//char temp_string_c[7];
long delayTime = 6000;
int  delayTimes = 100;
long shortLoop = 1000;
long shortDelay = 100;
int lettTodo = 10;

DS18S20MED mytest (shortDelay, shortLoop, lettTodo);

void setup() {
  // Set up the data pins for communication with DS18B20 sensors
  digitalWrite(SENSOR_A, LOW);
  pinMode(SENSOR_A, INPUT);
  /*digitalWrite(SENSOR_B, LOW); //required if more sensor are used
  pinMode(SENSOR_B, INPUT);
  digitalWrite(SENSOR_C, LOW);
  pinMode(SENSOR_C, INPUT);*/
  
  Serial.begin(9600);

}

void loop() {
  // lettura semplice del sensore
  Serial.print ("lettura getCurrentTemp ");
  Serial.println (mytest.getCurrentTemp (SENSOR_A));
  // lettura del sensore con ciclo completo
  // e calcolo della media
  Serial.print ("ciclo di lettura ");
  Serial.println (mytest.lettCycle(SENSOR_A));
  // conversione della lettura e scrittura
  // sul apposita stringa
  Serial.print ("valore convertito ");
  mytest.DataConv (mytest.lettCycle(SENSOR_A), temp_string_a);
  Serial.println (temp_string_a);
  Serial.println ("");
  delay (2000);
}
