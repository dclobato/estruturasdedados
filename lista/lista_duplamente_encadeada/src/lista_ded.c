#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <lista_ded.h>

bool inicializa_lista_de(LISTA_DE *lista)
{
  lista->numElementos = 0;
  lista->final = NULL;
  lista->dados = NULL;
  return true;
}

void imprime_lista_de(const LISTA_DE *lista)
{
  NOH_DE *p;
  unsigned int i;
  printf("Posicoes ocupadas: %u\n", tamanho_lista_de(lista));
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

void __imprime_lista_de(const LISTA_DE *lista)
{
  NOH_DE *p;
  unsigned int i;
  printf("Posicoes ocupadas........: %u\n", tamanho_lista_de(lista));
  printf("Posicao primeiro elemento: %p\n", lista->dados);
  printf("Posicao ultimo elemento..: %p\n", lista->final);
  p = lista->dados;
  i = 0;

  while (p != NULL)
  {
    printf("[%03u]: %d   (ant: %14p, p: %14p, prox: %14p)\n", i,
           p->dado, p->ant, p, p->prox);
    p = p->prox;
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
  p = lista->dados;

  while (p != NULL)
  {
    q = p;
    p = p->prox;
    libera_no_lista_de(&q);
  }

  lista->dados = NULL;
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

  p->prox = NULL;
  p->ant = NULL;
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
  t->prox = lista->dados;
  t->ant = NULL;

  if (lista->dados == NULL)
  {
    lista->dados = t;
    lista->final = t;
  }
  else
  {
    assert(lista->dados->ant == NULL);
    lista->dados->ant = t;
    lista->dados = t;
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
  t->prox = NULL;
  t->ant = lista->final;

  if (lista->final == NULL)
  {
    lista->dados = t;
    lista->final = t;
  }
  else
  {
    assert(lista->final->prox == NULL);
    lista->final->prox = t;
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

  assert(lista->dados != NULL);
  p = lista->dados;

  if (valor)
  {
    *valor = p->dado;
  }

  lista->dados = p->prox;

  if (lista->dados == NULL)
  {
    lista->final = NULL;
  }
  else
  {
    lista->dados->ant = NULL;
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

  lista->final = p->ant;

  if (lista->final == NULL)
  {
    lista->dados = NULL;
  }
  else
  {
    lista->final->prox = NULL;
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
  t->prox = NULL;
  t->ant = NULL;
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

    if (lista->final == NULL)
    {
      lista->final = t;
    }
  }
  else
  {
    q->prox = t;
    t->ant = q;

    // Final da lista?
    if (p == NULL)
    {
      lista->final = t;
    }
    else
    {
      t->prox = p;
      p->ant = t;
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

  assert(lista->dados != NULL);
  assert(lista->final != NULL);
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

    if (p->prox != NULL)
    {
      p->prox->ant = NULL;
    }
  }
  else
  {
    q->prox = p->prox;

    if (p->prox != NULL)
    {
      p->prox->ant = q;
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

  if (lista->dados == NULL)
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

  p = lista->dados;

  for (contador = 0; contador < posicao; contador++)
  {
    p = p->prox;
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
  t->prox = NULL;
  t->ant = NULL;
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

    if (t->prox != NULL)
    {
      t->prox->ant = t;
    }

    lista->dados = t;

    if (lista->final == NULL)
    {
      lista->final = t;
    }
  }
  else
  {
    q->prox = t;
    t->ant = q;

    // Final da lista?
    if (p == NULL)
    {
      lista->final = t;
    }
    else
    {
      t->prox = p;
      p->ant = t;
    }
  }

  lista->numElementos = lista->numElementos + 1;
  return true;
}

bool remove_chave_de(LISTA_DE *lista, const TIPO_DADO *valor)
{
  NOH_DE *p, *q;
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

  // Nao achou
  if (p == NULL)
  {
    return false;
  }

  if (q == NULL)
  {
    lista->dados = p->prox;

    if (p->prox != NULL)
    {
      p->prox->ant = NULL;
    }
  }
  else
  {
    q->prox = p->prox;

    if (p->prox != NULL)
    {
      p->prox->ant = q;
    }
  }

  if (p == lista->final)
  {
    lista->final = q;
  }

  if (lista->dados == NULL)
  {
    lista->final = NULL;
  }

  libera_no_lista_de(&p);
  lista->numElementos = lista->numElementos - 1;
  return true;
}

bool obtem_sucessor_de(const NOH_DE *nodo, NOH_DE **sucessor)
{
  if ((nodo == NULL) || (nodo->prox == NULL))
  {
    return false;
  }

  *sucessor = nodo->prox;
  return true;
}

bool obtem_predecessor_de(const NOH_DE *nodo, NOH_DE **predecessor)
{
  if ((nodo == NULL) || (nodo->ant == NULL))
  {
    return false;
  }

  *predecessor = nodo->ant;
  return true;
}

bool obtem_inicio_de(const LISTA_DE *lista, NOH_DE **nodo)
{
  if (tamanho_lista_de(lista) == 0)
  {
    return false;
  }

  *nodo = lista->dados;
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
  p = lista->dados;

  if (!valor)
  {
    return false;
  }

  while ((p != NULL) && (p->dado != *valor))
  {
    p = p->prox;
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
  t->prox = NULL;
  t->ant = NULL;
  p = lista->dados;
  q = NULL;

  while ((p != NULL) && (p != *nodo))
  {
    q = p;
    p = p->prox;
  }

  // inicio da lista ou lista vazia?
  if (q == NULL)
  {
    t->prox = lista->dados;

    if (t->prox != NULL)
    {
      t->prox->ant = t;
    }

    lista->dados = t;

    if (lista->final == NULL)
    {
      lista->final = t;
    }
  }
  else
  {
    q->prox = t;
    t->ant = q;

    // Final da lista?
    if (p == NULL)
    {
      lista->final = t;
    }
    else
    {
      t->prox = p;
      p->ant = t;
    }
  }

  lista->numElementos = lista->numElementos + 1;
  return true;
}

// TODO: implementar remocao de nodo
bool remove_nodo_de(LISTA_DE *lista, NOH_DE **nodo)
{
  NOH_DE *p, *q;
  p = lista->dados;
  q = NULL;

  while ((p != NULL) && (p != *nodo))
  {
    q = p;
    p = p->prox;
  }

  // Nao achou
  if (p == NULL)
  {
    return false;
  }

  if (q == NULL)
  {
    lista->dados = p->prox;

    if (p->prox != NULL)
    {
      p->prox->ant = NULL;
    }
  }
  else
  {
    q->prox = p->prox;

    if (p->prox != NULL)
    {
      p->prox->ant = q;
    }
  }

  if (p == lista->final)
  {
    lista->final = q;
  }

  if (lista->dados == NULL)
  {
    lista->final = NULL;
  }

  libera_no_lista_de(&p);
  lista->numElementos = lista->numElementos - 1;
  return true;
}
