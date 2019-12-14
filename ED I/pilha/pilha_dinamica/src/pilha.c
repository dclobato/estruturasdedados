#include <stdlib.h>
#include <stdbool.h>
#include <pilha.h>

bool pilha_inicializar(PILHA *pilha)
{
  *pilha = NULL;
  return true;
}

bool pilha_destruir(PILHA *pilha)
{
  NOH_PILHA *aux;

  while (*pilha != NULL)
  {
    aux = *pilha;
    *pilha = (*pilha)->sucessor;
    free(aux);
  }

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
  aux->sucessor = *pilha;
  *pilha = aux;
  return true;
}

bool pilha_POP(PILHA *pilha, TIPO_DADO *valor)
{
  NOH_PILHA *aux;

  if (pilha_esta_vazia(pilha))
  {
    return false;
  }

  *valor = (*pilha)->dado;
  aux = *pilha;
  *pilha = aux->sucessor;
  free(aux);
  return true;
}

bool pilha_PEEK(PILHA *pilha, TIPO_DADO *valor)
{
  if (pilha_esta_vazia(pilha))
  {
    return false;
  }

  *valor = (*pilha)->dado;
  return true;
}

bool pilha_esta_vazia(const PILHA *pilha)
{
  return (*pilha == NULL);
}

bool pilha_esta_cheia(const PILHA *pilha)
{
  // Como estamos com alocacao dinamica, nao ha como saber se a pilha
  // esta cheia antes de tentar fazer um novo PUSH
  return false;
}

unsigned int pilha_numero_de_elementos(const PILHA *pilha)
{
  NOH_PILHA *aux;
  unsigned int elementos;

  elementos = 0;
  aux = *pilha;

  while (aux != NULL)
  {
    aux = aux->sucessor;
    elementos++;
  }

  return (elementos);
}