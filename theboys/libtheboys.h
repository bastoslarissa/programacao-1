#include <stdio.h>
#include "fila.h"
#include "fprio.h"
#include "conjunto.h"

#define T_INICIO = 0
#define T_FIM_DO_MUNDO 10
#define N_TAMANHO_MUNDO 20000
#define N_HABILIDADES 10
#define N_HEROIS (N_HABILIDADES * 5)
#define N_BASES (N_HEROIS / 5)
#define N_MISSOES (T_FIM_DO_MUNDO / 100)
/*----------------------------------------*/
#define TIPO_CHEGA 1
#define TIPO_ESPERA 2
#define TIPO_DESISTE 3
#define TIPO_AVISA 4 
#define TIPO_ENTRA 5
#define TIPO_SAI 6
#define TIPO_VIAJA 7
#define TIPO_MORRE 8
#define TIPO_MISSAO 9
#define TIPO_FIM 10

extern int N_COMPOSTOS_V;

////////////////////////////////// ENTIDADES ///////////////////////////////////

struct heroi 
{
    int heroi_id;
    struct cjto_t habilidades;
    int paciencia;
    int velocidade;
    int experiencia;
    int base;
    int vivo;
};

struct coordenadas
{
    int x;
    int y;
};

struct base 
{
    int base_id;
    int lotacao;
    struct cjto_t *presentes;
    struct fila_t *espera;
    struct coordenadas local;
    int cont_espera;
};

struct missao 
{
    int missao_id;
    struct cjto_t *habilidades;
    struct coordenadas local;
    int tentativas;
    int *cont_missoes;
};

struct eventos 
{
    int tipo;
    int tempo;
    struct heroi *h;
    struct base *b;
    struct base *destino;
    struct mundo *w;
    struct missao *m;
    struct fprio_t *lef;
};

struct mundo 
{
    int NHerois;
    struct heroi *herois;
    int NBases;
    struct base *bases;
    int NMissoes;
    struct missao *missoes;
    int NHabilidades;
    int NCompostosV;
    struct coordenadas TamanhoMundo;
    int Relogio;
    struct eventos evento;
};

//------------------------------------------------------------------------------

////////////////////////////////// EVENTOS /////////////////////////////////////

void *chega (int tempo, struct eventos *evento);

void *espera (int tempo, struct eventos *evento);

void *desiste (int tempo, struct eventos *evento);

void *avisa (int tempo, struct eventos *evento);

void *entra (int tempo, struct eventos *evento);

void *sai (int tempo, struct eventos *evento);

void *viaja (int tempo, struct eventos *evento);

void *morre (int tempo, struct eventos *evento);

void *missao (int tempo, struct eventos *evento);

void *fim (int tempo, struct eventos *evento);

void *inicia_mundo(struct mundo *w, struct fprio_t *lef);