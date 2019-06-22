#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <fila.h>

int main()
{
  FILA fila;
  unsigned int i;
  TIPO_DADO v;
  srand(time(NULL));
  const unsigned int TAM_FILA = 10;

  if (!inicializa_fila(&fila))
  {
    return 1;
  }

  printf("A fila tem %u itens armazenados\n", tamanho_fila(&fila));

  for (i = 0 ; i < TAM_FILA ; i++)
  {
    v = (TIPO_DADO) rand() % 1000;

    if (!enfileira_prioridade(&fila, &v))
    {
      printf("Fila cheia\n");
    }
    else
    {
      printf("Inserido %d\n", v);
    }
  }

  imprime_fila(&fila);

  for (i = 0; i < TAM_FILA - 2; i++)
  {
    if (!desenfileira(&fila, &v))
    {
      printf("Fila vazia\n");
    }
    else
    {
      printf("Removido %d\n", v);
    }
  }

  imprime_fila(&fila);
  v = 999;
  enfileira(&fila, &v);
  printf("Inserido %d\n", v);
  imprime_fila(&fila);
  v = 111;

  if (!enfileira_prioridade(&fila, &v))
  {
    printf("Fila cheia\n");
  }
  else
  {
    printf("Inserido ordenado\n");
  }

  imprime_fila(&fila);
  printf("Destruindo a fila\n");
  destroi_fila(&fila);
  printf("Situacao final\n");
  imprime_fila(&fila);
  return 0;
}
