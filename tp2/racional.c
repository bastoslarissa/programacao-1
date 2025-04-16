/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo de implementação para TAD racional.
 * Feito em 20/09/2024 para a disciplina CI1001 - Programação 1.
 *
 * Este arquivo deve conter as implementações das funções cujos protótipos
 * foram definidos em racional.h. Neste arquivo também podem ser definidas
 * funções auxiliares para facilitar a implementação daquelas funções.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

/* retorna um número aleatório entre min e max, inclusive. */
long aleat (long min, long max) {

  long aleatorio = rand () % (max - min + 1) + min;

  return (aleatorio);
}

/* Máximo Divisor Comum entre a e b      */
/* calcula o MDC pelo método de Euclides */
long mdc (long a, long b) {

  if (a == 0)
    return (b);
  
  if (b == 0)
    return (a);

  int quociente = (a / b);
  int resto = (a % b);

  a = b * quociente + resto;
    return (mdc(a,b));
}

/* Mínimo Múltiplo Comum entre a e b */
long mmc (long a, long b) {

  int mmc_res = (a * b) / mdc(a, b); 

  return(mmc_res);

}

/* Recebe um número racional e o simplifica.
 * Por exemplo, ao receber 10/8 deve retornar 5/4.
 * Se ambos numerador e denominador forem negativos, deve retornar um positivo.
 * Se o denominador for negativo, o sinal deve migrar para o numerador.
 * Se r for inválido, devolve-o sem simplificar. */
struct racional simplifica_r (struct racional r) {
    int num_simplificado;
    int den_simplificado;
    struct racional num_r = r;
  
    num_simplificado = (num_r.num) / mdc(num_r.num, num_r.den);
  
    den_simplificado = (num_r.den) / mdc(num_r.num, num_r.den);
  
    if ( ((num_r.num < 0) && (num_r.den < 0)) || (den_simplificado < 0) ) {
      num_simplificado *= (-1);
      den_simplificado *= (-1);
    }

    /* if (den_simplificado < 0) {
      num_simplificado *= (-1);
      den_simplificado *= (-1);
    } */

    if (valido_r(num_r) == 1) {
      num_r.num = num_simplificado;
      num_r.den = den_simplificado;
      return (num_r);
    }

    return (r);
}

/* Cria um número racional com o numerador e denominador indicados. */
struct racional cria_r (long numerador, long denominador);