/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 24/09/2024 para a disciplina CI1001 - Programação 1.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

#define SIZE 100


/* Funções auxiliares */

/* Função que realiza a troca de dois elementos */
void ordena (struct racional v_aux[], int tam) { 
    
    int i, j, min;
    struct racional aux;

    for (i = 0; i < (tam-1); i++) {
       min = i;
       
       for (j = (i+1); j < tam; j++) {
         if((compara_r(v_aux[j], v_aux[min])) == -1) 
           min = j;
       }

       if (i != min) {
         aux = v_aux[i];
         v_aux[i] = v_aux[min];
         v_aux[min] = aux;
       }
    }
}



/* programa principal */
int main ()
{

  struct racional v[SIZE], v_aux[SIZE];
  struct racional *r3;
  int n, i, j = 0, m = 0;
  int soma;

  scanf("%d", &n);

  /*Preenche o vetor com n números racionais lidos da entrada */
  for (i = 0; i < n; i++) {
    scanf("%ld", &v[i].num);
    scanf("%ld", &v[i].den);
  }

  /* Imprime o conteúdo do vetor lido */
  printf("VETOR = ");
  for (i = 0; i < n; i++) {
     imprime_r(v[i]);
     printf(" ");
  }

  /* Elimina os racionais inválidos do vetor */
  for (i = 0; i < n; i++) {

    if (valido_r(v[i])) {
      v_aux[j].num = v[i].num;
      v_aux[j].den = v[i].den;
      j++;
      m++;
    }  
  }
  
  /* Imprime o conteúdo do vetor sem racionais inválidos */
  printf("\n VETOR = ");
  for (i = 0; i < m; i++) {
     imprime_r(v_aux[i]);
     printf(" ");
  }

  /* Ordena o vetor */
  ordena(v_aux, m);

  /* Imprime o vetor ordenado */
  printf("\n VETOR = ");
  for (i = 0; i < m; i++) {
     imprime_r(v_aux[i]);
     printf(" ");
  }

  /* Calcula a soma dos elementos do vetor */
  for (i = 0; i < m-1; i++) {
    soma_r(v[i], v[i + 1], r3);
    soma += r3;
  }
  
  return (0) ;
}
