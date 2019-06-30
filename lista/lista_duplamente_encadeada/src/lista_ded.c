#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <lista_ded.h>

bool inicializa_lista_de(LISTA_DE *lista)
{
  lista->numElementos = 0;
  lista->final = NULL;
  lista->inicio = NULL;
  return true;
}

void imprime_lista_de(const LISTA_DE *lista)
{
  NOH_DE *p;
  unsigned int i;
  printf("Posicoes ocupadas: %u\n", tamanho_lista_de(lista));
  p = lista->inicio;
  i = 0;

  while (p != NULL)
  {
    printf("[%03u]: %5d\n", i, p->dado);
    p = p->sucessor;
    i++;
  }

  printf("\n");
}

void __imprime_lista_de(const LISTA_DE *lista)
{
  NOH_DE *p;
  unsigned int i;
  printf("Posicoes ocupadas........: %u\n", tamanho_lista_de(lista));
  printf("Posicao primeiro elemento: %p\n", lista->inicio);
  printf("Posicao ultimo elemento..: %p\n", lista->final);
  p = lista->inicio;
  i = 0;

  while (p != NULL)
  {
    printf("[%03u]: %5d   (predecessor: %14p, p: %14p, sucessor: %14p)\n", i,
           p->dado, p->predecessor, p, p->sucessor);
    p = p->sucessor;
    i++;
  }

  printf("\n");
}

unsigned int tamanho_lista_de(const LISTA_DE *lista)
{
  return (lista->numElementos);
}

bool destroi_lista_de(LISTA_DE *lista)
{
  NOH_DE *p, *q;
  lista->numElementos = 0;
  p = lista->inicio;

  while (p != NULL)
  {
    q = p;
    p = p->sucessor;
    libera_no_lista_de(&q);
  }

  lista->inicio = NULL;
  lista->final = NULL;
  return true;
}

bool obtem_no_lista_de(NOH_DE **nodo)
{
  NOH_DE *p;
  p = (NOH_DE *) malloc(sizeof(NOH_DE));

  if (!p)
  {
    return false;
  }

  p->sucessor = NULL;
  p->predecessor = NULL;
  *nodo = p;
  return true;
}

bool libera_no_lista_de(NOH_DE **nodo)
{
  if (!*nodo)
  {
    return false;
  }

  free(*nodo);
  *nodo = NULL;
  return true;
}

bool insere_inicio_de(LISTA_DE *lista, const TIPO_DADO *valor)
{
  NOH_DE *t;

  if (!valor || !obtem_no_lista_de(&t))
  {
    return false;
  }

  t->dado = *valor;
  t->sucessor = lista->inicio;
  t->predecessor = NULL;

  if (lista->inicio == NULL)
  {
    lista->inicio = t;
    lista->final = t;
  }
  else
  {
    assert(lista->inicio->predecessor == NULL);
    lista->inicio->predecessor = t;
    lista->inicio = t;
  }

  lista->numElementos = lista->numElementos + 1;
  return true;
}

bool insere_final_de(LISTA_DE *lista, const TIPO_DADO *valor)
{
  NOH_DE *t;

  if (!valor || !obtem_no_lista_de(&t))
  {
    return false;
  }

  t->dado = *valor;
  t->sucessor = NULL;
  t->predecessor = lista->final;

  if (lista->final == NULL)
  {
    lista->inicio = t;
    lista->final = t;
  }
  else
  {
    assert(lista->final->sucessor == NULL);
    lista->final->sucessor = t;
    lista->final = t;
  }

  lista->numElementos = lista->numElementos + 1;
  return true;
}

bool remove_inicio_de(LISTA_DE *lista, TIPO_DADO *valor)
{
  NOH_DE *p;

  if (tamanho_lista_de(lista) == 0)
  {
    return false;
  }

  assert(lista->inicio != NULL);
  p = lista->inicio;

  if (valor)
  {
    *valor = p->dado;
  }

  lista->inicio = p->sucessor;

  if (lista->inicio == NULL)
  {
    lista->final = NULL;
  }
  else
  {
    lista->inicio->predecessor = NULL;
  }

  libera_no_lista_de(&p);
  lista->numElementos = lista->numElementos - 1;
  return true;
}

bool remove_final_de(LISTA_DE *lista, TIPO_DADO *valor)
{
  NOH_DE *p;

  if (tamanho_lista_de(lista) == 0)
  {
    return false;
  }

  assert(lista->final != NULL);
  p = lista->final;

  if (valor)
  {
    *valor = p->dado;
  }

  lista->final = p->predecessor;

  if (lista->final == NULL)
  {
    lista->inicio = NULL;
  }
  else
  {
    lista->final->sucessor = NULL;
  }

  libera_no_lista_de(&p);
  lista->numElementos = lista->numElementos - 1;
  return true;
}

bool insere_lista_de(LISTA_DE *lista, const TIPO_DADO *valor,
                     unsigned int posicao)
{
  NOH_DE *t;
  NOH_DE *p, *q;
  unsigned int contador;

  if ((posicao < 0) || (posicao > tamanho_lista_de(lista)))
  {
    return false;
  }

  if (!valor || !obtem_no_lista_de(&t))
  {
    return false;
  }

  t->dado = *valor;
  t->sucessor = NULL;
  t->predecessor = NULL;
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

    if (lista->final == NULL)
    {
      lista->final = t;
    }
  }
  else
  {
    q->sucessor = t;
    t->predecessor = q;

    // Final da lista?
    if (p == NULL)
    {
      lista->final = t;
    }
    else
    {
      t->sucessor = p;
      p->predecessor = t;
    }
  }

  lista->numElementos = lista->numElementos + 1;
  return true;
}

bool remove_lista_de(LISTA_DE *lista, TIPO_DADO *valor,
                     unsigned int posicao)
{
  NOH_DE *p, *q;
  unsigned int contador;

  if ((posicao < 0) || (posicao > (tamanho_lista_de(lista) - 1)))
  {
    return false;
  }

  assert(lista->inicio != NULL);
  assert(lista->final != NULL);
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

    if (p->sucessor != NULL)
    {
      p->sucessor->predecessor = NULL;
    }
  }
  else
  {
    q->sucessor = p->sucessor;

    if (p->sucessor != NULL)
    {
      p->sucessor->predecessor = q;
    }
  }

  if (valor)
  {
    *valor = p->dado;
  }

  if (p == lista->final)
  {
    lista->final = q;
  }

  if (lista->inicio == NULL)
  {
    lista->final = NULL;
  }

  libera_no_lista_de(&p);
  lista->numElementos = lista->numElementos - 1;
  return true;
}

bool consulta_lista_de(const LISTA_DE *lista, unsigned int posicao,
                       TIPO_DADO *valor)
{
  NOH_DE *p;
  int contador;

  if ((posicao < 0) || (posicao > (tamanho_lista_de(lista) - 1)))
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

bool insere_ordenado_de(LISTA_DE *lista, const TIPO_DADO *valor)
{
  NOH_DE *t;
  NOH_DE *p, *q;

  if (!valor || !obtem_no_lista_de(&t))
  {
    return false;
  }

  t->dado = *valor;
  t->sucessor = NULL;
  t->predecessor = NULL;
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

    if (t->sucessor != NULL)
    {
      t->sucessor->predecessor = t;
    }

    lista->inicio = t;

    if (lista->final == NULL)
    {
      lista->final = t;
    }
  }
  else
  {
    q->sucessor = t;
    t->predecessor = q;

    // Final da lista?
    if (p == NULL)
    {
      lista->final = t;
    }
    else
    {
      t->sucessor = p;
      p->predecessor = t;
    }
  }

  lista->numElementos = lista->numElementos + 1;
  return true;
}

bool remove_chave_de(LISTA_DE *lista, const TIPO_DADO *valor)
{
  NOH_DE *p, *q;
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

  // Nao achou
  if (p == NULL)
  {
    return false;
  }

  if (q == NULL)
  {
    lista->inicio = p->sucessor;

    if (p->sucessor != NULL)
    {
      p->sucessor->predecessor = NULL;
    }
  }
  else
  {
    q->sucessor = p->sucessor;

    if (p->sucessor != NULL)
    {
      p->sucessor->predecessor = q;
    }
  }

  if (p == lista->final)
  {
    lista->final = q;
  }

  if (lista->inicio == NULL)
  {
    lista->final = NULL;
  }

  libera_no_lista_de(&p);
  lista->numElementos = lista->numElementos - 1;
  return true;
}

bool obtem_sucessor_de(const NOH_DE *nodo, NOH_DE **sucessor)
{
  if ((nodo == NULL) || (nodo->sucessor == NULL))
  {
    return false;
  }

  *sucessor = nodo->sucessor;
  return true;
}

bool obtem_predecessor_de(const NOH_DE *nodo, NOH_DE **predecessor)
{
  if ((nodo == NULL) || (nodo->predecessor == NULL))
  {
    return false;
  }

  *predecessor = nodo->predecessor;
  return true;
}

bool obtem_inicio_de(const LISTA_DE *lista, NOH_DE **nodo)
{
  if (tamanho_lista_de(lista) == 0)
  {
    return false;
  }

  *nodo = lista->inicio;
  return true;
}

bool obtem_final_de(const LISTA_DE *lista, NOH_DE **nodo)
{
  if (tamanho_lista_de(lista) == 0)
  {
    return false;
  }

  *nodo = lista->final;
  return true;
}

bool busca_lista_de(const LISTA_DE *lista, const TIPO_DADO *valor,
                    NOH_DE **nodo)
{
  NOH_DE *p;
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

// TODO: implementar insercao antes do nodo
bool insere_antes_do_nodo_de(LISTA_DE *lista, const NOH_DE **nodo,
                             const TIPO_DADO *valor)
{
  NOH_DE *t;
  NOH_DE *p, *q;

  if (!valor || !obtem_no_lista_de(&t))
  {
    return false;
  }

  t->dado = *valor;
  t->sucessor = NULL;
  t->predecessor = NULL;
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

    if (t->sucessor != NULL)
    {
      t->sucessor->predecessor = t;
    }

    lista->inicio = t;

    if (lista->final == NULL)
    {
      lista->final = t;
    }
  }
  else
  {
    q->sucessor = t;
    t->predecessor = q;

    // Final da lista?
    if (p == NULL)
    {
      lista->final = t;
    }
    else
    {
      t->sucessor = p;
      p->predecessor = t;
    }
  }

  lista->numElementos = lista->numElementos + 1;
  return true;
}

// TODO: implementar remocao de nodo
bool remove_nodo_de(LISTA_DE *lista, NOH_DE **nodo)
{
  NOH_DE *p, *q;
  p = lista->inicio;
  q = NULL;

  while ((p != NULL) && (p != *nodo))
  {
    q = p;
    p = p->sucessor;
  }

  // Nao achou
  if (p == NULL)
  {
    return false;
  }

  if (q == NULL)
  {
    lista->inicio = p->sucessor;

    if (p->sucessor != NULL)
    {
      p->sucessor->predecessor = NULL;
    }
  }
  else
  {
    q->sucessor = p->sucessor;

    if (p->sucessor != NULL)
    {
      p->sucessor->predecessor = q;
    }
  }

  if (p == lista->final)
  {
    lista->final = q;
  }

  if (lista->inicio == NULL)
  {
    lista->final = NULL;
  }

  libera_no_lista_de(&p);
  lista->numElementos = lista->numElementos - 1;
  return true;
}
