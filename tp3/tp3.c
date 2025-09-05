/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 24/09/2024 para a disciplina CI1001 - Programação 1.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

/* programa principal */
int main () {

  int n;

  // lê um valor n tal que 0 < n < 100
  do 
    scanf("%d", &n);
  while (n < 0 && n > 100);

  // aloca um vetor de tamanho n
  struct racional *vetor = malloc(n * sizeof(struct racional)); 

  // preenche o vetor com n racionais lidos da entrada
  for (int i = 0; i < n; i++) {
    scanf("%ld", &vetor[i].num);
    scanf("%ld", &vetor[i].den);
  }

  // imprime o vetor lido
  printf("VETOR = ");
  for (int i = 0; i < n; i++) {
    imprime_r(&vetor[i]);
    printf(" ");
  }

  // elimina os racionais inválidos do vetor
  for (int i = 0; i < n; i++) {
    if (!valido_r(&vetor[i]))
      destroi_r(&vetor[i]);
  }

  // imprime o vetor sem inválidos
  printf("\nVETOR = ");
  for (int i = 0; i < n; i++) {
    imprime_r(&vetor[i]);
    printf(" ");
  }

return (0) ;
}

