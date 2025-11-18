#include <stdio.h>
#include <stdlib.h>
#include "conjunto.h"
#include "fila.h"
#include "fprio.h"
#include "mundo.h" 

/* Função auxiliar
* Gera um número aleatório entre min e max */
int aleat (int min, int max) {

    int aleat = rand()%(max - min + 1) + min;

    return aleat;

}


void inicializa_mundo (struct mundo_t *mundo) {

    // inicializa o mundo
    mundo -> NHerois = N_HEROIS;
    mundo -> NBases = N_BASES;
    mundo -> NMissoes = N_MISSOES;
    mundo -> NHabilidades = N_HABLIDADES;
    mundo -> NCompostosV = N_COMPOSTOS_V;
    mundo -> TamanhoMundo = N_TAMANHO_MUNDO;
    mundo -> relogio = 0;

    // inicializa os heróis
    mundo -> herois = malloc(sizeof(struct heroi_t) * N_HEROIS);

    for (int i = 0; i < N_HEROIS; i++) {

        mundo -> herois[i].id = i;
        mundo -> herois[i].experiencia = 0;
        mundo -> herois[i].paciencia = aleat(0, 100);   // nº aleatório entre 0 e 100
        mundo -> herois[i].velocidade = aleat(50, 5000);    // nº aleatório entre 50 e 5000 

        mundo -> herois[i].habilidades = cjto_aleat(aleat(1, 3), N_HABLIDADES);     // conjunto aleatório de [1...3] habilidades distintas
        
    }

    // inicializa as bases
    mundo -> bases = malloc(sizeof(struct base_t) * N_BASES);

    for (int i = 0; i < N_BASES; i++) {

        mundo -> bases[i].id = i;
        mundo -> bases[i].local.x = aleat(0, N_TAMANHO_MUNDO - 1);  // coordenada x aleatória 
        mundo -> bases[i].local.y = aleat(0, N_TAMANHO_MUNDO - 1);  // coordenada y aleatória 
        mundo -> bases[i].lotacao = aleat(3, 10);   // nº aleatório entre 3 e 10
        mundo -> bases[i].presentes = cjto_cria(mundo -> bases[i].lotacao);     // conjunto com capacidade da lotação aleatória gerada acima
        mundo -> bases[i].espera = fila_cria();     // fila vazia

        printf("base %d: id: %d\nlocal: (%d, %d)\nlotação: %d\n", i, mundo->bases[i].local.x,
        mundo->bases[i].local.y, mundo->bases[i].lotacao, cjto_card(mundo->bases[i].presentes));

        
    }

    // inicializa as missões 
    mundo -> missoes = malloc(sizeof(struct missao_t) * N_MISSOES);
    
    for (int i = 0; i < N_MISSOES; i++) {

        mundo -> missoes[i].id = i;
        mundo -> missoes[i].local.x = aleat(0, N_TAMANHO_MUNDO - 1);    // coordenada x aleatória 
        mundo -> missoes[i].local.y = aleat(0, N_TAMANHO_MUNDO - 1);    // coordenada y aleatória

        mundo -> missoes[i].habilidades = cjto_aleat(aleat(6, 10), N_HABLIDADES);  // conjunto com capacidade aleatória
    }

}


/* void eventos_iniciais (struct mundo_t *mundo) {

    struct fprio_t *lef = fprio_cria();

    // eventos iniciais : heróis
    for (int i = 0; i < N_HEROIS; i++) {

        mundo -> herois -> base = aleat(0, N_BASES);
        int tempo_heroi = aleat(0, 4320);   // 4.320 minutos = 3 dias;

        // insere na LEF o evento CHEGA 
        fprio_insere(lef, NULL, CHEGA, tempo_heroi);
    }

    // eventos iniciais: bases

} */

