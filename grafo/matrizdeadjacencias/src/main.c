#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <grafo.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
  TipoGrafo grafo;
  PercursoDFS percursodfs;
  PercursoBFS percursobfs;
  AGM agm;
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

  for (i = 0; i < nv; i++)
  {
    memset(rotulo, '\0', sizeof(rotulo));
    sprintf(rotulo, "%c", i + 65);

    if (!InsereRotulo(rotulo, strlen(rotulo), &grafo, &to))
      printf("Nao foi possivel inserir a aresta\n");
    else
      printf("Inserido vertice %u\n", to);
  }

  while (true)
  {
    scanf("%u %u %d", &from, &to, &weight);

    if ((from == -1) || (to == -1))
      break;

    if (!InsereAresta(from, to, weight, &grafo))
      printf("Nao foi possivel inserir a aresta\n");
  }

  ImprimeGrafo(&grafo);
  PercursoProfundidade(0, &grafo, &percursodfs, true);
  printf("DFS a partir de todos tem %d destinos\n", percursodfs.NumDestinos);
  printf("DAG: %d\n", percursodfs.DAG);
  printf("     V Cor Des Ter    Pai\n");

  for (to = 0; to < grafo.MaxVertices; to++)
    printf("%6u %3d %3d %3d %6u\n", to, percursodfs.vertex[to].cor,
           percursodfs.vertex[to].descoberta, percursodfs.vertex[to].termino,
           percursodfs.vertex[to].pai);

  if (percursodfs.DAG)
  {
    printf("Ordem topológica\n");

    for (to = 0; to < percursodfs.NumDestinos; to++)
      printf("%u ", percursodfs.OrdemTopologica[to]);
  }

  DestroiPercursoProfundidade(&percursodfs);
  PercursoLargura(0, &grafo, &percursobfs);
  DestroiPercursoLargura(&percursobfs);
  printf("\n");

  if (AGMPrim(0, &grafo, &agm))
  {
    printf("    De   Para    Peso\n");

    for (to = 0; to < grafo.MaxVertices; to++)
    {
      if (agm.pai[to] == UINT_MAX)
        printf("------ %6u -------\n", to);
      else
        printf("%6u %6u %7d\n", agm.pai[to], to, agm.custo[to]);
    }

    printf("Arestas: %d\tCusto: %ld\n", agm.NumArestas, agm.pesoTotal);
    DestroiAGM(&agm);
  }

  DestroiGrafo(&grafo);
  return true;
}
