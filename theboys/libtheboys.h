#include <stdio.h>
#include "fila.h"
#include "fprio.h"
#include "conjunto.h"

#define T_INICIO = 0
#define T_FIM_DO_MUNDO 525600
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
int cont_lef = 0;

////////////////////////////////// ENTIDADES ///////////////////////////////////

struct heroi 
{
    int heroi_id;
    int habilidades;
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

struct eventos 
{
    int tipo;
    int tempo;
    struct heroi *h;
    struct base *b;
    struct base *destino;
    struct mundo *w;
    struct missoes *m;
    struct fprio_t *lef;
};

//------------------------------------------------------------------------------

////////////////////////////////// EVENTOS /////////////////////////////////////

void *chega (int tempo, struct heroi *h, struct base *b, struct mundo *w, struct fprio_t *lef);

void *espera (int tempo, struct heroi *h, struct base *b, struct mundo *w, struct fprio_t *lef);

void *desiste (int tempo, struct heroi *h, struct base *b, struct mundo *w, struct fprio_t *lef);

void *avisa (int tempo, struct base *b, struct mundo *w, struct fprio_t *lef);

void *entra (int tempo, struct heroi *h, struct base *b, struct mundo *w, struct fprio_t *lef);

void *sai (int tempo, struct heroi *h, struct base *b, struct mundo *w, struct fprio_t *lef);

void *viaja (int tempo, struct heroi *h, struct base *b, struct base *destino, struct mundo *w, struct fprio_t *lef);

void *morre (int tempo, struct heroi *h, struct base *b, struct missao *m, struct mundo *w, struct fprio_t *lef);

void *missao (struct missao *m, int tempo, struct mundo *w, struct fprio_t *lef);

void *fim (int tempo, struct mundo *w, struct fprio_t *lef);

void *inicia_mundo(struct heroi *h, struct base *b, struct missao *m, struct mundo *w, struct eventos *evento, struct fprio_t *lef);