#include "textmode.h"
#define LARGURA 1068
#define ALTURA  659

//——Graficos.h------

int main_graphics (node_t ** head_trip, station_t ** head_station, station_t ** tail_station, char* argv[]); //funcao principal que chama tudo do SDL
//funcoes essenciais ao uso do SDL
void abreJanela(SDL_Window **window, SDL_Renderer ** renderer);
void IniciaSDLTodo();
void InicializaFonts(TTF_Font ** font, TTF_Font ** small_font);
//Funcoes que dao render de imagens e texto no ecrã
int RenderText(int x, int y, const char *text, TTF_Font *_font, SDL_Color *_color, SDL_Renderer* _renderer);
void loadMapa(SDL_Surface ** surface_mapa);
void loadLogo(SDL_Surface ** surface_logo);
void unloadMapa(SDL_Surface ** surface_mapa);
void RederMapa(SDL_Surface * surface_mapa, SDL_Surface * surface_logo, SDL_Renderer * renderer);
void RenderNomeEstacao (SDL_Renderer * renderer,TTF_Font * font, station_t * estacao);

//Funcoes auxiliares no tratamento de dados exclusivamente usados na parte grafica
void selecionaDia(node_t ** head, char * argv[], station_t *head_station);
float convertLat(float latitude);
float convertLong(float longitude);

//remove o dia da semana
node_t* remove_dia(int dia, node_t *head);

//Marca as estacoes no mapa
void drawStations(station_t * head, SDL_Renderer * renderer);
void marksTheStation (station_t *estacao_atual, SDL_Renderer * renderer);

//Traça as linhas das rotas no mapa
void traca_rotas(node_t *head_trips, station_t * head_stations, station_t * estacao_atual, SDL_Renderer * renderer, int flag, TTF_Font * font, rota_t *mais_popular);

//Imprime no ecra as instrucoes para utilizacao do programa
void renderInstrucoes(TTF_Font * font, SDL_Renderer * renderer);

//Imprime algumas informacoes sobre a rota mais popular para cada estacao
void melhor_rota_info(rota_t mais_popular, TTF_Font * font, SDL_Renderer * renderer);

//Imprime no sdl se as rotas a mostrar no mata têm a estacao como de partida ou de chegada
void estacao_chegada_partida(TTF_Font * font, SDL_Renderer * renderer, int flag);

//Vai imprimir com uma linha mais grossa e vermelha a rota com vais utilizadores
void rota_principal(rota_t mais_popular, SDL_Renderer * renderer);

