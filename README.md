# Horta Automatizada 🌻
### Por: Instituto Federal de Minas Gerais - Campus Ibirité
### Integrantes:
* [Professor Elias José de Rezende Freitas](https://github.com/eliasjof)
* [Professor Carlos Dias da Silva Jr.](https://github.com/Carlos-Jr)
* [Professor Rubens Palhares]()
* [Milena Nicoly Alves Moreira]()
* [Pietro Schuster Moreira](https://github.com/Schusteerr)
##

<br>
Apresentação do projeto no Ministério da Educação (MEC) - 2ª Semana Nacional da Educação Profissional e Tecnologia
<div align="center">
    <img align="center" src="https://raw.githubusercontent.com/Schusteerr/Horta-Automatizada/main/assets/MEC.png"> 
</div>

<br>


## Introdução 📃

Este projeto visa a elaboração e a implementação de uma prática educacional no contexto da Robótica Educacional sustentável para alunos do ensino médio, servindo de ponto de partida para as escolas integrarem a robótica em seu currículo. A prática consiste em construir uma horta automatizada de baixo custo pelos alunos, desenvolvendo capacidade criativa e cooperativa de trabalho nas turmas. Espera-se que o projeto possa também estimular os professores a incorporarem o uso da robótica educacional em sala de aula em uma metodologia multidisciplinar baseada em projetos, visando o protagonismo do aluno.

Além disso, este projeto está articulado com o Programa Innovation Management Professional IMP, iniciado em 03/2022, que irá orientar todo o esforço de aprendizagem, estudo e implementação da inovação pretendida. Este projeto faz parte de uma ação na linha da robótica educacional, propiciando incentivar o estudo da robótica bem como das áreas correlacionadas para alunos do ensino fundamental e médio.

<br>

## Desenvolvimento do Projeto 🛠
 
O projeto será desenvolvido em oito meses, contando com dois alunos bolsistas, um do curso técnico (PIBEX-Jr) e outro da graduação (PIBEX) do campus Ibirité. A metodologia do projeto pode ser divida em quatro macro atividades:

(i) produção de um protótipo: serão desenvolvidos os circuitos eletrônicos e o design 3D de um protótipo inicial.

(ii) validação do protótipo: testes em campo (na horta já existem da escola parceira selecionada) e, a partir desses testes, realizar melhorias no protótipo.

(iii) divulgação à comunidade externa: elaboração de roteiros de práticas utilizando aprendizagem ativa e oficinas com os alunos da escola parceira.

(iv) documentação e avaliação das atividades: Ao longo do projeto, as atividades desenvolvidas pelos participantes serão avaliadas para uma possível publicação ao final do projeto. Além disso, será dedicado tempo para a documentação do projeto, de maneira a possibilitar replicá-lo em outras escolas.

<br>

## Circuito 🔌
Disponibilizei aqui uma playlist de vídeos onde é mostrado detalhadamente como que funciona e monta o circuito, alguns detalhes também podem ser encontrados em [Guia De Montagem](https://github.com/Schusteerr/Horta-Automatizada/tree/main/assets/Guia%20de%20Montagem). Válido ressaltar também há uma explicação do código programado em [examples](https://github.com/Schusteerr/Horta-Automatizada/tree/main/examples).

* [Video Introdutório, explicando o que é ESP8266 (microcontrolador utilizado)](https://drive.google.com/file/d/1X2_XmF8DrqiNE6gwS2Za4bqmlusH6OXn/view?usp=share_link)
* [Video Explicativo sobre o Sensor de umidade utilizado](https://drive.google.com/file/d/1jrZ0Ppgodmlv2w3pgmT6o9LDGQujc-oJ/view?usp=share_link)
* [Real Time Clock utilizado e o porquê de usar](https://drive.google.com/file/d/1PfVyzLgJLrnmP6LEz6YhN6oHJYhQg-XR/view?usp=share_link)
* [Como funciona o recebimento de dados e como configurar -  Planilha + Código de Programação](https://drive.google.com/file/d/12t7kd5o8ClAIliTEEnxjDfcF6QjCyJ7u/view?usp=share_link)

<br>

## Energia 🔋

Sobre o método de fornecimento de energia, foi elaborada uma proposta de Energia Renovável que consiste em um painel solar, pensado para um terreno que possui maior incidência solar para trabalho, e, também, um pequeno circuito envolvendo uma bateria de 3 pilhas de Lithium em série (4.2V cada), que passam por um regulador de Tensão para alimentar devidamente o circuito. Segue a explicação dos itens abaixo:

* **Painel Solar**

Foi escolhido um panel solar Policristalino, que é de baixo custo/eficiência em relação ao Monocristalino, porem sua escolha se da em conta ao ambiente de trabalho, pois ele operará em áreas que contam com maior Incidência Solar, não havendo problemas em relação a fornecer uma devida alimentação de energia elétrica.

* **Baterias**

O Painel opera juntamente à um pequeno circuito de pilhas de Lithium, dispostas em série, sua função é mantelas carregadas, pois as pilhas - que são três de 4.2V, fornecendo aproximadamente 12V - são responsáveis por manter o circuito eletrônico sempre em funcionamento.

* **Step Down**

Para manter o circuito em funcionamento, é necessária uma tensão correta a ser aplicada, para que isso ocorra usa-se um regulador de tensão Step Down, que como o nome deixa evidente, regula a tensão para uma margem menor, um degrau para baixo, entregando para o microcontrolador do circuito 5V, um ideal para operá-lo.

<br>

## Referências 

NOVAES, Matheus Sinto Horta vertical com sistema de monitoramento IoT. Universidade Estadual Paulista (Unesp), 2022. Disponível em: <http://hdl.handle.net/11449/216233>.

FERNANDES, Caio Nascimento. Integração de dispositivos de medição e de comunicação para o monitoramento da umidade do solo e automação da irrigação. 2022.

SANTOS, Bernardo Schmitz dos. Estudo de um protótipo para controle e monitoramento em uma estufa de hortaliças baseado em internet das coisas e o microcontrolador ESP8266. 2020.

MADAKAM, Somayya et al. Internet of Things (IoT): A literature review. Journal of Computer and Communications, v. 3, n. 05, p. 164, 2015.