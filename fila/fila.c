#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

// Cria uma fila vazia.
// Retorno: ponteiro para a fila criada ou NULL se erro.
struct fila_t *fila_cria () {

    struct fila_t *f = malloc(sizeof(struct fila_t));

    /* verifica se a fila é válida */
    if (f == NULL)
        return NULL;

    /* atribui valores vazios aos elementos da fila */
    f -> prim = NULL;
    f -> fim = NULL;
    f -> num = 0; 
    
    return f;
}

// Libera todas as estruturas de dados da fila, inclusive os itens.
// Retorno: NULL.
struct fila_t *fila_destroi (struct fila_t *f) {

    /* verifica se a fila é válida */
    if (f == NULL || f -> num == 0)
        return NULL;

    /* percorre a fila liberando os nodos */
    for (int i = 0; i < f -> num; i++) {
        struct fila_nodo_t *aux = f -> prim;
        f -> prim = f -> prim -> prox;
        free(aux);
        f -> num--;

    }

    /* libera memória alocada para a fila */
    free(f);

    return NULL;

}

// Cria um nodo vazio.
//Retorno: ponteiro para o nodo criado ou NULL se erro.
struct fila_nodo_t *nodo_cria (void *item) {

    struct fila_nodo_t *nodo = malloc(sizeof(struct fila_nodo_t));

    /* verifica se o nodo é válido */
    if (nodo == NULL) 
        return NULL;

    /* atribui valores aos elementos do nodo */
    nodo -> prox = NULL;
    nodo -> item = item;

    return nodo;
}

// Insere o item na fila
// Inserir duas vezes o mesmo item (o mesmo ponteiro) é um erro.
// Retorno: número de itens na fila após a operação ou -1 se erro.
int fila_insere (struct fila_t *f, void *item) {

    /* verifica se a fila é válida */
    if (!f || !item)
        return -1;

    struct fila_nodo_t *aux = f -> prim;

    /* cria um novo nodo */
    struct fila_nodo_t *novo_nodo = nodo_cria(item);
        
        if (novo_nodo == NULL)
            return -1;

    /*verifica se a fila é vazia, se sim, insere na primeira posição */
    if (f -> num == 0) {
        f -> prim = novo_nodo;
        f -> fim = novo_nodo;
    }
    else {
        /* percorre a fila para checar se o item a ser inserido já está na fila */
        for (int i = 0; i < f -> num; i++) {

            if (aux -> item == item)
                return -1;
        }

        /* insere o novo item no fim da fila */
        f -> fim -> prox = novo_nodo;
        f -> fim = novo_nodo; 

    }

        return f -> num++;

}

// Retira o primeiro item da fila e o devolve
// Retorno: ponteiro para o item retirado ou NULL se fila vazia ou erro.
void *fila_retira (struct fila_t *f) {

    /* verifica se a fila é válida */
    if (f == NULL)
        return NULL;

    struct fila_nodo_t *aux = f -> prim;

    /* salva os dados do item a ser retirado */
    void *item = aux -> item;

    /* retira o primeiro item da fila */
    f -> prim = f -> prim -> prox;
    free(aux);
    f -> num--;

    return item;

}

// Informa o número de itens na fila.
// Retorno: N >= 0 ou -1 se erro.
int fila_tamanho (struct fila_t *f) {

    /* verifica se a fila é válida */
    if (f == NULL || f -> num < 0)
        return -1;
    
    /* retorna o número de itens da fila*/
    return f -> num;
    
}

// Imprime o conteúdo da fila 
void fila_imprime (struct fila_t *f) {

    /* verifica se a fila é válida */
    if(f == NULL || f -> num == 0) {
        printf("Fila vazia");
        return;
    }

    struct fila_nodo_t *aux = f -> prim;
    void *item = aux -> item;

    /* percorre a fila imprimindo os nodos */
    for (int i = 0; i < f -> num; i++) {
        item = aux -> item;
        printf ("(%d) ", *(int *) item);
        aux = aux -> prox;
    }
     
}
