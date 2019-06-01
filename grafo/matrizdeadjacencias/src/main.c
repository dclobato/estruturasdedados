#include <stdio.h>
#include <stdlib.h>
#include <grafo.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
  TipoGrafo grafo;
  PercursoBFS percursobfs;
  PercursoDFS percursodfs;
  unsigned from, to;
  int weight, i;
  unsigned gE, gS;

  if (!CriaGrafo(&grafo, 10, true))
  {
    printf("Problemas para criar o grafo\n");
    exit(1);
  }

  while (true)
  {
    printf("Digite a origem, o destino e o peso da aresta: ");
    scanf("%u %u %d", &from, &to, &weight);

    if ((from == -1) || (to == -1))
      break;

    if (!InsereAresta(from, to, weight, &grafo))
      printf("Nao foi possivel inserir a aresta\n");
  }

  ImprimeGrafo(&grafo);
  printf("     V  gE  gS\n");

  for (i = 0; i < grafo.MaxVertices; i++)
  {
    ObterGrauNo(i, &grafo, &gE, &gS);
    printf("%6u %3u %3u\n", from, gE, gS);
  }

  PercursoLargura(0, &grafo, &percursobfs);
  printf("BFS a partir de 0 tem %d destinos\n", percursobfs.NumDestinos);
  printf("     V Cor Dist    Pai\n");

  for (to = 0; to < grafo.MaxVertices; to++)
    printf("%6u %3d %4d %6u\n", to, percursobfs.vertex[to].cor,
           percursobfs.vertex[to].distancia, percursobfs.vertex[to].pai);

  PercursoProfundidade(0, &grafo, &percursodfs, true);
  printf("DFS a partir de todos tem %d destinos\n", percursodfs.NumDestinos);
  printf("DAG: %d\n", percursodfs.DAG);
  printf("     V Cor Des Ter    Pai\n");

  for (to = 0; to < grafo.MaxVertices; to++)
    printf("%6u %3d %3d %3d %6u\n", to, percursodfs.vertex[to].cor,
           percursodfs.vertex[to].descoberta, percursodfs.vertex[to].termino,
           percursodfs.vertex[to].pai);

  printf("Ordem topológica\n");

  for (to = 0; to < percursodfs.NumDestinos; to++)
    printf("%u ", percursodfs.OrdemTopologica[to]);

  printf("\n");
  return true;
}
