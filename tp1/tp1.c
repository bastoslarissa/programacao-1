/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 16/09/2024 para a disciplina CI1001 - Programação 1.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

/* programa principal */
int main () {

  int n;
  int max;
  int i;
  struct racional r_soma, r_sub, r_multi, r_div, r1, r2;

    srand (0); 
    
    /* lê um n que está entre 0 e 100*/
    scanf("%d", &n);
    while (n < 0 || n > 100)
      scanf("%d", &n);

    /* lê um max que está entre 0 e 30*/
    scanf("%d", &max);
    while (max < 0 || max > 30)
      scanf("%d", &max);


    for (i = 1; i <= n; i++) {
      printf("%d: ", i);

      r1 = sorteia_r(max * (-1), max);
      r2 = sorteia_r(max * (-1), max);

      imprime_r(r1);
      printf(" ");
      imprime_r(r2);
      printf(" ");

      r_soma = soma_r(r1, r2);
      r_sub = subtrai_r(r1, r2);
      r_multi = multiplica_r(r1, r2);
      r_div = divide_r(r1, r2);

      if (r_div.den == 0 || r_soma.den == 0 || r_sub.den == 0 || r_multi.den == 0)
        return (1);

      imprime_r(r_soma);
      printf(" ");

      imprime_r(r_sub);
      printf(" ");

      imprime_r(r_multi);
      printf(" ");

      imprime_r(r_div);
      printf(" ");

      printf("\n");
      
    }

    return (0) ;


}

