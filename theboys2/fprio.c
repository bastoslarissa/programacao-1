// TAD Fila de prioridades (FPRIO) genérica
// Implementação com lista encadeada simples

#include "fprio.h"
#include <stdio.h>
#include <stdlib.h>

// descreve um nodo da fila de prioridades
struct fpnodo_t
{
  void *item ;          // item associado ao nodo
  int   tipo ;          // tipo do item
  int   prio ;          // prioridade do item
  struct fpnodo_t *prox;    // próximo nodo
};

// descreve uma fila de prioridades
struct fprio_t
{
  struct fpnodo_t *prim ;   // primeiro nodo da fila
  int num ;         // número de itens na fila
} ;

struct fprio_t *fprio_cria () {

    struct fprio_t *fila = malloc (sizeof (struct fprio_t));

    if (!fila) 
        return NULL;

    fila -> num = 0;
    fila -> prim = NULL;

    return fila;
}

struct fprio_t *fprio_destroi (struct fprio_t *f) {

      if (!f)
        return NULL;

    struct fpnodo_t *nodo_aux = f -> prim;

    for (int i = 0; i < f -> num; i++) {
        f -> prim = nodo_aux -> prox;

        free (nodo_aux -> item);
        free (nodo_aux);

        nodo_aux = f -> prim;
    }

    free (f);

    return NULL;
}

int fprio_insere (struct fprio_t *f, void *item, int tipo, int prio) {

      if (!f || !item) 
        return -1;

    /* fila vazia */
    if (f -> num == 0) {
        struct fpnodo_t *nodo_novo = malloc (sizeof (struct fpnodo_t));

        nodo_novo -> item = item;
        nodo_novo -> prio = prio;
        nodo_novo -> prox = NULL;
        nodo_novo -> tipo = tipo;

        f -> num++;
        f -> prim = nodo_novo;
    }

    else {
        struct fpnodo_t *nodo_aux = f -> prim;

        /* verifica se o item esta na fila */
        for (int i = 0; i < f -> num; i++) {
            if (nodo_aux -> item == item && nodo_aux -> prio == prio) {
                return -1;
            }

            nodo_aux = nodo_aux -> prox;
        }
        
        nodo_aux = f -> prim;

        /* insere item no inicio da fila */
        if ((!nodo_aux -> prox && nodo_aux -> prio > prio) || nodo_aux -> prio > prio) {
            struct fpnodo_t *nodo_novo = malloc (sizeof (struct fpnodo_t));

            nodo_novo -> item = item;
            nodo_novo -> prio = prio;
            nodo_novo -> prox = f -> prim;
            nodo_novo -> tipo = tipo;

            f -> num++;
            f -> prim = nodo_novo;

            return f -> num;
        }

        while (nodo_aux -> prox && nodo_aux -> prox -> prio <= prio) {
            nodo_aux = nodo_aux -> prox;
        }

        /* insere no meio ou no final da fila */
        struct fpnodo_t *nodo_novo = malloc (sizeof (struct fpnodo_t));

        nodo_novo -> item = item;
        nodo_novo -> prio = prio;
        nodo_novo -> prox = nodo_aux -> prox;
        nodo_novo -> tipo = tipo;

        nodo_aux -> prox = nodo_novo;

        f -> num++;
    }

    return f -> num;
}

void *fprio_retira (struct fprio_t *f, int *tipo, int *prio) {

    if (!f || !tipo || !prio || f -> num == 0)
        return NULL;

    struct fpnodo_t *nodo = f -> prim;
    void *item = nodo -> item;

    *tipo = nodo -> tipo;
    *prio = nodo -> prio;

    f -> prim = nodo -> prox;
    f -> num--;

    free (nodo);

    return item;
}

int fprio_tamanho (struct fprio_t *f) {
    
   if (!f)
        return -1;

    return f -> num;
}

void fprio_imprime (struct fprio_t *f) {

    if (!f || f -> num == 0)
        return;

    struct fpnodo_t *nodo_aux = f -> prim;

    for (int i = 0; i < f -> num - 1; i++) {
        printf ("(%d %d) ", nodo_aux -> tipo, nodo_aux -> prio);

        nodo_aux = nodo_aux -> prox;
    }

    printf ("(%d %d)", nodo_aux -> tipo, nodo_aux -> prio);

}
