#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <lista_circ.h>

bool inicializa_lista_circ(LISTA_CIRC *lista)
{
  lista->numElementos = 0;
  lista->final = NULL;
  return true;
}

bool destroi_lista_circ(LISTA_CIRC *lista)
{
  NOH_CIRC *p, *q;

  if (lista->final == NULL)
  {
    return true;
  }

  p = lista->final->sucessor;

  while (p != lista->final)
  {
    q = p;
    p = p->sucessor;
    libera_no_lista_circ(&q);
    lista->numElementos--;
  }

  if (p != NULL)
  {
    libera_no_lista_circ(&p);
    lista->numElementos--;
  }

  lista->final = NULL;
  assert(lista->numElementos == 0);
  return true;
}

bool obtem_no_lista_circ(NOH_CIRC **nodo)
{
  NOH_CIRC *p;
  p = (NOH_CIRC *) malloc(sizeof(NOH_CIRC));

  if (!p)
  {
    return false;
  }

  p->sucessor = NULL;
  *nodo = p;
  return true;
}

bool libera_no_lista_circ(NOH_CIRC **nodo)
{
  if (!*nodo)
  {
    return false;
  }

  free(*nodo);
  *nodo = NULL;
  return true;
}

unsigned int tamanho_lista_circ(const LISTA_CIRC *lista)
{
  return (lista->numElementos);
}

void imprime_lista_circ(const LISTA_CIRC *lista)
{
  NOH_CIRC *p;
  unsigned int i;

  printf("Posicoes ocupadas: %u\n", tamanho_lista_circ(lista));

  if (lista->final == NULL)
  {
    return;
  }

  p = lista->final->sucessor;
  i = 0;

  do
  {
    printf("[%03u]: %5d\n", i, p->dado);
    p = p->sucessor;
    i++;
  } while (p != lista->final->sucessor);

  printf("\n");
}


void __imprime_lista_circ(const LISTA_CIRC *lista)
{
  NOH_CIRC *p;
  unsigned int i;
  printf("Posicoes ocupadas........: %u\n", tamanho_lista_circ(lista));
  printf("Posicao ultimo elemento..: %p\n", lista->final);

  if (lista->final == NULL)
  {
    return;
  }

  p = lista->final->sucessor;
  i = 0;

  do
  {
    printf("[%03u]: %5d   (p: %14p, sucessor: %14p)\n", i, p->dado, p, p->sucessor);
    p = p->sucessor;
    i++;
  } while (p != lista->final->sucessor);

  printf("\n");

}

bool consulta_lista_circ(const LISTA_CIRC *lista, unsigned int posicao, TIPO_DADO *valor)
{
  NOH_CIRC *p;
  unsigned int contador;

  if ((posicao < 0) || (posicao > (tamanho_lista_circ(lista) - 1)))
  {
    return false;
  }

  p = lista->final->sucessor;

  for (contador = 0; contador < posicao; contador++)
  {
    p = p->sucessor;
  }

  *valor = p->dado;
  return true;
}

bool busca_lista_circ(const LISTA_CIRC *lista, const TIPO_DADO *valor, NOH_CIRC **nodo)
{
  NOH_CIRC *p;

  if ((lista->final == NULL) || (!valor))
  {
    return false;
  }

  p = lista->final->sucessor;

  do
  {
    if (p->dado == *valor)
    {
      break;
    }
    p = p->sucessor;
  } while (p != lista->final->sucessor);

  *nodo = p;
  return (p->dado == *valor);
}

bool obtem_sucessor_circ(const NOH_CIRC *nodo, NOH_CIRC **sucessor)
{
  if (nodo == NULL)
  {
    return false;
  }

  *sucessor = nodo->sucessor;
  return true;
}

bool obtem_inicio_circ(const LISTA_CIRC *lista, NOH_CIRC **nodo)
{
  if (lista->final != NULL)
  {
    return false;
  }
  *nodo = lista->final->sucessor;
  return true;
}

bool obtem_final_circ(const LISTA_CIRC *lista, NOH_CIRC **nodo)
{
  if (lista->final != NULL)
  {
    return false;
  }
  *nodo = lista->final;
  return true;
}

bool insere_inicio_circ(LISTA_CIRC *lista, const TIPO_DADO *valor)
{
  NOH_CIRC *t;

  if (!valor || !obtem_no_lista_circ(&t))
  {
    return false;
  }

  t->dado = *valor;
  t->sucessor = t;

  if (lista->final != NULL)
  {
    t->sucessor = lista->final->sucessor;
    lista->final->sucessor = t;
  }
  else
  {
    lista->final = t;
  }
  lista->numElementos++;
  return true;
}

bool insere_final_circ(LISTA_CIRC *lista, const TIPO_DADO *valor)
{
  NOH_CIRC *t;

  if (!insere_inicio_circ(lista, valor))
  {
    return false;
  }

  lista->final = lista->final->sucessor;
  return true;

}

bool obtem_valor_no(const NOH_CIRC *nodo, TIPO_DADO *valor)
{
  if (nodo == NULL)
  {
    return false;
  }
  *valor = nodo->dado;
  return true;
}

bool definir_valor_no(NOH_CIRC *nodo, const TIPO_DADO *valor)
{
  if (nodo == NULL)
  {
    return false;
  }
  nodo->dado = *valor;
  return true;
}

bool shift_right_lista_circ(LISTA_CIRC *lista)
{
  if (lista->final == NULL)
  {
    return false;
  }

  lista->final = lista->final->sucessor;
  return true;
}

bool remove_inicio_circ(LISTA_CIRC *lista, TIPO_DADO *valor)
{
  NOH_CIRC *aux;
  if (lista->final == NULL)
  {
    return false;
  }

  aux = lista->final->sucessor;
  if (aux == lista->final)
  {
    lista->final = NULL;
  }
  else
  {
    lista->final->sucessor = aux->sucessor;
  }

  *valor = aux->dado;
  libera_no_lista_circ (&aux);
  lista->numElementos--;
  return true;
}

bool remove_final_circ(LISTA_CIRC *lista, TIPO_DADO *valor)
{
  NOH_CIRC *aux, *ant;

  if (lista->final == NULL)
  {
    return false;
  }

  ant = lista->final;
  aux = lista->final->sucessor;

  while (aux != lista->final)
  {
    ant = aux;
    aux = aux->sucessor;
  }

  ant->sucessor = aux->sucessor;

  if (ant == aux)
    lista->final = NULL;
  else
    lista->final = ant;

  *valor = aux->dado;
  libera_no_lista_circ (&aux);
  lista->numElementos--;
  return true;
}
