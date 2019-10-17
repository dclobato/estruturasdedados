#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <fila_est.h>

int
main()
{
  FILA f;
  int i;
  TIPO_DADO v;
  srand(time(NULL));

  if (!fila_inicializa(&f))
  {
    return 1;
  }

  printf("A fila tem %d itens armazenados\n", fila_tamanho(&f));
  if (fila_vazia(&f))
    printf("Fila esta vazia\n");
  else
    printf("Fila nao esta vazia\n");

  for (i = 0 ; i < TAM_FILA ; i++)
  {
    v = (TIPO_DADO) rand() % 1000;

    if (!fila_enfileira_prioridade(&f, &v))
    {
      printf("Fila cheia\n");
    }
    else
    {
      printf("Inserido %d\n", v);
    }
  }

  if (fila_cheia(&f))
    printf("Fila esta cheia\n");
  else
    printf("Fila nao esta cheia\n");

  fila_imprime(&f);
  printf("A fila tem %d itens armazenados\n", fila_tamanho(&f));

  for (i = 0; i < TAM_FILA - 2; i++)
  {
    if (!fila_desenfileira(&f, &v))
    {
      printf("Fila vazia\n");
    }
    else
    {
      printf("Removido %d\n", v);
    }
  }

  fila_imprime(&f);
  v = 999;
  fila_enfileira(&f, &v);
  printf("Inserido %d\n", v);
  fila_imprime(&f);
  v = 111;

  if (!fila_enfileira_prioridade(&f, &v))
  {
    printf("Fila cheia\n");
  }
  else
  {
    printf("Inserido ordenado\n");
  }

  fila_imprime(&f);
  printf("Destruindo a fila\n");
  fila_destroi(&f);
  printf("Situacao final\n");
  fila_imprime(&f);
  return 0;
}
