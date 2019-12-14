#include <stdio.h>
#include <stdbool.h>
#include <lista_seq.h>

/*
 * Operacoes de inicializacao, destruicao e metadados
 */
bool lista_inicializar(LISTA *lista)
{
  lista->numElementos = 0;
  return true;
}

bool lista_destruir(LISTA *lista)
{
  lista->numElementos = 0;
  return true;
}

unsigned lista_numero_de_elementos(const LISTA *lista)
{
  return (lista->numElementos);
}

unsigned lista_numero_de_nos_livres(const LISTA *lista)
{
  return (TAM_LISTA - lista_numero_de_elementos(lista));
}

bool lista_esta_vazia(const LISTA *lista)
{
  return (lista_numero_de_elementos(lista) == 0);
}

bool lista_esta_cheia(const LISTA *lista)
{
  return (lista_numero_de_elementos(lista) == TAM_LISTA);
}

/*
 * Operacoes de recuperacao de dados
 */
void lista_imprimir(const LISTA *lista)
{
  unsigned int i;
  unsigned int tamanho;
  TIPO_DADO v;

  tamanho = lista_numero_de_elementos(lista);

  printf("Capacidade da lista: %u\n", TAM_LISTA);
  printf("Posicoes ocupadas: %u\n", tamanho);

  for (i = 0; i < tamanho; i++)
  {
    lista_obter_chave_posicao(lista, &v, i);
    printf("[%03u]: %d\n", i, v);
  }
}

bool lista_obter_chave_posicao(const LISTA *lista, TIPO_DADO *valor, unsigned int posicao)
{
  if (lista_esta_vazia(lista))
  {
    return false;
  }
  
  if (posicao > lista_numero_de_elementos(lista) - 1)
  {
    return false;
  }

  *valor = lista->elementos[posicao];
  return true;
}

/*
 * Operacoes de insercao
 */
bool lista_inserir_chave_posicao(LISTA *lista, const TIPO_DADO *valor, unsigned posicao)
{
  unsigned int i;
  unsigned int inicio;
  TIPO_DADO v;

  inicio = lista_numero_de_elementos(lista);
  if (lista_esta_cheia(lista) || (posicao > inicio))
  {
    return false;
  }

  for (i = inicio; i > posicao; i--)
  {
    lista_obter_chave_posicao(lista, &v, i - 1);
    lista_definir_chave_posicao(lista, &v, i);
  }

  lista_definir_chave_posicao(lista, valor, posicao);
  lista->numElementos++;
  return true;
}

bool lista_inserir_chave_ordenado(LISTA *lista, const TIPO_DADO *valor)
{
  unsigned int posicao;
  TIPO_DADO v;

  if (lista_esta_cheia(lista))
  {
    return false;
  }

  for (posicao = lista_numero_de_elementos(lista); posicao > 0; posicao--)
  {
    lista_obter_chave_posicao(lista, &v, posicao - 1);
    if (*valor <= v)
    {
      break;
    }
    lista_obter_chave_posicao(lista, &v, posicao - 1);
    lista_definir_chave_posicao(lista, &v, posicao);
  }

  lista_definir_chave_posicao(lista, valor, posicao);
  lista->numElementos++;
  return true;
}

bool lista_inserir_chave_inicio(LISTA *lista, const TIPO_DADO *valor)
{
  return lista_inserir_chave_posicao(lista, valor, 0);
}

bool lista_inserir_chave_final(LISTA *lista, const TIPO_DADO *valor)
{
  return lista_inserir_chave_posicao(lista, valor, lista_numero_de_elementos(lista));
}

/*
 * Operacoes de remocao
 */
bool lista_remover_posicao(LISTA *lista, TIPO_DADO *valor, unsigned posicao)
{
  unsigned int i;
  unsigned int tamanho;
  TIPO_DADO v;

  tamanho = lista_numero_de_elementos(lista);

  if (lista_esta_vazia(lista) || (posicao > tamanho - 1))
  {
    return false;
  }

  if (valor != NULL)
  {
    lista_obter_chave_posicao(lista, valor, posicao);
  }

  for (i = posicao + 1; i < tamanho; i++)
  {
    lista_obter_chave_posicao(lista, &v, i);
    lista_definir_chave_posicao(lista, &v, i - 1);
  }

  lista->numElementos--;
  return true;
}

bool lista_remover_chave(LISTA *lista, const TIPO_DADO *valor)
{
  unsigned int i;
  unsigned int tamanho;
  TIPO_DADO v;

  if (valor == NULL)
  {
    return false;
  }

  tamanho = lista_numero_de_elementos(lista);

  for (i = 0; i < tamanho; i++)
  {
    lista_obter_chave_posicao(lista, &v, i);
    if (v == *valor)
    {
      return lista_remover_posicao(lista, NULL, i);
    }
  }

  return false;
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

bool lista_definir_chave_posicao(LISTA *lista, const TIPO_DADO *valor, unsigned int posicao)
{
  unsigned int i;
  unsigned int tamanho;

  if (posicao > TAM_LISTA - 1)
  {
    return false;
  }

  lista->elementos[posicao] = *valor;
  return true;
}

bool lista_obter_chave_inicio(const LISTA *lista, TIPO_DADO *valor)
{
  if (lista_esta_vazia(lista))
  {
    return false;
  }

  return lista_obter_chave_posicao(lista, valor, 0);
}

bool lista_obter_chave_final(const LISTA *lista, TIPO_DADO *valor)
{
  if (lista_esta_vazia(lista))
  {
    return false;
  }

  return lista_obter_chave_posicao(lista, valor, lista_numero_de_elementos(lista) - 1);
}

bool lista_obter_posicao_chave(const LISTA *lista, const TIPO_DADO *valor, unsigned int *posicao)
{
  unsigned int i;
  unsigned int tamanho;
  TIPO_DADO v;

  if (valor == NULL)
  {
    return false;
  }

  tamanho = lista_numero_de_elementos(lista);

  for (i = 0; i < tamanho; i++)
  {
    lista_obter_chave_posicao(lista, &v, i);
    if (v == *valor)
    {
      *posicao = i;
      return true;
    }
  }

  return false;
}
