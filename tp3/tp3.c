/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 24/09/2024 para a disciplina CI1001 - Programação 1.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include "racional.h"

/* coloque aqui as funções auxiliares que precisar neste arquivo */

/* programa principal */
int main ()
{
  struct racional *num_r;

num_r = cria_r(2,3);
printf("%ld/%ld \n", num_r -> num, num_r -> den);

if (valido_r(num_r)) {
  printf("válido \n");
}

destroi_r(num_r);

printf("%ld/%ld \n", num_r -> num, num_r -> den);

  return (0) ;
}

