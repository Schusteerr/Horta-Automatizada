#include <Arduino.h>
//Biblioteca responsável por conter funções necessárias para gerar comunicação entre dispositivos
#include <Wire.h>
//Biblioteca do Real Time Clock(RTC)
#include "RTClib.h"
//Bibliotecas para possibilitar conexão Wi-Fi e entre o servidor MQTT
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>


//Servidor Enviar Dados
#ifndef HTTPSERV
#define HTTPSERV  "" //inserir a URL do Servidor HTTP que deseja enviar os dados
#define HTTPTOKEN  "" //Token do Servidor HTTP
#endif
const char* server =  HTTPSERV;
const char* token = HTTPTOKEN;

//SSID e Senha para conectar ao Wi-Fi
#ifndef STASSID
#define STASSID //ssid do WIFI
#define STAPSK  //senha do WIFI
#endif
const char* ssid     = STASSID;
const char* password = STAPSK;

//Objetos
WiFiClient client;

//Variáveis para formação do percentual da umidade e seus respectivos níveis
double UMTporcentual;
#define nivelBaixo 30 
#define nivelAlto 85 
#define ideal (nivelBaixo + nivelAlto)/2 
#define margemErro 10

//Variáveis refente à umidade do solo
int dry = 0;
int green = 0;
int wet = 0;

//Real Time Clock sendo usado do tipo RTC_DS3231
RTC_DS3231 rtc;  
//Declara os dias da semana para o RTC
char diasDaSemana[7][12] = {"Domingo", "Segunda", "Terca", "Quarta", "Quinta", "Sexta", "Sabado"};



#define delayval 1000

//Função para configurar o código
void setup()
{ 
  //Inicia o microcontrolador - ESP8266 - com taxa de transferência de bits à 115200
  Serial.begin(115200); 

  //Chama a função que estabelece uma conexão Wi-Fi
  setup_wifi();

  //Informa a porta A0 como sensor - no caso, de umidade -
  pinMode(A0, INPUT);

  //Série de comandos para iniciar o RTC, onde, caso não inicie irá encerrar o programa                 
  if (! rtc.begin())
  {
    Serial.println("Não foi possível encontrar o RTC");
    Serial.flush();
    while (1) delay(10);
  }
  //Série de comandos para caso o RTC perca o poder, e ao conecta-lo novamente a hora irá configurar de acordo com a compilação
  if (rtc.lostPower())
  {
    Serial.println("RTC está sem energia, vamos configurar a hora!");
	  // Quando precisa ser colocado em um novo dispositivo, ou quando perde energia, as linhas a seguir configuram a hora para o tempo em que foi compilado
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  }

  // Quando o RTC precisa ser re-setado em um dispositivo previamente configurado, as linhas a seguir configuram a hora para o tempo em que foi compilado
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  // APOS DESCARREGAR O HORÁRIO ATUAL NO RTC, 'APAGUE' A LINHA ACIMA E DESCARREGUE O CÓDIGO NOVAMENTE DELE
  // caso contrario, o RTC irá voltar para um mesmo horário diversas vezes  
}

//Função para iniciar a conexão Wi-Fi
void setup_wifi()
{                                                     
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println("Waiting for connection");
  }                                    
}

//Função para enviar os dados - post HTTP -
void sendmensage()
{
  http.begin(client, server);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  String msg = token;
  msg += String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second()) + ";";
  msg += String(now.day()) + "/" + String(now.month()) + "/" + String(now.year());
  msg += ";" + String(UMTporcentual) + "%";

  int httpCode = http.POST(msg);
  Serial.println(httpCode);
  String payload = http.getString();
  Serial.println(payload);

  http.end();
}

//Função para enviar uma mensagem de erro - " " - 
void senderrormensage()
{
  http.begin(client, server);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  String msg = token;
  msg += String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second()) + ";";
  msg += String(now.day()) + "/" + String(now.month()) + "/" + String(now.year());
  msg += ";" + "wtf";

  int httpCode = http.POST(msg);
  Serial.println(httpCode);
  String payload = http.getString();
  Serial.println(payload);

  http.end();

}

//Função que separará a umidade coletada em diferentes níveis
void setHumidity()
{
  DateTime agora = rtc.now();
  delay(delayval);

  //Calculando porcentual de umidade a partir dos valores analógicos obtidos do sensor (varia de 0-1024)
  UMTporcentual = ((1024-analogRead(A0))/1024.0)*100.0;
  //Separando os níveis de umidade em 3 níveis e uma mensagem - wtf - caso não esteja operando corretamente 
  if(dry = ((UMTporcentual <= nivelBaixo + margemErro) && (UMTporcentual >= 0 ) ))
  {
    sendmensage(); //Envia mensagem de acordo com a umidade
  }
  else if(wet = (UMTporcentual >= nivelAlto - margemErro && UMTporcentual <= 100))
  {
    sendmensage();// "
  }
  else if((UMTporcentual >= nivelBaixo && UMTporcentual <= ideal) || (UMTporcentual > ideal && UMTporcentual < nivelAlto))
  {
    sendmensage();// "
  }
  else
  {
    senderrormensage()//Envia mensagem de erro caso a entrada de umidade for invalida
  }                   
}

//Escopo principal de operação
void loop()
{
  //Caso a conexão WI-FI for estabelecida inicia a sequencia de código no looping
  if (WiFi.status() == WL_CONNECTED)
  {
    HTTPClient http;
    DateTime agora = rtc.now();
    delay(delayval);

    //Condições para operar os sensores e enviar informações:
    if((agora.hour() >= 5) && (agora.hour() <= 10) & (agora.minute() == 30))   //Caso o horário esteja entre 6 e 10 horas - a cada meia hora -
    {
      setHumidity(); //Chamando a função de umidade para enviar os dados de umidade para o servidor
      delay(10000);
    }else if((agora.hour() >= 17) && (agora.hour() <= 22) & (agora.minute() == 30))  //Caso o horário esteja entre 17 e 22 horas - " " " " - 
    {
      setHumidity();
      delay(10000);
    }
    
  }else
  {
    Serial.println("Sem wifi...");
  }
  Serial.println("Esperando...");
  delay(30000);

}