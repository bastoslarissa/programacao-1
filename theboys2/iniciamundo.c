#include "iniciamundo.h"
#include "conjunto.h"

int aleat (int min, int max) {

    int aleat = rand()%(max - min + 1) + min;

    return aleat;

}

void inicializa_herois (struct heroi_t *heroi) {

    // atribui o id
    for (int i = 0; i < (N_HEROIS - 1); i++) {
        heroi -> id = i; 
    }

    heroi -> experiencia = 0;
    heroi -> paciencia = aleat(0, 100);
    heroi -> velocidade = aleat(50, 5000);
    heroi -> habilidades = cjto_aleat(aleat(1, 3), N_HABLIDADES);

}