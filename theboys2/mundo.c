#include "mundo.h" 

/* -------------------------------------------------------------------------------------
                              INICIALIZAÇÃO DO MUNDO
   ------------------------------------------------------------------------------------ */

/* Função auxiliar
* Gera um número aleatório entre min e max */
int aleat (int min, int max) {

    int aleat = (rand()%(max - min + 1)) + min;

    return aleat;

}

/* Função auxiliar
* Cria um evento */
struct evento_t *cria_evento (int tempo, int tipo, struct heroi_t *heroi, struct base_t *base, struct missao_t *missao) {

    struct evento_t *evento = malloc(sizeof(struct evento_t));

    // verificação
    if (!evento) {
        printf("Erro ao inserir evento\n");
        return NULL;
    }

    // atribuição 
    evento -> tempo = tempo;
    evento -> tipo = tipo;
    evento -> heroi = heroi;
    evento -> base = base;
    evento -> missao = missao;

    return evento;
}


void inicializa_mundo (struct mundo_t *mundo) {

    // inicializa o mundo
    mundo -> NHerois = N_HEROIS;
    mundo -> NBases = N_BASES;
    mundo -> NMissoes = N_MISSOES;
    mundo -> NHabilidades = N_HABILIDADES;
    mundo -> NCompostosV = N_COMPOSTOS_V;
    mundo -> TamanhoMundo = N_TAMANHO_MUNDO;
    mundo -> relogio = 0;

    // inicializa os heróis
    mundo -> herois = malloc(sizeof(struct heroi_t) * N_HEROIS);

    for (int i = 0; i < N_HEROIS; i++) {

        mundo -> herois[i].id = i;
        mundo -> herois[i].experiencia = 0;
        mundo -> herois[i].paciencia = aleat(0, 100);   // nº aleatório entre 0 e 100
        mundo -> herois[i].velocidade = aleat(50, 5000);    // nº aleatório entre 50 e 5000 

        mundo -> herois[i].habilidades = cjto_aleat(aleat(1, 3), N_HABILIDADES);     // conjunto aleatório de [1...3] habilidades distintas
        
    }

    // inicializa as bases
    mundo -> bases = malloc(sizeof(struct base_t) * N_BASES);

    for (int i = 0; i < N_BASES; i++) {

        mundo -> bases[i].id = i;
        mundo -> bases[i].local.x = aleat(0, N_TAMANHO_MUNDO - 1);  // coordenada x aleatória 
        mundo -> bases[i].local.y = aleat(0, N_TAMANHO_MUNDO - 1);  // coordenada y aleatória 
        mundo -> bases[i].lotacao = aleat(3, 10);   // nº aleatório entre 3 e 10
        mundo -> bases[i].presentes = cjto_cria(mundo -> NHerois);     // conjunto com capacidade da lotação aleatória gerada acima

        //mundo -> bases[i].presentes = cjto_cria(mundo -> bases[i].lotacao);     // conjunto com capacidade da lotação aleatória gerada acima
        mundo -> bases[i].espera = fila_cria();     // fila vazia

        printf("base id: %d\nbase local: (%d, %d)\nbase lotação: %d\nbase presentes: ", mundo -> bases[i].id, mundo -> bases[i].local.x, mundo -> bases[i].local.y, mundo -> bases[i].lotacao);
        cjto_imprime(mundo -> bases[i].presentes);
         printf("\n\n");
    }

    // inicializa as missões 
    mundo -> missoes = malloc(sizeof(struct missao_t) * N_MISSOES);
    
    for (int i = 0; i < N_MISSOES; i++) {

        mundo -> missoes[i].id = i;
        mundo -> missoes[i].local.x = aleat(0, N_TAMANHO_MUNDO - 1);    // coordenada x aleatória 
        mundo -> missoes[i].local.y = aleat(0, N_TAMANHO_MUNDO - 1);    // coordenada y aleatória

        mundo -> missoes[i].habilidades = cjto_aleat(aleat(6, 10), N_HABILIDADES);  // conjunto com capacidade aleatória
    }

}


void eventos_iniciais (struct mundo_t *mundo, struct fprio_t *lef) {

    // eventos iniciais : heróis
    for (int i = 0; i < N_HEROIS; i++) {

        int base_aleatoria = aleat(0, N_BASES);
        int tempo_heroi = aleat(0, 4320);   // 4.320 minutos = 3 dias;

        // cria o evento herói chega
        struct evento_t *evento_heroi_chega = cria_evento(tempo_heroi, CHEGA, &mundo -> herois[i], &mundo -> bases[base_aleatoria], NULL);

        // insere na LEF o evento CHEGA 
        fprio_insere(lef, evento_heroi_chega, CHEGA, tempo_heroi);
    }   


    // eventos iniciais: missões
    for (int i = 0; i < N_MISSOES; i++) {

        int tempo_missão = aleat(0, T_FIM_DO_MUNDO);

        // cria o evento missão
        struct evento_t *evento_missao = cria_evento(tempo_missão, MISSAO, NULL, NULL, &mundo -> missoes[i]);

        // insere na LEF o evento MISSÃO
        fprio_insere(lef, evento_missao, MISSAO, tempo_missão);
    }

    // eventos iniciais: fim 
    int tempo_fim = T_FIM_DO_MUNDO;
    struct evento_t *evento_fim = cria_evento(tempo_fim, FIM, NULL, NULL, NULL);
    fprio_insere(lef, evento_fim, FIM, T_FIM_DO_MUNDO);

}

/* -------------------------------------------------------------------------------------
                                  EXECUÇÃO DO MUNDO
   ------------------------------------------------------------------------------------ */

/* void iniciar_o_mundo () {



    
} */