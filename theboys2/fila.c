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

    return f;
}

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

struct fila_nodo_t *cria_nodo (void *item) {

    struct fila_nodo_t *nodo = malloc(sizeof(struct fila_nodo_t));

    // verificação
    if (!nodo)
        return NULL;

    nodo -> item = item;
    nodo -> prox = NULL;   

    return nodo;
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

    struct fila_nodo_t *aux;    // variável auxiliar
    struct fila_nodo_t *novo_nodo = cria_nodo(item);     // cria novo nodo a ser inserido


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

        f -> prim = novo_nodo;
        f -> fim = novo_nodo;
        (f -> num)++;
        printf("inseriu no inicio\n");
    }

    // caso: insere no fim da fila
    else if (f -> num != 0) {

        f -> fim -> prox = novo_nodo;
        f -> fim = novo_nodo;
        (f -> num)++;
        printf("inseriu no final\n");
    }

    return f -> num;
}

// Retira o primeiro item da fila e o devolve
// Retorno: ponteiro para o item retirado ou NULL se fila vazia ou erro.
int *fila_retira (struct fila_t *f) {

    //verificação
    if (!f || f -> num == 0)
        return NULL;

    struct fila_nodo_t *aux = f -> prim -> item;

    f -> prim = f -> prim -> prox;
    (f -> num)--;

    printf("item retirado\n");

    return aux -> item;
}

int fila_tamanho (struct fila_t *f) {

    // verificação
    if (!f)
        return -1;

    return f -> num;

}

void fila_imprime (struct fila_t *f) {

    // verificação
    if (!f || (f -> num) == 0)
        printf ("fila vazia");

    struct fila_nodo_t *aux = f -> prim;

    if ((f -> num) != 0) {

        for (int i = 0; i < f -> num; i++) {
            int *item = aux -> item;
            printf("%d", *(int *) item);
            aux = aux -> prox;

            if (i < ((f -> num) - 1))
                printf(" ");
        }
    }
}
 