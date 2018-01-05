/*
**----------- BikeStation--------------------- 
**Trabalho realizado por:
**  Marcelo Jacinto, no 87063
**  Joao Silva, no 87033
** Trabalho em que sao implementadas a parte grafica e textual do programa bikestation
** Permite a obtencao de algumas estatisticas quanto ao uso do servico de biciletas
** Algumas considerecoes no Ficheiro ReadMe
** Ano Letivo 2016/2017
** Disciplina de Programacao
*/ 
#include "main.h"
#include "Graficos.h"

//Codigo final para compilar
//gcc *.c -g -I/usr/local/include -Wall -pedantic -std=c99 -L/usr/local/lib -lm -lSDL2 -lSDL2_ttf -lSDL2_image -o bikestation

//Codigo para executar:
// ./bikestation -t  hubway_trips_v2.csv hubway_stations.csv
// ./bikestation -g  hubway_trips_v2.csv hubway_stations.csv

//Algumas informacoes disponiveis no ficheiro READ_ME

int main (int argc, char * argv[])
{
    //Ponteiros para a cabeça das listas
    node_t * head_node; //ponteiro para a cabeça da lista de viagens
    station_t * head_station; //poteiro para a cabeça da lista de estacoes
    station_t* tail_station = NULL;
    int lista_alterada = 0;   //variavel que vai servir ao longo do programa para indicar se a lista de viagens foi modificada ou nao

    int ui_mode = -1; //variavel que define o modo de interface que vai ser usado

    //Vamos validar os argumentos e indicar o modo escolhido (0 -graphical ; 1-text)
    ui_mode = argumentsValidator(argc, argv);

    //limpa o ecrã para o menu ficar com um aspeto mais limpo
    system("clear");

    //--------Loading Stations info ---------------
    head_station = file_load_station(argv);

    //-------Loading TRIPS info------------
    head_node = file_load_trips(argv, head_station);

    //obtém a cauda da lista de estações
    tail_station = getTail(head_station);

    //Vamos escolher o interface a usar
    switch(ui_mode)
    {
        case 0:
            //GET THE SDL INTERFACE
            main_graphics(&head_node, &head_station, &tail_station, argv);
            break;
        case 1:
            //GET THE TEXT MODE INTERFACE
            get_UI(&head_node, &head_station, &lista_alterada, argv);
            break;
    }


    //---------Vai dar unload da lista de viagens (libertar a memoria alocada)---------
    while (head_node != NULL)
    {
        remove_head_viagens( &head_node);
    }
    remove_head_viagens( &head_node);
    if (head_node == NULL)
    {
        printf("Unload viagens\n");
    }
    //--------Vai dar unload da lista de estacoes (libertar a memoria alocada)-----------
    while(head_station != NULL)
    {
        remove_head_station(&head_station);
    }
    remove_head_station(&head_station);
    if (head_station == NULL)
    {
        printf("Unload estacoes\n");
    }

    return EXIT_SUCCESS;
}
