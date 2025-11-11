// programa principal do projeto "The Boys - 2025/2"
// Autor: Larissa de Souza Bastos, GRR 20235088

#include "fila.h"
#include <stdio.h>
#include "iniciamundo.h"
#include "conjunto.h"

// seus #defines vão aqui

// minimize o uso de variáveis globais


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


void inicializa_herois (struct heroi_t *heroi) {

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
} 

// programa principal
int main ()
{

    struct heroi_t *heroi;
    struct base_t *base;

    inicializa_herois(heroi);
    inicializa_bases(base);

  // iniciar o mundo

  // executar o laço de simulação

  // destruir o mundo

  return (0) ;
}

