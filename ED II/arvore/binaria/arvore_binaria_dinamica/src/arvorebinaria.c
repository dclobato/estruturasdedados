#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <arvorebinaria.h>

bool arvore_binaria_inicializar(ARVORE *arvore)
{
  *arvore = NULL;
  return true;
}

bool arvore_binaria_destruir(ARVORE *arvore)
{
  if (*arvore == NULL)
  {
    return false;
  }

  if ((*arvore)->esq != NULL)
  {
    arvore_binaria_destruir(&((*arvore)->esq));
  }

  if ((*arvore)->dir != NULL)
  {
    arvore_binaria_destruir(&((*arvore)->dir));
  }

  arvore_binaria_liberar_no(arvore);
  *arvore = NULL;
  return true;
}

bool arvore_binaria_obter_no(ARVORE *arvore)
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

bool arvore_binaria_liberar_no(ARVORE *arvore)
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

bool arvore_binaria_inserir_chave(ARVORE *arvore, TipoNo tipo, const TIPO_DADO *valor)
{
  ARVORE p;

  if (((tipo == ESQ) || (tipo == DIR)) && (*arvore == NULL))
  {
    return false;
  }

  if (!arvore_binaria_obter_no(&p))
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

void arvore_binaria_imprimir(const ARVORE *arvore)
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
      printf("%s", "   ");
    }
    printf("%6d\n", (*arvore)->dado);
    __imprime_arvore(&((*arvore)->esq), linha);
    (*linha)--;
  }
}

bool arvore_binaria_busca_inserir_chave(ARVORE *arvore, const TIPO_DADO *valor)
{
  if (*arvore == NULL)
  {
    arvore_binaria_inserir_chave(arvore, RAIZ, valor);
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
      return (arvore_binaria_inserir_chave(arvore, ESQ, valor));
    }
    else
    {
      return (arvore_binaria_busca_inserir_chave(&((*arvore)->esq), valor));
    }
  }
  else     // insere na direita
  {
    // esta na folha
    if ((*arvore)->dir == NULL)
    {
      return (arvore_binaria_inserir_chave(arvore, DIR, valor));
    }
    else
    {
      return (arvore_binaria_busca_inserir_chave(&((*arvore)->dir), valor));
    }
  }
}

bool arvore_binaria_busca_pesquisar_chave(ARVORE *arvore, const TIPO_DADO *valor, ARVORE *nodo)
{
  if (*arvore == NULL)
  {
    return false;
  }

  if ((*arvore)->dado == *valor)
  {
    *nodo = *arvore;
    return true;
  }

  if ((*arvore)->dado > *valor)
  {
    return arvore_binaria_busca_pesquisar_chave(&(*arvore)->esq, valor, nodo);
  }
  else
  {
    return arvore_binaria_busca_pesquisar_chave(&(*arvore)->dir, valor, nodo);
  }
}

bool arvore_binaria_percorrer(const ARVORE *arvore, TipoPercurso tipo, PERCURSO *percurso)
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
      return (__percurso_pre((const ARVORE *) arvore, percurso));

    case IN:
      return (__percurso_in((const ARVORE *) arvore, percurso));

    case POS:
      return (__percurso_pos((const ARVORE *) arvore, percurso));

    case LARGURA:
      return (__percurso_largura((const ARVORE *) arvore, percurso));

    default:
      return false;
  }
}

bool arvore_binaria_destruir_percurso(PERCURSO *percurso)
{
  percurso->tamanho = 0;

  if (percurso->nodos != NULL)
  {
    free(percurso->nodos);
  }

  return true;
}

bool __percurso_pre(const ARVORE *arvore, PERCURSO *percurso)
{
  if (*arvore == NULL)
  {
    return true;
  }

  percurso->nodos = realloc(percurso->nodos, (percurso->tamanho + 1) * sizeof(TIPO_DADO));
  if (percurso->nodos == NULL)
  {
    return false;
  }
  *(percurso->nodos + percurso->tamanho) = (*arvore)->dado;
  percurso->tamanho = percurso->tamanho + 1;
  __percurso_pre((const ARVORE *) &(*arvore)->esq, percurso);
  __percurso_pre((const ARVORE *) &(*arvore)->dir, percurso);
  return true;
}

bool __percurso_in(const ARVORE *arvore, PERCURSO *percurso)
{
  if (*arvore == NULL)
  {
    return true;
  }

  __percurso_in((const ARVORE *) &(*arvore)->esq, percurso);
  percurso->nodos = realloc(percurso->nodos, (percurso->tamanho + 1) * sizeof(TIPO_DADO));
  if (percurso->nodos == NULL)
  {
    return false;
  }
  *(percurso->nodos + percurso->tamanho) = (*arvore)->dado;
  percurso->tamanho = percurso->tamanho + 1;
  __percurso_in((const ARVORE *) &(*arvore)->dir, percurso);
  return true;
}

bool __percurso_pos(const ARVORE *arvore, PERCURSO *percurso)
{
  if (*arvore == NULL)
  {
    return true;
  }

  __percurso_pos((const ARVORE *) &(*arvore)->esq, percurso);
  __percurso_pos((const ARVORE *) &(*arvore)->dir, percurso);
  percurso->nodos = realloc(percurso->nodos, (percurso->tamanho + 1) * sizeof(TIPO_DADO));
  if (percurso->nodos == NULL)
  {
    return false;
  }
  *(percurso->nodos + percurso->tamanho) = (*arvore)->dado;
  percurso->tamanho = percurso->tamanho + 1;
  return true;
}

bool __percurso_largura(const ARVORE *arvore, PERCURSO *percurso)
{
  ARVORE *fila;
  NO_ARVORE temp;
  unsigned int cabeca, cauda;

  if (*arvore == NULL)
  {
    return true;
  }

  fila = NULL;
  fila = (ARVORE *) realloc(fila, sizeof(NO_ARVORE));
  cabeca = 0;
  cauda = 0;
  if (fila == NULL)
  {
    printf("[AB:PL] Falha na alocacao de memoria\n");
    exit(1);
  }
  *(fila + cauda) = *arvore;
  cauda++;

  while (cauda != cabeca)
  {
    temp = **(fila + cabeca);
    cabeca++;

    percurso->nodos = realloc(percurso->nodos, (percurso->tamanho + 1) * sizeof(TIPO_DADO));
    if (percurso->nodos == NULL)
    {
      printf("[AB:PL] Falha na alocacao de memoria\n");
      exit(1);
    }
    *(percurso->nodos + percurso->tamanho) = temp.dado;
    percurso->tamanho = percurso->tamanho + 1;

    if (temp.esq != NULL)
    {
      fila = realloc(fila, (cauda + 1) * sizeof(NO_ARVORE));
      if (fila == NULL)
      {
        return false;
      }
      *(fila + cauda) = temp.esq;
      cauda++;
    }

    if (temp.dir != NULL)
    {
      fila = realloc(fila, (cauda + 1) * sizeof(NO_ARVORE));
      if (fila == NULL)
      {
        return false;
      }
      *(fila + cauda) = temp.dir;
      cauda++;
    }
  }

  free(fila);
  return true;
}

unsigned arvore_binaria_altura(const ARVORE *arvore)
{
  unsigned alturaEsquerda, alturaDireita;

  if (*arvore == NULL)
  {
    return 0;
  }

  alturaEsquerda = arvore_binaria_altura((const ARVORE *) &(*arvore)->esq);
  alturaDireita = arvore_binaria_altura((const ARVORE *) &(*arvore)->dir);
  return alturaEsquerda > alturaDireita ? alturaEsquerda + 1 : alturaDireita + 1;
}

unsigned arvore_binaria_numero_nodos(const ARVORE *arvore)
{
  if (*arvore == NULL)
  {
    return 0;
  }

  return arvore_binaria_numero_nodos((const ARVORE *) &(*arvore)->esq) + 1 +
         arvore_binaria_numero_nodos((const ARVORE *) &(*arvore)->dir);
}

unsigned arvore_binaria_nivel_nodo(const ARVORE *arvore, const TIPO_DADO *valor)
{
  if (((*arvore) == NULL) || (valor == NULL))
  {
    return 0;
  }

  return __nivel_do_nodo(arvore, valor, 1);
}

unsigned __nivel_do_nodo(const ARVORE *arvore, const TIPO_DADO *valor, unsigned nivel)
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

  nivel_para_baixo = __nivel_do_nodo((const ARVORE *) &(*arvore)->esq, valor, nivel + 1);

  if (nivel_para_baixo != 0)
  {
    return nivel_para_baixo;
  }

  nivel_para_baixo = __nivel_do_nodo((const ARVORE *) &(*arvore)->dir, valor, nivel + 1);
  return nivel_para_baixo;
}

bool arvore_binaria_sucessor_in_ordem(const ARVORE *raiz, ARVORE *sucessor, ARVORE *pai_sucessor)
{
  ARVORE temp;

  if (*raiz == NULL)
  { // arvore vazia
    return false;
  }

  if ((*raiz)->dir == NULL)
  { // nao possui filhos a direita
    return false;
  }

  // segue para a direita e, depois, pega o filho mais a esquerda
  *pai_sucessor = *raiz;
  *sucessor = (*raiz)->dir;
  temp = (*sucessor)->esq;
  while (temp != NULL)
  {
    *pai_sucessor = *sucessor;
    *sucessor = temp;
    temp = temp->esq;
  }

  return true;
}

bool arvore_binaria_busca_remover_chave(ARVORE *arvore, const TIPO_DADO *valor)
{
  ARVORE temp, ant, sucessor, pai_sucessor;
  TipoNo saiu_pela;

  if ((*arvore == NULL) || (valor == NULL))
  {
    return false;
  }

  temp = *arvore;
  ant = NULL;
  saiu_pela = RAIZ;
  while ((temp != NULL) && (temp->dado != *valor))
  {
    ant = temp;
    if (*valor > temp->dado)
    {
      temp = temp->dir;
      saiu_pela = DIR;
    }
    else
    {
      temp = temp->esq;
      saiu_pela = ESQ;
    }
  }

  if (temp == NULL)
  {
    return false;
  }

  // Primeiro caso: folha
  if ((temp->esq == NULL) && (temp->dir == NULL))
  {
    switch (saiu_pela) // NOLINT(hicpp-multiway-paths-covered)
    {
      case RAIZ:
        *arvore = NULL;
        break;
      case ESQ:
        ant->esq = NULL;
        break;
      case DIR:
        ant->dir = NULL;
        break;
    }
    return (arvore_binaria_liberar_no(&temp));
  }

  // Segundo caso: no com apenas um filho (XOR)
  if (((temp->esq == NULL) || (temp->dir == NULL)) && !((temp->esq == NULL) && (temp->dir == NULL)))
  {
    switch (saiu_pela) // NOLINT(hicpp-multiway-paths-covered)
    {
      case RAIZ:
        if (temp->esq == NULL)
        {
          *arvore = temp->dir;
          temp->dir = NULL;
        }
        else
        {
          *arvore = temp->esq;
          temp->esq = NULL;
        }
        break;
      case ESQ:
        if (temp->esq == NULL)
        {
          ant->esq = temp->dir;
          temp->dir = NULL;
        }
        else
        {
          ant->esq = temp->esq;
          temp->esq = NULL;
        }
        break;
      case DIR:
        if (temp->esq == NULL)
        {
          ant->dir = temp->dir;
          temp->dir = NULL;
        }
        else
        {
          ant->dir = temp->esq;
          temp->esq = NULL;
        }
        break;
    }
    return (arvore_binaria_liberar_no(&temp));
  }

  // Terceiro caso: no com dois filhos
  if ((temp->esq != NULL) && (temp->dir != NULL))
  {
    if (!arvore_binaria_sucessor_in_ordem(&temp, &sucessor, &pai_sucessor))
    {
      return false;
    }

    swap(temp->dado, sucessor->dado);
    if (temp == pai_sucessor)
    {
      temp->dir = sucessor->dir;
    }
    else
    {
      pai_sucessor->esq = sucessor->dir;
    }
    sucessor->dir = NULL;
    return (arvore_binaria_liberar_no(&sucessor));
  }
  return false;
}
