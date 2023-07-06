#include <Wire.h>

#define UMT A0
int umtValue=0;


void setup() {
  Serial.begin(9600);
  pinMode(UMT, INPUT);
  

}

void loop() {
  umtValue=analogRead(UMT);
  float UMTporcentual = ((1024-analogRead(UMT))/1024.0)*100.0; 
  Serial.println(UMTporcentual);
  delay(100);

}
