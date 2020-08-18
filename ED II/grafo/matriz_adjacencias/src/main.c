#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <grafo.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
  TipoGrafo grafo;
  unsigned *cores;
  char rotulo[MAXTAMROTULO];
  unsigned from, to, nv, i;
  int weight;
  int dirigido;
  int ponderado;

  printf("Numero de vertices: ");
  scanf("%u", &nv);

  if (nv > MAXNUMVERTICES)
  {
    printf("Numero de vertices maior que a capacidade\n");
    exit(1);
  }

  printf("Dirigido? ");
  scanf("%d", &dirigido);
  printf("Ponderado? ");
  scanf("%d", &ponderado);

  if (!cria_grafo(&grafo, nv, (bool) dirigido, ponderado))
  {
    printf("Problemas para criar o grafo\n");
    exit(1);
  }

  // limpa buffer dos inteiros
  scanf("%*c");

  for (i = 0; i < nv; i++)
  {
    printf("Rotulo do vertice %d: ", i);
    memset(rotulo, '\0', MAXTAMROTULO);
    fgets(rotulo, (int) MAXTAMROTULO, stdin);
    rotulo[strcspn(rotulo, "\n")] = '\0';

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
    printf("origem destino peso: ");
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

  //imprime_grafo(&grafo);
  gera_graphviz(&grafo);
  colorir_grafo(&grafo, &cores);
  printf("V C\n");

  for (i = 0; i < grafo.numVertices; i++)
  {
    printf("%s %u\n", grafo.rotulos[i], cores[i]);
  }

  free(cores);
  destroi_grafo(&grafo);
  printf("Final\n");
  return true;
}
