#include <stdbool.h>
#include <pilha.h>
#include <limits.h>

bool pilha_inicializar(PILHA *pilha)
{
  pilha->topo = UINT_MAX;
  return true;
}

bool pilha_PUSH(PILHA *pilha, const TIPO_DADO *valor)
{
  if (pilha_esta_cheia(pilha))
  {
    return false;
  }

  pilha->topo++;
  pilha->dados[pilha->topo] = *valor;
  return true;
}

bool pilha_POP(PILHA *pilha, TIPO_DADO *valor)
{
  if (pilha_esta_vazia(pilha))
  {
    return false;
  }

  *valor = pilha->dados[pilha->topo];
  pilha->topo--;
  return true;
}

bool pilha_PEEK(PILHA *pilha, TIPO_DADO *valor)
{
  if (pilha_esta_vazia(pilha))
  {
    return false;
  }

  *valor = pilha->dados[pilha->topo];
  return true;
}

bool pilha_destruir(PILHA *pilha)
{
  return pilha_inicializar(pilha);
}

bool pilha_esta_vazia(const PILHA *pilha)
{
  return (pilha->topo == UINT_MAX);
}

bool pilha_esta_cheia(const PILHA *pilha)
{
  return (pilha->topo == TAM_PILHA - 1);
}

unsigned int pilha_numero_de_elementos(const PILHA *pilha)
{
  if (pilha_esta_vazia(pilha))
  {
    return 0;
  }
  return (pilha->topo + 1);
}
