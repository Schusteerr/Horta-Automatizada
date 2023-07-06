# Código da horta automatizada 💻

<br>

Código de programação responsável por coletar os dados de umidade relativa do solo e enviar para visualização online.

Aqui você poderá encontrar a estrutura de programação utilizada na Horta Automatizada e exemplos separados de testes do [Real Time Clock - Relógio em Tempo Real -](https://github.com/Schusteerr/Horta-Automatizada/tree/main/examples/teste-rtc) e do [Sensor de Umidade](https://github.com/Schusteerr/Horta-Automatizada/tree/main/examples/teste-umidade) utilizados para melhor compreensão de como foi pensado o código.

* Link do código: [main.ino](https://github.com/Schusteerr/Horta-Automatizada/blob/main/examples/main.ino) 

<br>

# Notas 📝

<br>

**Válido ressaltar algumas coisas para garantir que não hajam erros, antes de tudo, pode-se encontrar um [Guia para montagem e conceitos técnicos](https://github.com/Schusteerr/Horta-Automatizada/assets/Guia-Montagem/)**

### Na Estrutura

Para poder utilizar o microcontrolador ESP-8266, juntamente com sua montagem, é necessario instalar o aplicativo ArduinoIDE em seu computador.

Segue aqui dois links para guia-lo:

* [App ArduinoIDE](https://www.robocore.net/tutoriais/instalando-arduino-ide)


Depois de configurar o seu computador, o aplicativo necessitará de algumas configurações para descarregar o código de programação no protótipo montado.

Primeiramente, deve configura-lo para reconhecer o microcontrolador ESP 8266, isto poder ser feito seguindo o link abaixo

* [Como Configurar o ESP 8266 NodeMCU](https://www.robocore.net/tutoriais/como-programar-nodemcu-arduino-ide)

Depois, para que o código funcione, serão necessárias instalar as bibliotecas que fornecem o entendimento do código para o microcontrolador, isso é feio telo app do ArduinoIDE também.

Aqui esá um link explicando como que instala essas bibliotecas e o nome das bibliotecas necessárias.
* [Como Instalar Bibliotecas](https://www.blogdarobotica.com/2022/08/01/como-adicionar-biblioteca-na-arduino-ide/)

Dentre essas bibliotecas, a do Real Time Clock (RTC) será a única que precisará ser adicionada via arquivo .ZIP. Então segue abaixo o link da biblioteca.



* [Biblioteca do RTC](https://www.arduino.cc/reference/en/libraries/rtclib/)


~~~ino
#include <Arduino.h> // Biblioteca já inclusa no App

//Biblioteca do Real Time Clock(RTC)
#include "RTClib.h"

//Bibliotecas para possibilitar conexão Wi-Fi e entre o ESP e a Planilha
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiClientSecureBearSSL.h>
#include <WiFiClient.h>
#include "ArduinoJson.h
~~~

## Setup da planilha do Google Sheets e Google Script

Foi elabora um video explicativo sobre o ambiente do qual os dados vão, o mesmo que pode ser encontrado no link abaixo.

Para preparar o Google Scrip é necessário o código abaixo, para gerar uma implementação contendo o link do qual os dados vão ser encaminhados.

Abaixo, deixo também um link contendo o material referência para configurar o ESP a planilha, quaisquer duvidas consulte-o.

~~~c++
var sheet_id = ""; // Inserir o ID da planilha, que está situado no link da mesma
var sheet_name = ""; //Inserir o nome da planilha
function doGet(e){
var ss = SpreadsheetApp.openById(sheet_id);
var sheet = ss.getSheetByName(sheet_name);
var hora = String(e.parameter.hora); //aqui foi dita uma coluna do nome 'hora', caso a sua for diferente apenas substitua
var dados = String(e.parameter.dados) //aqui foi dita uma coluna do nome 'dados', caso a sua for diferente apenas substitua
sheet.appendRow([dados,hora]); //efetue a substituição dos nomes da coluna aqui também, caso necessário
}
~~~

* [Referência](https://iotdesignpro.com/articles/esp32-data-logging-to-google-sheets-with-google-scripts)