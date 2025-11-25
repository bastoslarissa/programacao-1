#include "mundo.h"

// Função chega 
// Herói chega na base e decide se vai esperar ou desistir de entrar
void *chega (int *tempo, struct heroi_t *heroi, struct base_t *b, struct fprio_t *lef) {

    int espera;

    // atualiza a base de herói
    heroi -> base = b -> id;
    printf("--1\n");
    printf("base id: %d\nbase local: (%d, %d)\nbase lotação: %d\nbase presentes: ", b -> id, b -> local.x, b -> local.y, b -> lotacao);
    cjto_imprime(b -> presentes);
    printf("\n\n");


    int quantidade_presentes = cjto_card(b -> presentes);

    printf("--2\n");

    // caso: há vagas na base e a fila de espera está vazia
    if ( ( quantidade_presentes < (b -> lotacao) ) && (fila_tamanho(b -> espera) == 0) ) {

        espera = 1;
    }

    // caso: não há vagas na base ou a fila de espera não está vazia
    else if ( (heroi -> paciencia) > (10 * fila_tamanho(b -> espera)) ) {

        espera = 1;
    }
    
    else {

        espera = 0;
    }

    if (espera == 1) {

        // cria evento herói espera
        struct evento_t *evento_heroi_espera = cria_evento(*tempo, ESPERA,   heroi, b, NULL);

        // insere na LEF o evento ESPERA
        fprio_insere(lef, evento_heroi_espera, ESPERA, *tempo);

        printf("%6d: CHEGA HEROI %2d BASE %d (%2d/%2d) ESPERA\n", *tempo, heroi -> id, b -> id, cjto_card(b -> presentes), b -> lotacao);
    }

    else {

        // cria evento herói desiste
        struct evento_t *evento_heroi_desiste = cria_evento(*tempo, DESISTE, heroi, b, NULL);

        // insere na LEF o evento DESISTE
        fprio_insere(lef, evento_heroi_desiste, DESISTE, *tempo);

        printf("desiste\n");
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

    printf("avisa\n");

    return 0;
}