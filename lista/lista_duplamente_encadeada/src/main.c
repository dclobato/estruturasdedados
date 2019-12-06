#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <lista_ded.h>

int main()
{
  LISTA_DE l;
  NOH_DE *p, *q;
  unsigned int i;
  TIPO_DADO v, r;
  srand(time(NULL));
  const unsigned int TAM_LISTA = 9;

  if (!inicializa_lista_de(&l))
  {
    return 1;
  }

  for (i = 0; i < TAM_LISTA; i++)
  {
    v = (TIPO_DADO) (rand() % 1000);

    if (!insere_ordenado_de(&l, &v))
    {
      printf("Lista cheia\n");
    }
    else
    {
      printf("Inserido ordenado\n");
    }
  }

  __imprime_lista_de(&l);
  printf("Removendo o inicio... ");

  if (remove_inicio_de(&l, &v))
  {
    printf("valia %d\n", v);
  }
  else
  {
    printf("Nao deu certo!\n");
  }

  __imprime_lista_de(&l);
  printf("Removendo o final... ");

  if (remove_final_de(&l, &v))
  {
    printf("valia %d\n", v);
  }
  else
  {
    printf("Nao deu certo!\n");
  }

  __imprime_lista_de(&l);
  printf("Removendo da posicao 3... ");

  if (remove_lista_de(&l, &v, 3))
  {
    printf("valia %d\n", v);
  }
  else
  {
    printf("Nao deu certo!\n");
  }

  __imprime_lista_de(&l);
  printf("Inserindo '111' no final... ");
  v = 111;

  if (insere_final_de(&l, &v))
  {
    printf("Foi\n");
  }
  else
  {
    printf("Nao deu certo!\n");
  }

  __imprime_lista_de(&l);
  printf("Inserindo '999' no inicio... ");
  v = 999;

  if (insere_inicio_de(&l, &v))
  {
    printf("Foi\n");
  }
  else
  {
    printf("Nao deu certo!\n");
  }

  __imprime_lista_de(&l);
  printf("Inserindo '777' na posicao 1... ");
  v = 777;

  if (insere_lista_de(&l, &v, 1))
  {
    printf("Foi\n");
  }
  else
  {
    printf("Nao deu certo!\n");
  }

  __imprime_lista_de(&l);
  printf("Removendo chave '777'... ");
  v = 777;

  if (remove_chave_de(&l, &v))
  {
    printf("Foi\n");
  }
  else
  {
    printf("Nao existe!\n");
  }

  __imprime_lista_de(&l);
  printf("Removendo chave '999'... ");
  v = 999;

  if (remove_chave_de(&l, &v))
  {
    printf("Foi\n");
  }
  else
  {
    printf("Nao existe!\n");
  }

  __imprime_lista_de(&l);
  printf("Removendo chave '111'... ");
  v = 111;

  if (remove_chave_de(&l, &v))
  {
    printf("Foi\n");
  }
  else
  {
    printf("Nao existe!\n");
  }

  __imprime_lista_de(&l);
  printf("Removendo chave '-1'... ");
  v = -1;

  if (remove_chave_de(&l, &v))
  {
    printf("Foi\n");
  }
  else
  {
    printf("Nao existe!\n");
  }

  __imprime_lista_de(&l);
  printf("Quem esta na posicao 5?  ");

  if (consulta_lista_de(&l, 5, &v))
  {
    printf("%d\n", v);
  }
  else
  {
    printf("Nao existe!\n");
  }

  printf("Indo para o inicio da lista... ");

  if (!obtem_inicio_de(&l, &p))
  {
    printf("Lista nao tem inicio\n");
  }
  else
  {
    if (obtem_sucessor_de(p, &q))
    {
      if (obtem_valor_no(p, &v) && obtem_valor_no(q, &r))
      {
        printf("Depois de %d vem %d\n", v, r);
      }
    }
    else
    {
      obtem_valor_no(p, &v);
      printf("Depois de %d nao vem ninguem\n", v);
    }

    printf("Mudando o valor de %d para %d\n", v, v+1);
    v++;
    definir_valor_no(p, &v);

    if (obtem_predecessor_de(p, &q))
    {
      if (obtem_valor_no(p, &v) && obtem_valor_no(q, &r))
      {
        printf("Antes de %d vem %d\n", v, r);
      }
    }
    else
    {
      obtem_valor_no(p, &v);
      printf("Antes de %d nao vem ninguem\n", v);
    }
  }

  printf("Indo para o final da lista... ");

  if (!obtem_final_de(&l, &p))
  {
    printf("Lista nao tem final\n");
  }
  else
  {
    if (obtem_sucessor_de(p, &q))
    {
      if (obtem_valor_no(p, &v) && obtem_valor_no(q, &r))
      {
        printf("Depois de %d vem %d\n", v, r);
      }
    }
    else
    {
      obtem_valor_no(p, &v);
      printf("Depois de %d nao vem ninguem\n", v);
    }

    if (obtem_predecessor_de(p, &q))
    {
      if (obtem_valor_no(p, &v) && obtem_valor_no(q, &r))
      {
        printf("Antes de %d vem %d\n", v, r);
      }
    }
    else
    {
      obtem_valor_no(p, &v);
      printf("Antes de %d nao vem ninguem\n", v);
    }
  }

  consulta_lista_de(&l, 3, &v);
  busca_lista_de(&l, &v, &p);

  if (obtem_sucessor_de(p, &q))
  {
    if (obtem_valor_no(p, &v) && obtem_valor_no(q, &r))
    {
      printf("Depois de %d vem %d\n", v, r);
    }
  }
  else
  {
    obtem_valor_no(p, &v);
    printf("Depois de %d nao vem ninguem\n", v);
  }

  if (obtem_predecessor_de(p, &q))
  {
    if (obtem_valor_no(p, &v) && obtem_valor_no(q, &r))
    {
      printf("Antes de %d vem %d\n", v, r);
    }
  }
  else
  {
    obtem_valor_no(p, &v);
    printf("Antes de %d nao vem ninguem\n", v);
  }

  v = 1000;

  if (!insere_antes_do_nodo_de(&l, (const NOH_DE **) &p, &v))
  {
    printf("Problemas para inserir antes de %d\n", p->dado);
  }
  else
  {
    printf("Inserindo %d antes de %d\n", v, p->dado);
  }

  __imprime_lista_de(&l);
  printf("Removendo o nodo com %d... ", p->dado);

  if (remove_nodo_de(&l, &p))
  {
    printf("Deu certo!\n");
  }
  else
  {
    printf("Problemas para remover\n");
  }

  __imprime_lista_de(&l);
  printf("Destruindo a lista\n");
  destroi_lista_de(&l);
  printf("Situacao final\n");
  imprime_lista_de(&l);
  return 0;
}
