#include <stdio.h>
#include <stdbool.h>
#include <lista_seq.h>

/*
 * Operacoes de inicializacao, destruicao e metadados
 */
bool inicializa_lista(LISTA *lista)
{
  lista->numElementos = 0;
  return true;
}

bool destroi_lista(LISTA *lista)
{
  lista->numElementos = 0;
  return true;
}

unsigned tamanho_lista(LISTA *lista)
{
  return (lista->numElementos);
}

unsigned livres_lista(LISTA *lista)
{
  return (TAM_LISTA - lista->numElementos);
}

/*
 * Operacoes de recuperacao de dados
 */
void imprime_lista(const LISTA *lista)
{
  unsigned int i;
  printf("Lista com %u elementos usados de %u disponiveis\n",
         lista->numElementos,
         TAM_LISTA);
  /* Faca o que for necessario aqui para mostrar o seu tipo de dado.
   * Por exemplo, se o TIPO_DADO for int, algo do tipo abaixo resolve
   */

  for (i = 0; i < lista->numElementos; i++)
  {
    printf("[%03u]: %d\n", i, lista->elementos[i]);
  }
}

bool consulta_lista(LISTA *lista, unsigned posicao, TIPO_DADO *valor)
{
  if ((lista->numElementos == 0) || (posicao > lista->numElementos - 1) ||
      (posicao < 0))
  {
    return false;
  }

  *valor = lista->elementos[posicao];
  return true;
}

/*
 * Operacoes de insercao
 */
bool insere_lista(LISTA *lista, const TIPO_DADO *valor, unsigned posicao)
{
  unsigned int i;

  if ((lista->numElementos == TAM_LISTA) || (posicao > lista->numElementos))
  {
    return false;
  }

  for (i = lista->numElementos; i > posicao; i--)
  {
    lista->elementos[i] = lista->elementos[i - 1];
  }

  lista->elementos[posicao] = *valor;
  lista->numElementos = lista->numElementos + 1;
  return true;
}

bool insere_ordenado(LISTA *lista, const TIPO_DADO *valor)
{
  unsigned int i;

  if (lista->numElementos == TAM_LISTA)
  {
    return false;
  }

  for (i = lista->numElementos; ((i > 0) &&
                                 (*valor < lista->elementos[i - 1])); i--)
  {
    lista->elementos[i] = lista->elementos[i - 1];
  }

  lista->elementos[i] = *valor;
  lista->numElementos = lista->numElementos + 1;
  return true;
}

bool insere_inicio(LISTA *lista, const TIPO_DADO *valor)
{
  return insere_lista(lista, valor, 0);
  //  unsigned i;
  //
  //  if (lista->numElementos == TAM_LISTA)
  //  {
  //    return false;
  //  }
  //
  //  for (i = lista->numElementos; i > 0; i--)
  //  {
  //    lista->elementos[i] = lista->elementos[i - 1];
  //  }
  //
  //  lista->elementos[0] = *valor;
  //  lista->numElementos = lista->numElementos + 1;
  //  return true;
}

bool insere_final(LISTA *lista, const TIPO_DADO *valor)
{
  return insere_lista(lista, valor, tamanho_lista(lista));
  //  if (lista->numElementos == TAM_LISTA)
  //  {
  //    return false;
  //  }
  //
  //  lista->elementos[lista->numElementos] = *valor;
  //  lista->numElementos = lista->numElementos + 1;
  //  return true;
}

/*
 * Operacoes de remocao
 */
bool remove_lista(LISTA *lista, TIPO_DADO *valor, unsigned posicao)
{
  unsigned int i;

  if ((lista->numElementos == 0) || (posicao > lista->numElementos - 1) ||
      (posicao < 0))
  {
    return false;
  }

  if (valor)
  {
    *valor = lista->elementos[posicao];
  }

  for (i = posicao + 1; i < lista->numElementos; i++)
  {
    lista->elementos[i - 1] = lista->elementos[i];
  }

  lista->numElementos = lista->numElementos - 1;
  return true;
}

bool remove_chave(LISTA *lista, const TIPO_DADO *valor)
{
  unsigned int i;

  if (!valor)
  {
    return false;
  }

  for (i = 0; i < (lista->numElementos); i++)
  {
    if (lista->elementos[i] == *valor)
    {
      return remove_lista(lista, NULL, i);
    }
  }

  return false;
}

bool remove_inicio(LISTA *lista, TIPO_DADO *valor)
{
  return remove_lista(lista, valor, 0);
}

bool remove_final(LISTA *lista, TIPO_DADO *valor)
{
  return remove_lista(lista, valor, tamanho_lista(lista) - 1);
}

