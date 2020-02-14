#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <arvorebinaria.h>

int main()
{
  ARVORE tree, temp, anterior;
  PERCURSO p1, p2, p3, p4;
  int v, i;
  const int NUM_NOS = 15;
  srand(time(NULL));

  if (!arvore_binaria_inicializar(&tree))
  {
    printf("Erro na inicializacao\n");
    exit(1);
  }

  for (i = 0; i < NUM_NOS; i++)
  {
    v = (TIPO_DADO) rand() % 1000;

    if (!arvore_binaria_busca_inserir_chave(&tree, &v))
    {
      printf("Problema na insercao\n");
    }
    else
    {
      printf("Inserido %d\n", v);
    }
  }

  if (!arvore_binaria_busca_inserir_chave(&tree, &v))
  {
    printf("Bloqueou insercao de duplicado\n");
  }
  else
  {
    printf("Inseriu %d duplicado\n", v);
  }

  v = 1;

  if (!arvore_binaria_busca_inserir_chave(&tree, &v))
  {
    printf("Problema na insercao de %d\n", v);
  }
  else
  {
    printf("Inseriu %d\n", v);
  }

  v = 1000;

  if (!arvore_binaria_busca_inserir_chave(&tree, &v))
  {
    printf("Problema na insercao de %d\n", v);
  }
  else
  {
    printf("Inseriu %d\n", v);
  }

  arvore_binaria_imprimir(&tree);
  printf("Altura da arvore: %u\n", arvore_binaria_altura(&tree));
  printf("Numero de nodos: %u\n", arvore_binaria_numero_nodos(&tree));
  if (!arvore_binaria_sucessor_in_ordem(&tree, &temp, &anterior))
  {
    printf("Nao ha sucessor in-ordem da raiz");
  }
  else
  {
    printf("Sucessor in-ordem da raiz: %d\n", temp->dado);
  }

  do
  {
    v = (TIPO_DADO) rand() % 1000;
  } while (!arvore_binaria_busca_pesquisar_chave(&tree, &v, &temp));

  printf("Achou %u!\n", v);
  printf("Nivel do nodo %u --> %u\n", v, arvore_binaria_nivel_nodo(&tree, &v));
  v = 9999;
  printf("Nivel do nodo %u --> %u\n", v, arvore_binaria_nivel_nodo(&tree, &v));

  if (arvore_binaria_percorrer(&tree, POS, &p3))
  {
    printf("Pos ordem\n");

    for (i = 0; i < p3.tamanho; ++i)
    {
      printf("%d ", p3.nodos[i]);
    }

    printf("\n");
  }

  if (arvore_binaria_percorrer(&tree, PRE, &p1))
  {
    printf("Pre ordem\n");

    for (i = 0; i < p1.tamanho; ++i)
    {
      printf("%d ", p1.nodos[i]);
    }

    printf("\n");
  }

  if (arvore_binaria_percorrer(&tree, IN, &p2))
  {
    printf("In ordem\n");

    for (i = 0; i < p2.tamanho; ++i)
    {
      printf("%d ", p2.nodos[i]);
    }

    printf("\n");
  }

  if (arvore_binaria_percorrer(&tree, LARGURA, &p4))
  {
    printf("Largura\n");

    for (i = 0; i < p4.tamanho; ++i)
    {
      printf("%d ", p4.nodos[i]);
    }

    printf("\n");
  }

  printf("Removendo chaves\n");
  i = 0;
  while (i < NUM_NOS / 2)
  {
    v = (TIPO_DADO) rand() % 1000;
    if (arvore_binaria_busca_remover_chave(&tree, &v))
    {
      printf("Removido %d\n", v);
      arvore_binaria_imprimir(&tree);
      i++;
    }
  }

  printf("Destruindo arvore\n");

  if (!arvore_binaria_destruir(&tree))
  {
    printf("Nao pode destruir a arvore\n");
  }

  arvore_binaria_destruir_percurso(&p1);
  arvore_binaria_destruir_percurso(&p2);
  arvore_binaria_destruir_percurso(&p3);
  arvore_binaria_destruir_percurso(&p4);
  arvore_binaria_imprimir(&tree);
  return 0;
}
