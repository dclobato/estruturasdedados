#include <stdlib.h>
#include <stdbool.h>
#include <pilha.h>
bool pilha_inicializar(PILHA *pilha)
{
  pilha->numelementos = 0;
  pilha->elementos_da_pilha = NULL;
  return true;
}

bool pilha_destruir(PILHA *pilha)
{
  NOH_PILHA *aux;

  while (pilha->elementos_da_pilha != NULL)
  {
    aux = pilha->elementos_da_pilha;
    pilha->elementos_da_pilha = pilha->elementos_da_pilha->sucessor;
    free(aux);
  }

  pilha->numelementos = 0;
  return true;
}

bool pilha_PUSH(PILHA *pilha, const TIPO_DADO *valor)
{
  NOH_PILHA *aux;

  aux = (NOH_PILHA *) malloc(sizeof(NOH_PILHA));

  if (aux == NULL)
  {
    return false;
  }

  aux->dado = *valor;
  aux->sucessor = pilha->elementos_da_pilha;
  pilha->elementos_da_pilha = aux;

  pilha->numelementos++;
  return true;
}

bool pilha_POP(PILHA *pilha, TIPO_DADO *valor)
{
  NOH_PILHA *aux;

  if (pilha_esta_vazia(pilha))
  {
    return false;
  }

  *valor = pilha->elementos_da_pilha->dado;
  aux = pilha->elementos_da_pilha;
  pilha->elementos_da_pilha = aux->sucessor;
  free(aux);

  pilha->numelementos--;
  return true;
}

bool pilha_PEEK(PILHA *pilha, TIPO_DADO *valor)
{
  if (pilha_esta_vazia(pilha))
  {
    return false;
  }

  *valor = pilha->elementos_da_pilha->dado;
  return true;
}

bool pilha_esta_vazia(const PILHA *pilha)
{
  return (pilha->numelementos == 0);
}

bool pilha_esta_cheia(const PILHA *pilha)
{
  // Como estamos com alocacao dinamica, nao ha como saber se a pilha
  // esta cheia antes de tentar fazer um novo PUSH
  return false;
}

unsigned int pilha_numero_de_elementos(const PILHA *pilha)
{
  return pilha->numelementos;
}
