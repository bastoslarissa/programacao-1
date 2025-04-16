/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo de implementação para TAD racional.
 * Feito em 16/09/2024 para a disciplina CI1001 - Programação 1.
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
long aleat (long min, long max)
{

  int aleatorio;

  aleatorio = rand () % (max - min + 1) + min;

  return (aleatorio);

}

/* Máximo Divisor Comum entre a e b      */
/* calcula o MDC pelo método de Euclides */
long mdc (long a, long b) {

  if (a == 0)  
    return (b);
  if (b == 0) 
    return (a);

  int q = (a / b);
  int r = (a % b);

  a = b * q - r;
  return (mdc (b, r));
}



/* Mínimo Múltiplo Comum entre a e b */
long mmc (long a, long b)
{
  int res_mmc;
  int mdc_valor;

  mdc_valor = mdc(a, b);

  res_mmc = ((a * b) / mdc_valor);

  return(res_mmc);

} 

/* Recebe um número racional e o simplifica. */
struct racional simplifica_r (struct racional r)
{
  int num_simplificado;
  int den_simplificado;
  int mdc_valor;
  int res_valido_r;
  struct racional num_r = r;

  mdc_valor = mdc(num_r.num, num_r.den);

  num_simplificado = (num_r.num) / mdc_valor;

  den_simplificado = (num_r.den) / mdc_valor;

  if ((num_r.num < 0) && (num_r.den < 0)) {
    num_simplificado *= (-1);
    den_simplificado *= (-1);
  }

  if (den_simplificado < 0) {
    num_simplificado *= (-1);
    den_simplificado *= (-1);
  }

  res_valido_r = valido_r(num_r);  

  if (res_valido_r == 1) {
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

/* Verifica se r é um racional válido */
int valido_r (struct racional r){
  
  if ((r.den) == 0)
    return(0);
  else 
    return (1);
}

/* Retorna um número racional aleatório na forma simplificada. */
struct racional sorteia_r (long min, long max) {
  
  struct racional r_simplificado;
  struct racional r;

  r.num = aleat (min, max);
  r.den = aleat (min, max);

  r_simplificado = simplifica_r(r);

  return (r_simplificado);

} 

/* Imprime um racional r */
void imprime_r (struct racional r) {
  
  struct racional num_r;
  int eh_valido;
  
  num_r = simplifica_r(r);

  eh_valido = valido_r(r);

  if (eh_valido == 0) {
    printf("INVALIDO ");
    return;
  }
  
  else if (num_r.num == 0)
    printf("0 ");
       

  else if (num_r.den == 1)
    printf("%ld ", num_r.num);
        
        
  else if (num_r.num == num_r.den)
    printf("1 ");
         
  else 
    printf("%ld/%ld ", num_r.num, num_r.den);

} 

/* Retorna a soma dos racionais r1 e r2. */
struct racional soma_r (struct racional r1, struct racional r2) {

  int mmc_valor;
  struct racional r;

  if (!valido_r(r1) || !valido_r(r2)) {
    printf("NUMERO INVALIDO \n");
    r.num = 0;
    r.den = 0;
    return(r);
  }

  if (r1.den == r2.den) {
    r.num = (r1.num + r2.num);
    r.den = r1.den;
    return (r);
  } 

  else { 
    mmc_valor = mmc(r1.den, r2.den);
    r.num = ( ((mmc_valor / r1.den) * r1.num) + ((mmc_valor / r2.den) * r2.num) );
    r.den = mmc_valor;
  }

    return (r);
        
} 

/* Retorna a subtração dos racionais r1 e r2. */
struct racional subtrai_r (struct racional r1, struct racional r2) {

  int mmc_valor;
  struct racional r;
  
  if (!valido_r(r1) || !valido_r(r2)) {
    // printf("NUMERO INVALIDO \n");
    r.num = 0;
    r.den = 0;
    return(r);
  }

  if (r1.den == r2.den) {
    r.num = (r1.num - r2.num);
    r.den = r1.den;
    return (r);
  } 

  else { 
    mmc_valor = mmc(r1.den, r2.den);
    r.num = ( ((mmc_valor / r1.den) * r1.num) - ((mmc_valor / r2.den) * r2.num) );
    r.den = mmc_valor;
  }
  
  return(r);

}

/* Retorna a multiplicação dos racionais r1 e r2. */
struct racional multiplica_r (struct racional r1, struct racional r2){

  struct racional r;
  
  if (!valido_r(r1) || !valido_r(r2)) {
    // printf("NUMERO INVALIDO \n");
    r.num = 0;
    r.den = 0;
    return(r);
  }
  else { 
    r.num = (r1.num * r2.num);
    r.den = (r1.den * r2.den);
  }
  
  return(r);

}

/* Retorna a divisão dos racionais r1 e r2. */
struct racional divide_r (struct racional r1, struct racional r2) {

  struct racional r;

  if (!valido_r(r1) || !valido_r(r2)) {
    // printf("NUMERO INVALIDO \n");
    r.num = 0;
    r.den = 0;
    return(r);
  }

  r.num = (r1.num * r2.den);
  r.den = (r1.den * r2.num);

  if (!valido_r(r)) {
    printf("DIVISAO INVALIDA \n");
    r.num = 0;
    r.den = 0;
    return(r);
  }

  else {
    return(r);
  }

}



















