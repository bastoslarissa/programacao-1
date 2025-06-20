// TAD Fila de prioridades (FPRIO) genérica
// Carlos Maziero, DINF/UFPR, Out 2024
// Implementação com lista encadeada simples

#include <stdio.h>
#include <stdlib.h>
#include "fprio.h"

// descreve um nodo da fila de prioridades
struct fpnodo_t {
    struct fpnodo_t *prox;
    void *item;
    int tipo;
    int prio;
} ;

// descreve uma fila de prioridades
struct fprio_t {
    struct fpnodo_t *primeiro;
    struct fpnodo_t *ultimo;
    int tamanho;
} ;

// Cria uma fila vazia.
// Retorno: ponteiro para a fila criada ou NULL se erro.
struct fprio_t *fprio_cria () {

    struct fprio_t *fila = malloc(sizeof(struct fprio_t));

    /* Verifica se a fila é válida */
    if (fila == NULL)
        return NULL;

    /* atribui nulo aos elementos da fila alocada */
    fila -> primeiro = NULL;
    fila -> ultimo = NULL;
    fila -> tamanho = 0;

    return fila;
}

// Libera todas as estruturas de dados da fila, inclusive os itens.
// Retorno: NULL.
struct fprio_t *fprio_destroi (struct fprio_t *f) {

    /* verifica se a fila é válida */
    if (f == NULL || f -> tamanho == 0)
        return NULL;
    

    /* percorre a fila liberando a memória alocada para os nodos */
    for (int i = 0; i < f -> tamanho; i++) {
        struct fpnodo_t *aux = f -> primeiro;
        f -> primeiro = f -> primeiro -> prox;
        free(aux);
        f -> tamanho--;

    }

    /* libera a memória alocada para a fila */
    free(f);

    return NULL;
}

// Cria um nodo vazio.
//Retorno: ponteiro para o nodo criado ou NULL se erro.
struct fpnodo_t *fpnodo_cria (void *item, int tipo, int prio) {

    struct fpnodo_t *nodo = malloc(sizeof(struct fpnodo_t));

    /* verifica se o nodo é válido */
    if (nodo == NULL) 
        return NULL;

    /* atribui valores aos elementos do nodo */
    nodo -> prox = NULL;
    nodo -> item = item;
    nodo -> tipo = tipo;
    nodo -> prio = prio;

    return nodo;
}

// Insere o item na fila, mantendo-a ordenada por prioridades crescentes.
// Itens com a mesma prioridade devem respeitar a politica FIFO (retirar
// na ordem em que inseriu).
// Inserir duas vezes o mesmo item (o mesmo ponteiro) é um erro.
// Retorno: número de itens na fila após a operação ou -1 se erro.
int fprio_insere(struct fprio_t *f, void *item, int tipo, int prio) {

    /* verifica se a fprio, o novo nodo e o item passados são válidos */
    if (f == NULL || item == NULL) 
        return -1;  

    struct fpnodo_t *aux = f -> primeiro;

    /* cria um novo nodo */
    struct fpnodo_t *novo_nodo = fpnodo_cria(item, tipo, prio);
        
        if (novo_nodo == NULL)
            return -1;

    /* verifica se a fprio é vazia, se sim, insere o novo item na primeira posição */
    if (f -> tamanho == 0) {
        f -> primeiro = novo_nodo;
        f -> ultimo = novo_nodo;
    }
    else {
        /* percorre a fprio para checar se o item a ser inserido já está na fila */
        for (int i = 0; i < f -> tamanho; i++) {

            if (aux -> item == item)
                return -1;
        }

            /* insere o novo item na primeira posição se a prioridade dele for maior */
            if (f -> primeiro -> prio > prio) {
                novo_nodo -> prox = f -> primeiro;
                f -> primeiro = novo_nodo; 
            }

            else {
            /* insere o novo item na fprio com base na prioridade dele */
            struct fpnodo_t *aux_2 = f -> primeiro;

            while (aux_2 -> prox && (aux_2 -> prox -> prio < prio || (aux_2 -> prox -> prio == prio && aux_2 -> prox -> tipo != tipo))){
                aux_2 = aux_2 -> prox;
            }

            novo_nodo -> prox = aux_2 -> prox;
            aux_2 -> prox = novo_nodo;
            }
    }

        f -> tamanho++;

        return f -> tamanho;
}

// Retira o primeiro item da fila e o devolve; o tipo e a prioridade
// do item são devolvidos nos parâmetros "tipo" e "prio".
// Retorno: ponteiro para o item retirado ou NULL se fila vazia ou erro.
void *fprio_retira (struct fprio_t *f, int *tipo, int *prio) {

    /* verifica se a fprio é válida */
    if (!f || !tipo || !prio)
        return NULL;

    struct fpnodo_t *aux = f -> primeiro;

    /* salva os dados do item a ser retirado */
    void *item = aux -> item; 
    *tipo = f -> primeiro -> tipo;
    *prio = f -> primeiro -> prio;

    /* retira o primeiro item da fprio */
    f -> primeiro = aux -> prox;
    f -> tamanho--;

    /* libera a memória */
    free(aux);

    return item;

}

// Informa o número de itens na fila.
// Retorno: N >= 0 ou -1 se erro.
int fprio_tamanho (struct fprio_t *f) {

    /* verifica se a fprio é válida */
    if (f == NULL || f -> tamanho < 0)
        return -1;
    
        /* retorna o número de itens da fprio */
    return f -> tamanho;

}

// Imprime o conteúdo da fila no formato "(tipo prio) (tipo prio) ..."
// Para cada item deve ser impresso seu tipo e sua prioridade, com um
// espaço entre valores, sem espaços antes ou depois e sem nova linha.
void fprio_imprime(struct fprio_t *f) {

    /* verifica se a fila é válida */
    if ( f -> tamanho == 0 || !f -> primeiro) 
        return;  

    struct fpnodo_t *aux = f -> primeiro;
    int primeiro = 1;

    while (aux) {    
        if (!primeiro) 
            printf(" ");
            
        printf("(%d %d)", aux -> tipo, aux -> prio);
        primeiro = 0;
        aux = aux -> prox;
    }
}

