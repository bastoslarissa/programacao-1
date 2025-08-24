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

/* Função que lê o vetor */
struct racional le_vetor (int n, struct racional *v) {

  for (int i = 0; i < n; i++) {
    scanf("%ld", &v[i].num);
    scanf("%ld", &v[i].den);
  }

  return *v;
}

/* Função que imprime o vetor */
void imprime_vetor (int v_tam, struct racional *v) {

  printf("\nVETOR = ");

  for (int i = 0; i < v_tam; i++) {
     imprime_r(v[i]);
     printf(" ");
  } 
}

/* Função que remove racionais inválidos do vetor */
struct racional remove_invalidos (int n, struct racional *v, int *v_tam) {

  struct racional v_aux[SIZE];
  int j = 0;
  
  // verifica se o racional é válido, se sim, adiciona ele em um vetor auxiliar
  for (int i = 0; i < n; i++) {

    if (valido_r(v[i])) {
      v_aux[j].num = v[i].num;
      v_aux[j].den = v[i].den;
      j++;
      (*v_tam)++;
    }  
  }

  //atribui o vetor auxiliar ao vetor principal
  for (int i = 0; i < *v_tam; i++) {
    v[i] = v_aux[i];
  }

  return *v;
}

/* Função que ordena o vetor através do algoritmo Selection Sort */
void ordena_vetor (struct racional v_aux[], int tam) { 
    
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



/* Programa principal */
int main () {

  // declaração de variáveis 
  struct racional v[SIZE];
  int v_tam = 0;
  struct racional soma;
  soma.num = 0;
  soma.den = 1;
  struct racional soma_aux;
  struct racional *r3 = &soma;
  r3 -> num = 0;
  r3 -> den = 1;
  int n, i;

  scanf("%d", &n); // lê inteiro n

  le_vetor(n, v); // lê vetor de tamanho n

  imprime_vetor(n, v); // imprime conteúdo do vetor lido

  remove_invalidos(n, v, &v_tam); 
    
  imprime_vetor(v_tam, v); // imprime o conteúdo do vetor sem os racionais inválidos

  ordena_vetor(v, v_tam);

  imprime_vetor(v_tam, v); // imprime o vetor ordenado

  // calcula a soma dos racionais do vetor 
  for (i = 0; i < v_tam; i++) {
    soma_r(soma, v[i], &soma_aux);
    soma = soma_aux;
  }

  // imprime a soma dos racionais do vetor
  printf("\nSOMA = ");
  imprime_r(*r3);
  printf("\n");
    return (0) ;

}
  


