/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 09/09/2025 para a disciplina CI1001 - Programação 1.
*/

#include <stdio.h>
#include <stdlib.h>
#include "racional.h"


void le_vetor (int tam, struct racional **v) {

  long int numerador, denominador;

  // preenche o vetor com n racionais lidos da entrada
  for (int i = 0; i < tam; i++) {
    scanf("%ld", &numerador);
    scanf("%ld", &denominador);

    v[i] = cria_r(numerador, denominador);

  }
}

void imprime_vetor(int tam, struct racional **v) {
    printf("VETOR = ");
    for (int i = 0; i < tam; i++) {
        imprime_r(v[i]);

        if (i < tam - 1) 
          printf(" "); 
    }
}

void remove_invalidos (struct racional **v, int *v_tam) {

  int i = 0;
  int j = *v_tam - 1;

  // percorre o vetor do início ao fim
  while (i <= j) {
    if (!valido_r(v[i])) {
      free(v[i]); 

      while (j > i && !valido_r(v[j])) {
        free(v[j]);
        j--;
        (*v_tam)--;
      }

      if (j > i) {
        v[i] = v[j];
        j--;
        (*v_tam)--;
      }
      else {
        (*v_tam)--;
      }
    }
      i++;
        

  }
}      

void ordena_vetor (struct racional **v, int v_tam) {

  for (int i = 0; i < v_tam -1; i++) {
    int min = i;

    for (int j = i + 1; j < v_tam; j++) {

      if (compara_r(v[j], v[min]) == - 1) {
        min = j;
      }
    }
    if (min != i) {
      struct racional *aux = v[i];
      v[i] = v[min];
      v[min] = aux;
    }
  }

}

struct racional *soma_vetor(struct racional **v, int v_tam) {
    if (v_tam == 0)
        return cria_r(0, 1); 

    struct racional *soma = cria_r(numerador_r(v[0]), denominador_r(v[0]));
    struct racional *aux = cria_r(0, 1);

    for (int i = 1; i < v_tam; i++) {
        soma_r(soma, v[i], aux);
        destroi_r(&soma);

        soma = cria_r(numerador_r(aux), denominador_r(aux));
    }

    destroi_r(&aux);
    return soma;
}

void imprime_soma (struct racional *soma) {

  printf("SOMA = ");
  imprime_r(soma);
}

/* programa principal */
int main () {

  int n;

  // lê um valor n tal que 0 < n < 100
  do 
    scanf("%d", &n);
  while (n < 0 || n > 100);

  struct racional **v = malloc(n * sizeof(struct racional *));

  // preenche o vetor com n racionais lidos da entrada
  le_vetor(n, v);

  // imprime o vetor 
  imprime_vetor(n, v);
  printf("\n");

  int v_tam = n; 
  // remove inválidos do vetor
  remove_invalidos(v, &v_tam);

  // imprime o vetor sem inválidos
  imprime_vetor(v_tam, v);
  printf("\n");

  // ordena o vetor em ordem crescente 
  ordena_vetor(v, v_tam);

  // imprime o vetor ordenado
  imprime_vetor(v_tam, v);
  printf("\n");

  struct racional *soma;
  // calcula a soma dos racionais 
  soma = soma_vetor(v, v_tam);

  // imprime a soma do vetor;
  imprime_soma(soma);
  printf("\n");

  destroi_r(&soma);
  
  // libera racionais 
  for (int i = 0; i < v_tam; i++)
    destroi_r(&v[i]);

  // libera o vetor de ponteiros
  free(v);

return (0) ;
}

