#include <stdio.h>
#include <pilha.h>

int main()
{
  PILHA p;
  TIPO_DADO c;
  unsigned int i;

  printf("Inicializando pilha\n");

  if (!pilha_inicializar(&p))
  {
    return 1;
  }
  printf("Numero de elementos: %d\n", pilha_numero_de_elementos(&p));

  if (pilha_esta_vazia(&p))
  {
    printf("Pilha esta vazia\n");
  }
  else
  {
    printf("Pilha nao esta vazia\n");
  }

  printf("Empilhando...\n");

  for (i = 0; i < 15; i++)
  {
    if (pilha_PUSH(&p, (TIPO_DADO *) &i))
    {
      printf("Inserido %d\n", i);
      printf("Numero de elementos: %d\n", pilha_numero_de_elementos(&p));
    }
    else
    {
      printf("Pilha cheia\n");
    }
  }

  if (pilha_PEEK(&p, &c))
  {
    printf("Topo da pilha: %d\n", c);
  }
  if (pilha_esta_cheia(&p))
  {
    printf("Pilha esta cheia\n");
  }
  else
  {
    printf("Pilha nao esta cheia\n");
  }

  printf("Esvaziando a pilha\n");

  while (pilha_POP(&p, &c))
  {
    printf("%d\n", c);
  }

  printf("Destruindo a pilha\n");
  pilha_destruir(&p);

  printf("Numero de elementos: %d\n", pilha_numero_de_elementos(&p));

  return 0;
}