# Guia de Montagem 🔩

Aqui será apresentado um pouco sobre os itens utilizados para a montagem, a parte detalhada esta disponível em vídeos que podem ser encontrados na [Página Principal](https://github.com/Schusteerr/Horta-Automatizada#circuito-)

## Circuito Eletrônico
* para testes de montagem foi utilizada uma Protoboard, mas no protótipo os itens são soldados.

### **ESP8266 NodeMcu ESP-12**
Seu uso se dá a capacidade de poder trabalhar rapidamente com dados e possuir um módulo Wi-Fi para poder utilizar desses dados em diferentes aplicações, no projeto ele se comunica via HTTP

Naturalmente programamos o ESP para identificar em sua entrada analógica A0 (ADC0) o sensor de umidade e suportar o RTC nas estradas D1(SCL) e D2(SDA) para com parâmetro de horários.

<div align="center">
    <img align="center" src="https://i0.wp.com/randomnerdtutorials.com/wp-content/uploads/2019/05/ESP8266-NodeMCU-kit-12-E-pinout-gpio-pin.png?quality=100&strip=all&ssl=1">   
</div>

<br>

### **Sensor de Umidade**

O sensor de umidade opera fazendo uma leitura relativa da umidade pela comparação a Resistencia, onde a água diminui a resistência, enquanto o solo seco conduz com mais dificuldade.

Isso nos dá valores analógicos de 0-1024 para umidade, onde 0 é muito úmido e, logicamente, 1024 muito seco. O código no ESP converte esses valores para 0-100% de umidade e trabalhamos com esses dados.

<div align="center">
    <img align="center" src="https://www.baudaeletronica.com.br/media/catalog/product/cache/1/image/800x/9df78eab33525d08d6e5fb8d27136e95/u/m/umidade-do-solo.jpg">   
</div>

<br>

### **Real Time Clock (RTC) Modelo DS3231**

O RTC trata-se de um relógio que é configurado no código de programação para operar, neste caso, pelo Horário de Brasilia, onde ele puxa o tal configuração a partir do momento que o possui um modulo Wi-Fi junto ao circuito.

Sua utilidade se dá ao fato de poder deixar o circuito operando dentro de ciclos de horários específicos, por exemplo, coletar e enviar os dados de umidade entre 5a.m. e 10a.m. a cada 30 minutos. Também foi utilizado para enviar uma marcação de horário do tempo em que os dados foram coletados.

<div align="center">
    <img align="center" src="https://http2.mlstatic.com/D_NQ_NP_899832-MLB50562962756_072022-O.webp">   
</div>

<br>

##

## Power Supply



