#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fila.h>

bool inicializa_fila (FILA *fila)
{
  fila->numElementos = 0;
  fila->final = NULL;
  fila->dados = NULL;
  return true;
}

bool destroi_fila (FILA *fila)
{
  NOH_FILA *p, *q;
  fila->numElementos = 0;
  p = fila->dados;

  while (p != NULL)
  {
    q = p;
    p = p->prox;
    libera_no_fila(&q);
  }

  fila->dados = NULL;
  fila->final = NULL;
  return true;
}

unsigned int tamanho_fila (const FILA *fila)
{
  return (fila->numElementos);
}

bool fila_vazia (const FILA *fila)
{
  return (tamanho_fila(fila) == 0);
}

bool obtem_no_fila (NOH_FILA **nodo)
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

bool libera_no_fila (NOH_FILA **nodo)
{
  if (!*nodo)
  {
    return false;
  }

  free(*nodo);
  *nodo = NULL;
  return true;
}

bool enfileira (FILA *fila, const TIPO_DADO *valor)
{
  NOH_FILA *t;

  if (!valor || !obtem_no_fila(&t))
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

bool enfileira_prioridade (FILA *fila, const TIPO_DADO *valor)
{
  NOH_FILA *t;
  NOH_FILA *p, *q;

  if (!valor || !obtem_no_fila(&t))
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

bool desenfileira (FILA *fila, TIPO_DADO *valor)
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

void imprime_fila (const FILA *fila)
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
