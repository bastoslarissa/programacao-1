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
    struct coordenadas TamanhoMundo;    //coordenadas máximas do plano cartesiano que representa o mundo
    int relogio;
};

