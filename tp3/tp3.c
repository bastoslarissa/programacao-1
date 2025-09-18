/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 24/09/2024 para a disciplina CI1001 - Programação 1.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include <stdlib.h>
#include "racional.h"


void le_vetor (int tam, struct racional **v) {

  long int numerador, denominador;

  // preenche o vetor com n racionais lidos da entrada
  for (int i = 0; i < tam; i++) {
    scanf("%ld", numerador);
    scanf("%ld", denominador);

    cria_r(numerador, denominador);

  }
}

void imprime_vetor (int tam, struct racional **v) {

  // imprime o vetor lido
  printf("VETOR = ");
  for (int i = 0; i < tam; i++) {
    imprime_r(v[i]);
    printf(" ");
  }

}

struct racional remove_invalidos (int tam, struct racional **v, int v_tam) {

  struct racional *aux; 

  // percorre o vetor do início ao fim
  for (int i = 0; i < tam; i++) {

    if (!valido_r(v[i])) {
      
      for (int j = tam; j <= tam; tam--) {
        
        if (!valido_r(v[j])) 
          tam--;

        else if (valido(v[j])) {
          v[i] = v[j];
          tam--;
          break;
        }

      }      
    }
  }
}




/* programa principal */
int main () {

  int n, v_tam = 0;

  // lê um valor n tal que 0 < n < 100
  do 
    scanf("%d", &n);
  while (n < 0 && n > 100);

  // aloca um vetor de tamanho n
  struct racional **v = malloc(n * sizeof(struct racional)); 

  // preenche o vetor com n racionais lidos da entrada
  le_vetor(n, v);

  // imprime o vetor lido
  imprime_vetor(n, v);

  // elimina os racionais inválidos do vetor
  remove_invalidos(n, v, v_tam);

  // imprime o vetor sem inválidos
  imprime_vetor(v_tam, v);

  // ordena o vetor em ordem crescente





return (0) ;
}

