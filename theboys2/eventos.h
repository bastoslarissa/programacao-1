#include "mundo.h"

void *chega (int *tempo, struct heroi_t *heroi, struct base_t *base, struct fprio_t *lef);

void *espera (int *tempo, struct heroi_t *heroi, struct base_t *base, struct fprio_t *lef);

void *desiste (int *tempo, struct heroi_t *heroi, struct base_t *base, struct fprio_t *lef);

void *avisa (int *tempo, struct base_t *base, struct fprio_t *lef);

void *entra (int *tempo, struct heroi_t *heroi, struct base_t *base, struct fprio_t *lef);

void *sai (int *tempo, struct heroi_t *heroi, struct base_t *base, struct fprio_t *lef);

void *viaja (int *tempo, struct heroi_t *heroi, struct base_t *base_d, struct fprio_t *lef);

void *morre (int *tempo, struct heroi_t *heroi, struct base_t *base, struct fprio_t *lef);

void *missao (int *tempo, struct missao_t *missao, struct fprio_t *lef);

void *fim (int *tempo, struct fprio_t *lef);
