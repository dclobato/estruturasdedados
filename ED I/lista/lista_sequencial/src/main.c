#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <lista_seq.h>

int main()
{
  LISTA l;
  int i;
  TIPO_DADO v;
  srand(time(NULL));

  if (!lista_inicializar(&l))
  {
    return 1;
  }

  printf("A lista tem %d itens armazenados, e %d posicoes estao livres\n", lista_numero_de_elementos(&l),
         lista_numero_de_nos_livres(&l));

  if (lista_esta_vazia(&l))
  {
    printf("Lista esta vazia\n");
  }
  else
  {
    printf("Lista nao esta vazia\n");
  }

  for (i = 0; i < TAM_LISTA + 2; i++)
  {
    v = (TIPO_DADO) (rand() % 1000);

    if (lista_inserir_chave_ordenado(&l, &v))
    {
      printf("Inserido ordenado\n");
      lista_imprimir(&l);
    }
    else
    {
      printf("Lista cheia\n");
    }
  }

  lista_imprimir(&l);
  printf("Removendo o inicio... ");

  if (lista_remover_inicio(&l, &v))
  {
    printf("valia %d\n", v);
  }
  else
  {
    printf("Nao deu certo!\n");
  }

  lista_imprimir(&l);
  printf("Removendo o final... ");

  if (lista_remover_final(&l, &v))
  {
    printf("valia %d\n", v);
  }
  else
  {
    printf("Nao deu certo!\n");
  }

  lista_imprimir(&l);
  printf("Removendo da posicao 3... ");

  if (lista_remover_posicao(&l, &v, 3))
  {
    printf("valia %d\n", v);
  }
  else
  {
    printf("Nao deu certo!\n");
  }

  lista_imprimir(&l);
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

  lista_imprimir(&l);
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

  lista_imprimir(&l);
  printf("Inserindo '777' na posicao 1... ");
  v = 777;

  if (lista_inserir_chave_posicao(&l, &v, 1))
  {
    printf("Foi\n");
  }
  else
  {
    printf("Nao deu certo!\n");
  }

  lista_imprimir(&l);
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

  lista_imprimir(&l);
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

  lista_imprimir(&l);
  printf("Quem esta na posicao 5?  ");

  if (lista_obter_chave_posicao(&l, &v, 5))
  {
    printf("%d\n", v);
  }
  else
  {
    printf("Nao existe!\n");
  }

  v = v + 1;
  printf("Somando 1 na posicao 5  ");
  if (lista_definir_chave_posicao(&l, &v, 5))
  {
    printf("Feito");
  }

  if (lista_obter_posicao_chave(&l, &v, &i))
    printf("Encontramos %d na posicao %u\n", v, i);

  v = 919191;
  if (lista_obter_posicao_chave(&l, &v, &i))
    printf("Encontramos %d na posicao %u\n", v, i);
  else
    printf("Nao encontramos %d\n", v);


  if (lista_obter_chave_inicio(&l, &v))
    printf("Inicio da lista: %d\n", v);

  if (lista_obter_chave_final(&l, &v))
    printf("Final da lista: %d\n", v);

  lista_imprimir(&l);

  if (lista_esta_cheia(&l))
  {
    printf("Lista esta cheia\n");
  }
  else
  {
    printf("Lista nao esta cheia\n");
  }

  lista_imprimir(&l);
  printf("Destruindo a lista\n");
  lista_destruir(&l);
  printf("Situacao final\n");
  lista_imprimir(&l);
  return 0;
}
