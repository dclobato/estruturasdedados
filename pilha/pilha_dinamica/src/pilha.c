#include <stdlib.h>
#include <stdbool.h>
#include <pilha.h>

bool pilha_inicializa (PILHA *pilha)
{
  *pilha = NULL;
  return true;
}

bool pilha_destroi (PILHA *pilha)
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

bool pilha_PUSH (PILHA *pilha, const TIPO_DADO *valor)
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

bool pilha_POP (PILHA *pilha, TIPO_DADO *valor)
{
  NOH_PILHA *aux;

  if (*pilha == NULL)
  {
    return false;
  }

  *valor = (*pilha)->dado;
  aux = *pilha;
  *pilha = aux->sucessor;
  free(aux);
  return true;
}

bool pilha_estavazia (const PILHA *pilha)
{
  return (*pilha == NULL);
}

bool pilha_estacheia (const PILHA *pilha)
{
  return false;
}

unsigned int pilha_numelementos (const PILHA *pilha)
{
  NOH_PILHA *aux;
  unsigned int elementos;

  elementos = 0;
  aux = *pilha;

  while (aux)
  {
    aux = aux->sucessor;
    elementos++;
  }

  return (elementos);
}

bool pilha_descritor_inicializa (PILHA_DESCRITOR *pilha)
{
  pilha->numelementos = 0;
  pilha->elementos_da_pilha = NULL;
  return true;
}

bool pilha_descritor_destroi (PILHA_DESCRITOR *pilha)
{
  NOH_PILHA *ponteiro_auxiliar;
  ponteiro_auxiliar = pilha->elementos_da_pilha;

  while (ponteiro_auxiliar)
  {
    ponteiro_auxiliar = ponteiro_auxiliar->sucessor;
    pilha->elementos_da_pilha = ponteiro_auxiliar;
    free(ponteiro_auxiliar);
  }

  pilha->numelementos = 0;
  return true;
}

bool pilha_descritor_PUSH (PILHA_DESCRITOR *pilha, const TIPO_DADO *valor)
{
  NOH_PILHA *novo_noh;

  novo_noh = (NOH_PILHA *) malloc(sizeof(NOH_PILHA));

  if (!novo_noh)
  {
    return false;
  }

  novo_noh->dado = *valor;
  novo_noh->sucessor = pilha->elementos_da_pilha;
  pilha->elementos_da_pilha = novo_noh;

  pilha->numelementos++;
  return true;
}

bool pilha_descritor_POP (PILHA_DESCRITOR *pilha, TIPO_DADO *valor)
{
  NOH_PILHA *ponteiro_auxiliar;

  if (!pilha->elementos_da_pilha)
  {
    return false;
  }

  *valor = pilha->elementos_da_pilha->dado;
  ponteiro_auxiliar = pilha->elementos_da_pilha;
  pilha->elementos_da_pilha = ponteiro_auxiliar->sucessor;
  free(ponteiro_auxiliar);

  pilha->numelementos--;
  return true;
}

bool pilha_descritor_estavazia (const PILHA_DESCRITOR *pilha)
{
  return (pilha->numelementos == 0);
}

bool pilha_descritor_estacheia (const PILHA_DESCRITOR *pilha)
{
  return false;
}

unsigned int pilha_descritor_numelementos (const PILHA_DESCRITOR *pilha)
{
  return pilha->numelementos;
}
