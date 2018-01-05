#include "estruturas.h"

//——textmode.h---

//Declaração de Funcoes

//valida os argumentos passados aquando da execucao do programa
int argumentsValidator (int argc, char * argv[]);

//funcao que implementa o menu principal do modo textual
void get_UI(node_t ** head_node, station_t ** head_station, int * lista_alterada, char * argv[]);

//funcao que implenta o submenu de selecao de dados
void data_selection(node_t ** head_node, station_t * head_station, int * lista_alterada, char * argv[]);

//funcao que implementa a selecao de dados propriamente dita
void data_submenu1(node_t ** head_node, int* lista_vazia);

//funcao que implementa a selecao de estatiticas
void selecao_estatisticas(node_t ** head_node, station_t ** head_station);
