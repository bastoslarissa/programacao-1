/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 24/09/2024 para a disciplina CI1001 - Programação 1.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include "racional.h"

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

struct racional *num_r2 = cria_r(10, 15);
struct racional *num_r3 = cria_r(2, 0);

imprime_r(num_r2);
printf("\n");

if (compara_r(num_r2, num_r3) == -2)
  printf("invalido\n");
else if (compara_r(num_r2, num_r3) == -1)
  printf("r1 < r2\n");
else if (compara_r(num_r2, num_r3) == 0)
  printf("r1 = r2\n");
else if (compara_r(num_r2, num_r3) == 1)
  printf("r1 > r2\n");

return (0) ;
}

