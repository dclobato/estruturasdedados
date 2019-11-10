#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fila.h>

int main()
{
  FILA fila;
  unsigned int i;
  TIPO_DADO v;
  srand(time(NULL));
  const unsigned int TAM_FILA = 10;

  if (!fila_inicializa(&fila))
  {
    return 1;
  }

  printf("A fila tem %u itens armazenados\n", fila_tamanho(&fila));

  if (fila_vazia(&fila))
  {
    printf("A fila esta vazia\n");
  }
  else
  {
    printf("A fila nao esta vazia\n");
  }

  for (i = 0; i < TAM_FILA; i++)
  {
    v = (TIPO_DADO) rand() % 1000;

    if (!fila_enfileira_prioridade(&fila, &v))
    {
      printf("Fila cheia\n");
    }
    else
    {
      printf("Inserido %d\n", v);
    }
  }

  if (fila_cheia(&fila))
  {
    printf("A fila esta cheia\n");
  }
  else
  {
    printf("A fila nao esta cheia\n");
  }


  fila_imprime(&fila);

  for (i = 0; i < TAM_FILA - 2; i++)
  {
    if (!fila_desenfileira(&fila, &v))
    {
      printf("Fila vazia\n");
    }
    else
    {
      printf("Removido %d\n", v);
    }
  }

  fila_imprime(&fila);
  v = 999;
  fila_enfileira(&fila, &v);
  printf("Inserido %d\n", v);
  fila_imprime(&fila);
  v = 111;

  if (!fila_enfileira_prioridade(&fila, &v))
  {
    printf("Fila cheia\n");
  }
  else
  {
    printf("Inserido ordenado\n");
  }

  fila_imprime(&fila);
  printf("Destruindo a fila\n");
  fila_destroi(&fila);
  printf("Situacao final\n");
  fila_imprime(&fila);
  return 0;
}
