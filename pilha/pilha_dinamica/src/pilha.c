#include <stdlib.h>
#include <stdbool.h>
#include <pilha.h>

bool inicializa_pilha(PILHA *pilha)
{
  *pilha = NULL;
  return true;
}

bool destroi_pilha(PILHA *pilha)
{
  PILHA t;

  while (pilha)
  {
    t = *pilha;
    *pilha = (*pilha)->sucessor;
    free(t);
  }

  return true;
}

bool PUSH(PILHA *pilha, const TIPO_DADO *valor)
{
  PILHA t;
  t = (PILHA) malloc(sizeof(NOH));

  if (!t)
  {
    return false;
  }

  t->dado = *valor;
  t->sucessor = *pilha;
  *pilha = t;
  return true;
}

bool POP(PILHA *pilha, TIPO_DADO *valor)
{
  PILHA t;

  if (!*pilha)
  {
    return false;
  }

  *valor = (*pilha)->dado;
  t = *pilha;
  *pilha = t->sucessor;
  free(t);
  return true;
}
