// TAD lista de números inteiros
// Carlos Maziero - DINF/UFPR, Out 2024
//
// Implementação do TAD - a completar
//
// Implementação com lista encadeada dupla não-circular

#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

// estrutura de um item da lista
struct item_t {
  int valor;
  struct item_t *ant;
  struct item_t *prox;
} ;

// estrutura de uma lista
struct lista_t {
  struct item_t *primeiro;
  struct item_t *ultimo;
  int num;
} ;

// Cria uma lista vazia.
// Retorno: ponteiro p/ a lista ou NULL em erro.
struct lista_t *lista_cria () {
 
  struct lista_t *lista = malloc(sizeof(struct lista_t));

  /* verifica se a lista é nula (inexistente) */
  if (lista == NULL)
    return NULL;

  /* atribui nulo para as posições e zero para a quantidade de elementos da lista, porque é uma lista vazia */
  lista->primeiro = NULL;
  lista->ultimo = NULL;
  lista->num = 0;
  
  return lista;

}

// Remove todos os itens da lista e libera a memória.
// Retorno: NULL.
struct lista_t *lista_destroi (struct lista_t *lst) {
  
  struct item_t *end;

  for (int i = 0; i < lst->num; i++)
    *end = lst->


}

