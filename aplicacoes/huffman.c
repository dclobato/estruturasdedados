#pragma clang diagnostic push
#pragma ide diagnostic ignored "readability-redundant-control-flow"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <estruturas.h>

void mostra_freq(LISTA, bool);
void cria_arvore(ARVORE *);
void constroi_codigos(ARVORE, int);
void pp(ARVORE, int, char *);
bool codifica(LISTA, char *, char *);
bool decodifica(ARVORE, char *, char *);

int main(int argc, char *argv[])
{
  LISTA simbolos, folhas;
  int frequencia[256] = {0};
  char buffer[256];
  char codificado[1024];
  char decodificado[256];
  unsigned long tamanho, i;
    inicializa_lista(&simbolos);
  const char *cadeia = "o rato roeu a roupa do rei de roma";
  tamanho = strlen(cadeia);

  for (i = 0; i < tamanho; i++)
  {
    frequencia[(int) cadeia[i]] = frequencia[(int) cadeia[i]] + 1;
  }

  for (i = 0; i < 256; i++)
  {
    if (frequencia[i] > 0)
    {
      buffer[0] = (char) i;
      buffer[1] = '\0';

      if (!insere_ordenado(&simbolos, buffer, frequencia[i], NULL, NULL, true))
      {
        printf("Problemas em [%c]\n", (char) i);
        exit(1);
      }
    }
  }

  mostra_freq(simbolos, true);
  // guardando uma lista soh com as folhas, por onde vamos fazer a codificacao
  folhas = simbolos;
  cria_arvore(&simbolos);
  constroi_codigos(simbolos, 0);
  imprime_arvore(simbolos);
  mostra_freq(folhas, true);

  if (!codifica(folhas, (char *) cadeia, codificado))
  {
    printf("Achei um simbolo que nao tem codigo!\n");
  }

  printf("[%s]\n", codificado);

  if (!decodifica(simbolos, codificado, decodificado))
  {
    printf("Erro na cadeia codificada\n");
  }

  printf("[%s]\n", decodificado);
  return 0;
}

void mostra_freq(LISTA l, bool mostraCodigo)
{
  int t = 0;
  printf("--------+------+%s\n", mostraCodigo ? "-------------" : "");
  printf("Simbolo | Freq |%s\n", mostraCodigo ? " Codigo" : "");
  printf("--------+------+%s\n", mostraCodigo ? "-------------" : "");

  while (l != NULL)
  {
    printf("  [%s]   |  %3d | %s\n", l->simbolo, l->freq, mostraCodigo ? l->codigo : "");
    t = t + l->freq;

    if (mostraCodigo)
    {
      l = l->baseprox;
    }
    else
    {
      l = l->prox;
    }
  }

  printf("--------+------+%s\n", mostraCodigo ? "-------------" : "");
  printf("  TOTAL |  %3d |\n", t);
  printf("--------+------+%s\n", mostraCodigo ? "-------------" : "");
  return;
}


void cria_arvore(ARVORE *t)
{
  ARVORE t1, t2;
  int ftotal;
  char buffer[256];

  while ((*t)->prox != NULL)
  {
    t1 = *t;
    t2 = (*t)->prox;
    *t = t2->prox;
    ftotal = t1->freq + t2->freq;
    strcpy(buffer, t1->simbolo);
    strcat(buffer, t2->simbolo);

    if (!insere_ordenado(t, buffer, ftotal, t1, t2, false))
    {
      printf("Problemas na insercao do combinado de frequencia total %d\n", ftotal);
      exit(1);
    }

    t1->prox = NULL;
    t2->prox = NULL;
  }

  return;
}

void constroi_codigos(ARVORE t, int tamanhoCodigo)
{
  pp(t, tamanhoCodigo, NULL);
  return;
}

void pp(ARVORE t, int posicao, char *prefixo)
{
  char novoprefixo[128];

  if (t == NULL)
  {
    return;
  }

  strncpy(t->codigo, prefixo, posicao);
  t->codigo[posicao] = '\0';
  strcpy(novoprefixo, t->codigo);
  strcat(novoprefixo, "0");
  pp(t->esq, posicao + 1, novoprefixo);
  strcpy(novoprefixo, t->codigo);
  strcat(novoprefixo, "1");
  pp(t->dir, posicao + 1, novoprefixo);
  return;
}

bool codifica(LISTA l, char *in, char *out)
{
  unsigned long tamanho, i;
  LISTA t;
  tamanho = strlen(in);

  for (i = 0; i < tamanho; i++)
  {
    t = l;

    while ((t != NULL) && (t->simbolo[0] != in[i]))
    {
      t = t->baseprox;
    }

    if (t == NULL)
    {
      return false;
    }

    if (i == 0)
    {
      strcpy(out, t->codigo);
    }
    else
    {
      strcat(out, t->codigo);
    }
  }

  return true;
}

bool decodifica(ARVORE simbolos, char *in, char *out)
{
  unsigned long pin, pout, tam;
  ARVORE t;
  pin = 0;
  pout = 0;
  tam = strlen(in);
  t = simbolos;

  while ((t != NULL) && (pin <= tam))
  {
    if ((t->esq == NULL) && (t->dir == NULL))
    {
      if (pout == 0)
      {
        strcpy(out, t->simbolo);
      }
      else
      {
        strcat(out, t->simbolo);
      }

      pout++;

      if (pin < tam)
      {
        t = simbolos;
      }
    }

    if (pin < tam)
    {
      if (in[pin] == '0')
      {
        t = t->esq;
      }
      else
      {
        t = t->dir;
      }
    }

    pin++;
  }

  // acabou a arvore e ainda tem codigo
  // parou no meio da arvore
  if ((t == NULL) || ((t->esq != NULL) || (t->dir != NULL)))
  {
    return false;
  }
  else //if ((t->esq !=  NULL) || (t->dir != NULL))
  {
    return true;
  }
}
