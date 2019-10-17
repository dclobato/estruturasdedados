#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <lista_ed.h>

int
main()
{
  LISTA l;
  unsigned int i;
  NOH *p, *q;
  TIPO_DADO v;
  srand(time(NULL));
  const unsigned int TAM_LISTA = 9;

  if (!lista_inicializa(&l))
  {
    return 1;
  }

  for (i = 0 ; i < TAM_LISTA; i++)
  {
    v = (TIPO_DADO)(rand() % 1000);

    if (!lista_insere_ordenado(&l, &v))
    {
      printf("Lista cheia\n");
    }
    else
    {
      printf("Inserido ordenado\n");
    }
  }

  lista_imprime(&l);
  printf("Removendo o inicio... ");

  if (lista_remove_inicio(&l, &v))
  {
    printf("valia %d\n", v);
  }
  else
  {
    printf("Nao deu certo!\n");
  }

  lista_imprime(&l);
  printf("Removendo o final... ");

  if (lista_remove_final(&l, &v))
  {
    printf("valia %d\n", v);
  }
  else
  {
    printf("Nao deu certo!\n");
  }

  lista_imprime(&l);
  printf("Removendo da posicao 3... ");

  if (lista_remove_posicao(&l, &v, 3))
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

  if (lista_insere_final(&l, &v))
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

  if (lista_insere_inicio(&l, &v))
  {
    printf("Foi\n");
  }
  else
  {
    printf("Nao deu certo!\n");
  }

  lista_imprime(&l);
  printf("Inserindo '777' na posicao 1... ");
  v = 777;

  if (lista_insere(&l, &v, 1))
  {
    printf("Foi\n");
  }
  else
  {
    printf("Nao deu certo!\n");
  }

  lista_imprime(&l);
  printf("Removendo chave '777'... ");
  v = 777;

  if (lista_remove_chave(&l, &v))
  {
    printf("Foi\n");
  }
  else
  {
    printf("Nao existe!\n");
  }

  lista_imprime(&l);
  printf("Removendo chave '999'... ");
  v = 999;

  if (lista_remove_chave(&l, &v))
  {
    printf("Foi\n");
  }
  else
  {
    printf("Nao existe!\n");
  }

  lista_imprime(&l);
  printf("Removendo chave '111'... ");
  v = 111;

  if (lista_remove_chave(&l, &v))
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

  if (lista_remove_chave(&l, &v))
  {
    printf("Foi\n");
  }
  else
  {
    printf("Nao existe!\n");
  }

  lista_imprime(&l);
  printf("Quem esta na posicao 5?  ");

  if (lista_consulta_posicao(&l, 5, &v))
  {
    printf("%d\n", v);
  }
  else
  {
    printf("Nao existe!\n");
  }

  lista_imprime(&l);
  printf("Indo para o inicio da lista... ");

  if (!lista_obtem_inicio(&l, &p))
  {
    printf("Lista nao tem inicio\n");
  }
  else
  {
    if (lista_obtem_sucessor(p, &q))
    {
      printf("Sucessor de %d eh %d\n", p->dado, q->dado);
    }
    else
    {
      printf("%d nao tem sucessor\n", p->dado);
    }
  }

  printf("Indo para o final da lista... ");

  if (!lista_obtem_final(&l, &p))
  {
    printf("Lista nao tem final\n");
  }
  else
  {
    if (lista_obtem_sucessor(p, &q))
    {
      printf("Sucessor de %d eh %d\n", p->dado, q->dado);
    }
    else
    {
      printf("%d nao tem sucessor\n", p->dado);
    }
  }

  lista_consulta_posicao(&l, 3, &v);
  lista_busca_chave(&l, &v, &p);

  if (lista_obtem_sucessor(p, &q))
  {
    printf("Sucessor de %d eh %d\n", p->dado, q->dado);
  }
  else
  {
    printf("%d nao tem sucessor\n", p->dado);
  }

  v = 1000;

  if (!lista_insere_antes_do_nodo(&l, (const NOH **) &p, &v))
  {
    printf("Problemas para inserir antes de %d\n", p->dado);
  }
  else
  {
    printf("Inserindo %d antes de %d\n", v, p->dado);
  }

  __lista_imprime(&l);
  printf("Removendo o nodo com %d... ", p->dado);

  if (lista_remove_nodo(&l, &p))
  {
    printf("Deu certo!\n");
  }
  else
  {
    printf("Problemas para remover\n");
  }

  __lista_imprime(&l);
  printf("Destruindo a lista\n");
  lista_destroi(&l);
  printf("Situacao final\n");
  lista_imprime(&l);
  return 0;
}
