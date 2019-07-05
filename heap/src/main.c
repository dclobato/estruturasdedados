#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <heap.h>

int main()
{
  int i;
  TIPO_DADO valores[25];
  TIPO_DADO dado, dado2;
  tipoHeap tipo;
  unsigned limite;
  HEAP h;
  limite = 10;
  srand((unsigned)time(NULL));
  inicializa_heap(&h, limite + 1, MIN_HEAP);
  printf("Dados originais\n");

  for (i = 0; i < limite; i++)
  {
    valores[i] = rand() % 100;
    printf("%d ", valores[i]);
  }

  printf("\n\n");
  constroi_heap(&h, valores, limite);
  heap_tipo(&h, &tipo);
  limite = tamanho_heap(&h);
  printf("Heap tipo %d com %u elementos\n", tipo, limite);

  for (i = 0; i < limite; i++)
  {
    printf("%d ", h.dados[i]);
  }

  printf("\n\n");
  printf("Invertendo heap...\n");
  heap_inverte(&h);
  heap_tipo(&h, &tipo);
  limite = tamanho_heap(&h);
  printf("Heap tipo %d com %u elementos\n", tipo, limite);

  for (i = 0; i < limite; i++)
  {
    printf("%d ", h.dados[i]);
  }

  printf("\n\n");
  peek_heap(&h, &dado);
  printf("Topo da heap: %d\n", dado);
  printf("\n");
  printf("Tirando o topo da heap... ");
  pop_heap(&h, &dado);
  printf("Topo da heap: %d\n", dado);
  printf("\n");
  printf("%d %d\n", h.ocupados, h.tamanhoMaximo);
  heap_tipo(&h, &tipo);
  limite = tamanho_heap(&h);
  printf("Heap tipo %d com %u elementos\n", tipo, limite);

  for (i = 0; i < limite; i++)
  {
    printf("%d ", h.dados[i]);
  }

  printf("\n\n");
  dado2 = 101;
  pop_push_heap(&h, &dado, &dado2);
  heap_tipo(&h, &tipo);
  limite = tamanho_heap(&h);
  printf("Tirou %d, colocou %d e ficou uma heap tipo %d com %u elementos\n",
         dado, dado2, tipo, limite);

  for (i = 0; i < limite; i++)
  {
    printf("%d ", h.dados[i]);
  }

  printf("\n\n");
  dado = 120;
  printf("Adicionando %d aa heap... ", dado);

  if (push_heap(&h, &dado))
  {
    printf("Sucesso\n");
  }
  else
  {
    printf("Fracasso\n");
  }

  heap_tipo(&h, &tipo);
  limite = tamanho_heap(&h);

  for (i = 0; i < limite; i++)
  {
    printf("%d ", h.dados[i]);
  }

  printf("\n\n");
  dado = 0;
  printf("Adicionando %d aa heap... ", dado);

  if (push_heap(&h, &dado))
  {
    printf("Sucesso\n");
  }
  else
  {
    printf("Fracasso\n");
  }

  heap_tipo(&h, &tipo);
  limite = tamanho_heap(&h);

  for (i = 0; i < limite; i++)
  {
    printf("%d ", h.dados[i]);
  }

  printf("\n\n");
  dado = 110;
  printf("Adicionando %d aa heap... ", dado);

  if (push_heap(&h, &dado))
  {
    printf("Sucesso\n");
  }
  else
  {
    printf("Fracasso\n");
  }

  heap_tipo(&h, &tipo);
  limite = tamanho_heap(&h);

  for (i = 0; i < limite; i++)
  {
    printf("%d ", h.dados[i]);
  }

  printf("\n\n");

  do
  {
    dado = rand() % 100;
    printf("Tentando remover %d...\n", dado);
  } while (!remove_chave_heap(&h, &dado));

  printf("Removido %d\n", dado);
  dump_heap(&h);
  limite = tamanho_heap(&h);

  for (i = 0; i < limite; i++)
  {
    printf("%d ", h.dados[i]);
  }

  printf("\n\n");
  printf("Tirando os valores na ordem da heap\n");

  do
  {
    pop_heap(&h, &dado);
    printf("%d ", dado);
    limite = tamanho_heap(&h);
  } while (limite > 0);

  printf("\n\n");
  printf("Destruindo heap\n");
  destroi_heap(&h);
  return 0;
}
