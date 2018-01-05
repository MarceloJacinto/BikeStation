#include "estruturas.h"

//———estruturas.c—————

/*
** dia_semana:
** Funcao que vai ser usada no calculo do dia da semana com base na data do calendario
** NOTA: ESTE ALGORITMO FOI IMPLEMENTADO COM BASE NO QUE SE ENCONTRA NA PAGINA DA CADEIRA
** OS ALUNOS APENAS SE LIMITARAM A IMPLEMENTA-LO
*/
int dia_semana(int dia_inicial, int mes_inicial, int ano_inicial)
{
    int f = 0, m = 0, d = 0, c = 0, k = 0, _d = 0, x = 0, i = 0;    //variaveis auxiliares nas contas
    int dia_semana = 0;     //variavel que vai guardar o dia da semana


        k = dia_inicial;

        if ( 3 <= mes_inicial && mes_inicial <= 12)
        {
              //associa os valores às variáveis m, d e c, que são o mês,
              //o ano e o século, respetivamente
              m = mes_inicial - 2;
              d = ano_inicial % 100;
              c = ano_inicial / 100;

        }
        else if (mes_inicial == 1 || mes_inicial == 2)
        {
              //associa os valores às variáveis m, d e c, que são o mês,
              //o ano e o século, respetivamente
              m = mes_inicial + 10;
              _d = ano_inicial - 1;
              d = _d % 100;
              c = _d / 100;

        }
        f = k + ((13*m-1)/5) + d + (d/4) + (c/4) -(2*c);
        //associa um número de 0 a 6 à variável dia_semana, no caso em que f é positivo
        if (f>0)
        {
              dia_semana = f%7;
        }
        //associa um número de 0 a 6 à variável dia_semana, no caso em que f é negativo
        else if (f<0)
        {
              for (i=0; i>MIN_INTEGER; i--)
              {
                    x = 7*i;
                    if(x <= f)
                    {
                          dia_semana = f - x;
                          break;
                    }
              }
        }
        return dia_semana;
}

/*
** NewNode:
** Funcao que cria um novo no com um elemento do tipo no que lá dentro contem ponteiros e a estrura de viagem
** Preenche com os parametros que passamos
** Calula na hora o dia da semana me que a viagem ocorreu
*/
node_t * NewNode (int id, int dia_incial, int mes_inicial, int ano_inicial, int hora_inicial, int minutos_inicial, char bike_model_letter, int bike_model_number, int dia_final, int mes_final, int ano_final, int hora_final, int minutos_final, int duracao, station_t * estacao_inicial, station_t * estacao_final, char usertype[STRING_MAX], int birthday, char gender[STRING_MAX], int distancia, float velocidade)
{
    node_t * newTrip = NULL;

    //malloc para alocar memoria para o proximo elemento da lista
    newTrip = (node_t *)malloc(sizeof(node_t));

    //Verificação se a memória foi corretamente alocada
    if (newTrip == NULL)
    {
        printf("Memory was NOT allocated!!! Program will exit\n");
        exit(EXIT_FAILURE);
    }

    //----Vamos preencher esta viagem com os seus respetivos elementos----

    //Preenchimento dos campos da data de inicio
    newTrip->viagem.id = id;
    newTrip->viagem.data_inicial.day = dia_incial;
    newTrip->viagem.data_inicial.month = mes_inicial;
    newTrip->viagem.data_inicial.year =  ano_inicial;
    newTrip->viagem.data_inicial.hora = hora_inicial;
    newTrip->viagem.data_inicial.minutos = minutos_inicial;

    //Preenchimento dos campos do modelo da bicicleta
    newTrip->viagem.bike_model.letter = bike_model_letter;
    newTrip->viagem.bike_model.number = bike_model_number;

    //Preenchimento dos campos da data de fim
    newTrip->viagem.data_final.day = dia_final;
    newTrip->viagem.data_final.month = mes_final;
    newTrip->viagem.data_final.year =  ano_final;
    newTrip->viagem.data_final.hora = hora_final;
    newTrip->viagem.data_final.minutos = minutos_final;

    //Preenchimento dos restantes campos
    newTrip->viagem.duracao = duracao;
    newTrip->viagem.estacao_inicial = estacao_inicial;
    newTrip->viagem.estacao_final = estacao_final;
    strcpy(newTrip->viagem.usertype, usertype);
    newTrip->viagem.birthday = birthday;
    strcpy(newTrip->viagem.gender, gender);
    newTrip->viagem.velocidade = velocidade;
    newTrip->viagem.distancia = distancia;
    newTrip->viagem.dia_da_semana = dia_semana(dia_incial, mes_inicial, ano_inicial);
    newTrip->next = NULL;
    newTrip->last = NULL;

    //retorna o ponteiro para o elemento da lista criado
    return newTrip;
}

/*
** tailNode:
** Funcao que adiciona elementos à cauda da lista
** Chama a funcao para criar no e passa como parametros aqueles que recebe
** Retorna o ponteiro para o fim da lista, visto que a lista é duplamente ligado, depois andamos para trás na lista
** É este retorno que nos permite efetuar o rápido carregamento da lista
*/
node_t* tailNode (node_t * head,int id, int _dia_incial, int _mes_inicial, int _ano_inicial, int _hora_inicial, int _minutos_inicial, char _bike_model_letter, int _bike_model_number, int _dia_final, int _mes_final, int _ano_final, int _hora_final, int _minutos_final, int _duracao, station_t * estacao_inicial, station_t * estacao_final, char _usertype[STRING_MAX], int _birthday, char _gender[STRING_MAX], int distancia, float velocidade)
{
    node_t * atual; //ponteiro para o novo elemento que se pretende inserir
    node_t * auxiliar ; //ponteiro auxiliar para verificação da posicao na lista

    //vamos obter um ponteiro que aponta para o elemento que queremos acrescentar
    atual = NewNode (id, _dia_incial, _mes_inicial, _ano_inicial, _hora_inicial, _minutos_inicial, _bike_model_letter, _bike_model_number, _dia_final, _mes_final, _ano_final, _hora_final, _minutos_final, _duracao, estacao_inicial, estacao_final, _usertype, _birthday, _gender, distancia, velocidade);

    //se a lista estiver vazia:
    if (head == NULL)
    {
        //vamos por a "cabeça da lista" a apontar para este elemento
        return atual;
    }

    //se a lista nao está vazia
    auxiliar = head;

    //Vamos percorrer todos os elementos da lista
    while (auxiliar->next != NULL)
    {
        //incrementa o ponteiro para o proximo elemento da lista
        auxiliar = auxiliar ->next;
    }
    auxiliar->next = atual;
    atual->last = auxiliar;

    //vai retornar o ponteiro para o ultimo elemento da lista - cabeca vai ficar a apontar para o ultimo elemento da lista
    return  atual;

}

/*
** Funcao que vai extrair do ficheiro todas as informacoes relativas a viagens e chamar a funcao tailNode para preencher a lista
*/
node_t * extrairViagens (node_t * head, station_t * head_station, FILE * fp)
{
    char str[STR_MAX]; //declaracao de string auxiliar
    char * token;
    station_t * estacoes_pointer = head_station;

    int id, duracao, dia_inicial, mes_inicial, ano_inicial, hora_inicial, minutos_inicial, estacao_inicial;
    int dia_final, mes_final, ano_final, hora_final, minutos_final, estacao_final;
    char usertype[STRING_MAX];
    char bike_id_letter;
    int bike_id_number;
    int birthday;
    char gender[STRING_MAX];
    station_t * init_station;
    station_t * fim_station;
    int verified = 0;
    int distancia = 0;
    float velocidade  = 0;
    //está a 0 enquanto não houver porblemas com os dados
    //no caso de surgirem problemas o novo nó não e criado
    int flag = 0;

    while (fgets(str, STR_MAX, fp) != NULL)
    {
        //recebe o id
        token=strtok(str, ",");
        id = atoi(token);

        //recebe a duracao
        token=strtok (NULL, ",");
        duracao = atoi(token);

        //recebe o dia
        token = strtok(NULL, "/");
        mes_inicial = atoi(token);

        //recebe o mes
        token = strtok(NULL, "/");
        dia_inicial = atoi(token);

        //recebe o ano
        token = strtok(NULL, " ");
        ano_inicial = atoi(token);

        //recebe a hora inicial
        token = strtok(NULL, ":");
        hora_inicial = atoi(token);

        //recebe o minuto inicial
        token = strtok(NULL, ":");
        minutos_inicial = atoi(token);

        //recebe a estacao inicial
        token = strtok(NULL, ",");
        token = strtok(NULL, ",");
        estacao_inicial = atoi(token);

        //recebe o dia final
        token = strtok(NULL, "/");
        mes_final = atoi(token);

        //recebe o mes final
        token = strtok(NULL, "/");
        dia_final = atoi(token);

        //recebe o ano final
        token = strtok(NULL, " ");
        ano_final = atoi(token);

        //recebe a hora final
        token = strtok(NULL, ":");
        hora_final = atoi(token);

        //recebe o minuto final
        token = strtok(NULL, ":");
        minutos_final = atoi(token);

        //recebe a estacao final
        token = strtok(NULL, ",");
        token = strtok(NULL, ",");
        estacao_final = atoi(token);

        //Recebe a bike model
        token = strtok(NULL, ",");
        sscanf(token, "%c %d", &bike_id_letter, &bike_id_number);

        //Recebe o userType
        token = strtok(NULL, ",");
        strcpy(usertype, token);

        //salvaguarda para os utilizadores que nao sao registados
        if (strcmp("Registered", usertype) == 0)
        {
            //recebe a birthday
            token = strtok(NULL, ",");
            birthday = atoi(token);

            //recebe o gender
            token = strtok (NULL, "\n");
            strcpy(gender, token);
        }
        else if (strcmp("Casual", usertype)==0)
        {
            birthday = 0000;
            strcpy(gender, "UNKNOWN");
        }
        else
        {
            flag=1;
        }

        //vai descobrir o ponteiro para a estacao inicial
        while(estacoes_pointer != NULL && verified == 0)
        {
            if (estacao_inicial == estacoes_pointer->id_estacao)
            {
                init_station = estacoes_pointer;
                verified = 1;
            }
            estacoes_pointer = estacoes_pointer->next;
        }
        verified = 0;
        estacoes_pointer = head_station;

        //vai descobrir o ponteiro para a estacao final
        while(estacoes_pointer != NULL && verified == 0)
        {
            if (estacao_final == estacoes_pointer->id_estacao)
            {
                fim_station = estacoes_pointer;
                verified = 1;
            }
            estacoes_pointer = estacoes_pointer->next;
        }

        //vai calcular as distancias percorridas se os ponteiros para estacao incial e final nao estiverem a nulo caso contrario mete zero neste campos
        if (init_station != NULL && fim_station != NULL)
        {
            //Calcula a distancia percorrida
            distancia =  calc_distancia(init_station->latitude, fim_station->latitude, init_station->longitude, fim_station->longitude);
            //calcula a velocidade
            velocidade =  calc_velocidade(distancia, duracao);
        } else {
            distancia = 0;
            velocidade = 0;
        }

        verified = 0;
        estacoes_pointer = head_station;

        //vai adicionar ao fim da lista um elemento com todas estas propriedades
        if (flag == 0)
        {
            head = tailNode (head, id, dia_inicial, mes_inicial, ano_inicial, hora_inicial, minutos_inicial, bike_id_letter, bike_id_number, dia_final, mes_final, ano_final, hora_final, minutos_final, duracao, init_station, fim_station, usertype, birthday, gender, distancia, velocidade);
        }

        flag = 0;
    }

    //vai por a cabeça a apontar de volta para a cabeça da lista
    head = rewindtrips(head);
    return head;
}

/* rewindtrips:
** Poe um ponteiro da lista a apontar para o primeiro elemento da lista
*/
node_t * rewindtrips(node_t * head)
{
    while(head->last != NULL)
    {
        head = head->last;
    }
    return head;
}

/*
**  Remove elementos de viagens da lista de viagens pela cabeça
*/
void remove_head_viagens( node_t **head)
{
    node_t *aux = NULL; //usamos um auxiliar

    //verificamos se a lista nao está vazia
    if ( *head == NULL)
    {
        return;
    }

    aux = *head; //Fazemos uma copia do head para depois dar free à memória
    *head = (*head)->next; //push a head a apontar para o proximo elemento
    free(aux); //Faz free da memoria
}

/*
** Remove_dia_semana recebe o dia (0 -domingo a 6 - sábado), mantem esse dia e elimina todos os outros nos da lista
** Recebe ainda um ponteiro para a cabeça da lista de viagens e retorna esse ponteiro atualizado
*/
node_t * remove_dia_semana(int dia, node_t * head)
{

    node_t * aux = NULL;
    //Remoção incial de elementos -  se o elemento a remover estiver na head, será removido
    //Esta parte apenas remove as cabeças falsas
    while (head != NULL && head->viagem.dia_da_semana != dia)
    {
        aux = head;         //guarda a cabeça que vai ser removida
        head = head->next;  //mete a cabeça a apontar para a posicao seguinte
        head->last = NULL;  //mete a noa cabeca com o last a apontar para null
        free(aux);          //de-aloca memoria da cabeca antiga
    }

    // Remove todos os outros elementos cujo dia da semana nao corresponde ao pretendido
    node_t * posicao = head;
    while(posicao != NULL)
    {
        while (posicao->next != NULL && posicao->next->viagem.dia_da_semana != dia)
        {
            aux = posicao->next;        //aux será o elemento a remover
            posicao->next = aux->next;  //define que o next da posicao anterior aquela a remover será igual ao next daquela a remover
            if(aux->next != NULL)
            {
                aux->next->last = posicao;  //define que o ponteiro para a posicao anterior no elemento a seguir ao que vamos remover é igual ao elemento anterior ao elemento a remover
            }
            free(aux);
        }
        posicao = posicao->next;
    }

    posicao = head;

    return head;
}

/*
**  remove_duracao recebe a duracao maxima de uma viagem, mantem todas as duracoes inferiores ou iguais e apagas os restantes nos da lista
*/
node_t * remove_duracao(int duracao, node_t * head)
{
    node_t * aux = NULL;
    //Remoção incial de elementos -  se o elemento a remover estiver na head, será removido
    //Esta parte apenas remove as cabeças falsas
    while (head != NULL && head->viagem.duracao >= duracao)
    {
        aux = head;         //guarda a cabeça que vai ser removida
        head = head->next;  //mete a cabeça a apontar para a posicao seguinte
        free(aux);          //de-aloca memoria da cabeca antiga
    }

    // Remove todos os outros elementos cujo dia da semana nao corresponde ao pretendido
    node_t * posicao = head;
    while(posicao != NULL)
    {
        while (posicao->next != NULL && posicao->next->viagem.duracao >= duracao)
        {
            aux = posicao->next;        //aux será o elemento a remover
            posicao->next = aux->next;  //define que o next da posicao anterior aquela a remover será igual ao next daquela a remover
            if(aux->next != NULL)
            {
                aux->next->last = posicao;  //define que o ponteiro para a posicao anterior no elemento a seguir ao que vamos remover é igual ao elemento anterior ao elemento a remover
            }
            free(aux);
        }
        posicao = posicao->next;
    }

    return head;
}

/*
** remove_hora_ini remove da lista de viagens todas aquelas que possuiem uma hora inicial inferior à hora inicial escolhida
*/
node_t * remove_hora_init(int hora, node_t * head)
{

    node_t * aux = NULL;
    //Remoção incial de elementos -  se o elemento a remover estiver na head, será removido
    //Esta parte apenas remove as cabeças falsas
    while (head != NULL && head->viagem.data_inicial.hora < hora)
    {
        aux = head;         //guarda a cabeça que vai ser removida
        head = head->next;  //mete a cabeça a apontar para a posicao seguinte
        head->last = NULL;  //mete a noa cabeca com o last a apontar para null
        free(aux);          //de-aloca memoria da cabeca antiga
    }

    // Remove todos os outros elementos cujo dia da semana nao corresponde ao pretendido
    node_t * posicao = head;
    while(posicao != NULL)
    {
        while (posicao->next != NULL && posicao->next->viagem.data_inicial.hora < hora)
        {
            aux = posicao->next;        //aux será o elemento a remover
            posicao->next = aux->next;  //define que o next da posicao anterior aquela a remover será igual ao next daquela a remover
            if(aux->next != NULL)
            {
                aux->next->last = posicao;  //define que o ponteiro para a posicao anterior no elemento a seguir ao que vamos remover é igual ao elemento anterior ao elemento a remover
            }
            free(aux);
        }
        posicao = posicao->next;
    }

    return head;
}

/*
** remove_hora_ini2 remove da lista de viagens todas aquelas que possuiem uma hora inicial superior à hora final escolhida
*/
node_t * remove_hora_init2(int hora_fim, node_t * head)
{
    node_t * aux = NULL;
    //Remoção incial de elementos -  se o elemento a remover estiver na head, será removido
    //Esta parte apenas remove as cabeças falsas
    while (head != NULL && head->viagem.data_inicial.hora > hora_fim)
    {
        aux = head;         //guarda a cabeça que vai ser removida
        head = head->next;  //mete a cabeça a apontar para a posicao seguinte
        //head->last = NULL;  //mete a noa cabeca com o last a apontar para null
        free(aux);          //de-aloca memoria da cabeca antiga
    }

    // Remove todos os outros elementos cujo dia da semana nao corresponde ao pretendido
    node_t * posicao = head;
    while(posicao != NULL)
    {
        while (posicao->next != NULL && posicao->next->viagem.data_inicial.hora > hora_fim)
        {
            aux = posicao->next;        //aux será o elemento a remover
            posicao->next = aux->next;  //define que o next da posicao anterior aquela a remover será igual ao next daquela a remover
            if(aux->next != NULL)
            {
                    aux->next->last = posicao;  //define que o ponteiro para a posicao anterior no elemento a seguir ao que vamos remover é igual ao elemento anterior ao elemento a remover
            }
            free(aux);
        }
        posicao = posicao->next;
    }

    return head;
}

/*
** remove_hora_fim remove da lista de viagens todas aquelas que possuiem uma hora final superior à hora final escolhida
*/
node_t * remove_hora_fim(int hora, node_t * head)
{
     node_t * aux = NULL;
    //Remoção incial de elementos -  se o elemento a remover estiver na head, será removido
    //Esta parte apenas remove as cabeças falsas
    while (head != NULL && head->viagem.data_final.hora > hora)
    {
        aux = head;         //guarda a cabeça que vai ser removida
        head = head->next;  //mete a cabeça a apontar para a posicao seguinte
        //head->last = NULL;  //mete a noa cabeca com o last a apontar para null
        free(aux);          //de-aloca memoria da cabeca antiga
    }

    // Remove todos os outros elementos cujo dia da semana nao corresponde ao pretendido
    node_t * posicao = head;
    while(posicao != NULL)
    {
        while (posicao->next != NULL && posicao->next->viagem.data_final.hora > hora)
        {
            aux = posicao->next;        //aux será o elemento a remover
            posicao->next = aux->next;  //define que o next da posicao anterior aquela a remover será igual ao next daquela a remover
            if(aux->next != NULL)
            {
                aux->next->last = posicao;  //define que o ponteiro para a posicao anterior no elemento a seguir ao que vamos remover é igual ao elemento anterior ao elemento a remover
            }
            free(aux);
        }
        posicao = posicao->next;
    }

    return head;
}

/*
** remove_hora_fim remove da lista de viagens todas aquelas que possuiem uma hora final inferior à hora inicial escolhida
*/
node_t * remove_hora_fim2(int hora_init, node_t * head)
{
     node_t * aux = NULL;
    //Remoção incial de elementos -  se o elemento a remover estiver na head, será removido
    //Esta parte apenas remove as cabeças falsas
    while (head != NULL && head->viagem.data_final.hora < hora_init)
    {
        aux = head;         //guarda a cabeça que vai ser removida
        head = head->next;  //mete a cabeça a apontar para a posicao seguinte
        //head->last = NULL;  //mete a noa cabeca com o last a apontar para null
        free(aux);          //de-aloca memoria da cabeca antiga
    }

    // Remove todos os outros elementos cujo dia da semana nao corresponde ao pretendido
    node_t * posicao = head;
    while(posicao != NULL)
    {
        while (posicao->next != NULL && posicao->next->viagem.data_final.hora < hora_init)
        {
            aux = posicao->next;        //aux será o elemento a remover
            posicao->next = aux->next;  //define que o next da posicao anterior aquela a remover será igual ao next daquela a remover
            if(aux->next != NULL)
            {
                aux->next->last = posicao;  //define que o ponteiro para a posicao anterior no elemento a seguir ao que vamos remover é igual ao elemento anterior ao elemento a remover
            }
            free(aux);
        }
        posicao = posicao->next;
    }

    return head;
}


/*
** NewStation:
** Cria um no para uma nova estacao
*/
station_t * NewStation (int id_estacao, char short_name_letter, int short_name_number, char full_name[STRING_MAX], char municipio[STRING_MAX], float latitude, float longitude, char estado[STRING_MAX])
{
    station_t * newStation = NULL;

    //malloc para alocar memoria para o proximo elemento da lista
    newStation = (station_t *)malloc(sizeof(station_t));

    //Verificação se a memória foi corretamente alocada
    if (newStation == NULL)
    {
        printf("Memory was NOT allocated!!! Program will exit\n");
        exit(EXIT_FAILURE);
    }

    //----Vamos preencher esta Station com os seus respetivos elementos----

    //Preenchimento dos campos
    newStation->id_estacao = id_estacao;
    newStation->short_name.letter = short_name_letter;
    newStation->short_name.number = short_name_number;
    strcpy(newStation->full_name, full_name);
    strcpy(newStation->municipio, municipio);
    newStation->latitude = latitude;
    newStation->longitude = longitude;
    strcpy(newStation->estado, estado);
    newStation->next = NULL;
    newStation->last = NULL;

    //retorna o ponteiro para o elemento da lista criado
    return newStation;
}

/*
** getTail:
** Permite obter a cauda da lista de estacoes
*/
station_t* getTail(station_t *head_stations)
{
    station_t *aux = head_stations;     //auxiliares para percorrer a lista para apontar para a cauda
    station_t *tail = NULL;

    while (aux != NULL)
    {
        tail = aux;
        aux = aux->next;
    }

    return tail;
}

/*
**tailStation:
** Funcao que permite adioncar estacoes à cauda da lista de estacoes: chama a funcao NewStation para criar um no e passa como pararmetros aqueles que recebe
*/
station_t* tailStation (station_t * head, int id_estacao, char short_name_letter, int short_name_number, char full_name[STRING_MAX], char municipio[STRING_MAX], float latitude, float longitude, char estado[STRING_MAX])
{
    station_t * atual; //ponteiro para o novo elemento que se pretende inserir
    station_t * auxiliar ; //ponteiro auxiliar para verificação da posicao na lista

    //vamos obter um ponteiro que aponta para o elemento que queremos acrescentar
    atual = NewStation (id_estacao, short_name_letter, short_name_number, full_name, municipio, latitude, longitude, estado);
    //se a lista estiver vazia:
    if (head == NULL)
    {
        //vamos por a "cabeça da lista" a apontar para este elemento
        return atual;
    }

    //se a lista nao está vazia
    auxiliar = head;

    //Vamos percorrer todos os elementos da lista
    while (auxiliar->next != NULL)
    {
        //incrementa o ponteiro para o proximo elemento da lista
        auxiliar = auxiliar ->next;
    }
    auxiliar->next = atual;
    atual->last = auxiliar;

    //vai retornar o ponteiro para a cabeça da lista
    return  head;

}

/*
** extrairStation: 
** Vai extrair do ficheiro de estacoes todas as informacoes relativas às estacoes
** e chamar a funcao tailStation para adicionar elementos À cauda da lista de estacoes
*/
station_t * extrairStations(station_t * head, FILE * fp)
{
    char str[STR_MAX]; //declaracao de string auxiliar
    char * token;
    int i = 0;

    int id_estacao = 0;
    char short_name_letter;
    int short_name_number;
    char full_name[STRING_MAX];
    char municipio[STRING_MAX];
    float latitude = 0.0;
    float longitude = 0.0;
    char estado[STRING_MAX];

    while (fgets(str, STR_MAX, fp) != NULL)
    {
        
	if (i != 0 )
	{
	//recebe o id da estacao
        token = strtok(str, ",");
        id_estacao = atoi(token);

        //Recebe o nome curto do terminal
        token = strtok(NULL, ",");
        sscanf(token, "%c %d", &short_name_letter, &short_name_number);

        //Recebe o nome completo da estacao
        token = strtok(NULL, ",");
        strcpy(full_name, token);

        //recebe o nome completo do municipio
        token = strtok(NULL, ",");
        strcpy(municipio, token);

        //Recebe a latitude
        token = strtok(NULL, ",");
        sscanf(token, "%f", &latitude);

        //Recebe a longitude
        token = strtok(NULL, ",");
        sscanf(token, "%f", &longitude);

        token = strtok (NULL, "/0");
        strcpy(estado, token);

        //vai adicionar ao fim da lista um elemento com todas estas propriedades
        head =  tailStation (head, id_estacao, short_name_letter, short_name_number, full_name, municipio, latitude, longitude, estado);
        }
	i++;
    }
    return head;
}

//remove elementos da cabeça da lista de estacoes
void remove_head_station( station_t **head)
{
    station_t *aux = NULL; //usamos um auxiliar

    //verificamos se a lista nao está vazia
    if ( *head == NULL)
    {
        return;
    }

    aux = *head; //Fazemos uma copia do head para depois dar free à memória
    *head = (*head)->next; //push a head a apontar para o proximo elemento
    free(aux); //Faz free da memoria
}


/*
** FUNCAO QUE CRIA UMA LISTA DE ESTACOES - abre o ficheiro e chama a funcao que cria a lista de estacao, passando o ponteiro para o ficheiro
*/
station_t * file_load_station(char * argv[])
{
    //vai abrir o ficheiro de estacoes e retornar um ponteiro para a cabeça da lista de estacoes
    station_t * head_station = NULL;
    FILE * fp = NULL;

    fp = fopen(argv[3], "r");
    if (fp == NULL)
    {
        printf("File was NOT open correctly. Program will exit!!! \n");
        exit(EXIT_FAILURE);
    }

    //Loading the station list
    printf("->Loading Stations \n");
    head_station = extrairStations(head_station, fp);
    printf("->Stations Loaded 🍺 \n");
    fclose(fp);

    return head_station;
}

/*
**  FUNCAO QUE CRIA UMA LISTA DE VIAGENS - abre o ficheiro e chama a funcao que cria a lista de viagens, passando o ponteiro para o ficheiro
*/

node_t * file_load_trips(char * argv[], station_t * head_station)
{
    //vai abrir o ficheiro de estacoes e retornar um ponteiro para a cabeça da lista de viagens
    node_t * head_node = NULL;
    FILE * fp = NULL;


    fp = fopen(argv[2],"r");
    if (fp == NULL)
    {
        printf("File was NOT open correctly. Program will exit!!! \n");
        exit(EXIT_FAILURE);
    }

    //Loading the trips to a list
    printf("->Loading Trips \n");
    head_node = extrairViagens(head_node, head_station, fp);
    printf("->Trips Loaded 🍺 \n");

    return head_node;
}


//---------------FUNCOES QUE USAM AS LISTAS PARA FAZER ESTATISTICAS-------------------------------------------------------
/*
** Funcao que imprime todas as viagens que cumprem os criterios definidos na selecao de dados
**  Perguntam primeiro ao utilizador quantas viagens mostrar
*/
void printf_trips (node_t *head, int* flag_finish)
{

    int numero_viagens = 0; //vai guardar o numero de viagens a vizualizar no ecrã
    char str[STR_MAX]; //auxiliar na receção do numero de viagens a vizualicar no ecra
    int aux2 = 0;           //variaveis auxiliares para percorrer as listas
    node_t *aux = head;
    int i = 0;
    int j = 0;          //necessário para impelementar o sistema de páginas - conta os elementos na pagina
    char char_aux = 'a';
    //asks user for some info and validates it
    do {
        //clears the screen
        system("clear");
        printf("->Listagem de Viagens\n");
        printf("Quantas viagens deseja visualizar?\n");
        fgets(str, STR_MAX, stdin);
        aux2 = sscanf(str, "%d", &numero_viagens);
    } while (aux2 != 1 || numero_viagens < 1);

    //vai imprimir as informacoes relativas a todas as viagens
    while (aux != NULL)
    {
        if (j < numero_viagens && aux != NULL)  //vai definir se já imprimiu todos os elementos por pagina
        {
            //vai imprimir todas as informacoes para uma dada viagem
            printf("Viagem %d: \n", (i+1));
            printf("->ID: %d \n", aux->viagem.id);
            printf("->Duracao (s): %d \n", aux->viagem.duracao);
            printf("->Data de inicio: %d/%d/%d %d:%d \n", aux->viagem.data_inicial.day, aux->viagem.data_inicial.month, aux->viagem.data_inicial.year, aux->viagem.data_inicial.hora, aux->viagem.data_inicial.minutos);
            printf("->Estacao inicial: %s \n", aux->viagem.estacao_inicial-> full_name);
            printf("->Data de fim: %d/%d/%d %d:%d \n", aux->viagem.data_final.day, aux->viagem.data_final.month, aux->viagem.data_final.year, aux->viagem.data_final.hora, aux->viagem.data_final.minutos);
            printf("->Estacao final: %s \n", aux->viagem.estacao_final-> full_name);
            printf("->Tipo de utilizador: %s\n",aux->viagem.usertype);
            printf("->Ano de nascimento: %d \n", aux->viagem.birthday);
            printf("->Género: %s \n", aux->viagem.gender);
            printf("->ID da Bicicleta: %c%.5d\n", aux->viagem.bike_model.letter, aux->viagem.bike_model.number);

            printf("\n");
            j++;
            i++;
        //se todos os elementos da pagina já foram impressos, espera escoha de utilizador, para continuar ou sair
        } else {
            printf("Prima 'n' para avançar para a proxima pagina ou 'q' par sair\n");
            aux2 = 0;
            do {
                fgets(str, STR_MAX, stdin);
                aux2 = sscanf(str, "%c", &char_aux);
            } while ((aux2 != 1 || char_aux != 'n') && (char_aux != 'q' || aux2 != 1));

            if(char_aux == 'q')
            {
                //sai da funcao
                *flag_finish=1;
                return;
            }
            j = 0;      //da reset ao j
        }
         aux = aux->next;
    }
}

/*
** Funcao que imprime todas as estacoes e estatisticas quanto ao numero de bicicletas que nelas entram e saiem
** Perguntam ao utilizador quantas estacoes deseja mostrar
*/
void show_station(node_t * head_trips, station_t * head_stations)
{
    //nota: todas as variaveis sem comentarios, sao auxiliares na obtencao de informacoes
    station_t * aux_stations = head_stations;
    node_t * aux_trips = head_trips;
    int viagens[24] = {0};   //vetor em que cada posicao vai corresponder à hora do dia e o conteudo ao numero de viagens nessa hora a entrar
    int viagens_sair[24] = {0};     //a sair
    int i = 0;
    int j = 0; //usada para dar reset ao vetor que tem o numero de viagens
    int max = 0;
    int min = 5000000;      //inciacao do numero minimo com um valor alto para na proxima comparacao obter um valor minimo com sentido que nao zero
    long int soma_entrar = 0;
    int max_sair = 0;
    int min_sair = 5000000;
    long int soma_sair = 0;

    //declaracao de variaveis para receber o numero de estacoes por pagina
    char str[STR_MAX]; //auxiliar na receção do numero de viagens a vizualicar no ecra
    int aux2 = 0;        //necessário para impelementar o sistema de páginas
    char char_aux = 'a';
    int numero_estacoes = 0;
    int m = 0;

    //Pergunta ao utilizador quantas estacoes mostrar
    do {
        //clears the screen
        system("clear");
        printf("->Listagem de Estacoes\n");
        printf("Quantas estacoes deseja visualizar: ");
        fgets(str, STR_MAX, stdin);
        aux2 = sscanf(str, "%d", &numero_estacoes);
    } while (aux2 != 1 || numero_estacoes < 1);

    //vai percorrer a lista de estacoes
    while (aux_stations != NULL)
    {
        if (m < numero_estacoes && aux_stations != NULL)    //vai imprimir o numero certo de estacoes por pagina
        {
            //vai imprimir no ecra o nome da estacao, id e coordenadas
            printf("\nID da estacao: %d\n", aux_stations->id_estacao);
            printf("-> %s\n", aux_stations->full_name);
            printf("Latitude: %f\n", aux_stations->latitude);
            printf("Longitude: %f\n", aux_stations->longitude);
            //vamos percorrer todas as horas para uma dada estacao - das 8 - 22
            for (i = 8; i < 22; i++)
            {
                //vai percorrer todas as viagens
                while(aux_trips != NULL)
                {
                    //se a viagem tiver a hora que queremos
                    if (i == aux_trips->viagem.data_inicial.hora &&  aux_stations == aux_trips->viagem.estacao_inicial)
                    {
                        viagens[i]++;   //incrementamos o numero de viagens correspondentes a essa hora
                    }

                    //se a viagem tiver a hora que queremos
                    if (i == aux_trips->viagem.data_inicial.hora &&  aux_stations == aux_trips->viagem.estacao_final)
                    {
                        viagens_sair[i]++;  //incrementamos o numero de viagens correspondentes a essa hora
                    }
                    aux_trips = aux_trips->next;
                }

                //vamos calcular os minimos e maximos para viagens a entrar e a sair
                if(viagens[i] < min)
                {
                    min = viagens[i];
                }
                if (viagens[i] > max)
                {
                    max = viagens[i];
                }
                if (viagens_sair[i] < min_sair)
                {
                    min_sair = viagens_sair[i];
                }
                if (viagens_sair[i] > max_sair)
                {
                    max_sair = viagens_sair[i];
                }
                aux_trips = head_trips;
            }
            //vamos calcular a media e obter imprimir os maximos e minimos a entrar e a sair no ecrã
            for (i = 8; i < 22; i++)    //vamos fazer a soma de todas as viagens para todas as horas para uma dada estacao
            {
                soma_entrar = soma_entrar + viagens[i]; //obtem a soma total de viagens para uma dada estacao de todas as horas
                soma_sair = soma_sair + viagens_sair[i];
            }
            printf("Numero minimo de bicicletas a entrar: %d\n", min);
            printf("Numero maximo de bicilletas a entrar: %d\n", max);
            printf("Media de bicicletas a entrar: %0.1f\n", (float)soma_entrar / 14);       //divide por 14 horas

            printf("Numero minimo de bicicletas a sair: %d\n", min_sair);
            printf("Numero maximo de bicilletas a sair: %d\n", max_sair);
            printf("Media de bicicletas a sair: %0.2f\n", (float)soma_sair / 14);

            //vai dar reset à lista para poder ser usada para a proxima station
            for (j = 0; j < 24; j++)
            {
                viagens[j] = 0;
                viagens_sair[j] = 0;
            }
            //dá reset à média min e maximo para poder ser usado nas proximas estacoes
            min = 5000000;
            max = 0;
            soma_entrar = 0;
            min_sair = 5000000;
            max_sair = 0;
            soma_sair = 0;

            aux_stations = aux_stations->next;
            m++; //incrementa o numero do elemento na pagina
        }
        else //quando já se imprimiram todos os elementos por pagina, espera por instrucao do utilizador
        {
            printf("Prima 'n' para avançar para a proxima pagina ou 'q' par sair\n");
            aux2 = 0;
            do {
                fgets(str, STR_MAX, stdin);
                aux2 = sscanf(str, "%c", &char_aux);
            } while ((aux2 != 1 || char_aux != 'n') && (char_aux != 'q' || aux2 != 1));

            if(char_aux == 'q')
            {
                //sai da funcao
                return;
            }
            m = 0;      //da reset ao j
        }
    }
}

/*
**  Funcao responsavel por imprimir todas as rotas para uma dada estacao, selecionada a partir do seu respetivo ID
*/
void printf_rotas(node_t *head_trips, station_t * head_stations, int* flag_finish)
{
    //ID da viagem a analisar
    int id = -1;
    //variaveis auxiliares na obtenção do ID
    char str[STR_MAX]; //auxiliar na receção do numero de viagens a vizualicar no ecra
    int aux2 = 0;
    //Conversao da informacao para ponteiros
    station_t * stationAux = head_stations;
    station_t * estacao = NULL;             //onde vai ser guardada o ponteiro para a estacao a examinar

    //Variaveis auxiliares na procura de ROTAS
    node_t * aux_trips = head_trips;
    rota_t * rotas = NULL;
    rota_t ordenado;
    //rota_t * ordenar = NULL;
    int i = 0; //posicao no array    - numero de rotas totais
    int j = 0;
    int k = 0;
    int rotaguardada = 0;
    int numero_a_mostrar = -1;

    //Variaveis para impressao por paginas
    int m = 0;
    char char_aux = 'a';

    //Vamos criar um array com estruturas do tipo rota- estas estrutras contêm um ponteiro para a estacao inicial,
    //um ponteiro para a estacao final e ainda o numero de viagens efetuados nessa rota

    //asks user for some info and validates it
    do {
        //clears the screen
        system("clear");
        printf("->Listagem de Rotas\n");
        printf("Insira o ID da estacao: ");
        fgets(str, STR_MAX, stdin);
        aux2 = sscanf(str, "%d", &id);
    } while (aux2 != 1 || id < 1);

    //vamos decobrir o ponteiro para a estacao desejada e verificar se ela existe
    while(stationAux != NULL)
    {
        if (id == stationAux->id_estacao)
        {
            estacao = stationAux;
        }
        stationAux = stationAux->next;    //incrementa o ponteiro das viagens
    }
    if (estacao == NULL)
    {
        printf("A estacão não se encontra no sistema!\n");
        return;
    }
    //Vai perguntar quantas rotas imprimir por página
    do {
        printf("Insira o numero de rotas que deseja ver: ");
        fgets(str, STR_MAX, stdin);
        aux2 = sscanf(str, "%d", &numero_a_mostrar);
    } while (aux2 != 1 || numero_a_mostrar < 1);

   //vamos descobrir todas as rotas que tiveram como origem a estacao escolhida
   printf("->A descobrir as rotas...\n");
   stationAux = head_stations;      //mete o ponteiro de novo a apontar para a cabeça das viagens
   while(stationAux != NULL)
   {
        //para cada estacao vai percorrer todas as viagens que comecaram na estacao escolhida pelo user e terminaram na estacao a correr pelo loop
        //e todas as estacoes que comecar na estacao definida pelo loop e acabaram na estacao definida pelo user
        //vai adicionar essas viagens a um array para posteriormente poderem ser contadas
        while (aux_trips != NULL)
        {
            //se a estacao selecionada é a estacao inicial da viagem :
            if (aux_trips->viagem.estacao_final == stationAux && aux_trips->viagem.estacao_inicial == estacao && rotaguardada != 1)
            {
                //vai verificar se a rota já encontra guardada
                for (j = 0; j < i; j++)
                {
                    if(rotas[j].estacao_inicial == estacao && rotas[j].estacao_final == stationAux)
                    {
                        rotas[j].num_viagens = rotas[j].num_viagens + 1;    //incrementa o numero de viagens para essa rota
                        rotaguardada = 1;
                    }
                }
                //se a rota ainda nao estivesse presente no array, alocamos memoria para ela e preenchemos todos os dados
                if(rotaguardada == 0)
                {
                    //vai alocar memoria e adicionar a rota ao array
                    i++;
                    rotas = (rota_t *)realloc(rotas, sizeof(rota_t) * i);
                    if (rotas == NULL)
                    {
                        printf("nao foi possivel alocar memoria para rotas\n");
                        exit(EXIT_FAILURE);
                    }
                    rotas[i-1].estacao_inicial = estacao;
                    rotas[i-1].estacao_final = stationAux;
                    rotas[i-1].num_viagens = 1;
                }
            }
            //se a estacao selecionada é a estacao final da viagem :
            if (aux_trips->viagem.estacao_inicial == stationAux && aux_trips->viagem.estacao_final == estacao && rotaguardada != 1)
            {
                //vai verificar se a rota já encontra guardada
                for (j = 0; j < i; j++)
                {
                    if(rotas[j].estacao_inicial == stationAux && rotas[j].estacao_final == estacao)
                    {
                        rotas[j].num_viagens = rotas[j].num_viagens + 1; //incrementa o nuero de viagens para essa rota
                        rotaguardada = 1;
                    }
                }
                //se a rota ainda nao estivesse presente no array, alocamos memoria para ela e preenchemos todos os dados
                if (rotaguardada == 0)
                {
                    i++;  //vai alocar memoria e adicionar a rota ao array
                    rotas = (rota_t *)realloc(rotas, sizeof(rota_t) * i);
                    if (rotas == NULL)
                    {
                        printf("nao foi possivel alocar memoria para rotas\n");
                        exit(EXIT_FAILURE);
                    }
                    rotas[i-1].estacao_inicial = stationAux;
                    rotas[i-1].estacao_final = estacao;
                    rotas[i-1].num_viagens = 1;
                }
            }
            rotaguardada = 0;
            aux_trips = aux_trips->next;
        }
        aux_trips = head_trips;
        stationAux = stationAux->next;
   }

   //Vai ordernar as rotas da mais populares para as menos populares, percorrendo o array de rotas
   for ( k = 0; k < i; ++k)
	{
	       for(j = k+1; j < i; ++j)
	       {
		        if(rotas[k].num_viagens < rotas[j].num_viagens)
		        {
			        ordenado.estacao_inicial = rotas[k].estacao_inicial;
			        ordenado.estacao_final = rotas[k].estacao_final;
			        ordenado.num_viagens = rotas[k].num_viagens;

			        rotas[k].estacao_inicial = rotas[j].estacao_inicial;
			        rotas[k].estacao_final = rotas[j].estacao_final;
			        rotas[k].num_viagens = rotas[j].num_viagens;

			        rotas[j].estacao_inicial = ordenado.estacao_inicial;
			        rotas[j].estacao_final = ordenado.estacao_final;
			        rotas[j].num_viagens = ordenado.num_viagens;
		        }
	       }
	 }

   j = 0;   //resets j to be reused in the next loop
   //Vai imprimir todas as rotas
   //Vai imprimir todas as rotas com a estação selecionada como estação de partida
   printf("Rotas com estação %d como estação inicial\n", id);
   printf("\n");
   while (j < i)
   {
       if (m < numero_a_mostrar && j < i) //reponsavel pela impressao por pagina
       {
             if(rotas[j].estacao_inicial->id_estacao==id)
             {
          	       printf("Estação Inicial - ID: %d \n", rotas[j].estacao_inicial->id_estacao);
          	       printf("Estcao Inicial - Nome: %s \n", rotas[j].estacao_inicial->full_name);
          	       printf("Estação Final - ID: %d \n", rotas[j].estacao_final->id_estacao);
          	       printf("Estacao Final - Nome: %s\n", rotas[j].estacao_final->full_name);
          	       printf("Numero de viagens: %d\n", rotas[j].num_viagens);
          	       printf("\n");
          	       m++;
             }
            j++;
       } else { //se ja imprimiu todos os elementos na pagina, espera por input do utilizador
           aux2 = 0;
           do {
                printf("Prima 'n' para avançar para a proxima pagina ou 'q' para sair\n");
                fgets(str, STR_MAX, stdin);
                aux2 = sscanf(str, "%c", &char_aux);
          } while ((aux2 != 1 || char_aux != 'n') && (char_aux != 'q' || aux2 != 1));

           if(char_aux == 'q')
           {
               //sai da funcao
               *flag_finish=1;
               return;
           }
           m = 0;
       }
   }

   //reset de m e j para utilizar no proximo ciclo
   j=0;
   m=0;
    //Vai imprimir todas as rotas com a estação selecionada como estação de destino
   printf("Rotas com estação %d como estação de destino\n", id);
   printf("\n");
   while (j < i)
   {
       if (m < numero_a_mostrar && j < i)//reponsavel pela impressao por pagina
       {
             if(rotas[j].estacao_final->id_estacao==id)
             {
                   printf("Estação Inicial - ID: %d \n", rotas[j].estacao_inicial->id_estacao);
          	       printf("Estcao Inicial - Nome: %s \n", rotas[j].estacao_inicial->full_name);
          	       printf("Estação Final - ID: %d \n", rotas[j].estacao_final->id_estacao);
          	       printf("Estacao Final - Nome: %s\n", rotas[j].estacao_final->full_name);
          	       printf("Numero de viagens: %d\n", rotas[j].num_viagens);
          	       printf("\n");
          	       m++;
             }
            j++;
       } else {//se ja imprimiu todos os elementos na pagina, espera por input do utilizador
           aux2 = 0;
           do {
                printf("Prima 'n' para avançar para a proxima pagina ou 'q' para sair\n");
                fgets(str, STR_MAX, stdin);
                aux2 = sscanf(str, "%c", &char_aux);
          } while ((aux2 != 1 || char_aux != 'n') && (char_aux != 'q' || aux2 != 1));

           if(char_aux == 'q')
           {
               //sai da funcao
               *flag_finish=1;
               return;
           }
           m = 0;
       }
   }
   //liberta a memoria alocada para o vetor de rotas
   free(rotas);
}

/*
** Funcao que imprime num ficheiro as estatisticas por genero
*/
void genero_estatisticas(node_t * head_trips, station_t * head_station)
{
    node_t * aux_trips = head_trips;    //declaracao de ponteiro auxiliar para a lista de viagens
    int girls = 0;                      //conta o numero total de raparigas na lista
    int boys = 0;                       //conta o numero total de rapazes na lista
    int registados = 0;                 //conta o numero total de utilizadores registados na lista
    float media_girls = 0, media_boys = 0;  //vai guardar a média

    FILE * fp = NULL;

    //vai percorrer a lista de viagens inteira
    while (aux_trips != NULL)
    {
        //Nota : foi usado -13 no strcmp do gender porque como ele se encontra no final da string, ao ler do ficheiro ele adiciona caracter nao visivel
        if(strcmp("Registered", aux_trips->viagem.usertype) == 0)
        {
            registados++;       //incrementa o numero de registados
            if (strcmp("Male", aux_trips->viagem.gender) == -13)
            {
                boys++;         //incrementa o numero de rapazes
            }
            if (strcmp("Female", aux_trips->viagem.gender) == -13)
            {
                girls++;        //incrementa o numero de raparigas
            }
        }
        aux_trips = aux_trips->next;
    }

    //Vamos fazer as médias
    media_girls = ((float)girls / registados) * 100;
    media_boys = ((float)boys /registados) * 100;

    //vai criar o ficheiro com as informações
    fp = fopen("Estatísticas_género.txt", "w");

    //caso o ficheiro nao seja aberto corretament, o utilizador poderá verificar as estatísticas no ecrã
    if (fp == NULL)
    {
        printf("Erro: Ficheiro com estatísticas não gerado\n");
        printf("Ainda assim poderá verificar as estatísticas neste ecrã: \n");
        printf("Percentagem média de viagens efetuadas por rapazes registados: %0.2f%% \n", media_boys);
        printf("Percebentagem média de viagens efetuadas por raparigas registadas: %0.2f%% \n", media_girls);
        return;
    }

    //vai guardar as informacoes num ficheiro de estaticas
    fprintf(fp, "->Estatísticas por Género\n \n");
    fprintf(fp, "Percentagem média de viagens efetuadas por rapazes registados: %0.2f%% \n", media_boys);
    fprintf(fp, "Percebentagem média de viagens efetuadas por raparigas registadas: %0.2f%% \n", media_girls);
    fclose(fp);
}

/*
** Funcao que imprime num ficheiro as estatisticas por idade
*/
void idade_estatisticas(node_t * head_trips, station_t * head_station)
{
    //Variaveis necessárias para obter tudo o resto
    int idade = 0;     //idade minima à qual vai sendo somado 2 num loop até 100 anos para obter vários espetros de idades
    int todasidades[101] = {0};
    node_t * aux_trips = head_trips;    //ponteiro auxiliar para ajudar a percorrer todas as viagens
    int numeroRegistados = 0;
    int auxiliar = 0;
    float media = 0;
    //Variaveis para criar o ficheiro
    FILE * fp = NULL;

    //imprime esta nota, porque o utilizador podia usar idades falsas - por este motivo so consideramos idades ate aos 100 anos
    printf("NOTA: ESTE MODO APENAS TEM EM CONTA A IDADE DOS UTILIZADORES REGISTADOS\n");
    printf("          ESTE MODO ESTÀ AINDA SUJEITO A PROBLEMAS DE FIDELIDADE       \n");

    while(aux_trips != NULL)
    {
        //vai percorrer todas as idades
        for(idade  = 0; idade < 101; idade++)
        {   //vai guardar incrementar no respetivo lugar no array o numero de pessoas que viajaram com a respetiva idade
            if((aux_trips->viagem.data_final.year - aux_trips->viagem.birthday) == idade)
            {
                todasidades[idade]++;
            }
        }
        aux_trips = aux_trips->next;
    }

    //Como ficou predefinido que nas estruturas os utilizadores nao registados tinham data de nascimento 0, entao vamos fazer a media sem esses utilizadores
    for (idade = 1; idade <=101; idade++)
    {
        numeroRegistados = numeroRegistados + todasidades[idade];           //vai contar o numero total de utiliazadores registados
    }

    fp = fopen("Estatísticas_idade.txt", "w");
    if (fp == NULL)
    {
        printf("Não foi possivel geral o ficheiro de estatisticas por idade   :( \n");
        return;
    }

    fprintf(fp, "->Estatísticas por Idade\n \n");

    //vai agrupar o numero de pessoas 2 a dois e imprimir as estatisticas
    for(idade = 15; idade < 101; idade = idade + 2)
    {
        auxiliar = todasidades[idade] + todasidades[idade + 1];     //vai somar os dois anos
        media  = (((float)auxiliar / numeroRegistados)) * 100;
        fprintf(fp, "%d - %d: %0.2f%% \n", idade, idade + 1, media);
    }

    fclose(fp);
}

/*
** Ficheiro que imprime num ficheiro estatisticas da duração das viagens
*/
void duracao_estatisticas(node_t * head_trips, station_t * head_station)
{
    //variaveis usadas na contagem do numero de viagens para cada intervalo de tempo
    node_t * aux_trips = head_trips;         //ponteiro auxiliar para apontar para a lista de viagens
    int duracao [24] = {0};               //array que vai guardar para intervalos de tempo de 900 em 900 segundos (15 minutos) num total de 6 horas - 21 600s
    int num_total_viagens = 0;

    //variaveis usadas para escrever no ficheiro as estatisticas
    FILE * fp = NULL;
    int i = 0, inicio = 0, fim = 15;
    float media = 0;

    printf("\n \n a executar \n");

    //vamos percorrer toda a lista de viagens e dividir as duracoes em sub_categorias
    while (aux_trips != NULL)
    {
        if (aux_trips->viagem.duracao < 900) {
            duracao[0]++;
        } else if (aux_trips->viagem.duracao >= 900 && aux_trips->viagem.duracao < 1800) {
            duracao[1]++;
        } else if (aux_trips->viagem.duracao >= 1800 && aux_trips->viagem.duracao < 2700) {
            duracao[2]++;
        } else if (aux_trips->viagem.duracao >= 2700 && aux_trips->viagem.duracao < 3600) {
            duracao[3]++;
        } else if (aux_trips->viagem.duracao >= 3600 && aux_trips->viagem.duracao < 4500) {
            duracao[4]++;
        } else if (aux_trips->viagem.duracao >= 4500 && aux_trips->viagem.duracao < 5400) {
            duracao[5]++;
        } else if (aux_trips->viagem.duracao >= 5400  && aux_trips->viagem.duracao < 6300) {
            duracao[6]++;
        } else if (aux_trips->viagem.duracao >= 6300 && aux_trips->viagem.duracao < 7200) {
            duracao[7]++;
        } else if (aux_trips->viagem.duracao >= 7200 && aux_trips->viagem.duracao < 8100) {
            duracao[8]++;
        } else if (aux_trips->viagem.duracao >= 8100 && aux_trips->viagem.duracao < 9000) {
            duracao[9]++;
        } else if (aux_trips->viagem.duracao >= 9000 && aux_trips->viagem.duracao < 9900) {
            duracao[10]++;
        } else if (aux_trips->viagem.duracao >= 9900 && aux_trips->viagem.duracao < 10800) {
            duracao[11]++;
        } else if (aux_trips->viagem.duracao >=10800 && aux_trips->viagem.duracao < 11700) {
            duracao[12]++;
        } else if (aux_trips->viagem.duracao >= 11700 && aux_trips->viagem.duracao < 12600) {
            duracao[13]++;
        } else if (aux_trips->viagem.duracao >= 12600 && aux_trips->viagem.duracao < 13500) {
            duracao[14]++;
        } else if (aux_trips->viagem.duracao >= 13500 && aux_trips->viagem.duracao < 14400) {
            duracao[15]++;
        } else if (aux_trips->viagem.duracao >= 14400 && aux_trips->viagem.duracao < 15300) {
            duracao[16]++;
        } else if (aux_trips->viagem.duracao >= 15300 && aux_trips->viagem.duracao < 16200) {
            duracao[17]++;
        } else if (aux_trips->viagem.duracao >= 16200 && aux_trips->viagem.duracao < 17100) {
            duracao[18]++;
        } else if (aux_trips->viagem.duracao >= 17100 && aux_trips->viagem.duracao < 18000) {
            duracao[19]++;
        } else if (aux_trips->viagem.duracao >= 18000 && aux_trips->viagem.duracao < 18900) {
            duracao[20]++;
        } else if (aux_trips->viagem.duracao >= 18900 && aux_trips->viagem.duracao < 19800) {
            duracao[21]++;
        } else if (aux_trips->viagem.duracao >= 19800 && aux_trips->viagem.duracao < 20700) {
            duracao[22]++;
        } else if (aux_trips->viagem.duracao >= 20700 && aux_trips->viagem.duracao < 21600) {
            duracao[23]++;
        }
        num_total_viagens++;        //vai contanto o numero total de viagens para depois efetuar estatisticas
        aux_trips = aux_trips->next;
    }

    //Vai guardar tudo num ficheiro de estatisticas
    fp = fopen("Estatísticas_duracao.txt", "w");
    if (fp == NULL)
    {
        printf("Não foi possivel geral o ficheiro de estatisticas por duracao   :( \n");
        return;
    }

    fprintf(fp, "->Estatísticas por duracao\n \n");

    for (i = 0; i < 24; i++)
    {
        media = (((float)(duracao[i])) / num_total_viagens ) * 100;
        fprintf(fp, "Duracão: %d - %d minutos -> %0.2f%% \n", inicio, fim, media);
        inicio = inicio + 15;
        fim = fim + 15;
    }

    fclose(fp);
}

/*
** Vai calcular as estatisticas de velocidade
*/
void velocidade_estatisticas(node_t * head_trips, station_t * head_station)
{
    node_t * aux_trips = head_trips;  //auxiliar para apontar para a lista de viagens
    unsigned long long int velocidade[2][101] = {{0}};      //matriz que vai guardar a soma das velocidades para as categorias de idades e (rapazes ou raparigas)
    float num_somas[2][101] = {{0}};       //matriz que vai guardar o numero total de somas de velocidades feitas para categoria para efetuar a media
                                        //coluna zero para "Male" e coluna 1 para "Female"
    int i = 0;      //auxiliar para correr o loop
    float media_boys = 0;
    float media_girls = 0;

    FILE * fp = NULL;

    //vai percorrer toda a lista de viagens
    while (aux_trips  != NULL)
    {
        //vai percorrer para todas as idades dos 0 aos 100 anos
        for (i = 0; i < 101; i++)
        {
            if ((aux_trips->viagem.data_final.year - aux_trips->viagem.birthday) == i && aux_trips->viagem.velocidade != 0 && aux_trips->viagem.velocidade < 45 && aux_trips->viagem.velocidade > 0 && aux_trips->viagem.duracao > 0)
            {
                if(strcmp("Male", aux_trips->viagem.gender) == -13)
                {
                    //acrescenta a velocidade à posicao no array desejada (Male (coluna 0) e idade correspondente em linha)
                    velocidade[0][i] = velocidade[0][i] + aux_trips->viagem.velocidade;
                    //acrescenta à outra matriz 1, para informar que foi acrescentada mais uma velocidade -> para depois efetuar a média
                    num_somas[0][i]++;
                }

                if(strcmp("Female", aux_trips->viagem.gender) == -13)
                {
                    //acrescenta a velocidade à posicao no array desejada
                    velocidade[1][i] = velocidade[1][i] + aux_trips->viagem.velocidade;
                    //acrescenta à outra matriz 1, para informar que foi acrescentada mais uma velocidade -> para depois efetuar a média
                    num_somas[1][i]++;
                }
            }
        }

        aux_trips = aux_trips->next;
    }

    //Vai guardar tudo num ficheiro de estatisticas
    fp = fopen("Estatísticas_velocidade.txt", "w");
    if (fp == NULL)
    {
        printf("Não foi possivel geral o ficheiro de estatisticas por velocidade   :( \n");
        return;
    }

    fprintf(fp, "->Estatísticas por velocidade\n \n");

    //int idade = 0;
    fprintf(fp, "         |           Velocidade                      |\n");
    fprintf(fp, "Idade    |      Male  (Km/h)     |     Female (Km/h) |\n");

    //para cada conjunto de idades (grupos de 2 anos) - vai calcular a velocidade média
    for (i = 18; i < 100; i = i+2)
    {
        media_boys = (float)(velocidade[0][i] + velocidade[0][i + 1]) / (num_somas[0][i] + num_somas[0][i + 1]);
        media_girls = (float)(velocidade[1][i] + velocidade[1][i + 1]) / (num_somas[1][i] + num_somas[1][i + 1]);
        fprintf(fp, "%d - %d              %0.2f                   %0.2f  \n", i, i+1, media_boys, media_girls);
    }
    fclose(fp);
}


//------------CALCULO DE DISTANCIAS e VELOCIDADES DAS ROTAS---------------------
/*
** Calcula a distancia percorrida com base nas latitudes e longitudes e retorna a distancia em metros
** Nota: Este algoritmo foi completamente baseado no agoritmo fornecido na pagina da cadeira
** pelo que todos os créditos pela implementacao desta funcao nao se devem a nos, alunos 
*/
int calc_distancia(float _latitude1, float _latitude2, float _longitude1, float _longitude2)
{
    int Raio = 6371000;   //raio da terra em metros
    float latitude1 = (float)_latitude1; //latitude da estacao inicial
    float latitude2 = (float)_latitude2; //latitude da estacao final
    float diferenca_lat = latitude2 - latitude1;
    float diferenca_long = (_longitude2 - _longitude1); //subtrai a longitude final à longitude inicial

    float a = 0;
    float c = 0;
    float d = 0;

    //Conversoes para radianos
    latitude1 = ((latitude1 * 2 * PI) / 360);
    latitude2 = ((latitude2 * 2 * PI) / 360);
    diferenca_lat = ((diferenca_lat * 2 * PI) / 360);
    diferenca_long = ((diferenca_long * 2 * PI) / 360);

    //efetuar as multiplicacoes
    a = (sin((diferenca_lat / 2)) * sin ((diferenca_lat / 2))) +
        (cos(latitude1) * cos(latitude2) * sin((diferenca_long / 2)) * sin((diferenca_long / 2)));

    c = 2 * atan2(sqrt(a), sqrt(1 - a));
    d = Raio * c;
    return d;
}

/*
** Calcula a velocidade do utilizador em KM/h e retorna esse valor em float
*/
float calc_velocidade(int _distancia, int _time)
{
    //como recebemos o tempo em segundos e a distancia em metros, vamos converter estes valores para obtermos KM/h
    float distancia = (float)_distancia;
    distancia = distancia / 1000; //(conversao para kM)
    float timed = (float)_time;
    timed = timed / 3600; //vamos converter para horas, o tempo

    //vamos obter a velocidade
    float velocidade = distancia / timed;

    return velocidade;

}
