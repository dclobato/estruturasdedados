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

  if (!fila_inicializar(&fila))
  {
    return 1;
  }

  printf("A fila tem %u itens armazenados\n", fila_numero_de_elementos(&fila));

  if (fila_esta_vazia(&fila))
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

    if (!fila_enfileirar_com_prioridade(&fila, &v))
    {
      printf("Fila cheia\n");
    }
    else
    {
      printf("Inserido %d\n", v);
    }
  }

  if (fila_head(&fila, &v))
  {
    printf("Cabeca da fila: %d\n", v);
  }

  if (fila_tail(&fila, &v))
  {
    printf("Final da fila: %d\n", v);
  }

  if (fila_esta_cheia(&fila))
  {
    printf("A fila esta cheia\n");
  }
  else
  {
    printf("A fila nao esta cheia\n");
  }


  fila_imprimir(&fila);

  for (i = 0; i < TAM_FILA - 2; i++)
  {
    if (!fila_desenfileirar(&fila, &v))
    {
      printf("Fila vazia\n");
    }
    else
    {
      printf("Removido %d\n", v);
    }
  }

  fila_imprimir(&fila);
  v = 999;
  fila_enfileirar(&fila, &v);
  printf("Inserido %d\n", v);
  fila_imprimir(&fila);
  v = 111;

  if (!fila_enfileirar_com_prioridade(&fila, &v))
  {
    printf("Fila cheia\n");
  }
  else
  {
    printf("Inserido ordenado\n");
  }
  if (fila_head(&fila, &v))
  {
    printf("Cabeca da fila: %d\n", v);
  }

  if (fila_tail(&fila, &v))
  {
    printf("Final da fila: %d\n", v);
  }

  fila_imprimir(&fila);
  printf("Destruindo a fila\n");
  fila_destruir(&fila);
  printf("Situacao final\n");
  fila_imprimir(&fila);
  return 0;
}
