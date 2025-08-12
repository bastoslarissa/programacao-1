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
long aleat(long min, long max)
{

  long aleatorio = rand() % (max - min + 1) + min;

  return (aleatorio);
}

/* Máximo Divisor Comum entre a e b      */
/* calcula o MDC pelo método de Euclides */
long mdc(long a, long b)
{

  if (b == 0)
    return a;
  else
    return mdc(b, a % b);
}

/* Mínimo Múltiplo Comum entre a e b */
long mmc(long a, long b)
{

  int mmc_res = (a * b) / mdc(a, b);

  return (mmc_res);
}

// Recebe um número racional e o simplifica.
struct racional simplifica_r(struct racional r)
{
  long num_simplificado;
  long den_simplificado;
  struct racional num_r = r;

  num_simplificado = (num_r.num) / mdc(num_r.num, num_r.den);

  den_simplificado = (num_r.den) / mdc(num_r.num, num_r.den);

  if (((num_r.num < 0) && (num_r.den < 0)) || (den_simplificado < 0))
  {
    num_simplificado *= (-1);
    den_simplificado *= (-1);
  }

  if (den_simplificado < 0)
  {
    num_simplificado *= (-1);
    den_simplificado *= (-1);
  }

  if (valido_r(num_r) == 1)
  {
    num_r.num = num_simplificado;
    num_r.den = den_simplificado;
    return (num_r);
  }

  return (r);
}

/* Cria um número racional com o numerador e denominador indicados. */
struct racional cria_r(long numerador, long denominador)
{
  struct racional num_r;

  num_r.num = numerador;
  num_r.den = denominador;

  return (num_r);
}

/* Retorna 1 se o racional r for válido ou 0 se for inválido. */
int valido_r(struct racional r)
{

  if ((r.den) == 0)
    return (0);
  else
    return (1);
}

/* Retorna um número racional aleatório na forma simplificada. */
struct racional sorteia_r(long min, long max)
{

  struct racional r;

  r.num = aleat(min, max);
  r.den = aleat(min, max);

  return (simplifica_r(r));
}

/* Imprime um racional r, respeitando estas regras: */
void imprime_r(struct racional r)
{

  if (!valido_r(r))
  {
    printf("NaN");
    return;
  }

  r = simplifica_r(r);

  if (r.num == 0)
    printf("%d", 0);

  else if (r.den == 1)
    printf("%ld", r.num);

  else if (r.num == r.den)
    printf("%d", 1);

  else
    printf("%ld/%ld", r.num, r.den);
}

/* Compara dois racionais r1 e r2. Retorno: -2 se r1 ou r2 for inválido,
 * -1 se r1 < r2, 0 se r1 = r2 ou 1 se r1 > r2 */
int compara_r(struct racional r1, struct racional r2)
{

  if (!valido_r(r1) || !valido_r(r2))
    return (-2);

  if (((float)r1.num / r1.den) < ((float)r2.num / r2.den))
    return (-1);

  if (((float)r1.num / r1.den) == ((float)r2.num / r2.den))
    return (0);

  return (1);
}

/* Retorna a soma dos racionais r1 e r2 no parametro *r3. */
int soma_r(struct racional r1, struct racional r2, struct racional *r3)
{

  if ((!valido_r(r1) || !valido_r(r2)) || (r3 == NULL))
    return (0);

  if (r1.den == r2.den)
  {
    r3->num = (r1.num + r2.num);
    r3->den = r1.den;
  }

  else
  {
    r3->num = (((mmc(r1.den, r2.den)) / r1.den) * r1.num) + (((mmc(r1.den, r2.den)) / r2.den) * r2.num);
    r3->den = mmc(r1.den, r2.den);
  }

  *r3 = simplifica_r(*r3);

  return (1);
}

/* Retorna a subtracao dos racionais r1 e r2 no parametro *r3. */
int subtrai_r(struct racional r1, struct racional r2, struct racional *r3)
{

  if ((!valido_r(r1) || !valido_r(r2)) || (r3 == NULL))
    return (0);

  if (r1.den == r2.den)
  {
    r3->num = (r1.num - r2.num);
    r3->den = r1.den;
  }

  else
  {
    r3->num = (((mmc(r1.den, r2.den)) / r1.den) * r1.num) - (((mmc(r1.den, r2.den)) / r2.den) * r2.num);
    r3->den = mmc(r1.den, r2.den);
  }

  return (1);
}

/* Retorna a multiplicacao dos racionais r1 e r2 no parametro *r3. */
int multiplica_r(struct racional r1, struct racional r2, struct racional *r3)
{

  if ((!valido_r(r1) || !valido_r(r2)) || (r3 == NULL))
    return (0);

  r3->num = (r1.num * r2.num);
  r3->den = (r1.den * r2.den);

  return (1);
}

/* Retorna a divisao dos racionais r1 e r2 no parametro *r3.
 * Retorna 1 se a operacao foi bem sucedida ou
 *         0 se r1 ou r2 for inválido ou se *r3 for nulo */
int divide_r(struct racional r1, struct racional r2, struct racional *r3)
{

  r3->num = (r1.num * r2.den);
  r3->den = (r1.den * r2.num);

  if ((!valido_r(r1) || !valido_r(r2)) || (r3 == NULL))
    return (0);

  return (1);
}
