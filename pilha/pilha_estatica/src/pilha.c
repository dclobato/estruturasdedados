#include <stdbool.h>
#include <pilha.h>
#include <limits.h>

bool pilha_inicializa (PILHA *pilha)
{
  pilha->topo = UINT_MAX;
  return true;
}

bool pilha_PUSH (PILHA *pilha, const TIPO_DADO *valor)
{
  if (pilha->topo == TAM_PILHA - 1)
  {
    return false;
  }

  pilha->topo = pilha->topo + 1;
  pilha->dados[pilha->topo] = *valor;
  return true;
}

bool pilha_POP (PILHA *pilha, TIPO_DADO *valor)
{
  if (pilha->topo == UINT_MAX)
  {
    return false;
  }

  *valor = pilha->dados[pilha->topo];
  pilha->topo = pilha->topo - 1;
  return true;
}

bool pilha_destroi (PILHA *pilha)
{
  return pilha_inicializa(pilha);
}

bool pilha_estavazia (const PILHA *pilha)
{
  return (pilha->topo == UINT_MAX);
}

bool pilha_estacheia (const PILHA *pilha)
{
  return (pilha->topo == TAM_PILHA - 1);
}

unsigned int pilha_numelementos (const PILHA *pilha)
{
  if (pilha->topo == UINT_MAX)
    return 0;
  return (pilha->topo + 1);
}
