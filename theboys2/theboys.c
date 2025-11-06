// programa principal do projeto "The Boys - 2025/2"
// Autor: Larissa de Souza Bastos, GRR 20235088

#include "fila.h"
#include <stdio.h>

// seus #defines vão aqui

// minimize o uso de variáveis globais

// programa principal
int main ()
{

  struct fila_t *f;
  int *item, *item2, *item3;
  int x = 10, y = 20, z = 30;
  item = &x;
  item2 = &y;
  item3 = &z;

  f = fila_cria();

  fila_insere(f, item);
  fila_insere(f, item2);
  fila_insere(f, item3);

  fila_retira(f);

  int tam = fila_tamanho(f);

  printf("%d\n", tam);

 /*  fila_imprime(f); */

  // iniciar o mundo

  // executar o laço de simulação

  // destruir o mundo

  return (0) ;
}

