## Teste do Sensor de Umidade 💧

<br>

 Essa é a parte mais matemática que pode-se deparar neste projeto, onde, a partir do sensor de umidade, que nos dá os dados de maneira analógica - medições de 0 à 1024 -, pegamos um percentual de umidade, onde, a partir do mesmo, estabelecemos parâmetros de umidade para nos notificar o estado atual da umidade do solo.

<br>

~~~ino
//IN MAIN CODE:

//Variaveis para formação do percentual da umidade e seus respectivos níveis
double UMTporcentual;
#define nivelBaixo 30 
#define nivelAlto 85 
#define ideal (nivelBaixo + nivelAlto)/2 
#define margemErro 10


//Calculando porcentual de umidade a partir dos valores analógicos obtidos do sensor (varia de 0-1024)
UMTporcentual = ((1024-analogRead(A0))/1024.0)*100.0;

//A partir dos valores de UMTpercentual estabelecemos os parametros para níves seco, molhado e um ideial
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
    senderrormensage()//Envia mensagem de erro caso a entrada de umiade for invalida
} 
~~~