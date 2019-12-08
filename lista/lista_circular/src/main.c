#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <lista_circ.h>

int main()
{
  LISTA_CIRC l;
  NOH_CIRC *p, *r;
  unsigned int i, j;
  TIPO_DADO v, q;

  srand(time(NULL));
  const unsigned int TAM_LISTA = 2;

  if (!inicializa_lista_circ(&l))
  {
    return 1;
  }

  for (i = 0; i < TAM_LISTA; i++)
  {
    v = (TIPO_DADO) (rand() % 1000);
    //scanf("%d %d", &v,  &j);
    printf("Tentando %d na posicao %d... ", v, i);
    if (!insere_lista_circ(&l, &v, i))
    {
      printf("Lista cheia\n");
    }
    else
    {
      printf("Inserido %d\n", v);
      imprime_lista_circ(&l);
    }
  }

  printf("--------------\n");
  imprime_lista_circ(&l);
  printf("--------------\n");

  v = 999;
  if (!insere_inicio_circ(&l, &v))
  {
    printf("Lista cheia\n");
  }
  else
  {
    printf("Inserido %d na posicao %d\n", v, 0);
  }

  printf("--------------\n");
  imprime_lista_circ(&l);
  printf("--------------\n");

  v = 987123;
  i = tamanho_lista_circ(&l);

  if (!insere_final_circ(&l, &v))
  {
    printf("Lista cheia\n");
  }
  else
  {
    printf("Inserido %d na posicao %d\n", v, i);
  }

  printf("--------------\n");
  imprime_lista_circ(&l);
  printf("--------------\n");

  for (i = 0; i < tamanho_lista_circ(&l); i++)
  {
    consulta_lista_circ(&l, i, &v);
    printf("Posicao: %d\tValor: %d\n", i, v);
  }

  while (true)
  {
    v = (TIPO_DADO) (rand() % 1000);
    printf("Buscando por %d... ", v);
    if (busca_lista_circ(&l, &v, &p))
    {
      break;
    }
    else
    {
      printf("Nao\n");
    }
  }
  printf("Achou em %p\n", p);
  v = 555555;

  obtem_sucessor_circ(p, &r);
  if ((obtem_valor_no(p, &v)) && (obtem_valor_no(r, &q)))
  {
    printf("Depois de %d vem %d\n", v, q);
  }
  else
  {
    printf("Problemas\n");
  }
  q++;
  printf("Modificando %d por %d\n", q - 1, q);
  definir_valor_no(r, &q);

  printf("--------------\n");
  __imprime_lista_circ(&l);
  printf("--------------\n");

  if (remove_inicio_circ(&l, &v))
  {
    printf("Removemos %d do inicio\n", v);
  }
  printf("--------------\n");
  __imprime_lista_circ(&l);
  printf("--------------\n");

  if (remove_final_circ(&l, &v))
  {
    printf("Removemos %d do final\n", v);
  }

  printf("--------------\n");
  imprime_lista_circ(&l);
  printf("--------------\n");

  if (shift_left_lista_circ(&l))
  {
    printf("Rodando para a esquerda\n");
    imprime_lista_circ(&l);
  }

  if (shift_right_lista_circ(&l))
  {
    printf("Rodando para a direita\n");
    imprime_lista_circ(&l);
  }

  printf("Destruindo a lista\n");
  destroi_lista_circ(&l);
  printf("Situacao final\n");
  imprime_lista_circ(&l);

  return 0;
}