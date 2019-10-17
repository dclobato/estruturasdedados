#include <stdio.h>
#include <pilha.h>

int main()
{
  PILHA p;
  TIPO_DADO c;
  unsigned int i;
  printf("Inicializando pilha\n");

  if (!pilha_inicializa(&p))
  {
    return 1;
  }
  printf("Numero de elementos: %d\n", pilha_numelementos(&p));

  if (pilha_estavazia(&p))
    printf("Pilha esta vazia\n");

  printf("Empilhando...\n");

  for (i = 0; i < 15; i++)
    if (pilha_PUSH(&p, (TIPO_DADO *) &i))
    {
      printf("Inserido %d\n", i);
      printf("Numero de elementos: %d\n", pilha_numelementos(&p));
    }
    else
    {
      printf("Pilha cheia\n");
    }

  if (pilha_estacheia(&p))
    printf("Pilha esta cheia\n");

  printf("Esvaziando a pilha\n");

  while (pilha_POP(&p, &c))
  {
    printf("%d\n", c);
  }

  printf("Destruindo a pilha\n");
  pilha_destroi(&p);
  return 0;
}


