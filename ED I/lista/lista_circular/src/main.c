#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <lista_circ.h>

int main()
{
  LISTA_CIRCULAR l;
  NOH_CIRCULAR *nodo, *nodo2;
  unsigned int i;
  TIPO_DADO v;

  srand(time(NULL));
  const unsigned int TAM_LISTA = 2;

  if (!lista_circular_inicializar(&l))
  {
    return 1;
  }

  for (i = 0; i < TAM_LISTA; i++)
  {
    v = (TIPO_DADO) (rand() % 1000);
    printf("Tentando %d ordenado... ", v);
    if (lista_circular_inserir_chave_ordenado(&l, &v))
    {
      printf("Inserido %d\n", v);
      lista_circular_imprimir(&l);
    }
    else
    {
      printf("Problema na insercao\n");
    }
  }

  for (i = 0; i < TAM_LISTA; i++)
  {
    v = (TIPO_DADO) (rand() % 1000);
    printf("Tentando %d na posicao %d... ", v, i);
    if (lista_circular_inserir_chave_posicao(&l, &v, i))
    {
      printf("Inserido %d\n", v);
      lista_circular_imprimir(&l);
    }
    else
    {
      printf("Problema na insercao\n");
    }
  }

  printf("Inserindo no inicio\n");
  v = 11111;
  if (!lista_circular_inserir_chave_inicio(&l, &v))
  {
    printf("Problema na insercao\n");
  }

  printf("Inserindo no meio\n");
  v = 22222;
  if (!lista_circular_inserir_chave_posicao(&l, &v, lista_circular_numero_de_elementos(&l) / 2))
  {
    printf("Problema na insercao\n");
  }

  printf("Inserindo no final\n");
  v = 33333;
  if (!lista_circular_inserir_chave_final(&l, &v))
  {
    printf("Problema na insercao\n");
  }

  printf("--------------\n");
  __lista_circular_imprimir(&l);
  printf("--------------\n");

  printf("Mudando valor do inicio\n");
  v = 77777;
  if (!lista_circular_definir_chave_posicao(&l, &v, 0))
  {
    printf("Problema na alteracao\n");
  }

  printf("Mudando valor do meio\n");
  v = 88888;
  if (!lista_circular_definir_chave_posicao(&l, &v, lista_circular_numero_de_elementos(&l) / 2))
  {
    printf("Problema na alteracao\n");
  }

  printf("Mudando valor do final\n");
  v = 99999;
  if (!lista_circular_definir_chave_posicao(&l, &v, lista_circular_numero_de_elementos(&l) - 1))
  {
    printf("Problema na alteracao\n");
  }

  printf("--------------\n");
  __lista_circular_imprimir(&l);
  printf("--------------\n");

  printf("Obtendo o no no inicio... ");
  if (lista_circular_obter_no_inicio(&l, &nodo))
  {
    printf("%p\n", nodo);
  }

  printf("Obtendo o no na posicao 5... ");
  if (lista_circular_obter_no_posicao(&l, &nodo, 5))
  {
    printf("%p\n", nodo);
  }

  printf("Obtendo o no no final... ");
  if (lista_circular_obter_no_final(&l, &nodo))
  {
    printf("%p\n", nodo);
  }

  printf("Obtendo o no com chave 88888... ");
  v = 88888;
  if (lista_circular_obter_no_chave(&l, &v, &nodo))
  {
    printf("%p\n", nodo);
  }

  printf("Obtendo o sucessor de %p... ", nodo);
  if (lista_circular_obter_sucessor_de_no(nodo, &nodo2))
  {
    printf("%p\n", nodo2);
  }
  else
  {
    printf("Nao temos\n");
  }


  printf("Mudando a chave de 88888 para 55555... ");
  v = 55555;
  if (lista_circular_definir_chave_no(nodo, &v))
  {
    printf("Feito\n");
  }

  printf("Obtendo a chave no inicio... ");
  if (lista_circular_obter_chave_inicio(&l, &v))
  {
    printf("%d\n", v);
  }

  printf("Obtendo a chave na posicao 5... ");
  if (lista_circular_obter_chave_posicao(&l, &v, 5))
  {
    printf("%d\n", v);
  }

  printf("Obtendo o no no final... ");
  if (lista_circular_obter_chave_final(&l, &v))
  {
    printf("%d\n", v);
  }

  v = 55555;
  printf("Obtendo posicao da chave %d... ", v);
  if (lista_circular_obter_posicao_chave(&l, &v, &i))
  {
    printf("%d\n", i);
  }
  else
  {
    printf("Nao existe");
  }

  v = 12345;
  printf("Obtendo posicao da chave %d... ", v);
  if (lista_circular_obter_posicao_chave(&l, &v, &i))
  {
    printf("%d\n", i);
  }
  else
  {
    printf("Nao existe\n");
  }

  if (lista_circular_shift_left(&l))
  {
    printf("Shift left\n");
    printf("--------------\n");
    __lista_circular_imprimir(&l);
    printf("--------------\n");
  }
  if (lista_circular_shift_right(&l))
  {
    printf("Shift right\n");
    printf("--------------\n");
    __lista_circular_imprimir(&l);
    printf("--------------\n");
  }

  printf("Removendo posicao 3... ");
  if (lista_circular_remover_posicao(&l, &v, 3))
  {
    printf("%d\n", v);
  }
  else
  {
    printf("Erro\n");
  }
  printf("--------------\n");
  __lista_circular_imprimir(&l);
  printf("--------------\n");

  printf("Removendo posicao final... ");
  if (lista_circular_remover_final(&l, &v))
  {
    printf("%d\n", v);
  }
  else
  {
    printf("Erro\n");
  }
  printf("--------------\n");
  __lista_circular_imprimir(&l);
  printf("--------------\n");

  printf("Removendo posicao inicial... ");
  if (lista_circular_remover_inicio(&l, &v))
  {
    printf("%d\n", v);
  }
  else
  {
    printf("Erro\n");
  }

  printf("--------------\n");
  __lista_circular_imprimir(&l);
  printf("--------------\n");

  v = 9876543;
  printf("Removendo chave %d... ", v);
  if (lista_circular_remover_chave(&l, &v))
  {
    printf("Feito\n");
  }
  else
  {
    printf("Nao existe\n");
  }
  printf("--------------\n");
  __lista_circular_imprimir(&l);
  printf("--------------\n");

  lista_circular_obter_chave_final(&l, &v);
  printf("Removendo chave %d... ", v);
  if (lista_circular_remover_chave(&l, &v))
  {
    printf("Feito\n");
  }
  else
  {
    printf("Nao existe\n");
  }
  printf("--------------\n");
  __lista_circular_imprimir(&l);
  printf("--------------\n");

  lista_circular_obter_chave_inicio(&l, &v);
    printf("Removendo chave %d... ", v);
    if (lista_circular_remover_chave(&l, &v))
    {
      printf("Feito\n");
    }
    else
    {
      printf("Nao existe\n");
    }
    printf("--------------\n");
    __lista_circular_imprimir(&l);
    printf("--------------\n");

  printf("--------------\n");
  __lista_circular_imprimir(&l);
  printf("--------------\n");

  printf("Destruindo a lista... ");
  if (lista_circular_destruir(&l))
  {
    printf("Feito\n");
  }
  else
  {
    printf("Erro\n");
  }

  printf("--------------\n");
  __lista_circular_imprimir(&l);
  printf("--------------\n");

  return 0;
}