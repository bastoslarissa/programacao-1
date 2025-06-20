#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

// item a guardar na fila
struct item_t {
    int dado1;
    int dado2;
};

//------------------------------------------------------------------------------
// cria um novo item
struct item_t *item_cria(int a, int b) {
    struct item_t *item;
    item = malloc(sizeof(struct item_t));
    if (!item)
        abort();
    item->dado1 = a;
    item->dado2 = b;
    return item;
}

//------------------------------------------------------------------------------
// destroi um item
struct item_t *item_destroi(struct item_t *item) {
    if (item)
        free(item);
    return NULL;
}

//------------------------------------------------------------------------------
// imprime a fila
void fila_print(struct fila_t *f) {
    int tam = fila_tamanho(f);
    printf("Fila: ");
    fila_imprime(f);

    if (tam <= 0)
        printf(" (0 itens)\n");
    else if (tam == 1)
        printf(" (1 item)\n");
    else
        printf(" (%d itens)\n", tam);
}

//------------------------------------------------------------------------------
// imprime mensagem de erro e encerra execução
void erro(char *msg) {
    fprintf(stderr, "ERRO: %s\n", msg);
    exit(1);
}

//------------------------------------------------------------------------------
// main
int main() {
    struct fila_t *f;
    struct item_t *item;
    int status;

    // Cria a fila
    printf("Cria a fila:\n");
    f = fila_cria();
    if (!f)
        erro("não criou a fila");
    fila_print(f);
    printf("\n");

    // Insere itens na fila
    printf("Insere 5 itens:\n");
    for (int i = 0; i < 5; i++) {
        item = item_cria(i, i * 10);
        if (!item)
            erro("não criou o item");
        printf("Insere item [%d %d]\n", item->dado1, item->dado2);
        status = fila_insere(f, item);
        if (status < 0)
            erro("não inseriu na fila");
        fila_print(f);
    }
    printf("\n");

    // Retira 2 itens
    printf("Retira 2 itens:\n");
    for (int i = 0; i < 2; i++) {
        item = (struct item_t *)fila_retira(f);
        if (item) {
            printf("Retirou item [%d %d]\n", item->dado1, item->dado2);
            item = item_destroi(item);
        } else {
            erro("não retirou item");
        }
        fila_print(f);
    }
    printf("\n");

    // Insere mais 2 itens
    printf("Insere mais 2 itens:\n");
    for (int i = 5; i < 7; i++) {
        item = item_cria(i, i * 10);
        if (!item)
            erro("não criou o item");
        printf("Insere item [%d %d]\n", item->dado1, item->dado2);
        status = fila_insere(f, item);
        if (status < 0)
            erro("não inseriu na fila");
        fila_print(f);
    }
    printf("\n");

    // Retira todos os itens restantes
    printf("Retira todos os itens:\n");
    while (fila_tamanho(f) > 0) {
        item = (struct item_t *)fila_retira(f);
        if (item) {
            printf("Retirou item [%d %d]\n", item->dado1, item->dado2);
            item = item_destroi(item);
        } else {
            erro("não retirou item");
        }
        fila_print(f);
    }
    printf("\n");

    // Testa operações inválidas
    printf("Testa operações inválidas:\n");

    item = item_cria(99, 99);

    // insere com fila NULL
    status = fila_insere(NULL, item);
    if (status != -1)
        erro("insere com fila NULL não retornou erro");

    // insere com item NULL
    status = fila_insere(f, NULL);
    if (status != -1)
        erro("insere com item NULL não retornou erro");

    // retira com fila NULL
    item = fila_retira(NULL);
    if (item)
        erro("retira com fila NULL não retornou erro");

    // tamanho com fila NULL
    status = fila_tamanho(NULL);
    if (status != -1)
        erro("tamanho com fila NULL não retornou erro");

    item = item_destroi(item);
    printf("\n");

    // Destroi a fila
    printf("Destroi a fila:\n");
    f = fila_destroi(f);
    fila_print(f);
    printf("\n");

    return 0;
}
