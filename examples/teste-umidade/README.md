## Teste do Sensor de Umidade 💧

<br>

O sensor de umidade é o mais importante do projeto da Horta, pois através dele obtém-se os dados de umidade relativa do solo. Essa é a parte mais matemática que pode-se deparar neste projeto, pois o sensor ele procura por uma variação de resistência do solo ao conduzir uma pequena corrente elétrica, a partir da variação de umidade ele nos trás valores de umidade.

<br>

### Exemplificação

Quando os sensor procura pela variação de resistência, ele nos retorna valores que variam de 0 à 1024, sendo esses dos dados de umidade do solo. Então passam os dados para um percentual de umidade.
~~~ino
//CÓDIGO DE PROGRAMAÇÃO

//Calculando porcentual de umidade a partir dos valores analógicos obtidos do sensor (0-1024)
UMTpercentual = ((1024-analogRead(SensorUmidade))/1024.0)*100.0;
//nota-se que antes subtrai de 1024 o valor lido pelo sensor, pois seus valores são inversamente proporcionais quando passados para percentual.
~~~

<br>

Depois de ter os valores em percentual de umidade, é saparado em 3 níveis (0-100%) que nos dá uma ideia do que é um solo seco, molhado ou 'ideal'.
~~~ino
//CÓDIGO DE PROGRAMAÇÃO

//Variaveis para formação do percentual da umidade e seus respectivos níveis
double UMTpercentual;
#define nivelBaixo 30 //abaixo de 30% consideramos como seco
#define nivelAlto 85 //acima de 85% foi considerado molhado
#define ideal (nivelBaixo + nivelAlto)/2 //a partir da média entre seco e molhado acha-se o ideal
#define margemErro 10 //essa margem de erro é utilizada para depois de adquirir valores aumentar o espaço para o nível ideal


//SE a umidade foi menor que o nível baixo + margem de erro e maior que zero
if((UMTporcentual <= nivelBaixo + margemErro) && (UMTporcentual >= 0 ))
{
    sendmensage(); //Envia mensagem de acordo com a umidade
}
     //SE a umidade foi maior que o nível alto + margem de erro e menor que cem
else if(UMTporcentual >= nivelAlto - margemErro) && (UMTporcentual <= 100))
{
    sendmensage();// "

}    //SE a umidade tiver entre os níveis de alto baixo - nível ideal -
else if((UMTporcentual >= nivelBaixo && UMTporcentual <= ideal) || (UMTporcentual > ideal && UMTporcentual < nivelAlto))
{
    sendmensage();// "
}
else //SE NAO for nenhuma das anteriores, ocorreu algum erro
{
    senderrormensage() //Envia mensagem de erro caso a entrada de umiade for invalida
} 
~~~