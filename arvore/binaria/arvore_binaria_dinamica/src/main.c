#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <arvorebinaria.h>

int main()
{
  ARVORE tree, temp;
  PERCURSO p1, p2, p3, p4;
  int v, i;
  const int NUM_NOS = 10;
  srand(time(NULL));

  if (!inicializa_arvore(&tree))
  {
    printf("Erro na inicializacao\n");
    exit(1);
  }

  for (i = 0 ; i < NUM_NOS ; i++)
  {
    v = (TIPO_DADO) rand() % 1000;

    if (!insere_arvore_binaria_busca(&tree, &v))
    {
      printf("Problema na insercao\n");
    }
    else
    {
      printf("Inserido %d\n", v);
    }
  }

  if (!insere_arvore_binaria_busca(&tree, &v))
  {
    printf("Bloqueou insercao de duplicado\n");
  }
  else
  {
    printf("Inseriu %d duplicado\n", v);
  }

  v = 1;

  if (!insere_arvore_binaria_busca(&tree, &v))
  {
    printf("Problema na insercao de %d\n", v);
  }
  else
  {
    printf("Inseriu %d\n", v);
  }

  v = 1000;

  if (!insere_arvore_binaria_busca(&tree, &v))
  {
    printf("Problema na insercao de %d\n", v);
  }
  else
  {
    printf("Inseriu %d\n", v);
  }

  imprime_arvore(&tree);
  printf("Altura da arvore: %u\n", altura_da_arvore(&tree));
  printf("Numero de nodos: %u\n", numero_de_nodos(&tree));

  do
  {
    v = (TIPO_DADO) rand() % 1000;
  } while (!pesquisa_abb(&tree, &v, &temp));

  printf("Achou %u!\n", v);
  printf("Nivel do nodo %u --> %u\n", v, nivel_do_nodo(&tree, &v));
  v = 9999;
  printf("Nivel do nodo %u --> %u\n", v, nivel_do_nodo(&tree, &v));

  if (percurso(&tree, PRE, &p1))
  {
    printf("Pre ordem\n");

    for (int i = 0; i < p1.tamanho; ++i)
    {
      printf("%d ", p1.nodos[i]);
    }

    printf("\n");
  }

  if (percurso(&tree, IN, &p2))
  {
    printf("In ordem\n");

    for (int i = 0; i < p2.tamanho; ++i)
    {
      printf("%d ", p2.nodos[i]);
    }

    printf("\n");
  }

  if (percurso(&tree, POS, &p3))
  {
    printf("Pos ordem\n");

    for (int i = 0; i < p3.tamanho; ++i)
    {
      printf("%d ", p3.nodos[i]);
    }

    printf("\n");
  }

  if (percurso(&tree, LARGURA, &p4))
  {
    printf("Largura\n");

    for (int i = 0; i < p4.tamanho; ++i)
    {
      printf("%d ", p4.nodos[i]);
    }

    printf("\n");
  }

  printf("Destruindo arvore\n");

  if (!destroi_arvore(&tree))
  {
    printf("Nao pode destruir a arvore\n");
  }

  destroi_percurso(&p1);
  destroi_percurso(&p2);
  destroi_percurso(&p3);
  destroi_percurso(&p4);
  imprime_arvore(&tree);
  return 0;
}
