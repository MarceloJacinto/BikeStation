/*
** Ficheiro que contém as estruturas das TRIPS
** Contem e declaracao das funcoes relacionadas com a criacao de
** trips e da adição das mesmas a listas
*/
#include "main.h"

//-----estruturas.h---------

//Definicao da estrutura para datas
typedef struct data {
    int day;
    int month;
    int year;
    int hora;
    int minutos;
} data_t;

//definicao da estrutura para a bicicleta
typedef struct bike_id {
    char letter;
    int number;
}bike_id_t;

//Definicao da estrutura para o terminal
typedef struct terminal {
    char letter;
    int number;
}terminal_t;

//estrutura das estacoes
typedef struct station {
    int id_estacao; //id da estacao
    terminal_t short_name;  //nome curto da estacao
    char full_name[STRING_MAX]; //nome completo da estacação
    char municipio[STRING_MAX]; //nome do municipio
    float latitude; //latitude
    float longitude;  //longitude
    char estado[STRING_MAX]; //estado da estacao - existente ou removida
    struct station *next;
    struct station *last;
}station_t;

//lista que contem as trip
typedef struct trip {
    int id; //id da viagem
    int duracao;  //duracao da viagem em segundos
    data_t data_inicial; //data inicial da viagem
    station_t * estacao_inicial;  //estacao inicial da viagem
    data_t data_final;  //data de fim da viagem
    station_t * estacao_final;  //estacao final da viagem
    char usertype[STRING_MAX];  //tipo de utilizador (Casual ou Regular)
    bike_id_t bike_model; //BIKE ID - ex B456
    int birthday; //Ano de nascimento
    char gender[STRING_MAX];  //genero
    int distancia;      //distancia percorrida
    float velocidade;   //velocidade media desta trip - 0 quando nao temos informacoes suficientes
    int dia_da_semana; //0 corresponde a Domingo, 1 a Segunda e assim sucessivamente
} trip_t;

//Estrutura que contem tudo
typedef struct node {
    struct node * next;
    struct node * last;
    trip_t viagem;
} node_t;

typedef struct {
    station_t * estacao_inicial;
    station_t * estacao_final;
    int num_viagens;
}rota_t;

//----------FUNCTION DECLARATION-------------------

//função que associa dias da semana às datas
int dia_semana(int dia_inicial, int mes_inicial, int ano_inicial);

//calcula a distancia de uma dada viagem
int calc_distancia(float _latitude1, float _latitude2, float _longitude1, float _longitude2);

//calcula a velocidade de uma dada viagem
float calc_velocidade(int _distancia, int _time);

//Criar um novo elemento para a lista de Viagens
node_t * NewNode (int, int, int, int, int, int, char, int, int, int, int, int, int, int, station_t *, station_t *, char[STRING_MAX], int, char[STRING_MAX], int, float);

//Adicionar um elemento à lista de Viagens
node_t* tailNode (node_t * head,int id, int _dia_incial, int _mes_inicial, int _ano_inicial, int _hora_inicial, int _minutos_inicial, char _bike_model_letter, int _bike_model_number, int _dia_final, int _mes_final, int _ano_final, int _hora_final, int _minutos_final, int _duracao, station_t * estacao_inicial, station_t * estacao_final, char _usertype[STRING_MAX], int _birthday, char _gender[STRING_MAX], int, float);

//Extrai todas as viagens contidas no ficheiro de viagens para uma lista
node_t * extrairViagens (node_t * head, station_t * head_station, FILE * fp);

//Poe um ponteiro da lista a apontar para o primeiro elemento da lista
node_t * rewindtrips(node_t * head);

//Remove elementos da lista de viagens pela cabeça
void remove_head_viagens( node_t **head);

//Remove elementos com base no dia da semana
node_t * remove_dia_semana(int dia, node_t * head);

//Remove elementos da lista com base na duracao
node_t * remove_duracao(int , node_t * head);

//Remove elementos da lista com base no periodo de tempo
node_t * remove_hora_init(int hora, node_t * head);

//Removem elementos da lista com base no periodo de tempo
node_t * remove_hora_init2(int hora_fim, node_t * head);
node_t * remove_hora_fim(int hora, node_t * head);
node_t * remove_hora_fim2(int hora_init, node_t * head);

//obtém a cauda da lista de estações
station_t * getTail(station_t* head_stations);

//Criar um novo elemento para a lista de Estacoes
station_t * NewStation (int id_estacao, char short_name_letter, int short_name_number, char full_name[STRING_MAX], char municipio[STRING_MAX], float latitude, float longitude, char[STRING_MAX]);

//Adicionar um elemento à lista de Estacoes
station_t* tailStation (station_t *, int, char, int, char[STRING_MAX], char[STRING_MAX], float, float, char [STRING_MAX]);

//Extrai todas as Estaxoes contidas num ficheiro para uma lista
station_t * extrairStations(station_t *, FILE *);

//remove elementos da cabeça da lista de estacoes
void remove_head_station( station_t **head);


//---------------FUNCOES MAIS GERAIS----------------------------

//Cria uma lista de estacoes (abre o ficheiro e chama a extrairStations)
station_t * file_load_station(char * argv[]);

//Cria uma lista de trips(abre o ficheiro e chama a extrairViagens)
node_t * file_load_trips(char * argv[], station_t * head_station);


//_________________FUNCOES INVOCADAS NO MENU TEXTUAL______________________
//Imprime os dados de uma lista de viagens
void printf_trips (node_t *head, int* flag_finish);

//Imprime os dados de todas as estacoes
void show_station(node_t * head_trips, station_t * head_stations);

//Imprime as rotans
void printf_rotas(node_t *head_trips, station_t * head_stations, int *flag_finish);


//Grava um ficheiro com as estatísticas por genero
void genero_estatisticas(node_t * head_trips, station_t * head_station);

//Grava um ficheiro com as estatísticas por idade
void idade_estatisticas(node_t * head_trips, station_t * head_station);

//Grava um ficheiro com as estatisticas por duracao
void duracao_estatisticas(node_t * head_trips, station_t * head_station);

//Grava um ficheiro com estatisticas por velocidade
void velocidade_estatisticas(node_t * head_trips, station_t * head_station);
