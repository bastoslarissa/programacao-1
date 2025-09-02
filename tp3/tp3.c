/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 24/09/2024 para a disciplina CI1001 - Programação 1.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include "racional.h"

/* Maximo Divisor Comum entre a e b      */
/* calcula o mdc pelo metodo de Euclides */
 long mdc (long a, long b) {

  if (b == 0)
    return a;
  else
    return mdc(b, a % b);
  } 

/* Simplifica o número racional indicado no parâmetro.
 * Por exemplo, se o número for 10/8 muda para 5/4.
 * Retorna 1 em sucesso e 0 se r for inválido ou o ponteiro for nulo.
 * Se ambos numerador e denominador forem negativos, o resultado é positivo.
 * Se o denominador for negativo, o sinal deve migrar para o numerador. */
int simplifica_r (struct racional *r) 
{
  
  // verifica se o racional é válido
  if ( !r || (!valido_r(r)) )
    return 0;

  // simplifica o número racional 
  r -> num = r -> num / mdc(r -> num, r -> den);
  r -> den = r -> den / mdc(r -> num, r -> den);

  // se ambos numerador e denominador são negativos, muda o sinal
  if ((r -> num  < 0) && (r -> den < 0)) {
    r -> num = (r -> num) * (-1);
    r -> den = (r -> den) * (-1);
  }

  //se o denominador for negativo o sinal migra pro numerador
  else if ((r -> den < 0) && (r -> num > 0)) {
    r -> num = (r -> num ) * (-1);
    r -> den = (r -> den) * (-1);
  }

  return 1;
  
}

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

struct racional *num_r2 = cria_r(10, 8);

simplifica_r(num_r);

printf("%ld/%ld \n", num_r2 -> num, num_r2 -> den);


  return (0) ;
}

