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

    /* Verifica se a fila é inválida (vazia)*/
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

    /* verifica se a fila existe (se é válida) */
    if (!f)
        return NULL;
    
    /* variável auxiliar que recebe as insformações do nodo */
    struct fpnodo_t *aux;

    /* percorre os nodos da fila liberando a memória deles */
    for (int i = 0; i < f -> tamanho; i++) {
        aux = f -> primeiro;
        f -> primeiro = f -> primeiro -> prox;
        free(aux);
    }

    free(f);

    return NULL;
}

// Cria um nodo.
//Retorno: ponteiro para o nodo criado ou NULL se erro.
struct fpnodo_t *fpnodo_cria (void *item, int tipo, int prio, struct fpnodo_t *prox) {

    struct fpnodo_t *nodo = malloc(sizeof(struct fpnodo_t));

    /* verifica se o nodo é válido */
    if (nodo == NULL)
        return NULL;

    /* atribui nulo aos elementos do nodo */
    nodo -> prox = prox;
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
int fprio_insere (struct fprio_t *f, void *item, int tipo, int prio) {

    struct fpnodo_t *aux = f -> primeiro;

    /* verifica se o ponteiro a ser inserido já está na fila */
    for (int i = 0; i < f -> tamanho; i++) {

        if (aux -> item == item)
            return -1;
        
        aux = aux -> prox;
    }
    
    /* variável para contabilizar o auxiliar */
    struct fpnodo_t *aux_anterior = f -> primeiro;
    
    while (aux -> prio < prio) {
        aux_anterior = aux;
        aux = aux -> prox;
    }

    struct fpnodo_t *novo_nodo = fpnodo_cria(item, tipo, prio, aux_anterior -> prox);
    aux_anterior -> prox = novo_nodo;

    return f -> tamanho + 1;

}

// Retira o primeiro item da fila e o devolve; o tipo e a prioridade
// do item são devolvidos nos parâmetros "tipo" e "prio".
// Retorno: ponteiro para o item retirado ou NULL se fila vazia ou erro.
void *fprio_retira (struct fprio_t *f, int *tipo, int *prio) {

    if (!f)
        return NULL;

    struct fpnodo_t *aux;

    aux = f -> primeiro;
    *tipo = f -> primeiro -> tipo;
    *prio = f -> primeiro -> prio;
    f -> primeiro = f -> primeiro -> prox;

    return aux;

}

// Informa o número de itens na fila.
// Retorno: N >= 0 ou -1 se erro.
int fprio_tamanho (struct fprio_t *f) {

    if (f -> tamanho < 0)
        return -1;
    
    return f -> tamanho;

}

// Imprime o conteúdo da fila no formato "(tipo prio) (tipo prio) ..."
// Para cada item deve ser impresso seu tipo e sua prioridade, com um
// espaço entre valores, sem espaços antes ou depois e sem nova linha.
void fprio_imprime (struct fprio_t *f) {

    struct fpnodo_t *aux = f -> primeiro;

    for (int i = 1; i < f -> tamanho; i++) {
        printf("(%d %d) ", aux -> tipo, aux -> prio);
        aux = aux -> prox;
    }
}

