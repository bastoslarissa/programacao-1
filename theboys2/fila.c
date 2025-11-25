#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

// Cria uma fila vazia.
// Retorno: ponteiro para a fila criada ou NULL se erro.
struct fila_t *fila_cria () {

    struct fila_t *f = malloc(sizeof(struct fila_t));

    // verificação
    if (!f)
        return NULL;
    
    f -> prim = NULL;
    f -> ult = NULL;
    f -> num = 0;

    return f;
}

// Libera todas as estruturas de dados da fila, inclusive os itens.
// Retorno: NULL.
struct fila_t *fila_destroi (struct fila_t *f) {

    // verficação
    if (!f)
        return NULL;

    for (int i = 0; i < f -> num; i++) {
        struct fila_nodo_t *aux = f -> prim;
        f -> prim = f -> prim -> prox;
        free(aux); 
    }

    printf("fila destruida\n");

    return NULL;
} 

// Cria um nodo. 
// Retorno: ponteiro para o nodo criado ou NULL.
struct fila_nodo_t *cria_nodo (int item) {

    struct fila_nodo_t *nodo = malloc(sizeof(struct fila_nodo_t));

    // verificação
    if (!nodo)
        return NULL;

    nodo -> item = item;
    nodo -> prox = NULL;   

    return nodo;
}

// Insere um item no final da fila (politica FIFO).
// Retorno: 1 se tiver sucesso ou 0 se falhar.
int fila_insere (struct fila_t *f, int item) {

    // verificação
    if (!f || !item) {
        return 0;
    }

    struct fila_nodo_t *novo_nodo = cria_nodo(item);     // cria novo nodo a ser inserido


    // insere o item no fim da fila
    if (f -> num == 0) {

        f -> prim = novo_nodo;
        f -> ult = novo_nodo;

        (f -> num)++;   // incrementa a quantidade de elementos da fila
    }

    else if (f -> num != 0) {

        f -> ult -> prox = novo_nodo;
        f -> ult = novo_nodo;

        (f -> num)++;   // incrementa a quantidade de elementos da fila
    }

    return 1;
}

// Retira o primeiro item da fila e o devolve
// Retorno: ponteiro para o item retirado ou NULL se fila vazia ou erro.
int fila_retira (struct fila_t *f, int *item) {

    //verificação
    if (!f || f -> num == 0)
        return 0;

    int *aux = item;

    f -> prim = f -> prim -> prox;
    (f -> num)--;

    printf("item retirado\n");

    return *aux;
}   

// Informa o número de itens na fila.
// Retorno: N >= 0 ou -1 se erro.
int fila_tamanho (struct fila_t *f) {

    // verificação
    if (!f)
        return -1;

    return f -> num;

}

// Imprime o conteúdo da fila 
void fila_imprime (struct fila_t *f) {

    // verificação
    if (!f || (f -> num) == 0)
        printf ("fila vazia");

    struct fila_nodo_t *aux = f -> prim;

    if ((f -> num) != 0) {

        for (int i = 0; i < f -> num; i++) {
            int item = aux -> item;
            printf("%d", item);
            aux = aux -> prox;

            if (i < ((f -> num) - 1))
                printf(" ");
        }
    }
}
 