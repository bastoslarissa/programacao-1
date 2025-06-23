#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "libtheboys.h"


//Função auxiliar
// Cria um evento
struct eventos *cria_evento (int tempo, int tipo, struct heroi *h, struct base *b, struct base *destino, struct missao *m, struct mundo *w) {

    struct eventos *e = malloc (sizeof(struct eventos));

    /* verifica */
    if (!e) {
        printf("Erro ao alocar evento \n");
        return;
    }

    /* atribui valores */
    e -> tempo = tempo;
    e -> tipo = tipo;
    e -> h = h;
    e -> b = b;
    e -> destino = destino;
    e -> m = m;
    e -> w = w;

    return e;
}

// Evento CHEGA
// Herói chega na base
// Caso a base esteja lotada, o herói decide se espera para entrar ou desiste
void *chega (int tempo, struct eventos *evento) {

    /* parâmetros */
    struct heroi *h = evento -> h;
    struct base *b = evento -> b;
    struct mundo *w = evento -> w;
    struct fprio_t *lef = evento -> lef;


    /* atualiza o id da base que o herói está */
    h -> base = b -> base_id;

     int lotacao_tam = b->presentes->num;
     int fila_tam = fila_tamanho(b -> espera);

    /* verifica se há vagas na base e se há espaço na fila de espera */
    if ((b -> lotacao < lotacao_tam) && (b -> espera -> prim == 0)) {
        
        /* entra */
        struct eventos *evento_criado = cria_evento(tempo, TIPO_ENTRA, h, b, NULL, NULL, w);
        fprio_insere(lef, evento_criado, TIPO_ENTRA, tempo);  
    }
    /* verifica se o herói tem paciência o suficiente para esperar */
    else if (h -> paciencia > 10 * fila_tam) {

        /* escolhe esperar */
        struct eventos *evento_criado = cria_evento(tempo, TIPO_ESPERA, h, b, NULL, NULL, w);
        fprio_insere(lef, evento_criado, TIPO_ESPERA, tempo);

        printf("%6d: CHEGA HEROI %2d BASE %d (%2d/%2d) ESPERA", tempo, h->heroi_id, b->base_id, cjto_card(b -> presentes), b -> lotacao);


    }
    /* escolhe desistir */
    else {
        struct eventos *evento_criado = cria_evento(tempo, TIPO_DESISTE, h, b, NULL, NULL, w);
        fprio_insere(lef, evento_criado, TIPO_DESISTE, tempo);

        printf("%6d: CHEGA HEROI %2d BASE %d (%2d/%2d) DESISTE", tempo, h->heroi_id, b->base_id, cjto_card(b -> presentes), b -> lotacao);

    }
}

// Evento ESPERA
// Herói entra na fila de espera da base 
// Porteiro é avisado para verificar a fila
void *espera (int tempo, struct eventos *evento) {
    
    /* parâmetros */
    struct base *b = evento -> b;
    struct heroi *h = evento -> h;
    struct mundo *w = evento -> w;
    struct fprio_t *lef = evento -> lef;

    /* adiciona o herói no fim da fila da base */
    fila_insere(b -> espera, h);

    /* contador de máximo de heróis na fila de espera */
    if (b -> cont_espera < cjto_card(b -> espera))
        b -> cont_espera = cjto_card(b -> espera);

    /* insere na LEF o evento de AVISA */
    struct eventos *evento_criado = cria_evento(tempo, TIPO_AVISA, NULL, b, NULL, NULL, w);
    fprio_insere(lef, evento_criado,TIPO_AVISA, tempo) ;

    printf("%6d: ESPERA HEROI %2d BASE %d (%2d)", tempo, h->heroi_id, b->base_id, cjto_card(b -> espera));

}

// Evento DESISTE
// Herói desiste de entrar na base e viaja para outra base 
void *desiste (int tempo, struct heroi *h, struct base *b, struct mundo *w, struct fprio_t *lef) {
    
    /* herói escolhe uma base de destino aleatória */
    struct base *d;
    int base_aleat;

    base_aleat = rand () % ((w -> NBases - 1) - 0 + 1) + 0;
    
    d -> base_id = w -> bases[base_aleat].base_id;

    /* insere na LEF o evento VIAJA */
    fprio_insere(lef, viaja, TIPO_VIAJA, tempo);
    cont_lef++;

    printf("%6d: DESIST HEROI %2d BASE %d", tempo, h->heroi_id, b->base_id);

}

// Evento AVISA
// Porteiro permite a entrada de heróis na base com base na lotação 
void *avisa (int tempo, struct base *b, struct mundo *w, struct fprio_t *lef) {

    printf("%6d: AVISA PORTEIRO BASE %d (%2d/%2d) FILA [ ", tempo, b->base_id, cjto_card(b -> presentes), cjto_card(b -> espera) );
    cjto_imprime(b -> espera);
    printf(" ]");

    void *heroi_entrando;

    int lotacao_tam = cjto_card(b -> presentes);

    while (b -> lotacao < lotacao_tam && b -> espera > 0) {

        /* retira o primeiro herói da fila de espera da base e insere ele no conjunto de heróis presentes */
        int *ptr = fila_retira(b -> espera);
        heroi_entrando = *ptr;
        cjto_insere(b -> presentes, heroi_entrando);

        /* insere na LEF o evento ENTRA */
        fprio_insere(lef, entra, TIPO_ENTRA, tempo);
        cont_lef++;

        printf("%6d: AVISA PORTEIRO BASE %d ADMITE %2d", tempo, b->base_id, heroi_entrando);
    }
}

// Evento ENTRA 
// Herói entra na base e decide quanto tempo vai ficar 
void *entra (int tempo, struct heroi *h, struct base *b, struct mundo *w, struct fprio_t *lef) {

    /* calcula o tempo de permanência do herói na base */
    int aleatorio = rand () % (20 - 1 + 1) + 1;
    int tpb = ((15 + (h -> paciencia)) * aleatorio);
    
    /* insere na LEF o evento SAI */
    fprio_insere(lef, sai, TIPO_SAI, tempo + tpb);
    cont_lef++;

    printf("%6d: ENTRA HEROI %2d BASE %d (%2d/%2d) SAI %d", tempo, h->heroi_id, b->base_id, cjto_card(b -> presentes), b -> lotacao, tempo + tpb);
    
}

// Evento SAI
// Herói sai da base e viaja para uma outra base 
// O porteiro é avisado que liberou uma vaga
void *sai (int tempo, struct heroi *h, struct base *b, struct mundo *w, struct fprio_t *lef) {

    /* retira herói do conjunto de heróis presetes */
    cjto_retira(b -> presentes, h);

    /* herói escolhe uma base de destino aleatória */
    struct base *d;
    int base_aleat;

    base_aleat = rand () % ((w -> NBases - 1) - 0 + 1) + 0;
        
    d -> base_id = w -> bases[base_aleat].base_id;
    
    /* insere na LEF o evento VIAJA */
    fprio_insere(lef, viaja, TIPO_VIAJA, tempo);
    cont_lef++;

    /* insere na LEF o evento AVISA */
    fprio_insere(lef, avisa, TIPO_AVISA, tempo);
    cont_lef++;

    printf("%6d: SAI HEROI %2d BASE %d (%2d/%2d)", tempo, h->heroi_id, b->base_id, cjto_card(b->presentes), b->lotacao);

}

// Evento VIAJA 
// Herói viaja para uma base (pode ser outra ou a mesma que já está)
void *viaja (int tempo, struct heroi *h, struct base *b, struct base *destino, struct mundo *w, struct fprio_t *lef) {

    /* calcula a duração da viagem */
    int x1 = b -> local.x;
    int x2 = destino -> local.x;
    int y1 = b -> local.y;
    int y2 = destino -> local.y;
    

        /* distância entre base de origem e base destino */
        int distancia = sqrt( ((x2-x1) * (x2-x1)) + ((y2-y1) * (y2-y1)) );
        
        /* duração da viagem entre as duas bases */
        int duracao = distancia / h -> velocidade;

    /* insere na LEF o evento CHEGA */
    fprio_insere(lef, chega, TIPO_CHEGA, tempo + duracao);
    cont_lef++;

    printf("%6d: VIAJA HEROI %2d BASE %d DIST %d VEL %d CHEGA %d", tempo, h->heroi_id, b->base_id, distancia, h ->velocidade, tempo + duracao);
}

// Evento MORRE
// O herói morre no instante T
void *morre (int tempo, struct heroi *h, struct base *b, struct missao *m, struct mundo *w, struct fprio_t *lef) {

    /* retira o herói do conjunto de heróis presentes na base */
    cjto_retira(lef, h);

    /* muda o status de heroi para morto */
    h -> vivo = 0;

    /* insere na LEF o evento AVISA */
    fprio_insere(lef, avisa, TIPO_AVISA, tempo);
    cont_lef++;

    printf("%6d: MORRE HEROI %2d MISSAO %d", tempo, h->heroi_id, m->missao_id);
}

// Calcula a base mais próxima
/* distância de dois pontos: sqrt ((x2-x1)²+(y2-y1)²)*/
/* x1 e y1 : coordenadas da missão */
/* x2 e y2 : coordenadas da base */
struct base *bmp (struct mundo *w, struct missao *m) {

    struct base *base_mais_prox;
    int menor = 28.284; /* inicializa com a maior distância possível */
    int x, y, distancia;

    /* percorre o vetor das bases calculando a distância delas da distância  */
    for (int i = 0; i < N_BASES; i++) {

        /* calcula a distância da misão até a base[i] */
        x = ( ((w -> bases[i].local.x) - (m -> local.x)) * ((w -> bases[i].local.x) - (m -> local.x)) );
        y = ( ((w -> bases[i].local.y) - (m -> local.y)) * ((w -> bases[i].local.y - (m -> local.y))) );
        distancia = sqrt(x * y);

        /* verifica se essa é a base mais próxima */
        if (distancia < menor) 
            menor = distancia; 
            base_mais_prox = w -> bases[i].base_id;



    }

    return base_mais_prox;

}

// Evento MISSÃO
void *missao (struct missao *m, int tempo, struct mundo *w, struct fprio_t *lef) {

    printf("%6d: MISSAO %d TENT %d HAB REQ: [ ", tempo, m->missao_id, ++m -> tentativas);
    cjto_imprime(m->habilidades);
    printf(" ]");


    /* habilidades concedidas pelo Composto V */
    struct cjto_t *todas_habilidades = cjto_cria(3);
        for (int i = 0; i < 10; i++)
            cjto_insere(todas_habilidades, i);

    /* calcula a base mais próxima */
    struct base *base_mais_prox = bmp(w,m);

    struct cjto_t *herois_xp = cjto_cria(base_mais_prox -> presentes -> cap);
    struct cjto_t *temp = herois_xp;

    /* percorre o conjunto de heróis presentes na base e atribui as habilidades deles a um conjunto */
    for (int i = 0; i < base_mais_prox->presentes->cap; i++) {
        if (base_mais_prox->presentes->flag[i]) {
            herois_xp = cjto_uniao(herois_xp, w -> herois[i].habilidades);
        }  
    }

    free(temp);


    /* verifica se as habilidades dos heróis atendem as habilidades necessárias para a missão */
    if ((cjto_contem(herois_xp, m ->habilidades)) == 1) {

        /* marca a missão como concluída */
        fprio_retira(lef, m, tempo);

        /* contador de quantidade de missões participadas por base */
        m->cont_missoes[base_mais_prox->base_id]++;

        printf("%6d: MISSAO %d CUMPRIDA BASE %d HABS: [ ", tempo, m->missao_id, base_mais_prox->base_id);
        cjto_imprime(herois_xp);
        printf(" ]");

        /* incrementa a experiência dos heróis */
        for (int i =0; i < herois_xp->cap; i++) {
            w -> herois[i].experiencia++;
        }
    }

    /* faz o uso de Composto V, se possível */
    else if ( (N_COMPOSTOS_V > 0) && ((tempo % 2500) == 0) ) {
            N_COMPOSTOS_V--; 

            /* marca a missão como concluída */
            fprio_retira(lef, m, tempo); 

            /* acha o herói mais experiente */
            struct heroi *maior = w -> herois[0].heroi_id;

            for (int i = 1; i < herois_xp; i++) {
                if (w -> herois[i].experiencia > maior -> experiencia)
                    *maior = w -> herois[i];
            }

            maior -> habilidades = cjto_inter(maior -> habilidades, todas_habilidades);
            struct cjto_t *temp = herois_xp;
            herois_xp = cjto_uniao(herois_xp, maior -> habilidades);

                printf("%6d: MISSAO %d CUMPRIDA BASE %d HABS: [ ", tempo, m->missao_id, base_mais_prox->base_id);
                cjto_imprime(herois_xp);
                printf(" ]");

            /* cria e insere na LEF o evento MORRE p/ o herói mais experiente */
            fprio_insere(lef, morre, TIPO_MORRE, tempo);
            cont_lef++;

            /* incrementa a experiência dos heróis */
            for (int i =0; i < herois_xp->cap; i++) {
                w -> herois[i].experiencia++;
            }

    }

    /* marca a missão como impossível e adia ela por 24h */
    else {
        fprio_retira(lef, m, tempo);
        fprio_insere(lef, missao, TIPO_MISSAO, (tempo + 24*60));
        cont_lef++;

        printf("%6d: MISSAO %d IMPOSSIVEL", tempo, m->missao_id);
    }

    cjto_destroi(temp);
    cjto_destroi(herois_xp);
    cjto_destroi(todas_habilidades);

}

// Evento FIM
// retorna relatórios
// libera memória alocada dinâmicamente
void *fim (int tempo, struct mundo *w, struct fprio_t *lef) {

    printf("%d: FIM", tempo);

    /* relatório dos heróis */
    for (int i = 0; i < N_HEROIS; i++) {
        if (w -> herois[i].vivo = 1) {
            printf("HEROI %2d VIVO PAC %3d VEL %4d EXP %4d HABS [ ", w -> herois[i].heroi_id, w -> herois->paciencia, w -> herois->velocidade, w -> herois->experiencia);
            cjto_imprime(w -> herois[i].habilidades);
            printf(" ]");
        }
        else if (w -> herois[i].vivo = 0) {
            printf("HEROI %2d MORTO PAC %3d VEL %4d EXP %4d HABS [ ", w -> herois[i].heroi_id, w -> herois->paciencia, w -> herois->velocidade, w -> herois->experiencia);
            cjto_imprime(w -> herois[i].habilidades);
            printf(" ]");            
        }
    }


    /* relatório das bases */
    for (int i = 0; i < N_BASES; i++) {
        printf("BASE %2d LOT %2d FILA MAX %2d MISSOES %d", w -> bases[i].base_id, w -> bases->lotacao, w -> bases->cont_espera, w -> missoes->cont_missoes[w -> bases[i].base_id]);
    }

    /* relatório geral */

    /* eventos tratados*/
    printf("EVENTOS TRATADOS: %d", cont_lef);

    /* missões cumpridas */
    int soma_missoes = 0;
    float sucesso = 0;

    for (int i = 0; i < N_BASES; i++) {
        int soma_missoes =+ w -> missoes->cont_missoes[i];
    }

    sucesso = ( ((float)soma_missoes / (float)N_MISSOES) * 100);
    
    printf("MISSOES CUMPRIDAS: %d/%d (%.1f%)", soma_missoes, N_MISSOES, sucesso);

    /* tentativas por missão */
    int maior = 0;
    int menor = soma_missoes;
    int total_de_tentativas = 0;

        /* calcula maior quantidade de tentativas */
        for (int i = 0; i < N_MISSOES; i++) {
            if (w -> missoes[i].tentativas > maior) 
                maior = w -> missoes[i].tentativas;
        }

        /* calcula menor quantidade de tentativas */
        for (int i = 0; i < N_MISSOES; i++) {
            if (w -> missoes[i].tentativas < menor)
                menor = w -> missoes[i].tentativas;
        }
        
        /* calcula a média de tentativas por missão */
        for (int i = 0; i < N_MISSOES; i++) {
            total_de_tentativas =+ w -> missoes[i].tentativas;
        }

        float media = ((float)total_de_tentativas) / (float)N_MISSOES;
    
    printf("TENTATIVAS/MISSAO: MIN %d, MAX %d, MEDIA %.1f", menor, maior, media);

    /* taxa de mortalidade */
    int mortes_total = 0;
    float mortes_media = 0;

        for (int i = 0; i < N_HEROIS; i++) {
            if (w -> herois->vivo == 0) 
                mortes_total++;
        }

        mortes_media = ( ((float)mortes_total) / N_HEROIS ) * 100;

    printf("TAXA MORTALIDADE: %.1f%%", mortes_media);

    // LIBERA MEMÓRIA //
    fprio_destroi(lef);

    /* heróis */
    for (int i = 0; i < N_HEROIS; i++) {
        free(cjto_destroi(w -> herois[i].habilidades));
    }

    free(w -> herois);

    /* bases */
    for (int i = 0; i < N_BASES; i++) {
        free(cjto_destroi(w -> bases[i].presentes));
    }

    fila_destroi(w->bases->espera);
    free(w -> bases);

    /* missões */
    cjto_destroi(w->missoes->habilidades);

    for (int i = 0; i < N_MISSOES; i++) {
        free(w->missoes[i].cont_missoes);
    }
    free(w -> missoes);

}


// Estado Inicial
// Inicia Heróis, Bases e Missões
void *inicia_mundo(struct heroi *h, struct base *b, struct missao *m, struct mundo *w, struct eventos *evento, struct fprio_t *lef) {

    /* inicialização dos heróis */
    w -> herois = malloc (sizeof(struct heroi));

    for (int i = 0; i < N_HEROIS; i++) {
        w -> herois[i].heroi_id = i;
        w -> herois[i].experiencia = 0;
        w -> herois[i]. paciencia = rand () % (100 - 0 + 1) + 0;
        w -> herois[i].velocidade = rand () % (5000 - 50 + 1) + 50;
        w -> herois[i].habilidades = cjto_aleat((rand () % (3 - 1 + 1) + 1), 10);
    }

    /* inicialização de cada base */
    w -> bases = malloc (sizeof(struct base)); 

    for (int i = 0; i < N_BASES; i++) {
        w -> bases[i].base_id = i;
        w -> bases[i].local.x = rand () % ((N_TAMANHO_MUNDO-1) - 0 + 1) + 0;
        w -> bases[i].local.y = rand () % ((N_TAMANHO_MUNDO-1) - 0 + 1) + 0;
        w -> bases[i].lotacao = rand () % (10 - 3 + 1) + 3;
        w -> bases[i].presentes = cjto_cria(w -> bases[i].lotacao);
        w -> bases[i].espera = fila_cria();
        w -> bases[i].cont_espera = 0;
    }

    /* inicialização de cada missão */
    w -> missoes = malloc (sizeof(missao));
    w -> missoes->cont_missoes = malloc (sizeof(N_BASES));

    for (int i = 0; i < N_MISSOES; i++) {
        w -> missoes[i].missao_id = i;
        w -> missoes[i].local.x = rand () % ((N_TAMANHO_MUNDO-1) - 0 + 1) + 0;
        w -> missoes[i].local.y = rand () % ((N_TAMANHO_MUNDO-1) - 0 + 1) + 0;
        w -> missoes[i].habilidades = cjto_aleat((rand () % (10 - 6 + 1) + 6), 10); 
        w -> missoes[i].tentativas = 0;
        w -> missoes[i].cont_missoes = 0;
    }

   /* Inicialização da Lista de Eventos Futuros */

  /* agenda a chegada dos heróis na base */

    for (int i = 0; i < N_HEROIS; i++) {
        int tempo = rand () % (4320 - 0 + 1) + 0;
        int base_aleatoria = rand () % ((N_BASES - 1) - 0 + 1) + 0;

        evento -> tipo = TIPO_CHEGA;
        evento -> tempo = tempo;
        evento -> h = &w -> herois[i];
        evento -> b = &w -> bases[base_aleatoria];
        evento -> w = w;
        evento -> destino = NULL;
        evento -> m = m;
  
    fprio_insere(lef, &evento, TIPO_CHEGA, tempo);
    cont_lef++;
  }

  /* agenda as missões */
  for (int i = 0; i < N_MISSOES; i++) {
    int tempo = rand () % (T_FIM_DO_MUNDO - 0 + 1) + 0;

        evento -> tipo = TIPO_MISSAO;
        evento -> tempo = tempo;
        evento -> h = NULL;
        evento -> b = NULL;
        evento -> w = w;
        evento -> destino = NULL;
        evento -> m = m;

    fprio_insere(lef, &evento, TIPO_MISSAO, tempo);
    cont_lef++;
  }

  /* agenda o fim do mundo */
        evento -> tipo = TIPO_FIM;
        evento -> tempo = T_FIM_DO_MUNDO;
        evento -> h = NULL;
        evento -> b = NULL;
        evento -> w = w;
        evento -> destino = NULL;
        evento -> m = NULL;

  fprio_insere(lef, &evento, TIPO_FIM, T_FIM_DO_MUNDO);
  cont_lef++;

}

        
        
        
        
        
    
