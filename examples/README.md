## Teste do Real Time Clock

Encontra-se o arquivo utilizado para testar o Real Time Clock (RTC) utilizado para montagem do protótipo de Horta Automatizada. Sua utilidade se dá ao fato de, através das linhas de comando, poder capitar facilmente o atual horário de uma medição de umidade e, também, servir se parâmetro para o horário em que deve realizar suas medições ou irrigações. 


~~~ino
//IN CODE:
String msg = token;
msg += String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second()) + ";";
msg += String(now.day()) + "/" + String(now.month()) + "/" + String(now.year());
~~~
~~~
RESULTS:
14:25:13;17/11/2022;53.42%
~~~

No Exemplo acima