#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <lista_ed.h>

int main()
{
  LISTA l;
  unsigned int i;
  NOH_LISTA *p, *q;
  TIPO_DADO v, r;
  srand(time(NULL));
  const unsigned int TAM_LISTA = 9;

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


  for (i = 0; i < TAM_LISTA; i++)
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
  printf("Removendo chave '999'... ");
  v = 999;

  if (lista_remover_chave(&l, &v))
  {
    printf("Foi\n");
  }
  else
  {
    printf("Nao existe!\n");
  }

  lista_imprimir(&l);
  printf("Removendo chave '111'... ");
  v = 111;

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


  if (lista_obter_no_posicao(&l, &p, 5))
  {
    lista_obter_chave_no(p, &v);
    printf("%d\n", v);
  }
  else
  {
    printf("Nao existe!\n");
  }

  lista_imprimir(&l);
  printf("Indo para o inicio da lista... ");

  if (!lista_obter_no_inicio(&l, &p))
  {
    printf("Lista nao tem inicio\n");
  }
  else
  {
    if (lista_obter_sucessor_de_no(p, &q))
    {
      printf("Sucessor de %d eh %d\n", p->dado, q->dado);
    }
    else
    {
      printf("%d nao tem sucessor\n", p->dado);
    }
  }

  printf("Indo para o final da lista... ");

  if (!lista_obter_no_final(&l, &p))
  {
    printf("Lista nao tem final\n");
  }
  else
  {
    if (lista_obter_sucessor_de_no(p, &q))
    {
      printf("Sucessor de %d eh %d\n", p->dado, q->dado);
    }
    else
    {
      printf("%d nao tem sucessor\n", p->dado);
    }
  }

  lista_obter_no_posicao(&l, &p, 3);
  lista_obter_chave_no(p, &v);
  lista_obter_no_chave(&l, &v, &p);

  if (lista_obter_sucessor_de_no(p, &q))
  {
    lista_obter_chave_no(p, &v);
    lista_obter_chave_no(q, &r);
    printf("Sucessor de %d eh %d\n", v, r);
  }
  else
  {
    printf("%d nao tem sucessor\n", p->dado);
  }

  printf("Mudando o valor do sucesso de %d para %d\n", v, r+1);
  r++;
  lista_definir_chave_no(q, &r);

  v = 1000;

  if (!lista_inserir_chave_antes_no(&l, &v, (const NOH_LISTA **) &p))
  {
    printf("Problemas para inserir antes de %d\n", p->dado);
  }
  else
  {
    printf("Inserindo %d antes de %d\n", v, p->dado);
  }

  __lista_imprimir(&l);
  printf("Removendo o nodo com %d... ", p->dado);

  if (lista_remover_nodo(&l, &p))
  {
    printf("Deu certo!\n");
  }
  else
  {
    printf("Problemas para remover\n");
  }

  if (lista_esta_cheia(&l))
  {
    printf("Lista esta cheia\n");
  }
  else
  {
    printf("Lista nao esta cheia\n");
  }

  __lista_imprimir(&l);
  printf("Destruindo a lista\n");
  lista_destruir(&l);
  printf("Situacao final\n");
  lista_imprimir(&l);
  return 0;
}
