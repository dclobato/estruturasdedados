#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <grafo.h>
#include <stdbool.h>

bool CriaGrafo(TipoGrafo *Grafo, unsigned max, bool direcionado)
{
  unsigned i, j;

  if ((max > MAXNUMVERTICES) || (max < 1))
    return false;

  Grafo->MaxVertices = max;
  Grafo->NumVertices = 0;
  Grafo->NumArestas = 0;
  Grafo->Direcionado = direcionado;

  for (i = 0; i < Grafo->MaxVertices; i++)
    for (j = 0; j < Grafo->MaxVertices; j++)
      Grafo->Mat[i][j] = 0;

  return true;
}

bool InsereAresta(unsigned V1, unsigned V2, int Peso, TipoGrafo *Grafo)
{
  if ((Peso == 0) || (V1 > Grafo->MaxVertices) || (V2 > Grafo->MaxVertices) ||
      (V1 < 0) || (V2 < 0) || (Grafo->NumArestas == MAXNUMARESTAS))
    return false;

  Grafo->Mat[V1][V2] = Peso;

  if (!Grafo->Direcionado)
    Grafo->Mat[V2][V1] = Peso;

  Grafo->NumArestas++;
  return true;
}

bool RetiraAresta(unsigned V1, unsigned V2, int *Peso, TipoGrafo *Grafo)
{
  if ((V1 > Grafo->MaxVertices) || (V2 > Grafo->MaxVertices) || (V1 < 0) ||
      (V2 < 0))
    return false;

  *Peso = Grafo->Mat[V1][V2];

  if (*Peso == 0)
    return false;

  Grafo->Mat[V1][V2] = 0;

  if (!Grafo->Direcionado)
    Grafo->Mat[V2][V1] = 0;

  Grafo->NumArestas--;
  return true;
}

bool ExisteAresta(unsigned V1, unsigned V2, TipoGrafo *Grafo)
{
  if ((V1 > Grafo->MaxVertices) || (V2 > Grafo->MaxVertices) || (V1 < 0) ||
      (V2 < 0))
    return false;

  return (Grafo->Mat[V1][V2] != 0);
}

void ImprimeGrafo(TipoGrafo *Grafo)
{
  unsigned i, j;
  printf("   ");

  for (i = 0; i < Grafo->MaxVertices; i++)
    printf("%3d", i);

  printf("\n");

  for (i = 0; i < Grafo->MaxVertices; i++)
  {
    printf("%3d", i);

    for (j = 0; j < Grafo->MaxVertices; j++)
      printf("%3d", Grafo->Mat[i][j]);

    printf("\n");
  }

  return;
}

int ObterPesoAresta(unsigned V1, unsigned V2, TipoGrafo *Grafo, int *Peso)
{
  if ((V1 > Grafo->MaxVertices) || (V2 > Grafo->MaxVertices) || (V1 < 0) ||
      (V2 < 0))
    return false;

  *Peso = Grafo->Mat[V1][V2];
  return true;
}

bool ObterListaAdjacencias(unsigned V1, TipoGrafo *Grafo,
                           TipoListaAdjGrafo *Lista)
{
  unsigned i;
  int peso;

  if ((V1 > Grafo->MaxVertices) || (V1 < 0))
    return false;

  Lista->NumAdjacentes = 0;

  for (i = 0; i < Grafo->MaxVertices; i++)
  {
    if (ExisteAresta(V1, i, Grafo))
    {
      if (!ObterPesoAresta(V1, i, Grafo, &peso))
      {
        printf("Inconsistencia\n");
        exit(1);
      }

      Lista->Lista[Lista->NumAdjacentes].vertice = i;
      Lista->Lista[Lista->NumAdjacentes].peso = peso;
      Lista->NumAdjacentes++;
    }
  }

  return true;
}

bool ObterGrauNo(unsigned V1, TipoGrafo *Grafo, unsigned *gE, unsigned *gS)
{
  unsigned i;

  if ((V1 > Grafo->MaxVertices) || (V1 < 0))
    return false;

  *gE = 0;
  *gS = 0;

  for (i = 0; i < Grafo->MaxVertices; i++)
  {
    if (ExisteAresta(V1, i, Grafo))
      *gS = *gS + 1;

    if (ExisteAresta(i, V1, Grafo))
      *gE = *gE + 1;
  }

  return true;
}

void  PercursoLargura(unsigned V1, TipoGrafo *Grafo, PercursoBFS *bfs)
{
  unsigned i, u, v;
  unsigned *fila;
  int inicio, final;
  TipoListaAdjGrafo adjacentes;

  if ((V1 > Grafo->MaxVertices) || (V1 < 0))
    return;

  fila = (unsigned *) malloc(Grafo->MaxVertices * sizeof(unsigned));
  inicio = final = 0;

  for (i = 0; i < Grafo->MaxVertices; i++)
  {
    bfs->vertex[i].cor = BRANCO;
    bfs->vertex[i].pai = -1;
    bfs->vertex[i].distancia = -1;
  }

  bfs->Origem = V1;
  bfs->NumDestinos = 0;
  bfs->vertex[V1].cor = CINZA;
  bfs->vertex[V1].distancia = 0;
  fila[final++] = V1;

  while (inicio != final)
  {
    u = fila[inicio++];
    ObterListaAdjacencias(u, Grafo, &adjacentes);

    for (i = 0; i < adjacentes.NumAdjacentes; i++)
    {
      v = adjacentes.Lista[i].vertice;

      if (bfs->vertex[v].cor == BRANCO)
      {
        bfs->vertex[v].cor = CINZA;
        bfs->vertex[v].distancia = bfs->vertex[u].distancia + 1;
        bfs->vertex[v].pai = u;
        fila[final++] = v;
      }
    }

    bfs->vertex[u].cor = PRETO;
    bfs->NumDestinos = bfs->NumDestinos + 1;
  }

  free(fila);
  return;
}

void PercursoProfundidade(unsigned V1, TipoGrafo *Grafo, PercursoDFS *dfs,
                          bool todos)
{
  unsigned i;
  unsigned relogio;
  unsigned delta;

  if (((V1 > Grafo->MaxVertices) || (V1 < 0)) && (!todos))
    return;

  for (i = 0; i < Grafo->MaxVertices; i++)
  {
    dfs->vertex[i].cor        = BRANCO;
    dfs->vertex[i].pai        = -1;
    dfs->vertex[i].descoberta = -1;
    dfs->vertex[i].termino    = -1;
    dfs->OrdemTopologica[i]   = -1;
  }

  relogio = -1;
  dfs->NumDestinos = 0;
  dfs->DAG = true;

  if (!todos)
    _PP(V1, Grafo, dfs, &relogio, -1);
  else
  {
    for (i = 0; i < Grafo->MaxVertices; i++)
    {
      if (dfs->vertex[i].cor == BRANCO)
        _PP(i, Grafo, dfs, &relogio, -1);
    }
  }

  // Se for um DAG, tem ordem topologica
  // Entao, trazer os indices dos vertices para o inicio do vetor
  if (dfs->DAG)
  {
    delta = Grafo->MaxVertices - dfs->NumDestinos;

    for (i = 0; i < dfs->NumDestinos; i++)
      dfs->OrdemTopologica[i] = dfs->OrdemTopologica[i + delta];

    for (; i < Grafo->MaxVertices; i++)
      dfs->OrdemTopologica[i] = -1;
  }

  return;
}


void  _PP(unsigned vertice, TipoGrafo *Grafo, PercursoDFS *dfs,
          unsigned *relogio, unsigned pai)
{
  unsigned i, v;
  TipoListaAdjGrafo adjacentes;
  *relogio = *relogio + 1;
  dfs->vertex[vertice].cor = CINZA;
  dfs->vertex[vertice].descoberta = *relogio;
  ObterListaAdjacencias(vertice, Grafo, &adjacentes);

  for (i = 0; i < adjacentes.NumAdjacentes; i++)
  {
    v = adjacentes.Lista[i].vertice;

    switch (dfs->vertex[v].cor)
    {
      case CINZA: // Aresta de retorno
        //Se acho outro que esta sendo processado, o grafo
        // eh ciclico, entao deixa de ser um DAG
        dfs->DAG = false;
        break;

      case BRANCO: // Aresta de arvore
        dfs->vertex[v].pai = vertice;
        _PP(v, Grafo, dfs, relogio, vertice);
        break;

      case PRETO: // Aresta de avanco ou de cruzamento
        break;

      default:
        break;
    }
  }

  *relogio = *relogio + 1;
  dfs->vertex[vertice].cor = PRETO;
  dfs->vertex[vertice].termino = *relogio;
  dfs->NumDestinos = dfs->NumDestinos + 1;
  // Insere o vertice na cabeca da lista de ordenacao topologica
  dfs->OrdemTopologica[Grafo->MaxVertices - dfs->NumDestinos] = vertice;
  return;
}
