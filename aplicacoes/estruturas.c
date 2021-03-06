#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <estruturas.h>

bool inicializa_lista(LISTA *l)
{
  *l = NULL;
  return true;
}

bool insere_ordenado(LISTA *l, char *s, int f, ARVORE t1, ARVORE t2, bool atualizaBaseProx)
{
  LISTA tmp, aux, anterior;
  tmp = aloca_noh();
  strcpy(tmp->simbolo, s);
  tmp->freq = f;
  tmp->esq = t1;
  tmp->dir = t2;
  /* vamos manter uma lista usando os ponteiros de baseprox apenas com as folhas. ou seja,
     baseprox so vai ser atualizado na insercao dos simbolos individuais. quando for para colocar
     simbolos compostos, a gente encadeia soh por prox, e deixa o baseprox como esta. No final, se
     percorrer a lista por baseprox, vai andar so nas folhas */
  tmp->prox = NULL;
  tmp->baseprox = NULL;
  anterior = NULL;
  aux = *l;

  while ((aux != NULL) && (tmp->freq > aux->freq))
  {
    anterior = aux;
    aux = aux->prox;
  }

  if (anterior == NULL)
  {
    *l = tmp;
  }
  else
  {
    anterior->prox = tmp;

    if (atualizaBaseProx)
    {
      anterior->baseprox = tmp;
    }
  }

  tmp->prox = aux;

  if (atualizaBaseProx)
  {
    tmp->baseprox = aux;
  }

  return true;
}

LISTA aloca_noh(void)
{
  LISTA tmp;
  tmp = (LISTA) malloc(sizeof(NODO));

  if (tmp == NULL)
  {
    printf("Sem memoria\n");
    exit(1);
  }

  tmp->freq = 0;
  memset(tmp->simbolo, '\0', (size_t) sizeof(tmp->simbolo));
  memset(tmp->codigo, '\0', (size_t) sizeof(tmp->codigo));
  tmp->esq = NULL;
  tmp->dir = NULL;
  tmp->prox = NULL;
  return (tmp);
}

void _imprime_arvore(ARVORE p, int *linha)
{
  if (p != NULL)
  {
    (*linha)++;
    _imprime_arvore(p->dir, linha);
    int i;

    for (i = 0; i < (10 * (*linha)); i++)
    {
      printf(" ");
    }

    printf("[%s]\n", p->simbolo);
    _imprime_arvore(p->esq, linha);
    (*linha)--;
  }
}

void imprime_arvore(ARVORE p)
{
  int linha = 0;
  _imprime_arvore(p, &linha);
}
