// programa principal do projeto "The Boys - 2025/2"
// Autor: Larissa de Souza Bastos, GRR 20235088

#include "fila.h"

// seus #defines vão aqui

// minimize o uso de variáveis globais

// programa principal
int main ()
{

  struct fila_t *f;
  int *item;
  int x = 10;
  item = &x;

  f = fila_cria();

  f  = fila_destroi(f);

  fila_insere(f, item);

  fila_retira(f);

  // iniciar o mundo

  // executar o laço de simulação

  // destruir o mundo

  return (0) ;
}

