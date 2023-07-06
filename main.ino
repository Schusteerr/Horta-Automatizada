#include <Arduino.h>
//Biblioteca responsável por conter funções necessárias para gerar comunicação entre dispositivos
#include <Wire.h>
//Biblioteca do Real Time Clock(RTC)
#include "RTClib.h"
//Bibliotecas para possibilitar conexão Wi-Fi e entre o ESP e a Planilha
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiClientSecureBearSSL.h>
#include <WiFiClient.h>
#include "ArduinoJson.h"

//ID do Google Script
#ifndef SHEET_ID
#define SHEET_ID  "" //Inserir o ID do Google Script
#endif
String sheet_id =  SHEET_ID;

//Certificado de Segura do Google Script
const char fingerprint[] PROGMEM = "2B B5 F0 49 BB 7A DE CB 2F 32 67 2E 10 D5 45 3E BE 2C 18 0B"; //Inserir o Certificado de Segurança SHA-1 do Google Script

//SSID e Senha para conectar ao Wi-Fi
#ifndef STASSID
#define STASSID ""//ssid do WIFI
#define STAPSK  ""//senha do WIFI
#endif
const char* ssid = STASSID;
const char* password = STAPSK;

//Objetos
WiFiClient client;
ESP8266WiFiMulti WiFiMulti;

//Variáveis para formação do percentual da umidade e seus respectivos níveis
double UMTpercentual;
#define nivelBaixo 30 
#define nivelAlto 85 
#define ideal (nivelBaixo + nivelAlto)/2 
#define margemErro 10 //uma margem de erro que opera entre o nível ideal

//Real Time Clock sendo usado do tipo RTC_DS3231
RTC_DS3231 rtc;  

//Declara os dias da semana para o RTC
char diasDaSemana[7][12] = {"Domingo", "Segunda", "Terca", "Quarta", "Quinta", "Sexta", "Sabado"};

//define um valor de delay (atraso), usado em algumas ocasiões para questão de segurança - evitar bugs -
#define delayval 1000

//Função que inicia uma conexão à uma rede Wi-Fi
void setup_wifi()
{                                                     
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(ssid, password);

  //Enquanto não conseguir conectar a uma rede Wi-Fi será informado no Terminal do ArduinoIDE
  while ((WiFiMulti.run() != WL_CONNECTED))
  {
    delay(500);
    Serial.println("Waiting for connection");
  }                                    
}

//Função para configurar o código
void setup()
{ 
  //Inicia o microcontrolador - ESP8266 - com taxa de transferência de bits à 115200
  Serial.begin(115200); 

  //Chama a função que estabelece uma conexão Wi-Fi
  setup_wifi();

  //Informa a porta A0 como entrada de dados - porta a ser colocada o sensor de umidade -
  pinMode(A0, INPUT);

  //Caso o RTC não inicie informa um erro no Terminal Do ArduinoIDE              
  if (! rtc.begin())
  {
    Serial.println("Não foi possível encontrar o RTC");
    Serial.flush();
    while (1) delay(10);
  }
  //Caso o RTC perca energia informa no Terminal do ArduinoIDE e, caso recupere energia, ele reconfigura o Horário pela rede conectada
  if (rtc.lostPower())
  {
    Serial.println("RTC está sem energia, vamos configurar a hora!");
	  //Comando para configurar a hora do RTC pela Rede em que o ESP está conectado
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  }
 
}

//Função para enviar os dados para a Planilha
void sendmensage()
{
  //Puxando uma configuração para o RTC, onde 'agora' se situa como o momento horário do RTC
  DateTime agora = rtc.now();
  delay(delayval);

  //Define uma mensagem de texto contendo nela a data fornecida pelo RTC, no formato h:min:sec e DD/MM/AA
  String msgTime = String(agora.hour()) + ":" + String(agora.minute()) + ":" + String(agora.second()) + "-" + String(agora.day()) + "/" + String(agora.month()) + "/" + String(agora.year());
  //Define uma mensagem de texto contendo o porcentual de umidade
  String msgUMT = "Umidade:" + String(UMTpercentual);
  //Define, em texto, a URL do site do Google Script que dirá o horario e dado de umidade para por na planilha
  String urlFinal = "https://script.google.com/macros/s/"+sheet_id+"/exec?hora="+ msgTime +"&umidade="+ msgUMT;

  //Código que possibilita o Cliente Wi-Fi do ESP ser informado como Seguro para poder se conectar à um site em HTTPS
  std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
  client->setFingerprint(fingerprint); //Insere no cliente o Certificado de Segurança do Google Script
  HTTPClient http; //Comando que inicia a conexão HTTP
  http.begin(*client,urlFinal); //Comando para conectar o cliente Wi-Fi do ESP à URL definida anteriormente
  http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
  int httpCode = http.GET(); //Pega o Status do código de conexão HTTP, que através dele pode-se saber se tem erro de conexão
  Serial.print("HTTP Status Code: ");
  Serial.println(httpCode);
  String payload;
  if (httpCode > 0) {    //Caso o Status do Código de conexão HTTP for maior que 0, não há erro
      payload = http.getString();
      Serial.println("Payload: "+payload);  //Nos dá informação sobre o site conectado no Terminal do ArduinoIDE
  }
  http.end();
}

//Exatamente igual a função anterior que envia uma mensagem à planilha, porém, essa nos traz uma mensagem de erro caso haja algum problema com a medição de umidade
void senderrormensage()
{
  DateTime agora = rtc.now();
  delay(delayval);

  String msgTime = String(agora.hour()) + ":" + String(agora.minute()) + ":" + String(agora.second()) + "-" + String(agora.day()) + "/" + String(agora.month()) + "/" + String(agora.year());
  
  String urlFinal = "https://script.google.com/macros/s/"+sheet_id+"/exec?hora="+ msgTime +"&umidade=ERRO"; // Mensagem de erro
  
  std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
  client->setFingerprint(fingerprint);
  Serial.println("connected...");
  HTTPClient http;
  http.begin(*client,urlFinal);
  http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
  int httpCode = http.GET(); 
  Serial.print("HTTP Status Code: ");
  Serial.println(httpCode);
  String payload;
  if (httpCode > 0) {
      payload = http.getString();
      Serial.println("Payload: "+payload);    
  }
  http.end();
}

//Função de Umiade que calcula um porcentual de umidade e separa ele para três diferentes níveis
void setHumidity()
{
  DateTime agora = rtc.now();
  delay(delayval);

  //Calculando porcentual de umidade a partir dos valores analógicos obtidos do sensor (varia de 0-1024)
  UMTpercentual = ((1024-analogRead(A0))/1024.0)*100.0;

  //Separando os níveis de umidade em 3 níveis e uma ocasião caso não esteja operando corretamente e haja um erro 
  if(((UMTpercentual <= nivelBaixo + margemErro) && (UMTpercentual >= 0 ) ))
  {
    sendmensage(); //Envia mensagem de acordo com a umidade
  }
  else if((UMTpercentual >= nivelAlto - margemErro && UMTpercentual <= 100))
  {
    sendmensage();// "
  }
  else if((UMTpercentual >= nivelBaixo && UMTpercentual <= ideal) || (UMTpercentual > ideal && UMTpercentual < nivelAlto))
  {
    sendmensage();// "
  }
  else
  {
    senderrormensage(); //Envia a mensagem de erro
  }
}

//Função principal de operação, que deixa o ESP em looping dentro do que a função pede
void loop()
{
  //Caso a conexão WI-FI foi estabelecida, o ESP começa a olhar parâmetros de horário para chamar a função de Umidade, para então enviar os dados
  if ((WiFiMulti.run() == WL_CONNECTED))
  {
    //Chamando, novamente, a configuração do RTC, onde 'agora' condiz com o horário atual
    DateTime agora = rtc.now();
    delay(delayval);

    //Comando para CASO o horário atual esteja entre 5 e 10 horas, a cada meia hora, enviar os dados pela função de Umidade
    if((agora.hour() >= 5) && (agora.hour() <= 10) && ((agora.minute() == 30) || (agora.minute() == 0)) && (agora.second() <= 5)) 
    {
      setHumidity(); //Chamando a função de Umidade para enviar os dados de umidade para a planilha
      delay(delayval);
    }
    //Comando para CASO o horário atual esteja entre 17 e 22 horas, a cada meia hora, enviar os dados pela função de Umidade
    else if((agora.hour() >= 17) && (agora.hour() <= 22) && ((agora.minute() == 30) || (agora.minute() == 0)) && (agora.second() <= 5)) 
    {
      setHumidity();
      delay(delayval);
    }
    
  }else // Caso, inicialmente, não foi estabelecida Conexão Wi-Fi, o ESP informará no Terminal do ArduinoIDE
  {
    Serial.println("Sem wifi...");
  }
}