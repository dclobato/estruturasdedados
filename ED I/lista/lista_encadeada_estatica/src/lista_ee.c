#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <lista_ee.h>

unsigned int lista_numero_de_elementos(const LISTA *lista)
{
  return (lista->numElementos);
}

unsigned int lista_numero_de_nos_livres(const LISTA *lista)
{
  return (lista->numLivres);
}

bool lista_inicializar(LISTA *lista)
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

bool lista_destruir(LISTA *lista)
{
  return (lista_inicializar(lista));
}

bool lista_esta_cheia(const LISTA *lista)
{
  return (lista->numLivres == 0);
}

bool lista_esta_vazia(const LISTA *lista)
{
  return (lista->numElementos == 0);
}

bool lista_obter_no(LISTA *lista, unsigned int *posicao)
{
  if (lista_esta_cheia(lista))
  {
    return false;
  }

  *posicao = lista->inicioLivres;
  lista->inicioLivres = lista->dados[lista->inicioLivres].sucessor;

  lista->numLivres--;
  lista->numElementos++;
  return true;
}

bool lista_liberar_no(LISTA *lista, unsigned int posicao)
{
  lista->dados[posicao].sucessor = lista->inicioLivres;
  lista->inicioLivres = posicao;

  lista->numLivres++;
  lista->numElementos--;
  return true;
}

void __lista_imprime(const LISTA *lista)
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
      printf("[%3u] -> [%3u]: %d\n", i, lista->dados[i].sucessor, lista->dados[i].dado);
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

void lista_imprime(const LISTA *lista)
{
  unsigned i, j;
  printf("Posicoes ocupadas: %u\n", lista_numero_de_elementos(lista));
  printf("Posicoes livres: %u\n", lista_numero_de_nos_livres(lista));
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

bool lista_obter_chave_posicao(LISTA *lista, TIPO_DADO *valor, unsigned int posicao)
{
  unsigned int aux, contador;

  if (lista_esta_vazia(lista))
  {
    return false;
  }

  if (posicao > lista_numero_de_elementos(lista) - 1)
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

bool lista_inserir_chave_posicao(LISTA *lista, const TIPO_DADO *valor, unsigned int posicao)
{
  unsigned int nodo, aux;
  unsigned int contador, anterior;

  if (posicao > lista_numero_de_elementos(lista))
  {
    return false;
  }

  if (!lista_obter_no(lista, &nodo))
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

bool lista_inserir_chave_ordenado(LISTA *lista, const TIPO_DADO *valor)
{
  unsigned int nodo;
  unsigned int aux, anterior;

  if (lista_esta_cheia(lista))
  {
    return false;
  }

  if (!lista_obter_no(lista, &nodo))
  {
    return false;
  }

  lista->dados[nodo].dado = *valor;
  aux = lista->inicioElementos;
  anterior = UINT_MAX;

  while (aux != UINT_MAX)
  {
    if (*valor <= lista->dados[aux].dado)
    {
      break;
    }
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

bool lista_remover_inicio(LISTA *lista, TIPO_DADO *valor)
{
  if (lista_esta_vazia(lista))
  {
    return false;
  }

  return lista_remover_posicao(lista, valor, 0);
}

bool lista_remover_final(LISTA *lista, TIPO_DADO *valor)
{
  if (lista_esta_vazia(lista))
  {
    return false;
  }

  return lista_remover_posicao(lista, valor, lista_numero_de_elementos(lista) - 1);
}

bool lista_inserir_chave_final(LISTA *lista, const TIPO_DADO *valor)
{
  return lista_inserir_chave_posicao(lista, valor, lista_numero_de_elementos(lista));
}

bool lista_inserir_chave_inicio(LISTA *lista, const TIPO_DADO *valor)
{
  return lista_inserir_chave_posicao(lista, valor, 0);
}

bool lista_remover_chave(LISTA *lista, const TIPO_DADO *valor)
{
  unsigned int anterior, aux;

  if (valor == NULL)
  {
    return false;
  }

  anterior = UINT_MAX;
  aux = lista->inicioElementos;

  while (aux != UINT_MAX)
  {
    if (lista->dados[aux].dado == *valor)
    {
      break;
    }
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

  if (!lista_liberar_no(lista, aux))
  {
    printf("Problema da devolucao da memoria\n");
    exit(1);
  }

  return true;
}

bool lista_obter_posicao_chave(const LISTA *lista, const TIPO_DADO *valor, unsigned int *posicao)
{
  unsigned int aux;

  *posicao = 0;
  aux = lista->inicioElementos;

  if (valor == NULL)
  {
    return false;
  }

  while (aux != UINT_MAX)
  {
    if (lista->dados[aux].dado == *valor)
    {
      break;
    }
    aux = lista->dados[aux].sucessor;
    *posicao = *posicao + 1;
  }

  return (aux != UINT_MAX);
}

bool lista_obter_chave_inicio(const LISTA *lista, TIPO_DADO *valor)
{
  if (lista_esta_vazia(lista))
  {
    return false;
  }

  *valor = lista->dados[lista->inicioElementos].dado;
  return true;
}

bool lista_obter_chave_final(const LISTA *lista, TIPO_DADO *valor)
{
  unsigned int aux, anterior;

  if (lista_esta_vazia(lista))
  {
    return false;
  }

  anterior = UINT_MAX;
  aux = lista->inicioElementos;

  while (aux != UINT_MAX)
  {
    anterior = aux;
    aux = lista->dados[aux].sucessor;
  }

  *valor = lista->dados[anterior].dado;
  return true;
}

bool lista_definir_chave_posicao(LISTA *lista, const TIPO_DADO *valor, unsigned int posicao)
{
  unsigned int aux, contador;

  if (posicao > lista_numero_de_elementos(lista) - 1)
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

  lista->dados[aux].dado = *valor;
  return true;
}

bool lista_remover_posicao(LISTA *lista, TIPO_DADO *valor, unsigned int posicao)
{
  unsigned int contador, anterior, aux;

  if (lista_esta_vazia(lista))
  {
    return false;
  }

  if ((posicao > (lista_numero_de_elementos(lista) - 1)))
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

  if (valor != NULL)
  {
    *valor = lista->dados[aux].dado;
  }

  if (!lista_liberar_no(lista, aux))
  {
    return false;
  }

  return true;
}
