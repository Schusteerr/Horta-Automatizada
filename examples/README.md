## Código da horta automatizada 💻

<br>

Aqui você poderá encontrar a estrutura de código utilizada para programar a Horta Automatizada e exemplos separados de testes para um RTC e Sensor de Umidade utilizados para melhor compreensão de como foi pensado o código.

<br>

## Notes 📝

<br>

Válido ressaltar algumas coisas para garantir que não hajam erros, antes de tudo, pode-se encontrar um [Guia para montagem e conceitos técnicos](https://github.com/Schusteerr/Horta-Automatizada/assets/Guia-Montagem/)

### Na Estrutura
É válido salientar que para esse projeto foi utilizado um dispositivo ESP, que nos possibilita fazer comunicação via wi-fi sem precisar de um módulo extra e também nos oferece uma capacidade muito boa para trabalhar com dados.
Caso não esteja acostumado com o ESP é necessário fazer um 'setup' para que funcione corretamente, deixo aqui algumas referencias para auxiliar

* [App ArduinoIDE](https://www.robocore.net/tutoriais/instalando-arduino-ide)

* [ESP 8266 NodeMCU](https://www.robocore.net/tutoriais/como-programar-nodemcu-arduino-ide)

### No Código

Algumas bibliotecas são necessárias para executar o Código

~~~ino
//Biblioteca responsável por conter funções necessárias para gerar comunicação entre dispositivos
#include <Wire.h>
//Biblioteca do Real Time Clock(RTC)
#include "RTClib.h"
//Bibliotecas para possibilitar conexão Wi-Fi e entre o servidor MQTT
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
~~~
Dentre essas bibliotecas a do Real Time Clock(RTC) será a única que precisará ser adicionada via arquivo .ZIP.
Caso nao seja adepto em como instalar bibliotecas no ArduinoIDE, deixo aqui também algumas referências para servir de auxilio.

* [Como Instalar Bibliotecas](https://www.blogdarobotica.com/2022/08/01/como-adicionar-biblioteca-na-arduino-ide/)

* [Biblioteca do RTC](https://www.arduino.cc/reference/en/libraries/rtclib/)
