#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fila_est.h>

int main()
{
  FILA f;
  int i;
  TIPO_DADO v;
  srand(time(NULL));

  if (!fila_inicializar(&f))
  {
    return 1;
  }

  printf("A fila tem %d itens armazenados\n", fila_numero_de_elementos(&f));
  if (fila_esta_vazia(&f))
  {
    printf("Fila esta vazia\n");
  }
  else
  {
    printf("Fila nao esta vazia\n");
  }

  for (i = 0; i < TAM_FILA + 2; i++)
  {
    v = (TIPO_DADO) rand() % 1000;

    if (!fila_enfileirar(&f, &v))
    {
      printf("Fila cheia\n");
    }
    else
    {
      printf("Inserido %d\n", v);
    }
  }

  if (fila_esta_cheia(&f))
  {
    printf("Fila esta cheia\n");
  }
  else
  {
    printf("Fila nao esta cheia\n");
  }

  if (fila_head(&f, &v))
  {
    printf("Cabeca da fila: %d\n", v);
  }

  if (fila_tail(&f, &v))
  {
    printf("Final da fila: %d\n", v);
  }

  fila_imprimir(&f);
  printf("A fila tem %d itens armazenados\n", fila_numero_de_elementos(&f));

  for (i = 0; i < TAM_FILA - 2; i++)
  {
    if (!fila_desenfileirar(&f, &v))
    {
      printf("Fila vazia\n");
    }
    else
    {
      printf("Removido %d\n", v);
    }
  }

  fila_imprimir(&f);
  v = 999;
  fila_enfileirar(&f, &v);
  printf("Inserido %d\n", v);
  fila_imprimir(&f);
  v = 111;

  if (!fila_enfileirar_com_prioridade(&f, &v))
  {
    printf("Fila cheia\n");
  }
  else
  {
    printf("Inserido ordenado\n");
  }

  if (fila_head(&f, &v))
  {
    printf("Cabeca da fila: %d\n", v);
  }

  if (fila_tail(&f, &v))
  {
    printf("Final da fila: %d\n", v);
  }

  fila_imprimir(&f);
  printf("Destruindo a fila\n");
  fila_destruir(&f);
  printf("Situacao final\n");
  fila_imprimir(&f);
  return 0;
}
