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

  if (!inicializa_fila(&f))
  {
    return 1;
  }

  printf("A fila tem %d itens armazenados\n", tamanho_fila(&f));

  for (i = 0 ; i < TAM_FILA ; i++)
  {
    v = (TIPO_DADO) rand() % 1000;

    if (!enfileira_prioridade(&f, &v))
    {
      printf("Fila cheia\n");
    }
    else
    {
      printf("Inserido %d\n", v);
    }
  }

  imprime_fila(&f);

  for (i = 0; i < TAM_FILA - 2; i++)
  {
    if (!desenfileira(&f, &v))
    {
      printf("Fila vazia\n");
    }
    else
    {
      printf("Removido %d\n", v);
    }
  }

  imprime_fila(&f);
  v = 999;
  enfileira(&f, &v);
  printf("Inserido %d\n", v);
  imprime_fila(&f);
  v = 111;

  if (!enfileira_prioridade(&f, &v))
  {
    printf("Fila cheia\n");
  }
  else
  {
    printf("Inserido ordenado\n");
  }

  imprime_fila(&f);
  printf("Destruindo a fila\n");
  destroi_fila(&f);
  printf("Situacao final\n");
  imprime_fila(&f);
  return 0;
}
