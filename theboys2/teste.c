#include <stdio.h>
#include "iniciamundo.h"
#include "conjunto.h"
#include "entidades.h"

int aleat (int min, int max) {

    int aleat = rand()%(max - min + 1) + min;

    return aleat;

}
void inicializa_herois (struct heroi_t *heroi) {

    // aloca memória 
    heroi = malloc(sizeof(struct heroi_t) * N_HEROIS);

    // atribui o id
    for (int i = 0; i < (N_HEROIS - 1); i++) {
        heroi -> id = i; 
    }

    // atribui as outras características
    heroi -> experiencia = 0;
    heroi -> paciencia = aleat(0, 100);
    heroi -> velocidade = aleat(50, 5000);
    heroi -> habilidades = cjto_aleat(aleat(1, 3), N_HABLIDADES);

}

int main () {

    struct heroi_t *heroi;

    inicializa_herois(heroi);
}