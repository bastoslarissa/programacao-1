#include <stdio.h>
#include "entidades.h"

void *chega (int *tempo, struct heroi_t *heroi, struct base_t *base);

void *espera (int *tempo, struct heroi_t *heroi, struct base_t *base);

void *desiste (int *tempo, struct heroi_t *heroi, struct base_t *base);

void *avisa (int *tempo, struct base_t *base);

void *entra (int *tempo, struct heroi_t *heroi, struct base_t *base);

void *sai (int *tempo, struct heroi_t *heroi, struct base_t *base);

void *viaja (int *tempo, struct heroi_t *heroi, struct base_t *based);

void *morre (int *tempo, struct heroi_t *heroi, struct base_t *base);

void *missao (int *tempo, struct missao_t *missao);

void *fim (int *tempo);

