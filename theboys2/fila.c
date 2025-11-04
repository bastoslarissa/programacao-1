#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

struct fila_t *fila_cria () {

    struct fila_t *f = malloc(sizeof(struct fila_t));

    // verificação
    if (!f)
        return NULL;
    
    f -> prim = NULL;
    f -> fim = NULL;
    f -> num = 0;

    printf("fila criada \n");

    return f;
}

struct fila_t *fila_destroi (struct fila_t *f) {

    // verficiação
    if (!f)
        return NULL;

    struct fila_nodo_t *aux;

    for (int i = 0; i < f -> num; i++) {
        aux = f -> prim;
        f -> prim = f -> prim -> prox;
        free(aux);
    }

    printf("fila destruida\n");

    return NULL;
}

// Insere o item na fila
// Inserir duas vezes o mesmo item (o mesmo ponteiro) é um erro.
// Retorno: número de itens na fila após a operação ou -1 se erro.
int fila_insere (struct fila_t *f, void *item) {

    // verificação
    if (!f || !item) {
        printf("deu erro\n");
        return -1;
    }

    struct fila_nodo_t *aux;

    // caso: item igual
    for (int i = 0; i < f -> num; i++) {
        aux = f -> prim;

        if (aux -> item == item) {
            printf("item igual\n");
            return -1;
        }
        else
            aux = f -> prim -> prox; 
    }   

    // caso: insere na primeira posição
    if (f -> num == 0) {

        f -> prim -> item = item;
        f -> fim -> item = item;
        (f -> num)++;
        printf("inseriu no inicio\n");
    }

    // caso: insere no fim da fila
    if (f -> num > 0) {

        f -> fim -> prox -> item = item;
        f -> fim = f -> fim -> prox;
        (f -> num)++;
        printf("inseriu no final\n");
    }

    return f -> num;
}

// Retira o primeiro item da fila e o devolve
// Retorno: ponteiro para o item retirado ou NULL se fila vazia ou erro.
void *fila_retira (struct fila_t *f) {

    //verificação
    if (!f || f -> num == 0)
        return NULL;

    struct fila_nodo_t *aux = f -> prim -> item;

    f -> prim = f -> prim -> prox;

    printf("item retirado");

    return aux -> item;
}