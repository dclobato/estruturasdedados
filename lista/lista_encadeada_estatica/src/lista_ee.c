#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <lista_ee.h>

unsigned int tamanho_lista(const LISTA *lista)
{
  return (lista->numElementos);
}

unsigned int livres_lista(const LISTA *lista)
{
  return (lista->numLivres);
}

bool inicializa_lista(LISTA *lista)
{
  unsigned i, limite;
  lista->numElementos = 0;
  lista->numLivres = TAM_LISTA;
  lista->inicioElementos = UINT_MAX;
  lista->inicioLivres = 0;
  limite = TAM_LISTA - 1;

  for (i = 0; i < limite; i++)
  {
    lista->dados[i].sucessor = i + 1;
  }

  lista->dados[limite].sucessor = UINT_MAX;
  return true;
}

bool destroi_lista(LISTA *lista)
{
  return (inicializa_lista(lista));
}

bool obtem_no_lista(LISTA *lista, unsigned int *posicao)
{
  if (lista->numLivres == 0)
  {
    return false;
  }

  *posicao = lista->inicioLivres;
  lista->inicioLivres = lista->dados[*posicao].sucessor;
  lista->numLivres = lista->numLivres - 1;
  lista->numElementos = lista->numElementos + 1;
  return true;
}

bool libera_no_lista(LISTA *lista, unsigned int posicao)
{
  lista->dados[posicao].sucessor = lista->inicioLivres;
  lista->inicioLivres = posicao;
  lista->numLivres = lista->numLivres + 1;
  lista->numElementos = lista->numElementos - 1;
  return true;
}

bool insere_lista(LISTA *lista, const TIPO_DADO *valor,
                  unsigned int posicao)
{
  unsigned int nodo, aux;
  unsigned int contador, anterior;

  if ((posicao < 0) || (posicao > lista->numElementos) ||
      !obtem_no_lista(lista, &nodo))
  {
    return false;
  }

  contador = 0;
  anterior = UINT_MAX;
  lista->dados[nodo].dado = *valor;
  aux = lista->inicioElementos;

  while (contador < posicao)
  {
    anterior = aux;
    aux = lista->dados[aux].sucessor;
    contador++;
  }

  if (anterior == UINT_MAX)
  {
    lista->dados[nodo].sucessor = lista->inicioElementos;
    lista->inicioElementos = nodo;
  }
  else
  {
    lista->dados[nodo].sucessor = aux;
    lista->dados[anterior].sucessor = nodo;
  }

  return true;
}

void __imprime_lista(const LISTA *lista)
{
  int i;

  for (i = 0; i < TAM_LISTA; i++)
  {
    if (lista->dados[i].sucessor == UINT_MAX)
    {
      printf("[%3u] -> [ -1]: %d\n", i, lista->dados[i].dado);
    }
    else
    {
      printf("[%3u] -> [%3u]: %d\n", i, lista->dados[i].sucessor,
             lista->dados[i].dado);
    }
  }

  if (lista->inicioLivres == UINT_MAX)
  {
    printf("Inicio dos livres: -1\n");
  }
  else
  {
    printf("Inicio dos livres: %u\n", lista->inicioLivres);
  }

  if (lista->inicioElementos == UINT_MAX)
  {
    printf("Inicio dos elementos: -1\n");
  }
  else
  {
    printf("Inicio dos elementos: %u\n", lista->inicioElementos);
  }

  printf("\n\n");
  return;
}

bool remove_lista(LISTA *lista, TIPO_DADO *valor, unsigned int posicao)
{
  int contador, anterior, aux;

  if ((posicao < 0) || (posicao > (tamanho_lista(lista) - 1)))
  {
    return false;
  }

  contador = 0;
  anterior = UINT_MAX;
  aux = lista->inicioElementos;

  while (contador < posicao)
  {
    anterior = aux;
    aux = lista->dados[aux].sucessor;
    contador++;
  }

  if (anterior == UINT_MAX)
  {
    lista->inicioElementos = lista->dados[aux].sucessor;
  }
  else
  {
    lista->dados[anterior].sucessor = lista->dados[aux].sucessor;
  }

  if (valor)
  {
    *valor = lista->dados[aux].dado;
  }

  if (!libera_no_lista(lista, aux))
  {
    return false;
  }

  return true;
}

void imprime_lista(const LISTA *lista)
{
  unsigned i, j;
  printf("Posicoes ocupadas: %u\n", tamanho_lista(lista));
  printf("Posicoes livres: %u\n", livres_lista(lista));
  i = lista->inicioElementos;
  j = 0;

  while (i != UINT_MAX)
  {
    printf("[%03u]: %d\n", j, lista->dados[i].dado);
    i = lista->dados[i].sucessor;
    j++;
  }

  return;
}

bool consulta_lista(LISTA *lista, unsigned int posicao, TIPO_DADO *valor)
{
  unsigned int aux, contador;

  if ((posicao < 0) || (posicao > lista->numElementos))
  {
    return false;
  }

  contador = 0;
  aux = lista->inicioElementos;

  while (contador < posicao)
  {
    aux = lista->dados[aux].sucessor;
    contador++;
  }

  *valor = lista->dados[aux].dado;
  return true;
}

bool insere_ordenado(LISTA *lista, const TIPO_DADO *valor)
{
  unsigned int nodo;
  unsigned int aux, anterior;

  if (!obtem_no_lista(lista, &nodo))
  {
    return false;
  }

  lista->dados[nodo].dado = *valor;
  aux = lista->inicioElementos;
  anterior = UINT_MAX;

  while ((aux != UINT_MAX) && (*valor > lista->dados[aux].dado))
  {
    anterior = aux;
    aux = lista->dados[aux].sucessor;
  }

  if (anterior == UINT_MAX)
  {
    lista->dados[nodo].sucessor = lista->inicioElementos;
    lista->inicioElementos = nodo;
  }
  else
  {
    lista->dados[nodo].sucessor = aux;
    lista->dados[anterior].sucessor = nodo;
  }

  return true;
}

bool remove_inicio(LISTA *lista, TIPO_DADO *valor)
{
  return remove_lista(lista, valor, 0);
}

bool remove_final(LISTA *lista, TIPO_DADO *valor)
{
  return remove_lista(lista, valor, tamanho_lista(lista) - 1);
}


bool insere_inicio(LISTA *lista, const TIPO_DADO *valor)
{
  return insere_lista(lista, valor, 0);
}

bool insere_final(LISTA *lista, const TIPO_DADO *valor)
{
  return insere_lista(lista, valor, tamanho_lista(lista));
}


bool remove_chave(LISTA *lista, TIPO_DADO *valor)
{
  unsigned int anterior, aux;

  if (!valor)
  {
    return false;
  }

  anterior = UINT_MAX;
  aux = lista->inicioElementos;

  while ((aux != UINT_MAX) && (lista->dados[aux].dado != *valor))
  {
    anterior = aux;
    aux = lista->dados[aux].sucessor;
  }

  if (aux == UINT_MAX) // nao encontrou
  {
    return false;
  }

  if (anterior == UINT_MAX)
  {
    lista->inicioElementos = lista->dados[aux].sucessor;
  }
  else
  {
    lista->dados[anterior].sucessor = lista->dados[aux].sucessor;
  }

  if (!libera_no_lista(lista, aux))
  {
    printf("Problema da devolucao da memoria\n");
    exit(1);
  }

  return true;
}
