#include "mundo.h"
#include <math.h>

// Função Chega 
// Herói chega na base e decide se vai esperar ou desistir de entrar
void *chega (int *tempo, struct heroi_t *heroi, struct base_t *base, struct fprio_t *lef) {

    int espera;

    // atualiza a base de herói
    heroi -> base = base -> id;

    int quantidade_presentes = cjto_card(base -> presentes);

    // caso: há vagas na base e a fila de espera está vazia
    if ( ( quantidade_presentes < (base -> lotacao) ) && (fila_tamanho(base -> espera) == 0) ) {

        espera = 1;
    }

    // caso: não há vagas na base ou a fila de espera não está vazia
    else if ( (heroi -> paciencia) > (10 * fila_tamanho(base -> espera)) ) {

        espera = 1;
    }
    
    else {

        espera = 0;
    }

    if (espera == 1) {

        // cria e insere na LEF o evento ESPERA
        struct evento_t *evento_heroi_espera = cria_evento(*tempo, ESPERA,   heroi, base, NULL);

        fprio_insere(lef, evento_heroi_espera, ESPERA, *tempo);

        printf("%6d: CHEGA HEROI %2d BASE %d (%2d/%2d) ESPERA\n", *tempo, heroi -> id, base -> id, cjto_card(base -> presentes), base -> lotacao);
    }

    else {

        // cria e insere na LEF o evento DESISTE
        struct evento_t *evento_heroi_desiste = cria_evento(*tempo, DESISTE, heroi, base, NULL);

        fprio_insere(lef, evento_heroi_desiste, DESISTE, *tempo);

        printf("%6d: CHEGA HEROI %2d BASE %d (%2d/%2d) DESISTE\n", *tempo, heroi -> id, base -> id, cjto_card(base -> presentes), base -> lotacao);
    }

    return 0; 
} 

// Função Espera
// O herói entra na fila de espera da base
void *espera (int *tempo, struct heroi_t *heroi, struct base_t *base, struct fprio_t *lef) {

    // insere o herói no fim da fila de espera da base
    fila_insere( (base -> espera), heroi -> id);

    // cria e insere na LEF o evento AVISA, que avisa ao porteiro para verificar a fila de espera da base
    struct evento_t *evento_avisa = cria_evento(*tempo, AVISA, heroi, base, NULL);

    fprio_insere(lef, evento_avisa, AVISA, *tempo);

    printf("%6d: ESPERA HEROI %2d BASE %d (%2d)\n", *tempo, heroi -> id, base -> id, fila_tamanho(base -> espera));

    return 0;
}

// Função Desiste
// O herói desiste de entrar na base
void *desiste (int *tempo, struct heroi_t *heroi, struct base_t *base, struct fprio_t *lef) {

    // escolhe uma base destino aleatória
    int id_aleatorio = aleat(0, N_BASES - 1); 
    struct base_t *base_destino = &base[id_aleatorio];

    // cria e insere na LEF o evento VIAJA
    struct evento_t *evento_viaja = cria_evento(*tempo, VIAJA, heroi, base_destino, NULL);

    fprio_insere(lef, evento_viaja, VIAJA, *tempo);

    printf("%6d: DESISTE HEROI %2d BASE %d\n", *tempo, heroi -> id, base_destino -> id);

    return 0;
}

// Função Avisa
// O porteiro libera a entrada de alguns heróis na base
void *avisa (int *tempo, struct base_t *base, struct mundo_t *mundo, struct fprio_t *lef) {

    // Enquanto houver vaga em B e houver heróis esperando na fila
    while ( ( (cjto_card(base -> presentes)) < base -> lotacao) && (fila_tamanho(base -> espera) > 0) ) {

        printf("%6d: AVISA PORTEIRO BASE %d (%2d/%2d) FILA [", *tempo, base -> id, fila_tamanho(base -> espera), base -> lotacao);
        fila_imprime(base -> espera);
        printf("]\n");

        // retira o primeiro herói da fila
        struct heroi_t *heroi = &mundo->herois[base -> espera -> prim -> item];
        fila_retira(base -> espera, &base -> espera -> prim -> item);
        
        // insere o primeiro herói da fila no conjunto de heróis presentes
        cjto_insere(base -> presentes, heroi -> id);

        // cria e insere na LEF o evento ENTRA
        struct evento_t *evento_entra = cria_evento(*tempo, ENTRA, heroi, base, NULL);

        fprio_insere(lef, evento_entra, ENTRA, *tempo);

        printf("%6d: AVISA PORTEIRO BASE %d ADMITE %2d\n", *tempo, base -> id, heroi -> id);
    }

    return 0;
}

// Função Entra
// O herói entra na base, decide quanto tempo vai ficar e agenda sua saída da base
void *entra (int *tempo, struct heroi_t *heroi, struct base_t *base, struct fprio_t *lef) {

    // calcula o TPB (tempo de permanência na base)
    int tpb = 15 + heroi -> paciencia * (aleat(1, 20));

    // cria e insere na LEF o evento SAI
    struct evento_t *evento_sai = cria_evento(*tempo + tpb, SAI, heroi, base, NULL);

    fprio_insere(lef, evento_sai, SAI, *tempo + tpb);

    printf("%6d: ENTRA HEROI %2d BASE %d (%2d/%2d)\n", *tempo, heroi -> id, base -> id, cjto_card(base -> presentes), base -> lotacao);

    return 0;
}

// Função Sai
// O herói sai da base atual e escolhe uma base destino para viajar
// O porteiro é avisado que uma vaga foi liberada na base 
void *sai (int *tempo, struct heroi_t *heroi, struct base_t *base, struct fprio_t *lef) {

    // retira o herói do conjunto de heróis presentes na base
    cjto_retira(base -> presentes, heroi -> id);
    
    // escolhe uma base de destino aleatŕoia 
    struct base_t *base_destino = &base[aleat(0, N_BASES - 1)];

    // cria e insere na LEF o evento VIAJA
    struct evento_t *evento_viaja = cria_evento(*tempo, VIAJA, heroi, base_destino, NULL);

    fprio_insere(lef, evento_viaja, VIAJA, *tempo);

    // cria e insere na LEF o evento AVISA
    struct evento_t *evento_avisa = cria_evento(*tempo, AVISA, heroi, base, NULL);

    fprio_insere(lef, evento_avisa, AVISA, *tempo);

    printf("%6d: SAI HEROI %3d BASE %d (%2d/%2d)\n", *tempo, heroi -> id, base -> id, cjto_card(base -> presentes), base -> lotacao);

    return 0;
}

// Função Viaja
// o herói se desloca para uma base destino (que pode ser a mesma que ele está)
// Fórmula de cálculo de distância cartesiana: √((x2 - x1)² + (y2 - y1)²)
void *viaja (int *tempo, struct heroi_t *heroi, struct base_t *base_d, struct mundo_t *mundo, struct fprio_t *lef) {

    // calcula a duração da viagem
    
    int x1 = mundo -> bases[heroi -> base].local.x;    // coordenada x base origem 
    int y1 = mundo -> bases[heroi -> base].local.y;    // coordenada y base origem
    
    int x2 = base_d -> local.x;    // coordenada x base destino
    int y2 = base_d -> local.y;    // coordenada y base destino

        // calcula a distância cartesiana entre as bases
        int distancia = sqrt( ( pow((x2 - x1), 2) ) + (pow((y2 - y1), 2) ) );

    // calcula a duração da viagem
    int duracao = ( (distancia) / heroi -> velocidade );

    // cria e insere na LEF o evento CHEGA
    struct evento_t *evento_chega = cria_evento(*tempo + duracao, CHEGA, heroi, base_d, NULL);

    fprio_insere(lef, evento_chega, CHEGA, *tempo + duracao);

    printf("%6d: VIAJA HEROI %2d BASE %d BASE %d DIST %d VEL %d CHEGA %d\n", *tempo, heroi -> id, mundo -> bases[heroi -> base].id, base_d -> id, distancia, heroi -> velocidade, *tempo + duracao);

    return 0;

}
