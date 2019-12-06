#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <lista_circ.h>

int main()
{
  LISTA_CIRC l;
  NOH_CIRC *p, *r;
  unsigned int i;
  TIPO_DADO v, q;

  srand(time(NULL));
  const unsigned int TAM_LISTA = 5;

  if (!inicializa_lista_circ(&l))
  {
    return 1;
  }

  for (i = 0; i < TAM_LISTA; i++)
  {
    v = (TIPO_DADO) (rand() % 1000);
    if (!insere_final_circ(&l, &v))
    {
      printf("Lista cheia\n");
    }
    else
    {
      printf("Inserido %d\n", v);
    }
  }

  printf("--------------\n");
  imprime_lista_circ(&l);
  printf("--------------\n");

  for (i = 0; i < TAM_LISTA; i++)
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
  printf("Modificando %d por %d\n", q-1, q);
  definir_valor_no(r, &q);

  printf("--------------\n");
  __imprime_lista_circ(&l);
  printf("--------------\n");

//  while (remove_inicio_circ(&l, &v))
//  {
//    printf("Removemos %d do inicio\n", v);
//  }
  printf("--------------\n");
  __imprime_lista_circ(&l);
  printf("--------------\n");

  while (remove_final_circ(&l, &v))
  {
    printf("Removemos %d do final\n", v);
  }

  printf("Destruindo a lista\n");
  destroi_lista_circ(&l);
  printf("Situacao final\n");
  imprime_lista_circ(&l);


  return 0;
}