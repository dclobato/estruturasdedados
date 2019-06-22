#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "arvorebinaria.h"

bool inicializa_arvore(ARVORE *arvore)
{
  *arvore = NULL;
  return true;
}

bool destroi_arvore(ARVORE *arvore)
{
  if (*arvore == NULL)
  {
    return false;
  }

  if ((*arvore)->esq != NULL)
  {
    destroi_arvore(&((*arvore)->esq));
  }

  if ((*arvore)->dir != NULL)
  {
    destroi_arvore(&((*arvore)->dir));
  }

  destroi_nodo_arvore(arvore);
  *arvore = NULL;
  return true;
}

bool cria_nodo_arvore(ARVORE *arvore)
{
  ARVORE p;
  p = (ARVORE) malloc(sizeof(NO_ARVORE));

  if (p == NULL)
  {
    return false;
  }

  p->esq = NULL;
  p->dir = NULL;
  *arvore = p;
  return true;
}

bool destroi_nodo_arvore(ARVORE *arvore)
{
  if (*arvore == NULL)
  {
    return false;
  }

  if (((*arvore)->esq != NULL) || ((*arvore)->dir != NULL))
  {
    return false;
  }

  free(*arvore);
  return true;
}

bool insere_na_arvore(ARVORE *arvore, TipoNo tipo, const TIPO_DADO *valor)
{
  ARVORE p;

  if (((tipo == ESQ) || (tipo == DIR)) && (*arvore == NULL))
  {
    return false;
  }

  if (!cria_nodo_arvore(&p))
  {
    return false;
  }

  p->dado = *valor;
  p->esq = NULL;
  p->dir = NULL;

  switch (tipo)
  {
    case RAIZ:
      if (*arvore == NULL)
      {
        *arvore = p;
      }

      return true;

    case ESQ:
      if ((*arvore)->esq == NULL)
      {
        (*arvore)->esq = p;
      }

      return true;

    case DIR:
      if ((*arvore)->dir == NULL)
      {
        (*arvore)->dir = p;
      }

      return true;

    default:
      free(p);
      return false;
  }
}

void imprime_arvore(const ARVORE *arvore)
{
  unsigned int linha = 0;
  __imprime_arvore(arvore, &linha);
}

void __imprime_arvore(const ARVORE *arvore, unsigned int *linha)
{
  int i;

  if (*arvore != NULL)
  {
    (*linha)++;
    __imprime_arvore(&((*arvore)->dir), linha);

    for (i = 0; i < (3 * (*linha)); i++)
    {
      printf("  ");
    }

    printf("%d\n", (*arvore)->dado);
    __imprime_arvore(&((*arvore)->esq), linha);
    (*linha)--;
  }
}

bool insere_arvore_binaria_busca(ARVORE *arvore, const TIPO_DADO *valor)
{
  if (*arvore == NULL)
  {
    insere_na_arvore(arvore, RAIZ, valor);
    return true;
  }

  // duplicado
  if ((*arvore)->dado == *valor)
  {
    return false;
  }

  // insere na esquerda
  if ((*arvore)->dado > *valor)
  {
    // esta na folha
    if ((*arvore)->esq == NULL)
    {
      return (insere_na_arvore(arvore, ESQ, valor));
    }
    else
    {
      return (insere_arvore_binaria_busca(&((*arvore)->esq), valor));
    }
  }
  else     // insere na direita
  {
    // esta na folha
    if ((*arvore)->dir == NULL)
    {
      return (insere_na_arvore(arvore, DIR, valor));
    }
    else
    {
      return (insere_arvore_binaria_busca(&((*arvore)->dir), valor));
    }
  }
}

bool pesquisa_abb(ARVORE *arvore, const TIPO_DADO *valor, ARVORE *nodo)
{
  if (*arvore == NULL)
  {
    return false;
  }

  if ((*arvore)->dado == *valor)
  {
    nodo = arvore;
    return true;
  }

  if ((*arvore)->dado > *valor)
  {
    return pesquisa_abb(&(*arvore)->esq, valor, nodo);
  }
  else
  {
    return pesquisa_abb(&(*arvore)->dir, valor, nodo);
  }
}

bool percurso(ARVORE *arvore, TipoPercurso tipo, PERCURSO *percurso)
{
  if (*arvore == NULL)
  {
    return false;
  }

  percurso->nodos = NULL;
  percurso->tamanho = 0;

  switch (tipo)
  {
    case PRE:
      return (percurso_pre(arvore, percurso));

    case IN:
      return (percurso_in(arvore, percurso));

    case POS:
      return (percurso_pos(arvore, percurso));

    case LARGURA:
      return (percurso_largura(arvore, percurso));

    default:
      break;
  }

  return false;
}

bool destroi_percurso(PERCURSO *percurso)
{
  percurso->tamanho = 0;

  if (percurso->nodos != NULL)
  {
    free(percurso->nodos);
  }

  return true;
}

bool percurso_pre(ARVORE *arvore, PERCURSO *percurso)
{
  if (*arvore == NULL)
  {
    return true;
  }

  percurso->nodos = (TIPO_DADO *) realloc(percurso->nodos,
                                          (percurso->tamanho + 1) * sizeof(TIPO_DADO));

  if (percurso->nodos == NULL)
  {
    return false;
  }

  percurso->nodos[percurso->tamanho++] = (*arvore)->dado;
  percurso_pre(&(*arvore)->esq, percurso);
  percurso_pre(&(*arvore)->dir, percurso);
  return true;
}

bool percurso_in(ARVORE *arvore, PERCURSO *percurso)
{
  if (*arvore == NULL)
  {
    return true;
  }

  percurso->nodos = (TIPO_DADO *) realloc(percurso->nodos,
                                          (percurso->tamanho + 1) * sizeof(TIPO_DADO));

  if (percurso->nodos == NULL)
  {
    return false;
  }

  percurso_in(&(*arvore)->esq, percurso);
  percurso->nodos[percurso->tamanho++] = (*arvore)->dado;
  percurso_in(&(*arvore)->dir, percurso);
  return true;
}

bool percurso_pos(ARVORE *arvore, PERCURSO *percurso)
{
  if (*arvore == NULL)
  {
    return true;
  }

  percurso->nodos = (TIPO_DADO *) realloc(percurso->nodos,
                                          (percurso->tamanho + 1) * sizeof(TIPO_DADO));

  if (percurso->nodos == NULL)
  {
    return false;
  }

  percurso_pos(&(*arvore)->esq, percurso);
  percurso_pos(&(*arvore)->dir, percurso);
  percurso->nodos[percurso->tamanho++] = (*arvore)->dado;
  return true;
}

bool percurso_largura(ARVORE *arvore, PERCURSO *percurso)
{
  FILA fila;
  ARVORE temp;

  if (*arvore == NULL)
  {
    return true;
  }

  cria_fila(&fila);
  insere_fila(&fila, *arvore);
  percurso->tamanho = 0;

  while (fila != NULL)
  {
    remove_fila(&fila, &temp);
    percurso->nodos = (TIPO_DADO *) realloc(percurso->nodos,
                                            (percurso->tamanho + 1) * sizeof(TIPO_DADO));
    percurso->nodos[percurso->tamanho++] = temp->dado;

    if (temp->esq != NULL)
    {
      insere_fila(&fila, temp->esq);
    }

    if (temp->dir != NULL)
    {
      insere_fila(&fila, temp->dir);
    }
  }

  return true;
}

bool cria_fila(FILA *fila)
{
  *fila = NULL;
  return true;
}

bool insere_fila(FILA *fila, ARVORE nodo)
{
  FILA p, novo;
  novo = (FILA) malloc(sizeof(struct NOH_FILA));

  if (novo == NULL)
  {
    printf("Sem memoria para alocar\n");
    exit(1);
  }

  novo->item = nodo;
  novo->prox = NULL;
  p = *fila;

  while ((p != NULL) && (p->prox != NULL))
  {
    p = p->prox;
  }

  if (p == NULL)
  {
    *fila = novo;
  }
  else
  {
    p->prox = novo;
  }

  return true;
}

bool remove_fila(FILA *fila, ARVORE *nodo)
{
  FILA temp;

  if (*fila == NULL)
  {
    *nodo = NULL;
    return false;
  }

  temp = *fila;
  *nodo = (*fila)->item;
  *fila = (*fila)->prox;
  free(temp);
  return true;
}

unsigned altura_da_arvore(const ARVORE *arvore)
{
  unsigned alturaEsquerda, alturaDireita;

  if (*arvore == NULL)
  {
    return 0;
  }

  alturaEsquerda = altura_da_arvore((const ARVORE *) & (*arvore)->esq);
  alturaDireita = altura_da_arvore((const ARVORE *) & (*arvore)->dir);
  return alturaEsquerda > alturaDireita ? alturaEsquerda + 1 : alturaDireita +
         1;
}

unsigned numero_de_nodos(const ARVORE *arvore)
{
  if (*arvore == NULL)
  {
    return 0;
  }

  return numero_de_nodos((const ARVORE *) & (*arvore)->esq) + 1 +
         numero_de_nodos((const ARVORE *) & (*arvore)->dir);
}

unsigned nivel_do_nodo(const ARVORE *arvore, const TIPO_DADO *valor)
{
  if (((*arvore) == NULL) || (valor == NULL))
  {
    return 0;
  }

  return __nivel_do_nodo(arvore, valor, 1);
}

unsigned __nivel_do_nodo(const ARVORE *arvore, const TIPO_DADO *valor,
                         unsigned nivel)
{
  unsigned nivel_para_baixo;

  if (((*arvore) == NULL) || (valor == NULL))
  {
    return 0;
  }

  if ((*arvore)->dado == *valor)
  {
    return nivel;
  }

  nivel_para_baixo = __nivel_do_nodo((const ARVORE *) & (*arvore)->esq, valor,
                                     nivel + 1);

  if (nivel_para_baixo != 0)
  {
    return nivel_para_baixo;
  }

  nivel_para_baixo = __nivel_do_nodo((const ARVORE *) & (*arvore)->dir, valor,
                                     nivel + 1);
  return nivel_para_baixo;
}
