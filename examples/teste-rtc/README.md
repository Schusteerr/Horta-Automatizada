## Teste do Real Time Clock 🕒

<br>

Foi usado um Real Time Clock (Relógio de Tempo Real) - RTC de modelo DS3231- para montagem do protótipo de Horta Automatizada. Sua utilidade se dá ao fato de poder sincronizar com o atual horário, contando com diferença de fuso, poder adaptar o idioma e formatação de horário para diferentes idiomas e, também, servir se parâmetro para o horário em que deve realizar medições de umidade ou, se for o caso, irrigações. 

<br>

### Exemplos

Um fator a ser abordado é que o RTC obtém sua informação de data e hora através da Rede Wi-Fi em que o microcontrolador está conectado, então ele se configura automaticamente sincronizando com a Rede, contando com o fuso horário local.

~~~ino
//CÓDIGO DE PROGRAMAÇÃO

//Comando para configurar o horário do RTC pela Rede em que o ESP (microcontrolador) está conectado
rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
~~~

<br>

Ao fato dele ter a informação de data e hora que obtém da rede Wi-Fi, ele sincroniza o horário com um calendário que vêm incluso em sua configuração, então, é dito no código quais são os dias da semana para eu poder utilizar ele em diferentes idiomas, aqui estão exemplos disto em Português e Inglês:

~~~ino
//CÓDIGO DE PROGRAMAÇÃO

//Declara os dias da semana para o RTC - ptbr
char diasDaSemana[7][12] = {"Domingo", "Segunda", "Terca", "Quarta", "Quinta", "Sexta", "Sabado"};

//Declara os dias da semana para o RTC - en
char diasDaSemana[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
~~~

<br>

A partir daí, consegue-se usar do horário para enviar junto aos dados de umidade o tempo em que esses dados foram coletados, assim como definir os horários em que deve-se coletar esses dados

~~~ino
//CÓDIGO DE PROGRAMAÇÃO

//SE a hora for maior que 5 e menor que 10, onde os minutos são 30 ou 0, no intervalo de 0 segundos, eu habilito a função de umidade
if((agora.hour() >= 5) && (agora.hour() <= 10) & ((agora.minute() == 30) || (agora.minute() == 0)) && (agora.second() == 0))  
{
      setHumidity(); //Chamando a função de umidade para enviar os dados de umidade para o servidor
}
~~~

~~~ino
//CÓDIGO DE PROGRAMAÇÃO

//Defino uma mensagem de texto contendo a hora, minutos e segundos
String msgTime = String(agora.hour()) + ":" + String(agora.minute()) + ":" + String(agora.second()) 
~~~
~~~
Resultado: 
18:30:2-26/11/2022	Umidade:58.71
~~~