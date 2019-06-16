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

  if (!CriaGrafo(&grafo, nv, (bool) dirigido))
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

    if (!InsereVertice(rotulo, strlen(rotulo), &grafo, &to))
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

    if (!InsereAresta(from, to, weight, &grafo))
    {
      printf("Nao foi possivel inserir a aresta\n");
    }
  }

  ImprimeGrafo(&grafo);
  colorirGrafo(&grafo, &cores);
  printf("V C\n");

  for (i = 0; i < grafo.NumVertices; i++)
  {
    printf("%s %u\n", grafo.Rotulos[i], cores[i]);
  }

  free(cores);
  DestroiGrafo(&grafo);
  return true;
}
