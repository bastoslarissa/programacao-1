#include <stdio.h>
#include <stdlib.h>
#include "conjunto.h"
#include "fila.h"
#include "fprio.h"

// inicialização do mundo virtual
#define T_INICIO 0
#define T_FIM_DO_MUNDO 5256
#define N_TAMANHO_MUNDO 1000
#define N_HABILIDADES 10
#define N_HEROIS (N_HABILIDADES * 5)
#define N_BASES (N_HEROIS / 5)
#define N_MISSOES (T_FIM_DO_MUNDO / 100)
#define N_COMPOSTOS_V (N_HABILIDADES * 3)

#define CHEGA 1
#define ESPERA 2
#define DESISTE 3
#define AVISA 4
#define ENTRA 5
#define SAI 6
#define VIAJA 7
#define MORRE 8
#define MISSAO 9
#define FIM 10

/* -----------------------------------------------------------------
                            ENTIDADES                               
   -----------------------------------------------------------------*/

struct heroi_t {

    int id;
    struct cjto_t *habilidades;
    int paciencia;
    int velocidade;
    int experiencia;
    int base;
};

struct coordenadas {

    int x;
    int y;
};

struct base_t {

    int id;
    int lotacao;
    struct cjto_t *presentes;
    struct fila_t *espera;
    struct coordenadas local;
};

struct missao_t {

    int id;
    struct cjto_t *habilidades;
    struct coordenadas local;
};

struct mundo_t {

    int NHerois;
    struct heroi_t *herois;   // vetor de heróis
    int NBases;
    struct base_t *bases;     // vetor de bases
    int NMissoes;
    struct missao_t *missoes;     // vetor de missoes
    int NHabilidades;
    int NCompostosV;
    int TamanhoMundo;    //coordenadas máximas do plano cartesiano que representa o mundo
    int relogio;
};

struct evento_t {

    int tempo;
    int tipo;
    struct heroi_t *heroi;
    struct base_t *base;
    struct missao_t *missao;
    
};

/* -----------------------------------------------------------------
                             FUNÇÕES                               
   -----------------------------------------------------------------*/
int aleat (int min, int max);

struct evento_t *cria_evento (int tempo, int tipo, struct heroi_t *heroi, struct base_t *base, struct missao_t *missao);

void inicializa_mundo (struct mundo_t *mundo);

void eventos_iniciais (struct mundo_t *mundo, struct fprio_t *lef);

void iniciar_o_mundo ();