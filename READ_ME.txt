-------------BikeStation-----------------
                IST
Trabalho realizado por: Marcelo Fialho Jacinto nº 87063
                        João Silva nº 87033

Ano Letivo: 2016/2017
Disciplina: Programação
PROJETO FINAL

Implementações:
NOTA: Todas as funcoes que manipulam listas no modo textual encontram-se no estruturas.c
->implementacao das listas:
    *Foram usadas listas duplamente ligadas para estacoes e viagens
    *Foram colocados na estrutura de viagens a velocidade, a distancia percorrida e as velocidades que são calculados na altura do carregamento

->Carregamento da lista:
        //ordem pela qual são chamadas as funcões dentro umas das outras para a criacao de listas
        File_load_station->extrairStation->tailStation->newStation

        file_load_trips->extrairViagens->tailNode->newNode

**O Carregamento da lista é feito pela cauda porque as lista já se encontram organizadas por ID **
** e o ID está por ordem pela qual as viagens aconteceram no tempo **

->Funcoes que manipulam listas
  Existem duas funcoes que se limitam a implementar o codigo fornecido na pagina da cadeira:
  ->dia_semana -> que descobre o dia da semana com base na data
  ->calc_distancia -> calcula a distancia entre estacoes com base na latitude e longitude


NOTA: Todas as funcoes que fazem menus ou submenos ou operacoes restritas a menus encontram-se em textmode.c 
->Implementacao de menus

    Para a implementacao de menus existe uma funcao principal (menu principal)
    que é chamada no main para implementar o menu (get_UI)

    Essa funcao é chamada recursivamente quando se sai de um submenu

->Implementacao da parte grafica:
    NOTA: Todas as funcoes que implementam a parte grafica encontram-se em Graficos.c
   No main é chamada uma funcão que implementa a parte gráfica por completo. 
   Na parte grafica foi usada a funcão RenderText fornecida no projeto 1024 para dar render de texto no ecrã, 
   pelo que nós, alunos que realizámos o trabalho, não temos qualquer crédito pela sua implementacão

   
