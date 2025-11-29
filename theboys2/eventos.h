 #include "mundo.h"

int chega (int *tempo, struct heroi_t *heroi, struct base_t *base, struct fprio_t *lef);

int espera (int *tempo, struct heroi_t *heroi, struct base_t *base, struct fprio_t *lef);

int desiste (int *tempo, struct heroi_t *heroi, struct base_t *base, struct mundo_t *mundo, struct fprio_t *lef);

int avisa (int *tempo, struct base_t *base, struct mundo_t *mundo, struct fprio_t *lef);

int entra (int *tempo, struct heroi_t *heroi, struct base_t *base, struct fprio_t *lef);

int sai (int *tempo, struct heroi_t *heroi, struct base_t *base, struct mundo_t *mundo, struct fprio_t *lef);

int viaja (int *tempo, struct heroi_t *heroi, struct base_t *base_d, struct mundo_t *mundo, struct fprio_t *lef);

int morre (int *tempo, struct heroi_t *heroi, struct base_t *base, struct missao_t *missao, struct fprio_t *lef);

int missao (int *tempo, struct missao_t *missao, struct mundo_t *mundo, struct fprio_t *lef);

int fim (int *tempo, struct mundo_t *mundo, struct fprio_t *lef);
