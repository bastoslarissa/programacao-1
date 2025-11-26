// programa principal do projeto "The Boys - 2025/2"
// Autor: Larissa de Souza Bastos, GRR 20235088

#include <stdio.h>
#include "eventos.h"
#include <time.h>


// seus #defines vão aqui

// minimize o uso de variáveis globais

// programa principal
int main ()
{

    int relogio = 0; // inicializa o relógio

    srand(0); // inicializa a semente randomica

    struct mundo_t *mundo = malloc(sizeof(struct mundo_t)); // declaração do mundo

    // cria a Lista de Eventos Futuros (LEF)
    struct fprio_t *lef = fprio_cria();

    // inicializa o mundo e os eventos iniciais
    inicializa_mundo(mundo);
    eventos_iniciais(mundo, lef);

    // executa os eventos da fprio
    while (relogio < T_FIM_DO_MUNDO) {

    struct evento_t *evento_atual = fprio_retira(lef, &lef -> prim -> tipo, &lef -> prim -> prio);

    relogio = evento_atual -> tempo;

    if ( (evento_atual -> tipo) == CHEGA) {

        chega(&evento_atual -> tempo, evento_atual -> heroi, evento_atual -> base, lef);
    }

    else if ( (evento_atual -> tipo) == ESPERA) {

      espera(&evento_atual -> tempo, evento_atual -> heroi, evento_atual -> base, lef);
    }

    else if ( (evento_atual -> tipo) == DESISTE) {

      desiste(&evento_atual -> tempo, evento_atual -> heroi, evento_atual -> base, lef);
    }

    else if ( (evento_atual -> tipo) == AVISA) {

      avisa(&evento_atual -> tempo, evento_atual -> base, mundo, lef);
    }

    else if ( (evento_atual -> tipo) == ENTRA) {

      entra(&evento_atual -> tempo, evento_atual -> heroi, evento_atual -> base, lef);
    }

    else if ( (evento_atual -> tipo) == SAI) {

      sai(&evento_atual -> tempo, evento_atual -> heroi, evento_atual -> base, lef);
    }

     else if ( (evento_atual -> tipo) == VIAJA) {

      viaja(&evento_atual -> tempo, evento_atual -> heroi, evento_atual -> base, mundo, lef);
    } 
  }
   

  // iniciar o mundo

  // executar o laço de simulação

  // destruir o mundo

  return (0) ;

}

