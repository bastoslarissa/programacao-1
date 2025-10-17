#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

int main () {

    struct lista *list;

    list = lista_cria ();

    lista_destroi(&list);
}