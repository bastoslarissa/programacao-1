/* #include "eventos.h"
#include "entidades.h"
#include "conjunto.h"
#include "fila.h"

void *chega (int *tempo, struct heroi_t *heroi, struct base_t *base) {

    // atualiza a base de herói
    heroi -> base = base -> id;

    // caso: há vagas na base e a fila de espera está vazia
    if ( ( (cjto_card(base -> presentes)) < (base -> lotacao) ) && (fila_tamanho(base -> espera) == 0) ) {

        espera(tempo, heroi, base); // herói escolhe esperar
        //insere na lef evento espera
    }
    
    else 

}  */