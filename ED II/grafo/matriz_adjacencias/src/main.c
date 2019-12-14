#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <grafo.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
  TipoGrafo grafo;
  unsigned *cores;
  char rotulo[20];
  unsigned from, to, nv, i;
  int weight;
  int dirigido;
  scanf("%u", &nv);

  if (nv > MAXNUMVERTICES)
  {
    printf("Numero de vertices maior que a capacidade\n");
    exit(1);
  }

  scanf("%d", &dirigido);

  if (!cria_grafo(&grafo, nv, (bool) dirigido))
  {
    printf("Problemas para criar o grafo\n");
    exit(1);
  }

  // limpa buffer dos inteiros
  scanf("%*c");
  
  for (i = 0; i < nv; i++)
  {
    memset(rotulo, '\0', sizeof(rotulo));
    scanf("%19[^\n]\n", rotulo);

    if (!insere_vertice(&grafo, rotulo, strlen(rotulo), &to))
    {
      printf("Nao foi possivel inserir o vertice\n");
    }
    else
    {
      printf("Inserido vertice %u\n", to);
    }
  }

  while (true)
  {
    scanf("%u %u %d", &from, &to, &weight);

    if ((from == -1) || (to == -1))
    {
      break;
    }

    if (!insere_aresta(&grafo, from, to, weight))
    {
      printf("Nao foi possivel inserir a aresta\n");
    }
  }

  imprime_grafo(&grafo);
  colorir_grafo(&grafo, &cores);
  printf("V C\n");

  for (i = 0; i < grafo.numVertices; i++)
  {
    printf("%s %u\n", grafo.rotulos[i], cores[i]);
  }

  free(cores);
  destroi_grafo(&grafo);
  return true;
}
