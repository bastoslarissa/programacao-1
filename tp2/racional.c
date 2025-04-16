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

//Recebe um número racional e o simplifica.
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

    if (den_simplificado < 0) {
      num_simplificado *= (-1);
      den_simplificado *= (-1);
    }

    if (valido_r(num_r) == 1) {
      num_r.num = num_simplificado;
      num_r.den = den_simplificado;
      return (num_r);
    }

    return (r);
}

/* Cria um número racional com o numerador e denominador indicados. */
struct racional cria_r (long numerador, long denominador) {
  struct racional num_r; 

  num_r.num = numerador;
  num_r.den = denominador;

  return (num_r);

}

/* Retorna 1 se o racional r for válido ou 0 se for inválido. */
int valido_r (struct racional r) {

  if ((r.den) == 0)
    return(0);
  else 
    return (1);

}

/* Retorna um número racional aleatório na forma simplificada. */
struct racional sorteia_r (long min, long max) {

  struct racional r;

  r.num = aleat (min, max);
  r.den = aleat (min, max);

  return (simplifica_r(r));

}

/* Imprime um racional r, respeitando estas regras:
   - o racional deve ser impresso na forma simplificada;
   - não imprima espaços em branco e não mude de linha;
   - a saída deve ter o formato "num/den", a menos dos casos abaixo:
     - se o racional for inválido, imprime a mensagem "NaN" (Not a Number);
     - se o numerador for 0, imprime somente "0";
     - se o denominador for 1, imprime somente o numerador;
     - se o numerador e denominador forem iguais, imprime somente "1";
     - se o racional for negativo, o sinal "-" vem antes do numerador;
     - se numerador e denominador forem negativos, o racional é positivo. */
void imprime_r (struct racional r) { /* é um void, só vai printar as coisas na tela mesmo, não vai retornar nada */
 
  int mmc_valor;

  r = simplifica(r);
  
  if (!valido_r(r)) {
    printf("Nan");
  }

  if (r1.den == r2.den) {
    r.num = (r1.num + r2.num);
    r.den = r1.den;
  } 

  else { 
    mmc_valor = mmc(r1.den, r2.den);
    r.num = ( ((mmc_valor / r1.den) * r1.num) + ((mmc_valor / r2.den) * r2.num) );
    r.den = mmc_valor;
  }

        
}

/* Compara dois racionais r1 e r2. Retorno: -2 se r1 ou r2 for inválido,
 * -1 se r1 < r2, 0 se r1 = r2 ou 1 se r1 > r2 */
int compara_r (struct racional r1, struct racional r2) {

  if (!valido_r(r1) || !valido_r(r2)) 
    return (-2);

  if ( (r1.num / r1.den) < (r2.num / r2.den) ) 
    return (-1);

  if ((r1.num / r1.den) == (r2.num / r2.den) )
    return (0);

  if ( (r1.num / r1.den) > (r2.num / r2.den) )
    return (1);
}
