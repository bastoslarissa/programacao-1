// programa principal do projeto "The Boys - 2024/2"
// Autor: Larissa de Souza Bastos, GRR 20235088

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
  struct mundo w;
  int relogio;

  srand(time(NULL));

  /* inicialização da Lista de Eventos Futuros */
  struct fprio_t *lef = fprio_cria();

  /* inicialização do mundo */
  inicia_mundo(&w, lef);

  /* laço de simulação */

  relogio = 0;

  while (relogio != T_FIM_DO_MUNDO) { 

      struct eventos *evento_atual = fprio_retira(lef, &lef -> prim -> tipo, &lef -> prim -> prio);
      relogio = evento_atual->tempo;

      if (evento_atual -> tipo == TIPO_CHEGA) 
      chega(evento_atual->tempo, evento_atual);

      else if (evento_atual -> tipo == TIPO_ESPERA)
        espera(evento_atual -> tempo, evento_atual);

      else if (evento_atual -> tipo == TIPO_DESISTE)
        desiste(evento_atual -> tempo, evento_atual);

      else if (evento_atual -> tipo == TIPO_AVISA)
        avisa(evento_atual -> tempo, evento_atual);

      else if (evento_atual -> tipo == TIPO_ENTRA)
        entra(evento_atual -> tempo, evento_atual);

      else if (evento_atual -> tipo == TIPO_SAI)
        sai(evento_atual -> tempo, evento_atual);

      else if (evento_atual -> tipo == TIPO_VIAJA)
        viaja(evento_atual -> tempo, evento_atual);

      else if (evento_atual -> tipo == TIPO_MORRE)
        morre(evento_atual -> tempo, evento_atual);

      else if (evento_atual -> tipo == TIPO_MISSAO)
        missao(evento_atual -> tempo, evento_atual);

      else if (evento_atual -> tipo == TIPO_FIM) 
        fim(evento_atual -> tempo, evento_atual); // destrói o mundo
       
  }
    

  return (0) ;
}



