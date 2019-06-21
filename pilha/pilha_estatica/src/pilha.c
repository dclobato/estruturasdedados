#include <stdbool.h>
#include <stdio.h>
#include <pilha.h>
#include <limits.h>

bool inicializa_pilha(PILHA *pilha)
{
  pilha->topo = UINT_MAX;
  return true;
}

bool PUSH(PILHA *pilha, const TIPO_DADO *valor)
{
  if (pilha->topo == TAM_PILHA - 1)
  {
    return false;
  }

  pilha->topo = pilha->topo + 1;
  pilha->dados[pilha->topo] = *valor;
  return true;
}

bool POP(PILHA *pilha, TIPO_DADO *valor)
{
  if (pilha->topo == UINT_MAX)
  {
    return false;
  }

  *valor = pilha->dados[pilha->topo];
  pilha->topo = pilha->topo - 1;
  return true;
}

bool destroi_pilha(PILHA *pilha)
{
  return inicializa_pilha(pilha);
}
