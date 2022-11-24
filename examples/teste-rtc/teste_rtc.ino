
#include <Wire.h>
#include "RTClib.h"

RTC_DS3231 rtc; 
  
char diasDaSemana[7][12] = {"Domingo", "Segunda", "Terca", "Quarta", "Quinta", "Sexta", "Sabado"}; //Dias da semana

void setup () {
  Serial.begin(9600);                          
    if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    //rtc.adjust(DateTime(2022, 5, 30, 20, 45, 00));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }

  // When time needs to be re-set on a previously configured device, the
  // following line sets the RTC to the date & time this sketch was compiled
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  // This line sets the RTC with an explicit date & time, for example to set
  // January 21, 2014 at 3am you would call:
  // rtc.adjust(DateTime(2022, 7, 6, 15, 4, 00));
}
void loop () {
  DateTime agora = rtc.now();                             
  Serial.print("Data: ");
  Serial.print(agora.day(), DEC);                         
  Serial.print('/');                                      
  Serial.print(agora.month(), DEC);                       
  Serial.print('/');                                      
  Serial.print(agora.year(), DEC);                        
  Serial.print(" / Dia da semana: ");                     
  Serial.print(diasDaSemana[agora.dayOfTheWeek()]);       
  Serial.print(" / Horas: ");                             
  Serial.print(agora.hour(), DEC);                        
  Serial.print(':');                                      
  Serial.print(agora.minute(), DEC);                      
  Serial.print(':');                                      
  Serial.print(agora.second(), DEC);                      
  Serial.println();                                       
  delay(1000);                                            
}
