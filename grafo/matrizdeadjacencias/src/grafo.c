#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
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
  // Alocando dinamicamente a matriz de adjacencias
  Grafo->Mat = (int **) malloc(max * sizeof(int *));

  for (i = 0; i < Grafo->MaxVertices; i++)
  {
    Grafo->Mat[i] = (int *) malloc(max * sizeof(int));

    for (j = 0; j < Grafo->MaxVertices; j++)
      Grafo->Mat[i][j] = 0;
  }

  // Alocando dinamicamente o vetor de rotulos
  Grafo->Rotulos = (char **) malloc(Grafo->MaxVertices * sizeof(char *));

  for (i = 0; i < Grafo->MaxVertices; i++)
  {
    Grafo->Rotulos[i] = (char *) malloc((MAXTAMROTULO + 1) * sizeof(char));
    memset(Grafo->Rotulos[i], '\0', (size_t) sizeof(Grafo->Rotulos[i]));
  }

  return true;
}

bool InsereAresta(unsigned V1, unsigned V2, int Peso, TipoGrafo *Grafo)
{
  if ((Peso == 0) || (V1 > Grafo->NumVertices) || (V2 > Grafo->NumVertices) ||
      (V1 < 0) || (V2 < 0) || (Grafo->NumArestas == MAXNUMARESTAS))
    return false;

  Grafo->Mat[V1][V2] = Peso;

  if (!Grafo->Direcionado)
    Grafo->Mat[V2][V1] = Peso;

  Grafo->NumArestas++;
  return true;
}

bool InsereRotulo(char *rotulo, int tamanho, TipoGrafo *Grafo,
                  unsigned *vertice)
{
  if ((Grafo->NumVertices == MAXNUMVERTICES) || (tamanho > MAXTAMROTULO))
    return false;

  memset(Grafo->Rotulos[Grafo->NumVertices], '\0',
         (size_t) sizeof(*Grafo->Rotulos[Grafo->NumVertices]));
  strncpy(Grafo->Rotulos[Grafo->NumVertices], rotulo, tamanho);
  *vertice = Grafo->NumVertices++;
  return true;
}

bool RetiraAresta(unsigned V1, unsigned V2, int *Peso, TipoGrafo *Grafo)
{
  if ((V1 > Grafo->NumVertices) || (V2 > Grafo->NumVertices) || (V1 < 0) ||
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
  if ((V1 > Grafo->NumVertices) || (V2 > Grafo->NumVertices) || (V1 < 0) ||
      (V2 < 0))
    return false;

  return (Grafo->Mat[V1][V2] != 0);
}

void ImprimeGrafo(TipoGrafo *Grafo)
{
  unsigned i, j;

  for (i = 0; i < Grafo->NumVertices; i++)
    printf("Vertice %u: %s\n", i, Grafo->Rotulos[i]);

  printf("   ");

  for (i = 0; i < Grafo->NumVertices; i++)
    printf("%3d", i);

  printf("\n");

  for (i = 0; i < Grafo->NumVertices; i++)
  {
    printf("%3d", i);

    for (j = 0; j < Grafo->NumVertices; j++)
      printf("%3d", Grafo->Mat[i][j]);

    printf("\n");
  }

  return;
}

int ObterPesoAresta(unsigned V1, unsigned V2, TipoGrafo *Grafo, int *Peso)
{
  if ((V1 > Grafo->NumVertices) || (V2 > Grafo->NumVertices) || (V1 < 0) ||
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

  if ((V1 > Grafo->NumVertices) || (V1 < 0))
    return false;

  Lista->NumAdjacentes = 0;
  Lista->Lista = (RegistroAdjacencia *) malloc(Grafo->NumVertices * sizeof(
                   RegistroAdjacencia));

  for (i = 0; i < Grafo->NumVertices; i++)
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

  if ((V1 > Grafo->NumVertices) || (V1 < 0))
    return false;

  *gE = 0;
  *gS = 0;

  for (i = 0; i < Grafo->NumVertices; i++)
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

  if ((V1 > Grafo->NumVertices) || (V1 < 0))
    return;

  fila = (unsigned *) malloc(Grafo->NumVertices * sizeof(unsigned));
  inicio = final = 0;
  bfs->vertex = (RegistroLargura *) malloc(Grafo->NumVertices * sizeof(
                  RegistroLargura));

  for (i = 0; i < Grafo->NumVertices; i++)
  {
    bfs->vertex[i].cor = BRANCO;
    bfs->vertex[i].pai = UINT_MAX;
    bfs->vertex[i].distancia = UINT_MAX;
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

  if (((V1 > Grafo->NumVertices) || (V1 < 0)) && (!todos))
    return;

  dfs->vertex = (RegistroProfundidade *) malloc(Grafo->NumVertices * sizeof(
                  RegistroProfundidade));

  for (i = 0; i < Grafo->NumVertices; i++)
  {
    dfs->vertex[i].cor        = BRANCO;
    dfs->vertex[i].pai        = UINT_MAX;
    dfs->vertex[i].descoberta = UINT_MAX;
    dfs->vertex[i].termino    = UINT_MAX;
    dfs->OrdemTopologica[i]   = UINT_MAX;
  }

  relogio = -1;
  dfs->NumDestinos = 0;
  dfs->DAG = true;

  if (!todos)
    _PP(V1, Grafo, dfs, &relogio, UINT_MAX);
  else
  {
    for (i = 0; i < Grafo->NumVertices; i++)
    {
      if (dfs->vertex[i].cor == BRANCO)
        _PP(i, Grafo, dfs, &relogio, UINT_MAX);
    }
  }

  // Se for um DAG, tem ordem topologica
  // Entao, trazer os indices dos vertices para o inicio do vetor
  if (dfs->DAG)
  {
    delta = Grafo->NumVertices - dfs->NumDestinos;
    dfs->OrdemTopologica = (unsigned *) malloc(Grafo->NumVertices * sizeof(
                             unsigned));

    for (i = 0; i < dfs->NumDestinos; i++)
      dfs->OrdemTopologica[i] = dfs->OrdemTopologica[i + delta];

    for (; i < Grafo->NumVertices; i++)
      dfs->OrdemTopologica[i] = UINT_MAX;
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
  dfs->OrdemTopologica[Grafo->NumVertices - dfs->NumDestinos] = vertice;
  return;
}
