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
void *sai (int *tempo, struct heroi_t *heroi, struct base_t *base, struct mundo_t *mundo, struct fprio_t *lef) {

    // retira o herói do conjunto de heróis presentes na base
    cjto_retira(base -> presentes, heroi -> id);
    
    // escolhe uma base de destino aleatŕoia 
    int id_aleatorio = aleat(0, N_BASES - 1);
    struct base_t *base_destino = &mundo -> bases[id_aleatorio];
    
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

// Função Morre
// O herói morre
// O herói é retirado da base, o porteiro é avisado e os eventos futuros com esse herói são ignorados
void *morre (int *tempo, struct heroi_t *heroi, struct base_t *base, struct missao_t *missao, struct fprio_t *lef) {


    // retira o herói do conjunto de heróis presentes na base
    cjto_retira(base -> presentes, heroi -> id);
    
    // muda o status do herói para morto
    printf("heroi id: %d, heroi velocidade: %d\n", heroi->id, heroi->velocidade);

    heroi -> status = 0;

    // cria e insere na LEF o evento AVISA 
    struct evento_t *evento_avisa = cria_evento(*tempo, AVISA, heroi, base, NULL);

    fprio_insere(lef, evento_avisa, AVISA, *tempo);

    printf("%6d: MORRE HEROI %2d MISSAO %d\n", *tempo, heroi -> id, missao -> id);

    return 0;
}

// Função auxiliar da função Missão
// Verifica se os heróis presentes na base possuem juntos as habilidades necessárias para a missão
struct cjto_t *verifica_habilidades (struct base_t *base, struct missao_t *missao, struct mundo_t *mundo) {

    int habilidades_total = 0;  // contador de habilidades

    // cria uma fila com os heróis presentes na base
    struct fila_t *herois_presentes = fila_cria();

    for (int i = 0; i < N_HEROIS; i++) {    //percorre a fila de heróis presentes na base

        if ( (base -> presentes-> flag[i]) == true) {   

            fila_insere(herois_presentes, i);   // insere o id do herói na fila
            habilidades_total += mundo -> herois[i].habilidades -> num; 
        }
    }

    // cria um conjunto com as habilidades de todos os heróis presentes na base
    struct cjto_t *conjunto_habilidades = cjto_cria(habilidades_total);

    // adiciona as habilidades dos heróis ao conjunto
    int cont = 0;

    struct fila_nodo_t *heroi_id_aux = herois_presentes -> prim; 

    while (cont < herois_presentes -> num) {

        for (int i = 0; i < N_HABILIDADES; i++) {

            if ( ( (mundo -> herois[heroi_id_aux -> item]).habilidades -> flag[i] ) == true)
                
                cjto_insere(conjunto_habilidades, i);
        }

        cont++;

        heroi_id_aux = heroi_id_aux -> prox;
    }

    // compara o conjunto de habilidades presentes na base com as habilidades requeridas pela missão
    if ( (cjto_contem(conjunto_habilidades, missao -> habilidades)) == 1)

        return conjunto_habilidades;
    
    else 
        return NULL;
}

// Função auxiliar da função Missão
// Encontra a base mais próxima apta para realizar a missão
// Retorna a base mais próxima ou NULL se não houver base apta
struct base_t *encontra_bmp_apta (struct missao_t *missao, struct mundo_t *mundo) {

    int x1 = missao -> local.x;     // coordenada x do local da missão
    int y1 = missao -> local.y;     // coordenada y do local da missão

    int menor_distancia = 28284;     // maior distância cartesiana possível para um plano de tamanho (20.000, 20.000)
    struct base_t *base_mais_proxima;

    // calcula a distância de cada base ao local da missão
    for (int i = 0; i < N_BASES; i++) {

        int x2 = mundo -> bases[i].local.x;     // coordenada x do local da base
        int y2 = mundo -> bases[i].local.y;     // coordenada y do local da base

        // verifica se há bases aptas e qual delas é mais próxima da missão
        if ( (verifica_habilidades(&mundo -> bases[i], missao, mundo)) != NULL) {

            // calcula a distância cartesiana das bases
            int distancia = sqrt( ( pow((x2 - x1), 2) ) + (pow((y2 - y1), 2) ) );

            // verifica se essa é a base mais próxima 
            if (distancia < menor_distancia) {

                // atribui a menor distância à base 
                menor_distancia = distancia;
                base_mais_proxima = &mundo -> bases[i];
            }
        }

        // se a menor distância não tiver sido atualizada, significa que nenhuma base encontrada estava apta e base mais próxima recebe NULL
        else if (menor_distancia == 28284)

            base_mais_proxima = NULL;
    }

    // retorna a base mais próxima ou NULL se não houver base mais próxima apta para a missão
    return base_mais_proxima;
}

struct base_t *encontra_bmp (struct missao_t *missao, struct mundo_t *mundo) {

    int x1 = missao -> local.x;     // coordenada x do local da missão
    int y1 = missao -> local.y;     // coordenada y do local da missão

    int menor_distancia = 28284;     // maior distância cartesiana possível para um plano de tamanho (20.000, 20.000)
    struct base_t *base_mais_proxima;

    // calcula a distância de cada base ao local da missão
    for (int i = 0; i < N_BASES; i++) {

        int x2 = mundo -> bases[i].local.x;     // coordenada x do local da base
        int y2 = mundo -> bases[i].local.y;     // coordenada y do local da base

        // calcula a distância cartesiana das bases
        int distancia = sqrt( ( pow((x2 - x1), 2) ) + (pow((y2 - y1), 2) ) );

        // verifica se essa é a base mais próxima 
        if (distancia < menor_distancia) {

        // atribui a menor distância à base 
            menor_distancia = distancia;
            base_mais_proxima = &mundo -> bases[i];

        }
    }

    return base_mais_proxima;
}

// Função auxiliar da função missão 
// Incrementa experiência aos heróis que participaram da missão
void incrementa_experiencia(struct base_t *bmp, struct mundo_t *mundo) {

    // incrementa a experiência dos heróis 
    for (int i = 0; i < N_HEROIS; i++) {

        if (bmp -> presentes -> flag[i] == true) {

            (mundo -> herois[i].experiencia) += 1;
        }
    }
}

// Função auxiliar da função missão
// Encontra o herói mais experiente da base mais próxima 
struct heroi_t encontra_hme (struct base_t *bmp, struct mundo_t *mundo) {

    int maior_experiencia = 0;

    struct heroi_t *heroi_mais_experiente;

    // percorre o conjunto de heróis presentes na base
    for (int i = 0; i < N_HEROIS; i++) {

        if (bmp -> presentes -> flag[i] == true) {

            int heroi_experiencia = mundo -> herois[i].experiencia;

            // compara a experiência dos heróis para encontrar a maior
            if (heroi_experiencia > maior_experiencia) {

                maior_experiencia = heroi_experiencia;
                heroi_mais_experiente = &mundo -> herois[i];
            }
        }
    }

    return *heroi_mais_experiente;
}

// Função Missão
// Uma missão é disparada em um local aleatório com habilidades aleatórias como condição
void *missao (int *tempo, struct missao_t *missao, struct mundo_t *mundo, struct fprio_t *lef) {

    // incrementa a quantidade de tentativas de concluir a missão
    missao -> quantidade_tentativas += 1;

    printf("%6d: MISSAO %d TENT %d HAB REQ: [", *tempo, missao -> id, missao -> quantidade_tentativas);
    cjto_imprime(missao -> habilidades);
    printf("]\n");

    // encontra a base mais próxima da missão cujos heróis possam cumpri-la
    struct base_t *bmp = encontra_bmp_apta(missao, mundo);

    // caso em que há uma base
    if (bmp != NULL) {

        missao -> status = 1;   // marca a missão como concluída
        incrementa_experiencia(bmp, mundo);

        struct cjto_t *habilidades_reunidas = verifica_habilidades(bmp, missao, mundo);

        printf("%6d: MISSAO %d CUMPRIDA BASE %d HABS: [", *tempo, missao -> id, bmp -> id);
        cjto_imprime(habilidades_reunidas);
        printf("]\n");
    }

    // caso em que não há uma base apta
    else if (bmp == NULL) {

        // verifica se existem Compostos V disponíveis e se o tempo é múltiplo de 2500 (pré-requisitos para usar o CompostoV)
        if ( ( (mundo -> NCompostosV ) > 0 ) && ( (*tempo / 2500) == 0 )) {

            mundo -> NCompostosV -= 1;  // decrementa a quantidade total de compostos V

            missao -> status = 1;   // marca a missão como concluída
            
            struct base_t *bmp_nao_apta = encontra_bmp(missao, mundo);  // encontra a base mais próxima, sem se importar se ela possui as habilidades necessárias 

            struct heroi_t heroi_mais_experiente = encontra_hme(bmp_nao_apta, mundo);     // encontra o heroi mais experiente da base

            // crie e insere na LEF o evento MORRE para o herói mais experiente
            heroi_mais_experiente.status = 0;

            struct evento_t *evento_morre = cria_evento(*tempo, MORRE, &heroi_mais_experiente, bmp_nao_apta, missao);

            fprio_insere(lef, evento_morre, MORRE, *tempo);

            incrementa_experiencia(bmp_nao_apta, mundo);    // incrementa experiência para os demais heróis da base

            struct cjto_t *habilidades_reunidas = verifica_habilidades(bmp_nao_apta, missao, mundo);

            printf("%6d: MISSAO %d CUMPRIDA BASE %d HABS: [", *tempo, missao -> id, bmp_nao_apta -> id);
            cjto_imprime(habilidades_reunidas);
            printf("]\n");
        }
    }

    else {

        // adia a missão inserindo ela na lef novamente
        struct evento_t *evento_missao = cria_evento(*tempo + (24 * 60), MISSAO, NULL, NULL, missao);

        fprio_insere(lef, evento_missao, MISSAO, *tempo + (24 * 60));

        printf("%6d: MISSAO %d IMPOSSIVEL\n", *tempo, missao -> id);
    }

    return 0;
}

// Função Fim
// Encerra a simulação e apresenta as estatísticas das entidades
void *fim (int *tempo, struct mundo_t *mundo, struct fprio_t *lef) {

    // apresenta as estatísticas
    printf("%6d: FIM\n", *tempo); 

    // imprime as estatísticas dos heróis
    for (int i = 0; i < N_HEROIS; i++) {

        printf("heroi id %d status %d\n", mundo->herois[i].id, mundo->herois[i].status);
        if ( (mundo -> herois[i].status) == 0) {

            printf("HEROI %2d MORTO PAC %3d VEL %4d EXP %4d HABS [", mundo -> herois[i].id, mundo -> herois[i].paciencia, mundo -> herois[i].velocidade, mundo -> herois[i].experiencia);
            cjto_imprime(mundo -> herois[i].habilidades);
            printf("]\n");
        }

        else if ( (mundo -> herois[i].status) == 1) {

            printf("HEROI %2d VIVO PAC %3d VEL %4d EXP %4d HABS [", mundo -> herois[i].id, mundo -> herois[i].paciencia, mundo -> herois[i].velocidade, mundo -> herois[i].experiencia);
            cjto_imprime(mundo -> herois[i].habilidades);
            printf("]\n");
        }

    }

    return 0;

}

