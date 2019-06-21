#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <lista_seq.h>

int
main()
{
  LISTA l;
  int i;
  TIPO_DADO v;
  srand(time(NULL));

  if (!inicializa_lista(&l))
  {
    return 1;
  }

  printf("A lista tem %d itens armazenados, e %d posicoes estao livres\n",
         tamanho_lista(&l), livres_lista(&l));

  for (i = 0 ; i < TAM_LISTA + 2; i++)
  {
    v = (TIPO_DADO)(rand() % 1000);

    if (!insere_ordenado(&l, &v))
    {
      printf("Lista cheia\n");
    }
    else
    {
      printf("Inserido ordenado\n");
    }
  }

  imprime_lista(&l);
  printf("Removendo o inicio... ");

  if (remove_inicio(&l, &v))
  {
    printf("valia %d\n", v);
  }
  else
  {
    printf("Nao deu certo!\n");
  }

  imprime_lista(&l);
  printf("Removendo o final... ");

  if (remove_final(&l, &v))
  {
    printf("valia %d\n", v);
  }
  else
  {
    printf("Nao deu certo!\n");
  }

  imprime_lista(&l);
  printf("Removendo da posicao 3... ");

  if (remove_lista(&l, &v, 3))
  {
    printf("valia %d\n", v);
  }
  else
  {
    printf("Nao deu certo!\n");
  }

  imprime_lista(&l);
  printf("Inserindo '111' no final... ");
  v = 111;

  if (insere_final(&l, &v))
  {
    printf("Foi\n");
  }
  else
  {
    printf("Nao deu certo!\n");
  }

  imprime_lista(&l);
  printf("Inserindo '999' no inicio... ");
  v = 999;

  if (insere_inicio(&l, &v))
  {
    printf("Foi\n");
  }
  else
  {
    printf("Nao deu certo!\n");
  }

  imprime_lista(&l);
  printf("Inserindo '777' na posicao 1... ");
  v = 777;

  if (insere_lista(&l, &v, 1))
  {
    printf("Foi\n");
  }
  else
  {
    printf("Nao deu certo!\n");
  }

  imprime_lista(&l);
  printf("Removendo chave '777'... ");
  v = 777;

  if (remove_chave(&l, &v))
  {
    printf("Foi\n");
  }
  else
  {
    printf("Nao existe!\n");
  }

  imprime_lista(&l);
  printf("Removendo chave '-1'... ");
  v = -1;

  if (remove_chave(&l, &v))
  {
    printf("Foi\n");
  }
  else
  {
    printf("Nao existe!\n");
  }

  imprime_lista(&l);
  printf("Quem esta na posicao 5?  ");

  if (consulta_lista(&l, 5, &v))
  {
    printf("%d\n", v);
  }
  else
  {
    printf("Nao existe!\n");
  }

  imprime_lista(&l);
  printf("Destruindo a lista\n");
  destroi_lista(&l);
  printf("Situacao final\n");
  imprime_lista(&l);
  return 0;
}
