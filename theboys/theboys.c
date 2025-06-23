// programa principal do projeto "The Boys - 2024/2"
// Autor: Larissa de Souza Bastos, GRR 20235088

#include <stdio.h>
#include <stdlib.h>
#include "conjunto.h"
#include "fila.h"
#include "fprio.h"
#include "libtheboys.h"

// variável global
int N_COMPOSTOS_V = (N_HABILIDADES * 3);


// programa principal
int main ()
{
  // declaração de variáveis 
  struct heroi h[N_HEROIS];
  struct base b[N_BASES];
  struct missao m[N_MISSOES];
  struct mundo *w;

  // iniciar o mundo

  /* inicialização da Lista de Eventos Futuros */
  struct fprio_t *lef = fprio_cria();

  /* inicialização do mundo */
  inicia_mundo;

  // executar o laço de simulação


  // destruir o mundo

  return (0) ;
}

