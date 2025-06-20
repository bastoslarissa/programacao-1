#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

int main() {
    // 1. Cria a fila
    struct fila_t *f = fila_cria();
    printf("Fila criada.\n");
    fila_imprime(f);
    printf("\nTamanho da fila: %d\n\n", fila_tamanho(f));

    // 2. Insere elementos na fila
    int *a = malloc(sizeof(int));
    int *b = malloc(sizeof(int));
    int *c = malloc(sizeof(int));
    int *d = malloc(sizeof(int));
    int *e = malloc(sizeof(int));

    *a = 10;
    *b = 20;
    *c = 30;
    *d = 40;
    *e = 50;

    fila_insere(f, a);
    fila_insere(f, b);
    fila_insere(f, c);
    fila_insere(f, d);
    fila_insere(f, e);

    printf("Após inserir elementos:\n");
    fila_imprime(f);
    printf("\nTamanho da fila: %d\n\n", fila_tamanho(f));

    // 3. Retira um elemento
    int *removido = (int *)fila_retira(f);
    printf("Item removido: %d\n", *removido);
    free(removido); // libera o item removido

    printf("Após remover um elemento:\n");
    fila_imprime(f);
    printf("\nTamanho da fila: %d\n\n", fila_tamanho(f));

    // 4. Destroi a fila
    f = fila_destroi(f);
    printf("Fila destruída.\n");

    // Após destruir, tenta imprimir
    fila_imprime(f);
    printf("\nTamanho da fila: %d\n", fila_tamanho(f));

    return 0;
}
