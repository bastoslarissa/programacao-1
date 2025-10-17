#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

/* ------------------- Nao altere estas structs ------------------------- */
struct nodo {
    int chave;
    struct nodo *prox;
};

struct lista {
    struct nodo *ini;
    struct nodo *ptr; /* ponteiro para algum nodo da lista (iterador) */
    int tamanho;

};
/* ---------------------------------------------------------------------- */

struct lista *lista_cria () {

    struct lista *list = malloc(sizeof(struct lista));

    if (!list)
        return NULL;

    list -> ini = NULL;
    list -> ptr = NULL;
    list -> tamanho = 0;
    
    return list; 
}

void lista_destroi (struct lista **lista) {

    struct nodo *aux;

    for (int i = 0; i < (**lista).tamanho; i++) {
        aux = (**lista).ini;
        (**lista).ini = (**lista).ini -> prox;
        free (aux);
    }

}

int lista_insere_inicio (struct lista *lista, int chave) {

    if (!lista)
        return NULL;

    lista -> ini = chave;

    if (lista -> ini == chave) 
        return 1;
    else 
        return 0;
}

/* int lista_insere_fim (struct lista *lista, int chave){
}

int lista_insere_ordenado (struct lista *lista, int chave){
}

int lista_remove_inicio (struct lista *lista, int *chave){
}

int lista_remove_fim (struct lista *lista, int *chave){
}

int lista_remove_ordenado (struct lista *lista, int chave){
}

int lista_vazia (struct lista *lista){
}

int lista_tamanho (struct lista *lista){
}

int lista_pertence (struct lista *lista, int chave){
}

void lista_inicia_iterador (struct lista *lista){
}

int lista_incrementa_iterador (struct lista *lista, int *chave){
} */
