#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fila.h>

bool fila_inicializar(FILA *fila)
{
  fila->numElementos = 0;
  fila->final = NULL;
  fila->inicio = NULL;
  return true;
}

bool fila_destruir(FILA *fila)
{
  NOH_FILA *aux, *ant;
  fila->numElementos = 0;
  aux = fila->inicio;

  while (aux != NULL)
  {
    ant = aux;
    aux = aux->prox;
    fila_libera_no(&ant);
  }

  fila->inicio = NULL;
  fila->final = NULL;
  return true;
}

unsigned int fila_numero_de_elementos(const FILA *fila)
{
  return (fila->numElementos);
}

bool fila_esta_vazia(const FILA *fila)
{
  return (fila_numero_de_elementos(fila) == 0);
}

bool fila_esta_cheia(const FILA *fila)
{
  // Como estamos com alocacao dinamica, nao ha como saber se a pilha
  // esta cheia antes de tentar enfileirar um novo elemento
  return false;
}

bool fila_obtem_no(NOH_FILA **nodo)
{
  NOH_FILA *aux;
  aux = (NOH_FILA *) malloc(sizeof(NOH_FILA));

  if (aux == NULL)
  {
    return false;
  }

  aux->prox = NULL;
  *nodo = aux;
  return true;
}

bool fila_libera_no(NOH_FILA **nodo)
{
  if (*nodo == NULL)
  {
    return false;
  }

  free(*nodo);
  *nodo = NULL;
  return true;
}

bool fila_enfileirar(FILA *fila, const TIPO_DADO *valor)
{
  NOH_FILA *t;

  if ((valor == NULL) || !fila_obtem_no(&t))
  {
    return false;
  }

  t->dado = *valor;
  t->prox = NULL;

  if (fila_esta_vazia(fila))
  {
    fila->inicio = t;
  }
  else
  {
    fila->final->prox = t;
  }
  fila->final = t;

  fila->numElementos++;
  return true;
}

bool fila_enfileirar_com_prioridade(FILA *fila, const TIPO_DADO *valor)
{
  NOH_FILA *t;
  NOH_FILA *aux, *ant;

  if ((valor == NULL) || !fila_obtem_no(&t))
  {
    return false;
  }

  t->dado = *valor;
  t->prox = NULL;
  aux = fila->inicio;
  ant = NULL;

  while (aux != NULL)
  {
    if (*valor <= aux->dado)
    {
      break;
    }
    ant = aux;
    aux = aux->prox;
  }

  // inicio da lista ou lista vazia?
  if (ant == NULL)
  {
    t->prox = fila->inicio;
    fila->inicio = t;

    if (fila->final == NULL)
    {
      fila->final = t;
    }
  }
  else
  {
    // Final da lista?
    if (aux == NULL)
    {
      ant->prox = t;
      fila->final = t;
    }
    else
    {
      ant->prox = t;
      t->prox = aux;
    }
  }

  fila->numElementos++;
  return true;
}

bool fila_desenfileirar(FILA *fila, TIPO_DADO *valor)
{
  NOH_FILA *t;

  if ((fila_esta_vazia(fila)) || (valor == NULL))
  {
    return false;
  }

  t = fila->inicio;
  *valor = fila->inicio->dado;
  fila->inicio = fila->inicio->prox;

  if (fila->inicio == NULL)
  {
    fila->final = NULL;
  }

  free(t);
  fila->numElementos--;
  return true;
}

void fila_imprimir(const FILA *fila)
{
  NOH_FILA *p;
  printf("Numero de elementos: %d\n", fila->numElementos);
  p = fila->inicio;

  while (p != NULL)
  {
    printf("%d\n", p->dado);
    p = p->prox;
  }
}

bool fila_head(const FILA *fila, TIPO_DADO *valor)
{
  if (fila_esta_vazia(fila))
  {
    return false;
  }
  *valor = fila->inicio->dado;
  return true;
}
bool fila_tail(const FILA *fila, TIPO_DADO *valor)
{
  if (fila_esta_vazia(fila))
  {
    return false;
  }
  *valor = fila->final->dado;
  return true;
}
