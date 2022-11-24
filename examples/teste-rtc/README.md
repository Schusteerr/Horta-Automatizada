## Teste do Real Time Clock ⏰

<br>

Aqui temos um exemplo do Real Time Clock (RTC) utilizado para montagem do protótipo de Horta Automatizada. Sua utilidade se dá ao fato de, através das linhas de comando, poder capitar facilmente o atual horário de uma medição de umidade e, também, servir se parâmetro para o horário em que deve realizar suas medições ou irrigações. 

<br>

~~~ino
//IN MAIN CODE:

//Criando a estrutura da mensagem a ser enviada, contendo data, hora e umidade
String msg = token; //token refere-se ao meio de post via HTTP para o servidor utilizado
msg += String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second()) + ";";
msg += String(now.day()) + "/" + String(now.month()) + "/" + String(now.year());
msg += ";" + String(UMTporcentual) + "%";

//post da mensagem via http
int httpCode = http.POST(msg);
String payload = http.getString();
http.end();
~~~

~~~ino
if((agora.hour() >= 5) && (agora.hour() <= 10) & (agora.minute() == 30))   //Caso o horário esteja entre 6 e 10 horas - a cada meia hora -
{
      setHumidity(); //Chamando a função de umidade para enviar os dados de umidade para o servidor
      delay(10000);
}else if((agora.hour() >= 17) && (agora.hour() <= 22) & (agora.minute() == 30))  //Caso o horário esteja entre 17 e 22 horas - " " " " - 
{
      setHumidity();
      delay(10000);
}
~~~
