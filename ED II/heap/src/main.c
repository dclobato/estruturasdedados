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
  HEAP h, p;
  limite = 10;
  srand((unsigned)time(NULL));
  heap_inicializa(&h, limite + 1, MIN_HEAP);
  heap_inicializa(&p, limite + 1, MIN_HEAP);
  printf("Dados originais\n");

  for (i = 0; i < limite; i++)
  {
    valores[i] = rand() % 100;
    printf("%d ", valores[i]);
    heap_push(&p, &valores[i]);
  }

  printf("\n\n");
  heap_constroi(&h, valores, limite);
  tipo_heap(&h, &tipo);
  limite = heap_tamanho(&h);
  printf("Heap tipo %d com %u elementos\n", tipo, limite);

  for (i = 0; i < limite; i++)
  {
    printf("%d ", h.dados[i]);
  }

  printf("\n");

  for (i = 0; i < limite; i++)
  {
    printf("%d ", p.dados[i]);
  }

  heap_destroi(&p);

  printf("\n\n");
  printf("Invertendo heap...\n");
  heap_inverte(&h);
  tipo_heap(&h, &tipo);
  limite = heap_tamanho(&h);
  printf("Heap tipo %d com %u elementos\n", tipo, limite);

  for (i = 0; i < limite; i++)
  {
    printf("%d ", h.dados[i]);
  }

  printf("\n\n");
  heap_peek(&h, &dado);
  printf("Topo da heap: %d\n", dado);
  printf("\n");
  printf("Tirando o topo da heap... ");
  heap_pop(&h, &dado);
  printf("Topo da heap: %d\n", dado);
  printf("\n");
  tipo_heap(&h, &tipo);
  limite = heap_tamanho(&h);
  printf("Heap tipo %d com %u elementos\n", tipo, limite);

  for (i = 0; i < limite; i++)
  {
    printf("%d ", h.dados[i]);
  }

  printf("\n\n");
  dado2 = 101;
  heap_pop_push(&h, &dado, &dado2);
  tipo_heap(&h, &tipo);
  limite = heap_tamanho(&h);
  printf("Tirou %d, colocou %d e ficou uma heap tipo %d com %u elementos\n",
         dado, dado2, tipo, limite);

  for (i = 0; i < limite; i++)
  {
    printf("%d ", h.dados[i]);
  }

  printf("\n\n");
  dado = 120;
  printf("Adicionando %d aa heap... ", dado);

  if (heap_push(&h, &dado))
  {
    printf("Sucesso\n");
  }
  else
  {
    printf("Fracasso\n");
  }

  tipo_heap(&h, &tipo);
  limite = heap_tamanho(&h);

  for (i = 0; i < limite; i++)
  {
    printf("%d ", h.dados[i]);
  }

  printf("\n\n");
  dado = 0;
  printf("Adicionando %d aa heap... ", dado);

  if (heap_push(&h, &dado))
  {
    printf("Sucesso\n");
  }
  else
  {
    printf("Fracasso\n");
  }

  tipo_heap(&h, &tipo);
  limite = heap_tamanho(&h);

  for (i = 0; i < limite; i++)
  {
    printf("%d ", h.dados[i]);
  }

  printf("\n\n");
  dado = 110;
  printf("Adicionando %d aa heap... ", dado);

  if (heap_push(&h, &dado))
  {
    printf("Sucesso\n");
  }
  else
  {
    printf("Fracasso\n");
  }

  tipo_heap(&h, &tipo);
  limite = heap_tamanho(&h);

  for (i = 0; i < limite; i++)
  {
    printf("%d ", h.dados[i]);
  }

  printf("\n\n");

  do
  {
    dado = rand() % 100;
    printf("Tentando remover %d...\n", dado);
  } while (!heap_remove_chave(&h, &dado));

  printf("Removido %d\n", dado);
  __heap_dump(&h);
  limite = heap_tamanho(&h);

  for (i = 0; i < limite; i++)
  {
    printf("%d ", h.dados[i]);
  }

  printf("\n\n");
  printf("Tirando os valores na ordem da heap\n");

  do
  {
    heap_pop(&h, &dado);
    printf("%d ", dado);
  } while (!heap_vazia(&h));

  printf("\n\n");
  printf("Destruindo heap\n");
  heap_destroi(&h);
  return 0;
}
