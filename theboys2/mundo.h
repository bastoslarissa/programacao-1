
// inicialização do mundo virtual
#define T_INICIO 0
#define T_FIM_DO_MUNDO 525600
#define N_TAMANHO_MUNDO 20000
#define N_HABLIDADES 10
#define N_HEROIS (N_HABLIDADES * 5)
#define N_BASES (N_HEROIS / 5)
#define N_MISSOES (T_FIM_DO_MUNDO / 100)
#define N_COMPOSTOS_V (N_HABLIDADES * 3)

/* -----------------------------------------------------------------
                            ENTIDADES                               
   -----------------------------------------------------------------*/

struct heroi_t {

    int id;
    int habilidades;
    int paciencia;
    int velocidade;
    int experiencia;
    int base;
};

struct coordenadas {

    int x;
    int y;
};

struct base_t {

    int id;
    int lotacao;
    struct cjto_t *presentes;
    struct fila_t *espera;
    struct coordenadas local;
};

struct missao_t {

    int id;
    struct cjto_t *habilidades;
    struct coordenadas local;
};

struct mundo_t {

    int NHerois;
    struct heroi *herois;   // vetor de heróis
    int NBases;
    struct base *bases;     // vetor de bases
    int NMissoes;
    struct missao *missoes;     // vetor de missoes
    int NHabilidades;
    int NCompostosV;
    int TamanhoMundo;    //coordenadas máximas do plano cartesiano que representa o mundo
    int relogio;
};

/* talvez apagar isso? */

// inicialização de cada herói
/* void inicializa_herois (struct heroi_t *heroi); */

// inicialização de cada base 
/* void inicializa_bases (struct base_t *base); */

// inicialização de cada missão 
/* void inicializa_missoes (struct missao_t *missoes); */

void inicializa_mundo (struct mundo_t *mundo);