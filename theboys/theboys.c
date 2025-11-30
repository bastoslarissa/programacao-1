// programa principal do projeto "The Boys - 2025/2"
// Autor: Larissa de Souza Bastos, GRR 20235088

#include <stdio.h>
#include "eventos.h"

// programa principal
int main () {
    
    struct mundo_t *mundo = malloc(sizeof(struct mundo_t)); // declaração do mundo

    // cria a Lista de Eventos Futuros (LEF)
    struct fprio_t *lef = fprio_cria();

    iniciar_o_mundo(mundo, lef);

    executar_o_laco_de_simulacao(mundo, lef);

    destruir_o_mundo(mundo, lef);

  return (0) ;

}

