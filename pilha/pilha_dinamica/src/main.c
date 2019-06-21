#include <stdio.h>
#include <pilha.h>

int main()
{
  PILHA p;
  TIPO_DADO c;
  int i;
  printf("Inicializando pilha\n");

  if (!inicializa_pilha(&p))
  {
    return 1;
  }

  printf("Empilhando...\n");

  for (i = 0; i < 15; i++)
    if (PUSH(&p, (TIPO_DADO *)&i))
    {
      printf("Inserido %d\n", i);
    }
    else
    {
      printf("Pilha cheia\n");
    }

  printf("Esvaziando a pilha\n");

  while (POP(&p, &c))
  {
    printf("%d\n", c);
  }

  printf("Destruindo a pilha\n");
  destroi_pilha(&p);
  return 0;
}
