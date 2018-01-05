#include "Graficos.h"

//———Graficos.c————

int main_graphics (node_t ** head_trip, station_t ** head_station, station_t **tail_station, char * argv[])
{
    SDL_Window *window;                    // Declara um ponteiro para janela, renderers, surface, eventos, etc..
    SDL_Renderer *renderer;
    SDL_Surface *mapa_surface, *logo_surface;       //Surface que vai usar usada para dar load do mapa e do logo
    SDL_Event event;
    int quit = 0;                           //varivel que define a execução do programa
    int delay = 300;                        //delay usado para refresh rate do ecrã
    station_t * copia_station = *head_station;      //ponteiro auxiliar para navegar nas estacoes
    TTF_Font * SanFrancisco = NULL;             //fonts usadas
    TTF_Font * small_font = NULL;
    int partida_chegada = 1;                    //indica se quer ver as rotas que tiveram a estacao como estacao de partida ou de chagada
                                                // 1 - estacao de partida   2 - estacao de chegada
    rota_t mais_popular;    //declara uma variavel que vai guardar a rota mais popular para depois imprimir algumas informacoes na sidebar

    selecionaDia(head_trip, argv, *head_station);   //selecao dos dias da semana a remover


    IniciaSDLTodo();                                            //vai inicializar o SDL
    InicializaFonts(&SanFrancisco, &small_font);                     //Inicializa a font
    abreJanela(&window, &renderer);                     //vai abrir a janela do programa
    loadMapa(&mapa_surface);                            //Dá Load do mapa para uma surface
    loadLogo(&logo_surface);


    //LOOP PRINCIPAL
    while (quit == 0)
    {
        //Se houver a deteção de eventos
        while( SDL_PollEvent( &event ) )
        {
            if( event.type == SDL_QUIT )    //equivale a clicar no botao de fechar a janela
            {
                quit = 1;
            }
            else if ( event.type == SDL_KEYDOWN )   //equivale a pressionar uma tecla
            {
                switch ( event.key.keysym.sym )
                {
                    case SDLK_RIGHT:
                        //vai andar para a estacao seguinte para analizar
                        if (copia_station->next != NULL)
                        {
                            copia_station = copia_station->next;
                        }
                        else
                        {
                            copia_station = *head_station;
                        }
                        break;
                    case SDLK_LEFT:
                        //vai andar para a estacao anterior
                        if (copia_station->last != NULL)
                        {
                            copia_station = copia_station->last;
                        }
                        else
                        {
                            copia_station = *tail_station;
                        }
                        break;
                    case SDLK_UP:
                        //vai alterar o estado da estacao -> se é estacao de partida ou estacao de chegadas
                        if (partida_chegada == 0 || partida_chegada == 2)
                        {
                            partida_chegada = 1;
                        } else if (partida_chegada == 0 || partida_chegada == 1){
                            partida_chegada = 2;
                        }
                        break;
                    case SDLK_DOWN:
                        //vai alterar o estado da estacao -> se é estacao de partida ou estacao de chegada
                        if (partida_chegada == 0 || partida_chegada == 2)
                        {
                            partida_chegada = 1;
                        } else if (partida_chegada == 0 || partida_chegada == 1){
                            partida_chegada = 2;
                        }
                        break;
                    default:
                        break;
                }
            }
        }
        //Dá render do mapa que se encontrava na surface
        RederMapa(mapa_surface, logo_surface, renderer);        //dá redner do mapa
        RenderNomeEstacao(renderer, SanFrancisco, copia_station );  //dá render do nome da estacao atual
        drawStations(*head_station, renderer);      //marca todas as estacoes no mapa
        marksTheStation(copia_station, renderer);   //marca a estacao atual no mapa
        traca_rotas(*head_trip, *head_station, copia_station,renderer, partida_chegada, small_font, &mais_popular); //traca todas as rotas com cores
        renderInstrucoes(small_font,renderer);      //mostra as instrucoes na sidebar
        melhor_rota_info(mais_popular, small_font, renderer);   //vai indicar na sidebar a rota mais popular para aquela estacao
        estacao_chegada_partida(small_font, renderer, partida_chegada); //indica se a rota é de partida ou chegada
        rota_principal(mais_popular, renderer); //vai traçar uma reta mais grossa por cima da rota mais popular
        SDL_RenderPresent(renderer);            //Atualiza o ecrã
        SDL_Delay(delay);                       //Faz um delay para definir um refresh rate

    }
    //vai dar free da memoria alocada para os diferentes elementos do sdl usados
    TTF_CloseFont(SanFrancisco);
    TTF_CloseFont(small_font);
    SDL_FreeSurface(logo_surface);
    SDL_FreeSurface(mapa_surface);
    SDL_Delay(3000);                        //coloca um delay (vai definir o refresh rate do programa)
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);              //vai destruir a janela
    SDL_Quit();                             //vai fechar tudo o que está relacionado com o SDL


    return 1;
}

//Vai abrir uma janela e o seu renderer
void abreJanela(SDL_Window **window, SDL_Renderer ** renderer)
{
    //Abre uma janela com as seguintes definições:
    *window = SDL_CreateWindow(
        "BikeStation",                      // Titulo
        SDL_WINDOWPOS_CENTERED,             // posicao x onde aparece no ecra
        SDL_WINDOWPOS_CENTERED,             // posicao y onde aparece no ecra
        LARGURA,                                // largura na janela
        ALTURA,                                // altura da janela
        0                                   // flags - nenhuma
    );
    //verificacao da correta abertura de janela
    if (*window  == NULL)
    {
        printf("Erro a criar uma janela\n");
        exit(EXIT_FAILURE);
    }

    *renderer = SDL_CreateRenderer(*window, -1, 0);   //vai criar um renderer
    //verificacao da criacao de renderer
    if (*renderer == NULL)
    {
        printf("Erro a criar um renderer\n");
        exit(EXIT_FAILURE);
    }
}

/*
** Vai iniciar a library SDL e library de fonts
*/
void IniciaSDLTodo()
{
    // init SDL library
    if ( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        printf(" Failed to initialize SDL : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // Init font library
    if(TTF_Init()==-1)
    {
        printf("TTF_Init: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
}

/*
** Inicializa todas fonts usadas no programa
*/
void InicializaFonts(TTF_Font ** font, TTF_Font ** small_font)
{
    // Vai abrir a Font Sao Francico com um tamanho 20
    *font = TTF_OpenFont("SanFrancisco.ttf", 20);
    if(!*font)
    {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    // Vai abrir a Font Sao Francisco com um tamanho 12
    *small_font = TTF_OpenFont("SanFrancisco.ttf", 12);
    if(!*small_font)
    {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
}

/*
** Funcao que vai dar load do mapa para uma surface dedidcada
*/
void loadMapa(SDL_Surface ** surface_mapa)
{
    *surface_mapa= IMG_Load(".//img//mapa_pequeno.png");    //localizacao do mapa
    //verificacao da correta abertura do mapa
    if (*surface_mapa == NULL)
        {
            printf("Unable to load image: %s\n", SDL_GetError());
            exit(EXIT_FAILURE);
        }
}

/*
** Funcao que vai carregar o logo para uma surface
*/
void loadLogo(SDL_Surface ** surface_logo)
{
    *surface_logo = IMG_Load(".//img//logo.png");       //localizacao do logo
    //verificacao da correta abertura do logo
    if (*surface_logo == NULL)
    {
        printf("Unable to load logo: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
}

/**
 ** RenderText: Dá render de texto na janela
 ** Recebe a coordenadas onde vai ser escrito o texto, o texto a ser escrito, a font, a cor e o render
 **------------------------------------------------------------------------------------
 ** ------NOTA: ESTA FUNCAO FOI USADA NO PROJRETO 1024 NO CODIGO PRE-FORNECIDO----
 ** OS ALUNOS APENAS USARAM ESTA FUNCAO PARA FACILITAR A RENDERIZACAO DE TEXTO NO ECRA
 */
int RenderText(int x, int y, const char *text, TTF_Font *_font, SDL_Color *_color, SDL_Renderer* _renderer)
{
    SDL_Surface *text_surface;      //declaracao de texturas, surfaces e retangulo onde o texto sera "desenhado"
    SDL_Texture *text_texture;
    SDL_Rect solidRect;

    solidRect.x = x;    //mete o retangulo no local desejado pelo utilizador
    solidRect.y = y;

    //cria a surface para a string a escrever
    text_surface = TTF_RenderText_Blended(_font,text,*_color);
    if(!text_surface)
    {
        printf("TTF_RenderText_Blended: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    //cira a textura
    text_texture = SDL_CreateTextureFromSurface(_renderer, text_surface);
    //Obtem o tamanho
    SDL_QueryTexture( text_texture, NULL, NULL, &solidRect.w, &solidRect.h );
    //Dá render da extura
    SDL_RenderCopy(_renderer, text_texture, NULL, &solidRect);
    //Liberta a memoria alocada
    SDL_DestroyTexture(text_texture);
    SDL_FreeSurface(text_surface);
    return solidRect.h;
}

/*
** Vai dar render do mapa (que tinha sido feito upload para uma surface)
** Vai ainda dar Load de uma sideBar do lado esquerdo - estilo google maps mas apenas por
** motivos estéticos
*/
void RederMapa(SDL_Surface * surface_mapa, SDL_Surface * surface_logo, SDL_Renderer * renderer)
{
    //------Variaveis para uso no mapa-----
    SDL_Texture *mapa_texture, *logo_texture;  //Cria uma textura da surface que continha o mapa
    SDL_Rect tableSrc, tableDest, tableLogo, tableLG;   //Vai criar retângulos com o tamanho e posicao desejados para a imagem
    //Vai definir coordenadas para poder usar o RenderCopy
    tableDest.x = tableSrc.x = 0;
    tableDest.y = tableSrc.y = 0;
    tableSrc.w = surface_mapa->w;
    tableSrc.h = surface_mapa->h;
    tableDest.w = LARGURA;
    tableDest.h = ALTURA;

    //-----Variaveis para uso na sidebar----
    //Vai desenhar a sidebar no ecrã
    SDL_Color light = { 236, 236, 236 }; //Vai definir a cor para a sideBar
    SDL_Rect sidebar;
    sidebar.x = 0;         //Sidebar vai encontrar-se na lateral esquerda do programa
    sidebar.y = 150;
    sidebar.w = 200;        //Sidebar vai ter a larguar de 100 pixels
    sidebar.h = ALTURA - 200;     //Sidebar vai ter a altura da janela

    //Vai definir os retangulos para desenhar o logo
    tableLG.x = tableLogo.x = 0;
    tableLG.y = tableLogo.y = 10;
    tableLogo.w = tableLG.w = (surface_logo->w);
    tableLogo.h = tableLG.h = (surface_logo->h);

    //Limpa a Janela
    SDL_RenderClear( renderer );

    //Desenha o mapa no ecrã
    mapa_texture = SDL_CreateTextureFromSurface(renderer, surface_mapa);
    SDL_RenderCopy(renderer, mapa_texture, &tableSrc, &tableDest);

    //Vai meter a cor no renderer para a sidebar
    SDL_SetRenderDrawColor(renderer, light.r, light.g, light.b, light.a );
    SDL_RenderFillRect(renderer, &sidebar);

    //Desenha o logotipo no ecrã
    logo_texture = SDL_CreateTextureFromSurface(renderer, surface_logo);
    SDL_RenderCopy(renderer, logo_texture, &tableLogo, &tableLG);

    //Remove a memoria alocada para a textura
    SDL_DestroyTexture(mapa_texture);
}

/*
** Vai imprimir algumas informacoes sobre a estacao atual
*/
void RenderNomeEstacao (SDL_Renderer * renderer,TTF_Font * font, station_t * estacao)
{
    SDL_Color dark = { 44, 44, 44 };//Cor escura
    SDL_Color light = { 236, 236, 236 }; //Cor clara

    //Retangulo que vai ser o fundo das letras com o nome da estacao
    SDL_Rect rect;
    rect.x = 250;
    rect.y = 560;
    rect.w = 700;
    rect.h = 45;

    //vamos definir a cor do renderer para dar cor a sidebar
    SDL_SetRenderDrawColor(renderer, light.r, light.g, light.b, light.a );
    SDL_RenderFillRect( renderer, &rect);

    //Vai imprimir o nome da estacao no retangulo para esse desenhado para esse efeito
    RenderText(rect.x + 4, rect.y + 15, estacao->full_name, font, &dark, renderer);
}



/*
** Vai pedir ao utilizador para restringir os dados a um dia da semana
** Vai receber por referencia a cabeça da lista de viagens
** Pode receber mais do que um dia da semana
** Se a lista ficar vazia, vai enchela de novo e pedir novamente para restringir os dias da semana
*/

void selecionaDia(node_t ** head, char * argv[], station_t *head_station)
{
    char str[STR_MAX];  //string auxiliar na receção de dados do utilizador
    int dia = 0;    //vai servir para escolher o dia da semana
    int ret = 0;    //vai servir para verificacao de correta aceitacao de parametros
    char str2[STR_MAX]; //string auxiliar na rececao de dados do utilizador
    int ret2 = 0;   //vai servir para verificacao de correta aceitacao de parametros
    char teste = 'n'; //vai servir para saber se o utilizador pretende remover mais dias ou nao
    int i = 0;  //conta o numero de dias removidos - se maior que 6, entao vai dar reload na lista de viagens

    while(teste == 'n')
    {
        do {
            printf("Insira o dia da semana a remover da lista (0 - Domingo <-> 6 - Sábado): ");  //vai pedir ao utilizador para remover pelo menos um dia da semana da lista
            fgets(str, STR_MAX, stdin);
            ret = sscanf(str, "%d", &dia);
        }while(dia > 6 || dia < 0 || ret != 1);

        i++;
        if (i == 7)             //verificacao se a lista ficou fazia
        {
            system("clear");
            printf("A lista ficou vazia e por isso será carregada de novo!\n");
            *head = file_load_trips(argv, head_station);
            i = 0;
            selecionaDia(head, argv, head_station); //vai chamar outra vez a funcao para correr a funcao de novo
        }
        *head = remove_dia(dia, *head);     ///vai remover o dia selecionado

        //vai detetar se o utilizador quer remover mais dias da semana ou nao
        do {
            printf("Prima n para remover mais dias da semana ou prima outra tecla para continuar: ");
            fgets(str2, STR_MAX, stdin);
            ret2 = sscanf(str2, "%c", &teste);
        }while(ret2 != 1);
    }

}

/*
** Funcao responsavel pela remoção de nos da lista da viagem com base no dia a semana que queremos remover
** Remove todos as viagens com os dias iguais aos selecionados
*/
node_t* remove_dia(int dia, node_t *head)
{
    node_t * aux = NULL;    //ponteior auxiliar para ajuda na remocao

    //Remoção incial de elementos -  se o elemento a remover estiver na head, será removido
    //Esta parte apenas remove as cabeças falsas, sempre que a cabeça tenha um dia da semana que deve de ser removido
    while (head != NULL && head->viagem.dia_da_semana == dia && head->next != NULL)
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
        while (posicao->next != NULL && posicao->next->viagem.dia_da_semana == dia)
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

    //salvaguarda se a lista ficar com apenas um elemento
    if (head != NULL && head->viagem.dia_da_semana == dia && head->next == NULL)
    {
	    aux = head;
	    head = NULL;
	    free(aux);
	    return head;
	}

    posicao = head;
    return head;
}



/*
** Vai receber a latitude e converter para a respetiva posicao em pixeis
** Foi usada uma simples equacao em que se teve em conta as latitude dos extremos e o tamanho da janela em pixeis
*/
float convertLat(float latitude)
{
    //vai retornar a posicao dessa latitude em pixeis
    float pixeis = 0;
    pixeis = ((latitude - 42.376145))/(-0.0001376);
    return pixeis;
}

/*
** Vai receber a longitude e converter para a respetiva posicao em pixeis
** Foi usada uma simples equacao em que se teve em conta as latitude dos extremos e o tamanho da janela em pixeis
*/
float convertLong(float longitude)
{
    //vai retornar a posicao dessa longitude em pixeis
    float pixeis = 0;
    pixeis = ((longitude + 71.196210))/0.0001866;
    return pixeis;
}

/*
** Vai desenhar todas as estacoes no mapa como quadrados pretos
*/
void drawStations(station_t * head, SDL_Renderer * renderer)
{
    SDL_Color dark = { 44, 44, 44 };//Cor escura
    SDL_Rect rect;  //retangulo

    //vai percorrer todas as estacoes
    while(head != NULL)
    {
        rect.x = convertLong(head->longitude);
        rect.y = convertLat(head->latitude);
        rect.w = 5;
        rect.h = 5;

        //vai desenhar um quadrado para cada estacao
        SDL_SetRenderDrawColor(renderer, dark.r, dark.g, dark.b, dark.a );
        SDL_RenderFillRect( renderer, &rect);
        head = head->next;
    }
}


/*
** Indica no mapa, com um quadrado vermelho a posicao da estacao atual
*/
void marksTheStation (station_t *estacao_atual, SDL_Renderer * renderer)
{
        SDL_Color red = { 253, 55, 62 };//Cor vermelha
        SDL_Rect rect;

        //vai desenhar o quadrado vermelho na posicao da estacao atua a visualizar
        rect.x = convertLong(estacao_atual->longitude);
        rect.y = convertLat(estacao_atual->latitude);
        rect.w = 7;
        rect.h = 7;

        SDL_SetRenderDrawColor(renderer, red.r, red.g, red.b, red.a );
        SDL_RenderFillRect( renderer, &rect);
}

/*
** Vai calcular as rotas efetuadas - faz a distincao entre estacao de partida e de chegada
** Vai desenhar as linhas para traçar as rotas que têm a estacao escolhida como estacao de destino
** AS CORES SAO INDICATIVAS DAS AFLUENCIAS DAS ROTA POIS A LARGURA DA RETA IMPEDIA UMA BOA VISUALIZACAO NO MAPA
** Nota: poderiam ser usadas retas mais grossas usando o seguinte pseudo-codigo:
** for (i = 0; i < (numero total viagen nessa rota)/5; i++)
** Draw linha
*/
void traca_rotas(node_t *head_trips, station_t * head_stations, station_t * estacao_atual, SDL_Renderer * renderer, int flag, TTF_Font * font, rota_t *mais_popular)
{
    station_t * stationAux = head_stations; //cria um ponteiro auxiliar para percorrer a lista de estacoes

    //Variaveis auxiliares na procura de ROTAS
    node_t * aux_trips = head_trips;    //ponteiro auxiliar para percorrer a lista de viagens
    rota_t * rotas = NULL;              //ponteiro para rota que serve para apontar para a rota mais popular para uma dada estacao
    rota_t melhor_rota;                 //vai conter a melhor rota para uma dada estacao
    melhor_rota.num_viagens = 0;        //garante que o tipo melhor rota é iniciado com o numero de viagens a 0
    int i = 0;                          //posicao no array    - numero de rotas totais  - tamanho do array
    int j = 0;                          //auxiliar para percorrer arrays
    int rotaguardada = 0;               //essencial para detetar se uma rota já foi guardada ou nao

    //Vamos criar um array com estruturas do tipo rota - estas estrutras contêm um ponteiro para a estacao inicial, estacao final e o numero de viagens total
   while(stationAux != NULL)
   {
        //para cada estacao vai percorrer todas as viagens que comecaram na estacao escolhida pelo user e terminaram na estacao a correr pelo loop
        //e todas as estacoes que comecar na estacao definida pelo loop e acabaram na estacao definida pelo user
        //vai adicionar essas viagens a um array para posteriormente poderem ser contadas
        while (aux_trips != NULL)
        {
            //verifica se a viagem tem como estacao inicial a selecionada pelo utilizador e se a rota já foi guardada
            if (aux_trips->viagem.estacao_final == stationAux && aux_trips->viagem.estacao_inicial == estacao_atual && rotaguardada != 1)
            {
                //vai correr o loop que verifica se a rota já se encontra no array de rotas
                for (j = 0; j < i; j++)
                {
                    //se a rota já se encontrar no array de rotas, entao vamos incrementar o numero de viagens para essa rota
                    if(rotas[j].estacao_inicial == estacao_atual && rotas[j].estacao_final == stationAux)
                    {
                        rotas[j].num_viagens = rotas[j].num_viagens + 1;
                        rotaguardada = 1;
                    }
                }
                //se a rota ainda nao estivesse presente no array, alocamos memoria para ela e guardados os respetivos dados
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
                    rotas[i-1].estacao_inicial = estacao_atual;
                    rotas[i-1].estacao_final = stationAux;
                    rotas[i-1].num_viagens = 1;
                }
            }
            //verifica se a viagem tem como estacao final a selecionada pelo utilizador e se a rota já foi guardada o passo anterior (como estacao de partida, para nao haver repeticoes quando a estacao de
            //partida é igual à estacao de chegada)
            if (aux_trips->viagem.estacao_inicial == stationAux && aux_trips->viagem.estacao_final == estacao_atual && rotaguardada != 1)
            {
                //verifica se a rota está presente no array de rotas
                for (j = 0; j < i; j++)
                {
                    //se estiver vai incrementar o numero de viagens para essa rota
                    if(rotas[j].estacao_inicial == stationAux && rotas[j].estacao_final == estacao_atual)
                    {
                        rotas[j].num_viagens = rotas[j].num_viagens + 1;
                        rotaguardada = 1;
                    }
                }
                //se a rota nao estiver presente no array
                //vai alocar memoria e adicionar a rota ao array e preenche com os respetivos dados
                if (rotaguardada == 0)
                {
                    i++;
                    rotas = (rota_t *)realloc(rotas, sizeof(rota_t) * i);
                    if (rotas == NULL)
                    {
                        printf("nao foi possivel alocar memoria para rotas\n");
                        exit(EXIT_FAILURE);
                    }
                    rotas[i-1].estacao_inicial = stationAux;
                    rotas[i-1].estacao_final = estacao_atual;
                    rotas[i-1].num_viagens = 1;
                }
            }
            rotaguardada = 0;
            aux_trips = aux_trips->next;
        }
        aux_trips = head_trips;
        stationAux = stationAux->next;
   }
   //vamos percorrer o array obtido e traçar as linhas correspondentes
   for (j = 0; j < i; j++)
   {
        //vai definir a cor das linhas com base na afluencia da rota
        if(rotas[j].num_viagens < 5) {
            SDL_SetRenderDrawColor(renderer, 134, 200, 227, 50);     //azul - mesmo muito poucas viagens
        }else if(rotas[j].num_viagens >= 5 && rotas[j].num_viagens < 15) {
            SDL_SetRenderDrawColor(renderer, 47, 213, 102, 50);     //verde - muito poucas viagens
        } else if (rotas[j].num_viagens >= 15 && rotas[j].num_viagens < 30) {
            SDL_SetRenderDrawColor(renderer, 215, 239, 10, 50);     //verde amarelado - poucas viagens
        } else if (rotas[j].num_viagens >= 30 && rotas[j].num_viagens < 45) {
            SDL_SetRenderDrawColor(renderer, 242, 241, 53, 50);     //amarelo - medio viagens
        } else if (rotas[j].num_viagens >= 45 && rotas[j].num_viagens < 60) {
            SDL_SetRenderDrawColor(renderer, 239, 126, 45, 50);     //laranja - algumas viagens
        } else if(rotas[j].num_viagens >= 60 && rotas[j].num_viagens < 75) {
            SDL_SetRenderDrawColor(renderer, 186, 125, 121, 50);     //rosa-castanho - numero consideravel de viagens
        }else if (rotas[j].num_viagens >= 75 && rotas[j].num_viagens < 90) {
            SDL_SetRenderDrawColor(renderer, 248, 57, 61, 50);     //avermelhado - muitas viagens
        } else if (rotas[j].num_viagens >= 90) {
            SDL_SetRenderDrawColor(renderer, 129, 3, 10, 50);     //avermelhado - muitas viagens
        }
        //vai imprimir todas as rotas que tiveram como estacao incial a estacao atual - depende do que o utilizador quer ver no ecra
        if (flag == 1)
        {
            if (rotas[j].estacao_inicial == estacao_atual)
            {
                SDL_RenderDrawLine(renderer, convertLong(rotas[j].estacao_inicial->longitude),
                                     convertLat(rotas[j].estacao_inicial->latitude),
                                     convertLong(rotas[j].estacao_final->longitude),
                                     convertLat(rotas[j].estacao_final->latitude)); //x,y   x,y
            }
        //vai imprimir todas as rotas que tiveram como estacao final a estacao atual
        }
        else if (flag == 2)
        {
            if (rotas[j].estacao_final == estacao_atual)
            {
                SDL_RenderDrawLine(renderer, convertLong(rotas[j].estacao_inicial->longitude),
                                     convertLat(rotas[j].estacao_inicial->latitude),
                                     convertLong(rotas[j].estacao_final->longitude),
                                     convertLat(rotas[j].estacao_final->latitude)); //x,y   x,y
            }
        }
   }
	//vamos guardar a rota mais popular para depois indicar na sidebar
	 if (i != 0) // se o vetor de rotas nao estiver vazio
	 {
		   for(j = 0; j < i; j++){
	   	    if(rotas[j].num_viagens > melhor_rota.num_viagens)
       		{
            	melhor_rota.num_viagens = rotas[j].num_viagens;
            	melhor_rota.estacao_inicial = rotas[j].estacao_inicial;
            	melhor_rota.estacao_final = rotas[j].estacao_final;
       		}
        }
	} else {
	   	melhor_rota.num_viagens = 0;
      melhor_rota.estacao_inicial = NULL;
      melhor_rota.estacao_final = NULL;
	}


   (*mais_popular).num_viagens = melhor_rota.num_viagens;
   (*mais_popular).estacao_inicial = melhor_rota.estacao_inicial;
   (*mais_popular).estacao_final = melhor_rota.estacao_final;
   free(rotas);
}


/*
** Vamos imprimir na sidebar alguma informacoes relativamente à rota mais popular
*/
void melhor_rota_info(rota_t mais_popular, TTF_Font * font, SDL_Renderer * renderer)
{
   //vai dar print na sidebar das informacoes relativas à rota mais popular relativamente à estacao escolhida
   char instrucao[STR_MAX] = " ------ROTA MAIS POPULAR------";      //variaveis usadas para imprimir algum texto no ecrã
   char instrucao2[STR_MAX] = "ESTACAO INICIAL:";
   char instrucao3[STR_MAX] = "Latitude:";
   char instrucao4[STR_MAX] = "Longitude:";
   char instrucao6[STR_MAX] = "ESTACAO FINAL:";
   char instrucao8[STR_MAX] = "Numero de viagens: ";
   char longitude[10000]= {0};
   char latitude[STR_MAX]= {0};
   char num_viagens[STR_MAX]= {0};
   if (mais_popular.estacao_inicial != NULL && mais_popular.estacao_final != NULL)
   {
     sprintf(num_viagens, "%d", mais_popular.num_viagens );           //vai tranformar os numeros em texto para poder ser dado render no ecrã
     sprintf(longitude, "%0.6f", mais_popular.estacao_inicial->longitude );
    }
   int xPos = 5;
   int yPos = 370;
   SDL_Color dark = { 44, 44, 44 };//Cor escura

   //Vamos dar render das frases no ecrã

   if (mais_popular.estacao_inicial != NULL && mais_popular.estacao_final != NULL)
   {
    RenderText(xPos, yPos     , instrucao, font, &dark, renderer);
    RenderText(xPos, yPos + 20, instrucao2, font, &dark, renderer);
   RenderText(xPos, yPos + 40, mais_popular.estacao_inicial->full_name, font, &dark, renderer);

   //imprime a latitude e longitude da estacao inicial
   sprintf(latitude, "%0.6f", mais_popular.estacao_inicial->latitude );
   RenderText(xPos, yPos + 60, instrucao3, font, &dark, renderer);
   RenderText(xPos + 60, yPos + 60, latitude, font, &dark, renderer);
   sprintf(longitude, "%0.6f", mais_popular.estacao_inicial->longitude );
   RenderText(xPos, yPos + 80, instrucao4, font, &dark, renderer);
   RenderText(xPos + 60, yPos + 80, longitude, font, &dark, renderer);

   RenderText(xPos, yPos + 120, instrucao6, font, &dark, renderer);
   RenderText(xPos, yPos + 140, mais_popular.estacao_final->full_name, font, &dark, renderer);

   //Imprime a latitude e longitude da estacao final
   sprintf(latitude, "%0.6f", mais_popular.estacao_final->latitude );
   RenderText(xPos, yPos + 160, instrucao3, font, &dark, renderer);
   RenderText(xPos + 60, yPos + 160, latitude, font, &dark, renderer);
   sprintf(longitude, "%0.6f", mais_popular.estacao_final->longitude );
   RenderText(xPos, yPos + 180, instrucao4, font, &dark, renderer);
   RenderText(xPos + 60, yPos + 180, longitude, font, &dark, renderer);

   //vai imprimir o numero de viagens
   RenderText(xPos, yPos + 210, instrucao8, font, &dark, renderer);
   RenderText(xPos + 120, yPos + 210, num_viagens, font, &dark, renderer);
    }
}

/*
** Vai dar render de algumas instrucoes na sidebar
*/
void renderInstrucoes(TTF_Font * font, SDL_Renderer * renderer)
{
    int xPos = 5;
    int yPos = 155;

    SDL_Color dark = { 44, 44, 44 };//Cor escura
    char instrucao[] = "            INSTRUCOES";        //Frases que contém instrucoes parar imprimir no ecrã
    char instrucao1[] = "*Use a seta (->)para avancar para a";
    char instrucao3[] = "proxima estacao";

    char instrucao4[] = "*Utilize a seta para";
    char instrucao5[] = "cima/baixo para alternar";
    char instrucao6[] = "a estacao de partida/chegada";

    char instrucao7[] = "*Cores = afluencia de rotas";
    char instrucao8[] = "Azul -> menor";
    char instrucao9[] = "Vermelho -> maior";

    //Vamos dar render das frases no ecrã
    RenderText(xPos, yPos     , instrucao, font, &dark, renderer);
    RenderText(xPos, yPos + 20, instrucao1, font, &dark, renderer);

    RenderText(xPos, yPos + 35, instrucao3, font, &dark, renderer);
    RenderText(xPos, yPos + 65, instrucao4, font, &dark, renderer);
    RenderText(xPos, yPos + 80, instrucao5, font, &dark, renderer);
    RenderText(xPos, yPos + 95, instrucao6, font, &dark, renderer);

    RenderText(xPos, yPos + 125, instrucao7, font, &dark, renderer);
    RenderText(xPos, yPos + 140, instrucao8, font, &dark, renderer);
    RenderText(xPos, yPos + 155, instrucao9, font, &dark, renderer);
}

/*
** Imprime na sidebar a informacao se as rotas que estao a ser mostradas sao as que têm a estacao seleciona como destino ou partida
*/
void estacao_chegada_partida(TTF_Font * font, SDL_Renderer * renderer, int flag)
{
    SDL_Color dark = { 44, 44, 44 };//Cor escura
    char instrucao1[] = "->ESTACAO DE PARTIDA<-";   //variaveis auxiliar para dar o render
    char instrucao2[] = "->ESTACAO DE CHEGADA<-";

    if (flag  == 1)
    {
        RenderText(20, 340, instrucao1, font, &dark, renderer);
    }
    else if (flag == 2)
    {
        RenderText(20, 340, instrucao2, font, &dark, renderer);
    }
}

/*
** rota_prinicipal: 
** Vai imprimir com uma linha mais grossa e vermelha a rota com vais utilizadores
*/
void rota_principal(rota_t mais_popular, SDL_Renderer * renderer)
{
    int i = 0;
    SDL_SetRenderDrawColor(renderer, 255, 3, 10, 50);

    if (mais_popular.estacao_inicial != NULL && mais_popular.estacao_final != NULL)
    {
        for (i = 0; i <  20; i++ )
        {
            
            SDL_RenderDrawLine(renderer, convertLong(mais_popular.estacao_inicial->longitude)+(i/4),
                                     convertLat(mais_popular.estacao_inicial->latitude)+(i/4),
                                     convertLong(mais_popular.estacao_final->longitude)+(i/4),
                                     convertLat(mais_popular.estacao_final->latitude)+(i/4));
        }
    }
    //SDL_SetRenderDrawColor(renderer, 44, 44, 44, 50);
}
