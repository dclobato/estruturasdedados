#include <stdio.h>
#include <pilha.h>

int main()
{
  PILHA p;
  PILHA_DESCRITOR p2;
  TIPO_DADO c;
  unsigned int i;

  printf("---------------------------- Sem descritor\n");

  printf("Inicializando pilha\n");

  if (!pilha_inicializa(&p))
  {
    return 1;
  }
  printf("Numero de elementos: %d\n", pilha_numelementos(&p));

  if (pilha_estavazia(&p))
    printf("Pilha esta vazia\n");
  else
    printf("Pilha nao esta vazia\n");

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
  else
    printf("Pilha nao esta cheia\n");

  printf("Esvaziando a pilha\n");

  while (pilha_POP(&p, &c))
  {
    printf("%d\n", c);
  }

  printf("Destruindo a pilha\n");
  pilha_destroi(&p);

  printf("Numero de elementos: %d\n", pilha_numelementos(&p));

  printf("---------------------------- Com descritor\n");

  printf("Inicializando pilha\n");

  if (!pilha_descritor_inicializa(&p2))
  {
    return 1;
  }
  printf("Numero de elementos: %d\n", pilha_descritor_numelementos(&p2));

  if (pilha_descritor_estavazia(&p2))
    printf("Pilha esta vazia\n");
  else
    printf("Pilha nao esta vazia\n");

  printf("Empilhando...\n");

  for (i = 0; i < 15; i++)
    if (pilha_descritor_PUSH(&p2, (TIPO_DADO *) &i))
    {
      printf("Inserido %d\n", i);
      printf("Numero de elementos: %d\n", pilha_descritor_numelementos(&p2));
    }
    else
    {
      printf("Pilha cheia\n");
    }

  if (pilha_descritor_estacheia(&p2))
    printf("Pilha esta cheia\n");
  else
    printf("Pilha nao esta cheia\n");

  printf("Esvaziando a pilha\n");

  while (pilha_descritor_POP(&p2, &c))
  {
    printf("%d\n", c);
  }

  printf("Destruindo a pilha\n");
  pilha_descritor_destroi(&p2);

  printf("Numero de elementos: %d\n", pilha_descritor_numelementos(&p2));

  return 0;
}


