#include "textmode.h"

//——textmode.c---

/*
** Funcao que valida os dados inseridos como argumentos para iniciar o programa
*/
int argumentsValidator (int argc, char * argv[])
{
    int modevalue = 0; //defines the desired interface mode

    FILE *fp = NULL; //declaration of a pointer to a file

    //--------CHECK NUMBER OF ARGUMENTS------------------------------
    //If there arguments mssing, it wont execute the program
    if (argc != 4)
    {
        printf("Incorrect number of arguments. Try again!!!\n");
        exit(EXIT_FAILURE);
    }
    //If the selected mode doesnt exist, then it wont execute
    else if(strcmp("-g", argv[1]) != 0 && strcmp("-t", argv[1]) != 0)
    {
        printf("Selected a non supported mode!!!\n");
        exit(EXIT_FAILURE);
    }

    //------CHECKS IF THE FILES ARE OPPENING CORRECTLY--------------
    fp = fopen(argv[2], "r");
    if (fp == NULL)
    {
        printf("File %s was NOT open successfuly! Try again!!!\n", argv[2]);
        exit(EXIT_FAILURE);
    }
    fclose(fp);
    fp = fopen(argv[3], "r");
    if (fp == NULL)
    {
        printf("File %s was NOT open successfuly! Try again!!!\n", argv[3]);
        exit(EXIT_FAILURE);
    }
    fclose(fp);

    //------Returns 0-> graphical     -------Returns 1-> textual
    if (strcmp("-g", argv[1]) == 0)
    {
        modevalue = 0;
    }
    else if (strcmp("-t", argv[1]) == 0) {
        modevalue = 1;
    }

    return modevalue;
}

/* get_UI imprime o main text UI para o utilizador  - ESTA FUNCAO IMPLEMENTA O MENU PRINCIPAL
**  Recebe como parametros por referencia os ponteiros para as cabeças das listas de estacoes e de viagens
*/
void get_UI(node_t ** head_node, station_t ** head_station, int * lista_alterada, char * argv[])
{
    //declares the variables where the chosen option will be stored
    char menu1[STR_MAX]={0};
    int option1 = 0;
    //declares the variable ret that will have the value 1 when sscanf can read one integer value from menu1
    int ret=0;

    //variável que serve como flag no menu de rotas
    int flag_finish=0;

    char trash = '0';      //int auxiliar que apenas serve no modo de listagem de viagens para aguardar uma key press

    //no auxiliar para a cabeça da lista de viagens
    node_t * auxiliar_trips = *head_node;

    //sub-menus
    //int listagem_viagens_numero = 0;

    //prints the menu
    printf("Selecione um numero de 1 a 5 para escolher uma opção!\n");
    printf("1 - Seleção de Dados\n");
    printf("2 - Listagem de Viagens\n");
    printf("3 - Listagem de Estações\n");
    printf("4 - Listagem de Rotas\n");
    printf("5 - Listagem de Estatísticas\n");
    printf("6 - Sair \n");

    //reads the integer value inserted by the user
    fgets(menu1, STR_MAX, stdin);
    ret=sscanf(menu1, "%d", &option1);

    //checks if the inserted value is valid, and asks for it again if it isn't
    while (ret!=1 || option1<1 || option1>6)
    {
        printf("Selecione uma opção válida\n");

        //reads the integer value inserted by the user
        fgets(menu1, STR_MAX, stdin);
        ret=sscanf(menu1, "%d", &option1);
    }

    switch (option1){
        case 1:
            //vai aplicar os filtros de selecao à lista de viagens
            data_selection(head_node,*head_station,  lista_alterada, argv);                          //Funcao que chama o submenu para escolher o modo de selecao de dados
            system("clear");
            //vai voltar para o menu inicial automaticamente
            get_UI(head_node, head_station, lista_alterada, argv);
            break;
        case 2:
            //vai imprimir todas as viagens e vai chamar de novo o menu inicial
            printf_trips (auxiliar_trips, &flag_finish);
            //vai esperar por uma tecla qualquer para voltar para o menu inicial
            if(flag_finish==0)
            {
                //printf("\nPrima qualquer tecla para voltar para o menu! \n");
                do {
                    fgets(menu1, STR_MAX, stdin);
                    ret = sscanf(menu1, "%c", &trash);
                }while (ret != 1);
                system("clear");
                get_UI(head_node, head_station, lista_alterada, argv);
            }
            else if(flag_finish==1)
            {
                system("clear");
                flag_finish=0;
                get_UI(head_node, head_station, lista_alterada, argv);
            }
            break;
        case 3:
            //vai imprimir todas as viagens e chamar de novo o menu inicial
            show_station(*head_node,* head_station);
            //Funcao responsavel por fazer a listagem das estacoes
            //vai esperar por uma tecla qualquer para voltar para o menu inicial
            printf("\nPrima qualquer tecla para voltar para o menu! \n");
            if (flag_finish == 0)
            {
                  do {
                      fgets(menu1, STR_MAX, stdin);
                      ret = sscanf(menu1, "%c", &trash);
                  }while (ret != 1);
                  system("clear");
                  get_UI(head_node, head_station, lista_alterada, argv);
            }
            else if( flag_finish == 1)
            {
                  system("clear");
                  flag_finish=0;
                  get_UI(head_node, head_station, lista_alterada, argv);
            }

            break;
        case 4:
            system("clear");
            //vai abrir o menu de rotas e volta a invocar o menu inicial
            printf_rotas(*head_node, *head_station, &flag_finish);        //funcao responsavel por imprimir rotas

            if (flag_finish==0)
            {
                  printf("\nPrima qualquer tecla para voltar para o menu! \n");
                  do {
                      fgets(menu1, STR_MAX, stdin);
                      ret = sscanf(menu1, "%c", &trash);
                  }while (ret != 1);
                  system("clear");
                  get_UI(head_node, head_station, lista_alterada, argv);
            }
            else if (flag_finish==1)
            {
                  system("clear");
                  flag_finish=0;
                  get_UI(head_node, head_station, lista_alterada, argv);
            }

            break;
        case 5:
            printf("5\n");
            system("clear");
            //vai abrir o submenu de selecao de estatisticas
            selecao_estatisticas(head_node, head_station);
            get_UI(head_node, head_station, lista_alterada, argv);
            break;
        case 6:
            //exit = 1;
            break;
        default:
            printf("Valor inválido!\n");
    }
}

/* data_selection define a o interface para o sub-menu da selecao de dados
**
*/
void data_selection(node_t ** head_node, station_t * head_station, int * lista_alterada, char * argv[])
{
    //declares the variables where tha data read from the keyboard will be stored
    char str[STR_MAX] = {0};
    int n = 0;
    //variable that will have the value 1 when sscanf can read one integer value
    int ret = 0;
    char trash;

    int lista_vazia=0;

    //Clears the screen
    system("clear");

    //Impressao do menu
    printf("Seleção de Dados\n");
    printf("Choose one of the following options, by pressing 1 or 2!\n");
    printf("1. - Usar todas as viagens\n");
    printf("2. - Selecionar viagens\n");
    printf("3. - Limpar filtros\n");
    printf("4. - Voltar ao menu\n");
    fgets(str, STR_MAX, stdin);
    ret = sscanf(str, "%d", &n);

    //confirms if the inserted data is valid and asks for it again if it isn't
    while(ret!=1 || (n!=1 && n!=2 && n!=3 && n!=4))
    {
        printf("Insert a valid value!\n");
        fgets(str, STR_MAX, stdin);
        ret = sscanf(str, "%d", &n);
    }

    if (n == 1) //se a opcao selecionada for 1 vai usar todas as viagens
    {
        printf("A atualizar lista\n");
        if (*lista_alterada == 1)
        {
            printf("A dar reset à lista!\n");
            //vai limpar a lista anterior
            while (*head_node != NULL)
            {
                remove_head_viagens( head_node);
            }
            remove_head_viagens(head_node);

            //vai dar load da nova lista
            *head_node = file_load_trips(argv, head_station);

            lista_alterada = 0;

        }
        printf("Lista atualizada\n");
    }
    else if(n == 2) //vai aplicar filtros de selecao
    {
        if (*lista_alterada == 0)
        {
            data_submenu1(head_node, &lista_vazia);
            *lista_alterada = 1;
        } else {
            //vai limpar a lista anterior
            printf("A dar reset à lista para poder aplicar filtros!\n");
            while (*head_node != NULL)
            {
                remove_head_viagens( head_node);
            }
            remove_head_viagens( head_node);

            //vai dar load da nova lista
            *head_node = file_load_trips(argv, head_station);
            //vai aplicar os novos filtros
            data_submenu1(head_node, &lista_vazia);
            *lista_alterada = 1;
        }
    }
    else if (n == 3) //Vai remover filtros previamente aplicados
    {
        //verifica se tinham havido alterações na lista_alterada
        //se não tiver havido alterações não há filtros por limpar
        if(*lista_alterada == 0)
        {
            printf("Não existiam critérios para limpar!\n");
            printf("\n");
            printf("Pressiona qualquer tecla para voltar ao menu principal\n");
            //vai esperar por uma tecla para voltar para o menu principal
             do {
                        fgets(str, STR_MAX, stdin);
                        ret = sscanf(str, "%c", &trash);
                    }while (ret != 1);

            data_selection(head_node, head_station, lista_alterada, argv);
        }
        else if (n == 4) //volta para o menu principal
        {
            return;
        }
        //verifica se tinham havido alterações na lista
        //se tiver havido alterações a lista é carregada de novo
        else
        {
            //vai dar load da nova lista
            *head_node = file_load_trips(argv, head_station);
            printf("Os critérios foram limpos com sucesso!\n");
        }
    }

    if (lista_vazia == 1) //se a lista ficou vazia vai dar reload da lista
    {
        printf("\n");
        *head_node = file_load_trips(argv, head_station);

        printf("\n");
        printf("Pressiona qualquer tecla para voltar ao menu principal\n");
        //vai esperar por uma tecla para voltar para o menu principal
         do {
            fgets(str, STR_MAX, stdin);
            ret = sscanf(str, "%c", &trash);
        }while (ret != 1);
    }

}

/*
** data_submenu1
** Aplica as retricoes às listas da forma que o utilizador desejar
*/
void data_submenu1(node_t ** head_node, int *lista_vazia)
{
    char str[STR_MAX] = {0};    //variaveis auxiliares na obtencao das restricoes a aplicar nas listas
    char yes_no = 'A';      //com base nas escolhas do utilizador
    int ret = 0;
    int hora_inicio;
    int hora_fim;
    int dia;
    int duracao;

    //PERGUNTA AO USER SE QUER USAR A HORA COMO CRITERIO DE SELECAO
    do {
        system("clear");
        printf("->Escolher critérios de seleção\n");
        printf("Deseja usar a hora de inicio e de fim da viagem como critério de seleção? (y/n)");
        fgets(str, STR_MAX, stdin);
        ret = sscanf(str, "%c", &yes_no);
    } while (ret != 1 || (yes_no != 'y' && yes_no != 'n'));

    //Se deseja usar a hora como criterio de seleção vai pedir ao user as horas
    if (yes_no == 'y')
    {
        do {
            printf("Insira a hora de inicio (0 - 23): ");
            fgets(str, STR_MAX, stdin);
            ret = sscanf(str, "%d", &hora_inicio);
        }while(hora_inicio > 23 || hora_inicio < 0 || ret != 1);

        do {
            printf("Insira a hora de fim (hora fim - 24): ");
            fgets(str, STR_MAX, stdin);
            ret = sscanf(str, "%d", &hora_fim);
        } while(hora_fim > 24 || hora_fim < 0 || ret != 1 || hora_fim <= hora_inicio);
        printf("Hora inicio:  %d    Hora fim:   %d\n", hora_inicio, hora_fim);
        *head_node = remove_hora_init(hora_inicio, * head_node);
        *head_node = remove_hora_init2(hora_fim, * head_node);
        *head_node = remove_hora_fim(hora_fim, * head_node);
        *head_node = remove_hora_fim2(hora_inicio, * head_node);
    }

    //PERGUNTA AO USER SE QUER USAR O DIA DA SEMANA COMO CRITERIO DE SELECAO
     do {
        system("clear");
        printf("->Escolher critérios de seleção\n");
        printf("Deseja usar o dia da semana como critério de seleção? (y/n)");
        fgets(str, STR_MAX, stdin);
        ret = sscanf(str, "%c", &yes_no);
    } while (ret != 1 || (yes_no != 'y' && yes_no != 'n'));

    if (yes_no == 'y')
    {
        do {
            printf("Insira o dia ao qual pretende restringir os dados(0 - Domingo <-> 6 - Sábado): ");
            fgets(str, STR_MAX, stdin);
            ret = sscanf(str, "%d", &dia);
        }while(dia > 6 || dia < 0 || ret != 1);
        *head_node = remove_dia_semana(dia, *head_node);

    }

    //PERGUNTA AO USER SE DESEJA USAR A DURACAO COMO CRITERIO DE SELECAO
    do {
        system("clear");
        printf("->Escolher critérios de seleção\n");
        printf("Deseja usar a duração da viagem como critério de seleção? (y/n)");
        fgets(str, STR_MAX, stdin);
        ret = sscanf(str, "%c", &yes_no);
    } while (ret != 1 || (yes_no != 'y' && yes_no != 'n'));

    if (yes_no == 'y')
    {
        do {
            printf("Insira a duracao maxima: ");
            fgets(str, STR_MAX, stdin);
            ret = sscanf(str, "%d", &duracao);
        }while( duracao < 1 || ret != 1);
        *head_node = remove_duracao(duracao, *head_node);

    }

    //se a lista ficar vazia, vai ativar uma flag
    if (*head_node == NULL)
    {
        printf("A lista ficou vazia!\n");
        printf("A carregar a lista de novo...\n");
        *lista_vazia = 1;
    }
}

/*
** Implementa o submenu de selecao de estatiscticas
*/
void selecao_estatisticas(node_t ** head_node, station_t ** head_station)
{
    //declares the variables where tha data read from the keyboard will be stored
    char str[STR_MAX] = {0};
    int n = 0;
    //variable that will have the value 1 when sscanf can read one integer value
    int ret = 0;
    char trash = '0';   //variavel que serve apenas para esperar que o utilizador pressione uma tecla

    //Clears the screen
    system("clear");

    //Impressao do menu
    printf("Listagem de Estatisticas\n");
    printf("Escolha uma das opções ao clicar 1, 2, 3 ou 4\n");
    printf("1. - Estatisticas por genero\n");
    printf("2. - Estatisticas por idade\n");
    printf("3. - Estatisticas por duração\n");
    printf("4. - Estatisticas por velocidade\n");
    printf("5. - Voltar ao menu\n");
    fgets(str, STR_MAX, stdin);
    ret = sscanf(str, "%d", &n);

    //confirms if the inserted data is valid and asks for it again if it isn't
    while(ret!=1 || n > 5 || n < 1)
    {
        printf("Insert a valid value!\n");
        fgets(str, STR_MAX, stdin);
        ret = sscanf(str, "%d", &n);
    }

    switch(n){
        case 1:
            printf("A guardar num ficheiro as estatisticas por género!\n");
            //chama a funcao que guarda as estatisticas por género
            genero_estatisticas(*head_node, *head_station);
            printf("->Estatisticas por género geradas. Prima alguma tecla para voltar\n");
            break;
        case 2:
            printf("->A guardar num ficheiro as estatisticas por idade!\n\n");
            //chama a funcao que guarda as estatisticas por idade
            idade_estatisticas(* head_node, * head_station);
            printf("\n->Estatisticas por idade geradas. Prima alguma tecla para voltar\n");

            break;
        case 3:
            printf("A guardar num ficheiro as estatisticas por duracao!\n");
            //chama a funcao que guarda as estatisticas por duracao
            duracao_estatisticas(* head_node,* head_station);
            printf("->Estatisticas por duracao geradas. Prima alguma tecla para voltar\n");

            break;
        case 4:
            printf("A guardar num ficheiro as estatisticas por velocidade!\n");
            //chama a funcao que guarda as estatisticas por velocidade
            velocidade_estatisticas(* head_node, * head_station);
            printf("->Estatisticas por velocidade geradas. Prima alguma tecla para voltar\n");
            break;
        case 5:
            system("clear");
            return;
            break;
        default:
            printf("Funcionalidade inexistente    :(   ");
            break;
    }
    //vai esperar por uma tecla para voltar para o menu principal
     do {
                fgets(str, STR_MAX, stdin);
                ret = sscanf(str, "%c", &trash);
            }while (ret != 1);
            system("clear");
}
