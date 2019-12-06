#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <lista_ed.h>

bool lista_inicializa(LISTA *lista)
{
  lista->numElementos = 0;
  lista->final = NULL;
  lista->inicio = NULL;
  return true;
}

void lista_imprime(const LISTA *lista)
{
  NOH_LISTA *p;
  unsigned int i;
  printf("Posicoes ocupadas: %u\n", lista_tamanho(lista));
  p = lista->inicio;
  i = 0;

  while (p != NULL)
  {
    printf("[%03u]: %d\n", i, p->dado);
    p = p->sucessor;
    i++;
  }

  printf("\n");
}

void __lista_imprime(const LISTA *lista)
{
  NOH_LISTA *p;
  unsigned int i;
  printf("Posicoes ocupadas........: %u\n", lista_tamanho(lista));
  printf("Posicao primeiro elemento: %p\n", lista->inicio);
  printf("Posicao ultimo elemento..: %p\n", lista->final);
  p = lista->inicio;
  i = 0;

  while (p != NULL)
  {
    printf("[%03u]: %d   (posicao: %p, proximo: %p)\n", i, p->dado, p, p->sucessor);
    p = p->sucessor;
    i++;
  }

  printf("\n");
}

unsigned int lista_tamanho(const LISTA *lista)
{
  return (lista->numElementos);
}

bool lista_destroi(LISTA *lista)
{
  NOH_LISTA *p, *q;
  lista->numElementos = 0;
  p = lista->inicio;

  while (p != NULL)
  {
    q = p;
    p = p->sucessor;
    lista_libera_no(&q);
  }

  lista->inicio = NULL;
  lista->final = NULL;
  return true;
}

bool lista_vazia(const LISTA *lista)
{
  return (lista->inicio == NULL);
}

bool lista_cheia(const LISTA *lista)
{
  // Como estamos com alocacao dinamica, nao ha como saber se a lista
  // esta cheia antes de tentar inserir um novo elemento
  return false;
}

bool __lista_obtem_no(NOH_LISTA **nodo)
{
  NOH_LISTA *p;
  p = (NOH_LISTA *) malloc(sizeof(NOH_LISTA));

  if (!p)
  {
    return false;
  }

  p->sucessor = NULL;
  *nodo = p;
  return true;
}

bool lista_libera_no(NOH_LISTA **nodo)
{
  if (!*nodo)
  {
    return false;
  }

  free(*nodo);
  *nodo = NULL;
  return true;
}

bool lista_insere_inicio(LISTA *lista, const TIPO_DADO *valor)
{
  return (lista_insere(lista, valor, 0));
}

bool lista_insere_final(LISTA *lista, const TIPO_DADO *valor)
{
  return (lista_insere(lista, valor, lista_tamanho(lista)));
}

bool lista_remove_inicio(LISTA *lista, TIPO_DADO *valor)
{
  return lista_remove_posicao(lista, valor, 0);
}

bool lista_remove_final(LISTA *lista, TIPO_DADO *valor)
{
  return lista_remove_posicao(lista, valor, lista_tamanho(lista) - 1);
}

bool lista_insere(LISTA *lista, const TIPO_DADO *valor, unsigned int posicao)
{
  NOH_LISTA *t;
  NOH_LISTA *p, *q;
  unsigned int contador;

  if ((posicao < 0) || (posicao > lista_tamanho(lista)))
  {
    return false;
  }

  if (!valor || !__lista_obtem_no(&t))
  {
    return false;
  }

  t->dado = *valor;
  t->sucessor = NULL;
  p = lista->inicio;
  q = NULL;
  contador = 0;

  while (contador < posicao)
  {
    q = p;
    p = p->sucessor;
    contador++;
  }

  // inicio da lista ou lista vazia?
  if (q == NULL)
  {
    t->sucessor = lista->inicio;
    lista->inicio = t;

    if (!lista->final)
    {
      lista->final = t;
    }
  }
  else
  {
    q->sucessor = t;

    // Final da lista?
    if (p == NULL)
    {
      lista->final = t;
    }
    else
    {
      t->sucessor = p;
    }
  }

  lista->numElementos = lista->numElementos + 1;
  return true;
}

bool lista_remove_posicao(LISTA *lista, TIPO_DADO *valor, unsigned int posicao)
{
  NOH_LISTA *p, *q;
  unsigned int contador;

  if ((posicao < 0) || (posicao > (lista_tamanho(lista) - 1)))
  {
    return false;
  }

  p = lista->inicio;
  q = NULL;

  for (contador = 0; contador < posicao; contador++)
  {
    q = p;
    p = p->sucessor;
  }

  if (q == NULL)
  {
    lista->inicio = p->sucessor;
  }
  else
  {
    q->sucessor = p->sucessor;
  }

  if (valor)
  {
    *valor = p->dado;
  }

  if (p->sucessor == NULL)
  {
    lista->final = q;
  }

  if (lista->inicio == NULL)
  {
    lista->final = NULL;
  }

  lista_libera_no(&p);
  lista->numElementos = lista->numElementos - 1;
  return true;
}

bool lista_consulta_posicao(const LISTA *lista, unsigned int posicao, NOH_LISTA **nodo)
{
  NOH_LISTA *p;
  unsigned int contador;

  if ((posicao < 0) || (posicao > (lista_tamanho(lista) - 1)))
  {
    return false;
  }

  p = lista->inicio;

  for (contador = 0; contador < posicao; contador++)
  {
    p = p->sucessor;
  }

  *nodo = p;
  return true;
}

bool lista_insere_ordenado(LISTA *lista, const TIPO_DADO *valor)
{
  NOH_LISTA *t;
  NOH_LISTA *p, *q;

  if (!valor || !__lista_obtem_no(&t))
  {
    return false;
  }

  t->dado = *valor;
  t->sucessor = NULL;
  p = lista->inicio;
  q = NULL;

  while ((p != NULL) && (*valor > p->dado))
  {
    q = p;
    p = p->sucessor;
  }

  // inicio da lista ou lista vazia?
  if (q == NULL)
  {
    t->sucessor = lista->inicio;
    lista->inicio = t;

    if (!lista->final)
    {
      lista->final = t;
    }
  }
  else
  {
    // Final da lista?
    if (p == NULL)
    {
      q->sucessor = t;
      lista->final = t;
    }
    else
    {
      q->sucessor = t;
      t->sucessor = p;
    }
  }

  lista->numElementos = lista->numElementos + 1;
  return true;
}

bool lista_remove_chave(LISTA *lista, const TIPO_DADO *valor)
{
  NOH_LISTA *p, *q;
  p = lista->inicio;
  q = NULL;

  if (!valor)
  {
    return false;
  }

  while ((p != NULL) && (p->dado != *valor))
  {
    q = p;
    p = p->sucessor;
  }

  if (p == NULL)
  {
    return false;
  }

  if (q == NULL)
  {
    lista->inicio = p->sucessor;
  }
  else
  {
    q->sucessor = p->sucessor;
  }

  if (p->sucessor == NULL)
  {
    lista->final = q;
  }

  if (lista->inicio == NULL)
  {
    lista->final = NULL;
  }

  lista_libera_no(&p);
  lista->numElementos = lista->numElementos - 1;
  return true;
}

bool lista_busca_chave(const LISTA *lista, const TIPO_DADO *valor, NOH_LISTA **nodo)
{
  NOH_LISTA *p;
  p = lista->inicio;

  if (!valor)
  {
    return false;
  }

  while ((p != NULL) && (p->dado != *valor))
  {
    p = p->sucessor;
  }

  // Nao achou
  if (p == NULL)
  {
    return false;
  }

  *nodo = p;
  return true;
}

bool lista_obtem_sucessor(const NOH_LISTA *nodo, NOH_LISTA **proximo)
{
  if ((nodo == NULL) || (nodo->sucessor == NULL))
  {
    return false;
  }

  *proximo = nodo->sucessor;
  return true;
}

bool lista_obtem_inicio(const LISTA *lista, NOH_LISTA **nodo)
{
  if (lista_tamanho(lista) == 0)
  {
    return false;
  }

  *nodo = lista->inicio;
  return true;
}

bool lista_obtem_final(const LISTA *lista, NOH_LISTA **nodo)
{
  if (lista_tamanho(lista) == 0)
  {
    return false;
  }

  *nodo = lista->final;
  return true;
}

bool lista_remove_nodo(LISTA *lista, NOH_LISTA **nodo)
{
  NOH_LISTA *p, *q;

  if (lista_tamanho(lista) == 0)
  {
    return false;
  }

  p = lista->inicio;
  q = NULL;

  while ((p != NULL) && (p != *nodo))
  {
    q = p;
    p = p->sucessor;
  }

  if (p == NULL)
  {
    return false;
  }

  if (q == NULL)
  {
    lista->inicio = p->sucessor;
  }
  else
  {
    q->sucessor = p->sucessor;
  }

  if (p->sucessor == NULL)
  {
    lista->final = q;
  }

  if (lista->inicio == NULL)
  {
    lista->final = NULL;
  }

  lista_libera_no(&p);
  lista->numElementos = lista->numElementos - 1;
  return true;
}

bool lista_insere_antes_do_nodo(LISTA *lista, const NOH_LISTA **nodo, const TIPO_DADO *valor)
{
  NOH_LISTA *t;
  NOH_LISTA *p, *q;

  if (!valor || !__lista_obtem_no(&t))
  {
    return false;
  }

  t->dado = *valor;
  t->sucessor = NULL;
  p = lista->inicio;
  q = NULL;

  while ((p != NULL) && (p != *nodo))
  {
    q = p;
    p = p->sucessor;
  }

  // inicio da lista ou lista vazia?
  if (q == NULL)
  {
    t->sucessor = lista->inicio;
    lista->inicio = t;

    if (!lista->final)
    {
      lista->final = t;
    }
  }
  else
  {
    // Final da lista?
    if (p == NULL)
    {
      q->sucessor = t;
      lista->final = t;
    }
    else
    {
      q->sucessor = t;
      t->sucessor = p;
    }
  }

  lista->numElementos = lista->numElementos + 1;
  return true;
}

bool lista_obtem_valor_no(const NOH_LISTA *nodo, TIPO_DADO *valor)
{
  if (nodo == NULL)
  {
    return false;
  }
  *valor = nodo->dado;
  return true;
}

bool lista_definir_valor_no(NOH_LISTA *nodo, const TIPO_DADO *valor)
{
  if (nodo == NULL)
  {
    return false;
  }
  nodo->dado = *valor;
  return true;
}