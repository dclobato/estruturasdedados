#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <lista_ed.h>

bool inicializa_lista(LISTA *lista)
{
  lista->numElementos = 0;
  lista->final = NULL;
  lista->dados = NULL;
  return true;
}

void imprime_lista(const LISTA *lista)
{
  NOH *p;
  unsigned int i;
  printf("Posicoes ocupadas: %u\n", tamanho_lista(lista));
  p = lista->dados;
  i = 0;

  while (p != NULL)
  {
    printf("[%03u]: %d\n", i, p->dado);
    p = p->prox;
    i++;
  }

  printf("\n");
}

void __imprime_lista(const LISTA *lista)
{
  NOH *p;
  unsigned int i;
  printf("Posicoes ocupadas........: %u\n", tamanho_lista(lista));
  printf("Posicao primeiro elemento: %p\n", lista->dados);
  printf("Posicao ultimo elemento..: %p\n", lista->final);
  p = lista->dados;
  i = 0;

  while (p != NULL)
  {
    printf("[%03u]: %d   (posicao: %p, proximo: %p)\n", i, p->dado, p, p->prox);
    p = p->prox;
    i++;
  }

  printf("\n");
}

unsigned int tamanho_lista(const LISTA *lista)
{
  return (lista->numElementos);
}

bool destroi_lista(LISTA *lista)
{
  NOH *p, *q;
  lista->numElementos = 0;
  p = lista->dados;

  while (p != NULL)
  {
    q = p;
    p = p->prox;
    libera_no_lista(&q);
  }

  lista->dados = NULL;
  lista->final = NULL;
  return true;
}

bool obtem_no_lista(NOH **nodo)
{
  NOH *p;
  p = (NOH *) malloc(sizeof(NOH));

  if (!p)
  {
    return false;
  }

  p->prox = NULL;
  *nodo = p;
  return true;
}

bool libera_no_lista(NOH **nodo)
{
  if (!*nodo)
  {
    return false;
  }

  free(*nodo);
  *nodo = NULL;
  return true;
}

bool insere_inicio(LISTA *lista, const TIPO_DADO *valor)
{
  return (insere_lista(lista, valor, 0));
}

bool insere_final(LISTA *lista, const TIPO_DADO *valor)
{
  return (insere_lista(lista, valor, tamanho_lista(lista)));
}

bool remove_inicio(LISTA *lista, TIPO_DADO *valor)
{
  return remove_lista(lista, valor, 0);
}

bool remove_final(LISTA *lista, TIPO_DADO *valor)
{
  return remove_lista(lista, valor, tamanho_lista(lista) - 1);
}

bool insere_lista(LISTA *lista, const TIPO_DADO *valor,
                  unsigned int posicao)
{
  NOH *t;
  NOH *p, *q;
  unsigned int contador;

  if ((posicao < 0) || (posicao > tamanho_lista(lista)))
  {
    return false;
  }

  if (!valor || !obtem_no_lista(&t))
  {
    return false;
  }

  t->dado = *valor;
  t->prox = NULL;
  p = lista->dados;
  q = NULL;
  contador = 0;

  while (contador < posicao)
  {
    q = p;
    p = p->prox;
    contador++;
  }

  // inicio da lista ou lista vazia?
  if (q == NULL)
  {
    t->prox = lista->dados;
    lista->dados = t;

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
      q->prox = t;
      lista->final = t;
    }
    else
    {
      q->prox = t;
      t->prox = p;
    }
  }

  lista->numElementos = lista->numElementos + 1;
  return true;
}

bool remove_lista(LISTA *lista, TIPO_DADO *valor, unsigned int posicao)
{
  NOH *p, *q;
  unsigned int contador;

  if ((posicao < 0) || (posicao > (tamanho_lista(lista) - 1)))
  {
    return false;
  }

  p = lista->dados;
  q = NULL;

  for (contador = 0; contador < posicao; contador++)
  {
    q = p;
    p = p->prox;
  }

  if (q == NULL)
  {
    lista->dados = p->prox;
  }
  else
  {
    q->prox = p->prox;
  }

  if (valor)
  {
    *valor = p->dado;
  }

  if (lista->dados == NULL)
  {
    lista->final = NULL;
  }

  libera_no_lista(&p);
  lista->numElementos = lista->numElementos - 1;
  return true;
}

bool consulta_lista(const LISTA *lista, unsigned int posicao,
                    TIPO_DADO *valor)
{
  NOH *p;
  int contador;

  if ((posicao < 0) || (posicao > (tamanho_lista(lista) - 1)))
  {
    return false;
  }

  p = lista->dados;

  for (contador = 0; contador < posicao; contador++)
  {
    p = p->prox;
  }

  *valor = p->dado;
  return true;
}

bool insere_ordenado(LISTA *lista, const TIPO_DADO *valor)
{
  NOH *t;
  NOH *p, *q;

  if (!valor || !obtem_no_lista(&t))
  {
    return false;
  }

  t->dado = *valor;
  t->prox = NULL;
  p = lista->dados;
  q = NULL;

  while ((p != NULL) && (*valor > p->dado))
  {
    q = p;
    p = p->prox;
  }

  // inicio da lista ou lista vazia?
  if (q == NULL)
  {
    t->prox = lista->dados;
    lista->dados = t;

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
      q->prox = t;
      lista->final = t;
    }
    else
    {
      q->prox = t;
      t->prox = p;
    }
  }

  lista->numElementos = lista->numElementos + 1;
  return true;
}

bool remove_chave(LISTA *lista, const TIPO_DADO *valor)
{
  NOH *p, *q;
  p = lista->dados;
  q = NULL;

  if (!valor)
  {
    return false;
  }

  while ((p != NULL) && (p->dado != *valor))
  {
    q = p;
    p = p->prox;
  }

  if (p == NULL)
  {
    return false;
  }

  if (q == NULL)
  {
    lista->dados = p->prox;
  }
  else
  {
    q->prox = p->prox;
  }

  if (lista->dados == NULL)
  {
    lista->final = NULL;
  }

  libera_no_lista(&p);
  lista->numElementos = lista->numElementos - 1;
  return true;
}
