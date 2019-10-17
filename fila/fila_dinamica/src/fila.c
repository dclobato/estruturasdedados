#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fila.h>

bool fila_inicializa(FILA *fila)
{
  fila->numElementos = 0;
  fila->final = NULL;
  fila->dados = NULL;
  return true;
}

bool fila_destroi(FILA *fila)
{
  NOH_FILA *p, *q;
  fila->numElementos = 0;
  p = fila->dados;

  while (p != NULL)
  {
    q = p;
    p = p->prox;
    __fila_libera_no(&q);
  }

  fila->dados = NULL;
  fila->final = NULL;
  return true;
}

unsigned int fila_tamanho(const FILA *fila)
{
  return (fila->numElementos);
}

bool fila_vazia(const FILA *fila)
{
  return (fila_tamanho(fila) == 0);
}

bool fila_cheia(const FILA *fila)
{
  return false;
}

bool __fila_obtem_no(NOH_FILA **nodo)
{
  NOH_FILA *p;
  p = (NOH_FILA *) malloc(sizeof(NOH_FILA));

  if (!p)
  {
    return false;
  }

  p->prox = NULL;
  *nodo = p;
  return true;
}

bool __fila_libera_no(NOH_FILA **nodo)
{
  if (!*nodo)
  {
    return false;
  }

  free(*nodo);
  *nodo = NULL;
  return true;
}

bool fila_enfileira(FILA *fila, const TIPO_DADO *valor)
{
  NOH_FILA *t;

  if (!valor || !__fila_obtem_no(&t))
  {
    return false;
  }

  t->dado = *valor;
  t->prox = NULL;
  fila->numElementos = fila->numElementos + 1;

  if (fila_vazia(fila))
  {
    fila->dados = t;
    fila->final = t;
  }
  else
  {
    fila->final->prox = t;
  }

  return true;
}

bool fila_enfileira_prioridade(FILA *fila, const TIPO_DADO *valor)
{
  NOH_FILA *t;
  NOH_FILA *p, *q;

  if (!valor || !__fila_obtem_no(&t))
  {
    return false;
  }

  t->dado = *valor;
  t->prox = NULL;
  p = fila->dados;
  q = NULL;

  while ((p != NULL) && (*valor > p->dado))
  {
    q = p;
    p = p->prox;
  }

  // inicio da lista ou lista vazia?
  if (q == NULL)
  {
    t->prox = fila->dados;
    fila->dados = t;

    if (!fila->final)
    {
      fila->final = t;
    }
  }
  else
  {
    // Final da lista?
    if (p == NULL)
    {
      q->prox = t;
      fila->final = t;
    }
    else
    {
      q->prox = t;
      t->prox = p;
    }
  }

  fila->numElementos = fila->numElementos + 1;
  return true;
}

bool fila_desenfileira(FILA *fila, TIPO_DADO *valor)
{
  NOH_FILA *t;

  if ((fila_vazia(fila)) || !valor)
  {
    return false;
  }

  t = fila->dados;
  *valor = fila->dados->dado;
  fila->dados = fila->dados->prox;

  if (fila->dados == NULL)
  {
    fila->final = NULL;
  }

  free(t);
  fila->numElementos = fila->numElementos - 1;
  return true;
}

void fila_imprime(const FILA *fila)
{
  NOH_FILA *p;
  printf("Numero de elementos: %d\n", fila->numElementos);
  p = fila->dados;

  while (p != NULL)
  {
    printf("%d\n", p->dado);
    p = p->prox;
  }
}
