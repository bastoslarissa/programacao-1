#include <stdio.h>
#include <stdlib.h>
#include "entidades.h"

// inicialização do mundo virtual
#define T_INICIO 0
#define T_FIM_DO_MUNDO 525600
#define N_TAMANHO_MUNDO 20000
#define N_HABLIDADES 10
#define N_HEROIS (N_HABLIDADES * 5)
#define N_BASES (N_HEROIS / 5)
#define N_MISSOES (T_FIM_DO_MUNDO / 100)
#define N_COMPOSTOS_V (N_HABLIDADES * 3)

// inicialização de cada herói
void inicializa_herois (struct heroi_t *heroi);

// inicialização de cada base 
void inicializa_bases (struct base_t *base);

// inicialização de cada missão 
void inicializa_missoes (struct missao_t *missoes);