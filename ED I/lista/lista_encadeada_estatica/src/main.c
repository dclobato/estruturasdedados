#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <lista_ee.h>

int main()
{
  LISTA l;
  unsigned int i;
  TIPO_DADO v;
  srand(time(NULL));

  if (!lista_inicializar(&l))
  {
    return 1;
  }

  if (lista_esta_vazia(&l))
  {
    printf("Lista esta vazia\n");
  }
  else
  {
    printf("Lista nao esta vazia\n");
  }
  __lista_imprime(&l);
  for (i = 0; i < TAM_LISTA + 2; i++)
  {
    v = (TIPO_DADO) (rand() % 1000);

    if (!lista_inserir_chave_ordenado(&l, &v))
    {
      printf("Lista cheia\n");
    }
    else
    {
      printf("Inserido ordenado\n");
    }
  }

  __lista_imprime(&l);
  printf("Removendo o inicio... ");

  if (lista_remover_inicio(&l, &v))
  {
    printf("valia %d\n", v);
  }
  else
  {
    printf("Nao deu certo!\n");
  }

  lista_imprime(&l);
  printf("Removendo o final... ");

  if (lista_remover_final(&l, &v))
  {
    printf("valia %d\n", v);
  }
  else
  {
    printf("Nao deu certo!\n");
  }

  lista_imprime(&l);
  printf("Removendo da posicao 3... ");

  if (lista_remover_posicao(&l, &v, 3))
  {
    printf("valia %d\n", v);
  }
  else
  {
    printf("Nao deu certo!\n");
  }

  lista_imprime(&l);
  printf("Inserindo '111' no final... ");
  v = 111;

  if (lista_inserir_chave_final(&l, &v))
  {
    printf("Foi\n");
  }
  else
  {
    printf("Nao deu certo!\n");
  }

  lista_imprime(&l);
  printf("Inserindo '999' no inicio... ");
  v = 999;

  if (lista_inserir_chave_inicio(&l, &v))
  {
    printf("Foi\n");
  }
  else
  {
    printf("Nao deu certo!\n");
  }

  lista_imprime(&l);
  printf("Inserindo '777' na posicao 3... ");
  v = 777;

  if (lista_inserir_chave_posicao(&l, &v, 3))
  {
    printf("Foi\n");
  }
  else
  {
    printf("Nao deu certo!\n");
  }

  if (lista_obter_posicao_chave(&l, &v, &i))
  {
    printf("O valor %d esta na posicao %lu\n", v, i);
  }
  else
  {
    printf("O valor &d nao existe\n, v");
  }

  lista_imprime(&l);
  printf("Removendo chave '777'... ");
  v = 777;

  if (lista_remover_chave(&l, &v))
  {
    printf("Foi\n");
  }
  else
  {
    printf("Nao existe!\n");
  }

  lista_imprime(&l);
  printf("Removendo chave '-1'... ");
  v = -1;

  if (lista_remover_chave(&l, &v))
  {
    printf("Foi\n");
  }
  else
  {
    printf("Nao existe!\n");
  }

  printf("Colocando 1001 na posicao 4...");
  v = 1001;
  if (lista_definir_chave_posicao(&l, &v, 4))
  {
    printf("Foi\n");
  }
  else
  {
    printf("Nao foi\n");
  }

  lista_imprime(&l);
  printf("Quem esta na posicao 5?  ");

  if (lista_obter_chave_posicao(&l, &v, 5))
  {
    printf("%d\n", v);
  }
  else
  {
    printf("Nao existe!\n");
  }

  printf("Somando 1 na posicao 5");
  v = v+1;
  if (lista_definir_chave_posicao(&l, &v, 5))
    printf("Feito");

  lista_imprime(&l);

  if (lista_esta_cheia(&l))
  {
    printf("Lista esta cheia\n");
  }
  else
  {
    printf("Lista nao esta cheia\n");
  }

  if (lista_obter_chave_inicio(&l, &v))
  {
    printf("O inicio da lista vale %d\n", v);
  }

  if (lista_obter_chave_final(&l, &v))
  {
    printf("O final da lista vale %d\n", v);
  }

  lista_imprime(&l);
  printf("Destruindo a lista\n");
  printf("\n\n");
  lista_destruir(&l);
  printf("Situacao final\n");
  lista_imprime(&l);
  return 0;
}
