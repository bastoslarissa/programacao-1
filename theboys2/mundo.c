#include <stdio.h>
#include <stdlib.h>
#include "conjunto.h"
#include "fila.h"
#include "fprio.h"
#include "mundo.h"


// Função auxiliar
// Gera um número aleatório entre min e max
int aleat (int min, int max) {

    int aleat = rand()%(max - min + 1) + min;

    return aleat;

}

// Função Auxiliar
// Gera um conjunto aleatório de habilidades para o herói
int gera_habilidades (int n_habilidades) {

    int *habilidades;

    habilidades = malloc(sizeof(n_habilidades));

    for (int i = 0; i < n_habilidades; i++) {

        habilidades[i] = aleat(0, N_HABLIDADES);
    }

    return *habilidades;
}


/* void inicializa_herois (struct heroi_t *heroi) {

    // aloca memória 
    heroi = malloc(sizeof(struct heroi_t) * N_HEROIS);

    // atribui o id
    for (int i = 0; i < (N_HEROIS - 1); i++) {
        heroi[i].id = i; 
    

        // atribui as outras características
        heroi[i].experiencia = 0;
        heroi[i].paciencia = aleat(0, 100);
        heroi[i].velocidade = aleat(50, 5000);
        heroi[i].habilidades = gera_habilidades(aleat(1, 3));
    }

}

void inicializa_bases (struct base_t *base) {

    // aloca memória 
    base = malloc(sizeof(struct base_t));

    // atribui o id 
    for (int i = 0; i < (N_MISSOES - 1); i++) {
        base[i].id = i;
    

        // atribui coordenadas
        base[i].local.x = aleat(0, N_TAMANHO_MUNDO - 1);
        base[i].local.y = aleat(0, N_TAMANHO_MUNDO - 1);
        
        // atribui as outras características
        base[i].lotacao = aleat(3, 10);
        base[i].presentes = cjto_cria(base[i].lotacao);
        base[i].espera = fila_cria();
    }
}  */

void inicializa_mundo (struct mundo_t mundo) {

    struct fprio_t *lef = fprio_cria;

    // inicializa o mundo
    mundo.NHerois = N_HEROIS;
    mundo.herois = malloc(sizeof(struct heroi_t) * N_HEROIS);
    mundo.NBases = N_BASES;
    mundo.bases = malloc(sizeof(struct base_t) * N_BASES);
    mundo.NMissoes = N_MISSOES;
    mundo.missoes = malloc(sizeof(struct missao_t) * N_MISSOES);
    mundo.NHabilidades = N_HABLIDADES;
    mundo.NCompostosV = N_COMPOSTOS_V;
    mundo.TamanhoMundo = N_TAMANHO_MUNDO;
    mundo.relogio = 0;

    // inicializa os heróia

}