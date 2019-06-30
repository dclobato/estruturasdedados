#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <lista_ed.h>

bool inicializa_lista(LISTA *lista)
{
  lista->numElementos = 0;
  lista->final = NULL;
  lista->inicio = NULL;
  return true;
}

void imprime_lista(const LISTA *lista)
{
  NOH *p;
  unsigned int i;
  printf("Posicoes ocupadas: %u\n", tamanho_lista(lista));
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

void __imprime_lista(const LISTA *lista)
{
  NOH *p;
  unsigned int i;
  printf("Posicoes ocupadas........: %u\n", tamanho_lista(lista));
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

unsigned int tamanho_lista(const LISTA *lista)
{
  return (lista->numElementos);
}

bool destroi_lista(LISTA *lista)
{
  NOH *p, *q;
  lista->numElementos = 0;
  p = lista->inicio;

  while (p != NULL)
  {
    q = p;
    p = p->sucessor;
    libera_no_lista(&q);
  }

  lista->inicio = NULL;
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

  p->sucessor = NULL;
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

bool remove_lista(LISTA *lista, TIPO_DADO *valor, unsigned int posicao)
{
  NOH *p, *q;
  unsigned int contador;

  if ((posicao < 0) || (posicao > (tamanho_lista(lista) - 1)))
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

  p = lista->inicio;

  for (contador = 0; contador < posicao; contador++)
  {
    p = p->sucessor;
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

bool remove_chave(LISTA *lista, const TIPO_DADO *valor)
{
  NOH *p, *q;
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

  libera_no_lista(&p);
  lista->numElementos = lista->numElementos - 1;
  return true;
}

bool busca_lista(const LISTA *lista, const TIPO_DADO *valor, NOH **nodo)
{
  NOH *p;
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

bool obtem_sucessor(const NOH *nodo, NOH **proximo)
{
  if ((nodo == NULL) || (nodo->sucessor == NULL))
  {
    return false;
  }

  *proximo = nodo->sucessor;
  return true;
}

bool obtem_inicio(const LISTA *lista, NOH **nodo)
{
  if (tamanho_lista(lista) == 0)
  {
    return false;
  }

  *nodo = lista->inicio;
  return true;
}

bool obtem_final(const LISTA *lista, NOH **nodo)
{
  if (tamanho_lista(lista) == 0)
  {
    return false;
  }

  *nodo = lista->final;
  return true;
}

bool remove_nodo(LISTA *lista, NOH **nodo)
{
  NOH *p, *q;

  if (tamanho_lista(lista) == 0)
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

  libera_no_lista(&p);
  lista->numElementos = lista->numElementos - 1;
  return true;
}

bool insere_antes_do_nodo(LISTA *lista, const NOH **nodo,
                          const TIPO_DADO *valor)
{
  NOH *t;
  NOH *p, *q;

  if (!valor || !obtem_no_lista(&t))
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

