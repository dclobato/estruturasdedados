#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <grafo.h>
#include <stdbool.h>

bool cria_grafo(TipoGrafo *grafo, unsigned maximoVertices, bool direcionado)
{
  unsigned int i, j;

  if ((maximoVertices > MAXNUMVERTICES) || (maximoVertices < 1))
  {
    return false;
  }

  grafo->maxVertices = maximoVertices;
  grafo->numVertices = 0;
  grafo->numArestas = 0;
  grafo->direcionado = direcionado;
  // Alocando dinamicamente a matriz de adjacencias
  grafo->matriz = (int **) malloc(maximoVertices * sizeof(int *));

  for (i = 0; i < grafo->maxVertices; i++)
  {
    grafo->matriz[i] = (int *) malloc(maximoVertices * sizeof(int));

    for (j = 0; j < grafo->maxVertices; j++)
    {
      grafo->matriz[i][j] = 0;
    }
  }

  // Alocando dinamicamente o vetor de rotulos
  grafo->rotulos = (char **) malloc(grafo->maxVertices * sizeof(char *));

  for (i = 0; i < grafo->maxVertices; i++)
  {
    grafo->rotulos[i] = (char *) malloc((MAXTAMROTULO + 1) * sizeof(char));
    memset(grafo->rotulos[i], '\0', (size_t) sizeof(grafo->rotulos[i]));
  }

  return true;
}

bool destroi_grafo(TipoGrafo *grafo)
{
  unsigned i;

  for (i = 0; i < grafo->maxVertices; i++)
  {
    free(grafo->rotulos[i]);
    free(grafo->matriz[i]);
  }

  free(grafo->rotulos);
  free(grafo->matriz);
  return true;
}

bool insere_aresta(TipoGrafo *grafo, unsigned verticeOrigem,
                   unsigned verticeDestino, int peso)
{
  if ((peso == 0) || (verticeOrigem > grafo->numVertices) ||
      (verticeDestino > grafo->numVertices) ||
      (verticeOrigem < 0) || (verticeDestino < 0) ||
      (grafo->numArestas == MAXNUMARESTAS))
  {
    return false;
  }

  grafo->matriz[verticeOrigem][verticeDestino] = peso;

  if (!grafo->direcionado)
  {
    grafo->matriz[verticeDestino][verticeOrigem] = peso;
  }

  grafo->numArestas++;
  return true;
}

bool insere_vertice(TipoGrafo *grafo, char *rotulo, size_t tamanho,
                    unsigned *numeroVertice)
{
  if ((grafo->numVertices == MAXNUMVERTICES) || (tamanho > MAXTAMROTULO))
  {
    return false;
  }

  memset(grafo->rotulos[grafo->numVertices], '\0',
         (size_t) sizeof(*grafo->rotulos[grafo->numVertices]));
  strncpy(grafo->rotulos[grafo->numVertices], rotulo, tamanho);
  *numeroVertice = grafo->numVertices++;
  return true;
}

bool retira_aresta(TipoGrafo *grafo, unsigned verticeOrigem,
                   unsigned verticeDestino, int *peso)
{
  if ((verticeOrigem > grafo->numVertices) ||
      (verticeDestino > grafo->numVertices) || (verticeOrigem < 0) ||
      (verticeDestino < 0))
  {
    return false;
  }

  *peso = grafo->matriz[verticeOrigem][verticeDestino];

  if (*peso == 0)
  {
    return false;
  }

  grafo->matriz[verticeOrigem][verticeDestino] = 0;

  if (!grafo->direcionado)
  {
    grafo->matriz[verticeDestino][verticeOrigem] = 0;
  }

  grafo->numArestas--;
  return true;
}

bool existe_aresta(const TipoGrafo *grafo, unsigned verticeOrigem,
                   unsigned verticeDestino)
{
  if ((verticeOrigem > grafo->numVertices) ||
      (verticeDestino > grafo->numVertices) || (verticeOrigem < 0) ||
      (verticeDestino < 0))
  {
    return false;
  }

  return (grafo->matriz[verticeOrigem][verticeDestino] != 0);
}

void imprime_grafo(const TipoGrafo *grafo)
{
  unsigned i, j;
  printf("----------------------------------------\n");
  printf("Rotulos dos vertices\n");
  printf("--------------------\n");

  for (i = 0; i < grafo->numVertices; i++)
  {
    printf("Vertice %u: %s\n", i, grafo->rotulos[i]);
  }

  printf("--------------------\n");
  printf("\n");
  printf("   ");

  for (i = 0; i < grafo->numVertices; i++)
  {
    printf("%3d", i);
  }

  printf("\n");

  for (i = 0; i < grafo->numVertices; i++)
  {
    printf("%3d", i);

    for (j = 0; j < grafo->numVertices; j++)
    {
      printf("%3d", grafo->matriz[i][j]);
    }

    printf("\n");
  }
  printf("----------------------------------------\n");
}

bool obter_peso_aresta(const TipoGrafo *grafo, unsigned verticeOrigem,
                       unsigned verticeDestino, int *peso)
{
  if ((verticeOrigem > grafo->numVertices) ||
      (verticeDestino > grafo->numVertices) || (verticeOrigem < 0) ||
      (verticeDestino < 0))
  {
    return false;
  }

  *peso = grafo->matriz[verticeOrigem][verticeDestino];
  return true;
}

bool obter_lista_adjacentes(const TipoGrafo *grafo, unsigned vertice,
                            ListaVerticesAdjacentes *listaAdjacentes,
                            bool complemento)
{
  unsigned i;
  int peso;

  if ((vertice > grafo->numVertices) || (vertice < 0))
  {
    return false;
  }

  listaAdjacentes->numAdjacentes = 0;
  listaAdjacentes->listaDeVertices = (RegistroVertices *) malloc(
                                       grafo->numVertices * sizeof(
                                         RegistroVertices));

  // complemento == true --> lista de NAO adjacentes
  if (!complemento)
  {
    for (i = 0; i < grafo->numVertices; i++)
    {
      /*
      if (existe_aresta(vertice, i, grafo))
      {
        if (!obter_peso_aresta(vertice, i, grafo, &peso))
        {
          printf("Inconsistencia\n");
          exit(1);
        }
       */
      obter_peso_aresta(grafo, vertice, i, &peso);

      if (peso != 0)
      {
        listaAdjacentes->listaDeVertices[listaAdjacentes->numAdjacentes].vertice =
          i;
        listaAdjacentes->listaDeVertices[listaAdjacentes->numAdjacentes].peso =
          peso;
        listaAdjacentes->numAdjacentes++;
      }
    }
  }
  else
  {
    for (i = 0; i < grafo->numVertices; i++)
    {
      if (!existe_aresta(grafo, vertice, i))
      {
        listaAdjacentes->listaDeVertices[listaAdjacentes->numAdjacentes].vertice =
          i;
        listaAdjacentes->listaDeVertices[listaAdjacentes->numAdjacentes].peso = 0;
        listaAdjacentes->numAdjacentes++;
      }
    }
  }

  return true;
}

bool destroi_lista_adjacentes(ListaVerticesAdjacentes *listaAdjacentes)
{
  free(listaAdjacentes->listaDeVertices);
  return true;
}

bool obter_grau_vertice(const TipoGrafo *grafo, unsigned vertice,
                        unsigned *grauEntrada, unsigned *grauSaida)
{
  unsigned i;

  if ((vertice > grafo->numVertices) || (vertice < 0))
  {
    return false;
  }

  if (grauEntrada)
  {
    *grauEntrada = 0;
  }

  if (grauSaida)
  {
    *grauSaida = 0;
  }

  for (i = 0; i < grafo->numVertices; i++)
  {
    if (grauSaida)
      if (existe_aresta(grafo, vertice, i))
      {
        *grauSaida = *grauSaida + 1;
      }

    if (grauEntrada)
      if (existe_aresta(grafo, i, vertice))
      {
        *grauEntrada = *grauEntrada + 1;
      }
  }

  return true;
}

bool percurso_largura(const TipoGrafo *grafo, unsigned vertice,
                      PercursoBFS *percurso)
{
  unsigned i, u, v;
  unsigned *fila;
  unsigned int inicio, final;
  ListaVerticesAdjacentes adjacentes;

  if ((vertice > grafo->numVertices) || (vertice < 0))
  {
    return false;
  }

  fila = (unsigned *) malloc(grafo->numVertices * sizeof(unsigned));
  inicio = final = 0;
  percurso->vertex = (RegistroVertices *) malloc(grafo->numVertices * sizeof(
                       RegistroVertices));

  for (i = 0; i < grafo->numVertices; i++)
  {
    percurso->vertex[i].corTrabalho = BRANCO;
    percurso->vertex[i].pai = UINT_MAX;
    percurso->vertex[i].distancia = UINT_MAX;
  }

  percurso->verticeOrigem = vertice;
  percurso->numDestinos = 0;
  percurso->vertex[vertice].corTrabalho = CINZA;
  percurso->vertex[vertice].distancia = 0;
  fila[final++] = vertice;

  while (inicio != final)
  {
    u = fila[inicio++];
    obter_lista_adjacentes(grafo, u, &adjacentes, false);

    for (i = 0; i < adjacentes.numAdjacentes; i++)
    {
      v = adjacentes.listaDeVertices[i].vertice;

      if (percurso->vertex[v].corTrabalho == BRANCO)
      {
        percurso->vertex[v].corTrabalho = CINZA;
        percurso->vertex[v].distancia = percurso->vertex[u].distancia + 1;
        percurso->vertex[v].pai = u;
        fila[final++] = v;
      }
    }

    percurso->vertex[u].corTrabalho = PRETO;
    percurso->numDestinos = percurso->numDestinos + 1;
    destroi_lista_adjacentes(&adjacentes);
  }

  free(fila);
  return true;
}

bool destroi_percurso_largura(PercursoBFS *percurso)
{
  free(percurso->vertex);
  return true;
}

bool percurso_profundidade(const TipoGrafo *grafo, unsigned vertice,
                           PercursoDFS *percurso, bool todos)
{
  unsigned i;
  unsigned relogio;
  unsigned delta;

  if (((vertice > grafo->numVertices) || (vertice < 0)) && (!todos))
  {
    return false;
  }

  percurso->vertex = (RegistroVertices *) malloc(grafo->numVertices * sizeof(
                       RegistroVertices));
  percurso->ordemTopologica = (unsigned *) malloc(grafo->numVertices * sizeof(
                                unsigned));

  for (i = 0; i < grafo->numVertices; i++)
  {
    percurso->vertex[i].corTrabalho = BRANCO;
    percurso->vertex[i].pai        = UINT_MAX;
    percurso->vertex[i].descoberta = UINT_MAX;
    percurso->vertex[i].termino    = UINT_MAX;
    percurso->ordemTopologica[i]   = UINT_MAX;
  }

  relogio = -1;
  percurso->numDestinos = 0;
  percurso->DAG = true;

  if (!todos)
  {
    __percurso_profundidade(grafo, vertice, UINT_MAX, percurso, &relogio);
  }
  else
  {
    for (i = 0; i < grafo->numVertices; i++)
    {
      if (percurso->vertex[i].corTrabalho == BRANCO)
      {
        __percurso_profundidade(grafo, i, UINT_MAX, percurso, &relogio);
      }
    }
  }

  // Se for um DAG, tem ordem topologica
  // Entao, trazer os indices dos vertices para o inicio do vetor
  if (percurso->DAG)
  {
    delta = grafo->numVertices - percurso->numDestinos;

    for (i = 0; i < percurso->numDestinos; i++)
    {
      percurso->ordemTopologica[i] = percurso->ordemTopologica[i + delta];
    }

    // TODO: reescrever essa parte com realloc de dfs->OrdemTopologica
    for (; i < grafo->numVertices; i++)
    {
      percurso->ordemTopologica[i] = UINT_MAX;
    }
  }
  else
  {
    free(percurso->ordemTopologica);
  }

  return true;
}

bool destroi_percurso_profundidade(PercursoDFS *percurso)
{
  free(percurso->vertex);

  if (percurso->DAG)
  {
    free(percurso->ordemTopologica);
  }

  return true;
}

void
__percurso_profundidade(const TipoGrafo *grafo, unsigned vertice,
                        unsigned pai, PercursoDFS *percurso,
                        unsigned *relogio)
{
  unsigned i, v;
  ListaVerticesAdjacentes adjacentes;
  *relogio = *relogio + 1;
  percurso->vertex[vertice].corTrabalho = CINZA;
  percurso->vertex[vertice].descoberta = *relogio;
  obter_lista_adjacentes(grafo, vertice, &adjacentes, false);

  for (i = 0; i < adjacentes.numAdjacentes; i++)
  {
    v = adjacentes.listaDeVertices[i].vertice;

    switch (percurso->vertex[v].corTrabalho)
    {
      case CINZA: // Aresta de retorno
        //Se acho outro que esta sendo processado, o grafo
        // eh ciclico, entao deixa de ser um DAG
        percurso->DAG = false;
        break;

      case BRANCO: // Aresta de arvore
        percurso->vertex[v].pai = vertice;
        __percurso_profundidade(grafo, v, vertice, percurso, relogio);
        break;

      case PRETO: // Aresta de avanco ou de cruzamento
        break;

      default:
        break;
    }
  }

  destroi_lista_adjacentes(&adjacentes);
  *relogio = *relogio + 1;
  percurso->vertex[vertice].corTrabalho = PRETO;
  percurso->vertex[vertice].termino = *relogio;
  percurso->numDestinos = percurso->numDestinos + 1;

  // Insere o vertice na cabeca da lista de ordenacao topologica, se ainda for DAG
  if (percurso->DAG)
  {
    percurso->ordemTopologica[grafo->numVertices - percurso->numDestinos] =
      vertice;
  }
}

bool arvore_geradora_minima_prim(const TipoGrafo *grafo, unsigned vertice,
                                 ArvoreGeradoraMinima *arvore)
{
  unsigned i, j, nv;
  unsigned to, from;
  bool *pertenceMST;
  int peso;
  ListaVerticesAdjacentes adjacentes;

  if ((vertice > grafo->numVertices) || (vertice < 0) || (grafo->direcionado))
  {
    return false;
  }

  pertenceMST = (bool *) malloc(grafo->numVertices * sizeof(bool));
  arvore->custo = (int *) malloc(grafo->numVertices * sizeof(int));
  arvore->pai = (unsigned *) malloc(grafo->numVertices * sizeof(unsigned));

  for (i = 0; i < grafo->numVertices; i++)
  {
    pertenceMST[i] = false;
    arvore->custo[i] = INT_MAX;
  }

  arvore->custo[vertice] = INT_MIN;
  arvore->pai[vertice] = UINT_MAX;
  arvore->numArestas = 0;
  nv = grafo->numVertices - 1;

  for (i = 0; i < nv; i++)
  {
    from = minKey(arvore->custo, pertenceMST, grafo->numVertices);
    pertenceMST[from] = true;
    arvore->numArestas++;
    obter_lista_adjacentes(grafo, from, &adjacentes, false);

    for (j = 0; j < adjacentes.numAdjacentes; j++)
    {
      to = adjacentes.listaDeVertices[j].vertice;
      peso = adjacentes.listaDeVertices[j].peso;

      if ((!pertenceMST[to]) && (peso < arvore->custo[to]))
      {
        arvore->pai[to] = from;
        arvore->custo[to] = peso;
      }
    }

    destroi_lista_adjacentes(&adjacentes);
  }

  arvore->pesoTotal = 0L;

  for (i = 0; i < grafo->numVertices; i++)
    arvore->pesoTotal = arvore->pesoTotal + (arvore->pai[i] != UINT_MAX ?
                        arvore->custo[i] :
                        0);

  free(pertenceMST);
  // Arvore geradora minima tem que ter o minimo de arestas para ligar
  // todos os nos do grafo. Se nao tiver exatamente isso, ou tem algo
  // errado aqui, e apareceu um ciclo, ou o grafo nao eh conectado
  return (arvore->numArestas == nv);
}

bool destroi_arvore_geradora_minima(ArvoreGeradoraMinima *arvore)
{
  free(arvore->pai);
  free(arvore->custo);
  return true;
}

unsigned minKey(const int *custo, const bool *pertenceArvoreGeradora,
                unsigned numeroVertices)
{
  int min;
  unsigned min_index, vertice;
  min = INT_MAX;
  min_index = UINT_MAX;

  for (vertice = 0; vertice < numeroVertices; vertice++)
    if ((!pertenceArvoreGeradora[vertice]) && (custo[vertice] < min))
    {
      min = custo[vertice];
      min_index = vertice;
    }

  return min_index;
}

bool calcula_melhor_caminho_Dijkstra(const TipoGrafo *grafo,
                                     unsigned verticeOrigem, Caminho **caminho)
{
  unsigned i, j;
  unsigned vertice;
  int peso;
  int menor;

  if ((verticeOrigem > grafo->numVertices) || (verticeOrigem < 0))
  {
    return false;
  }

  *caminho = (Caminho *) malloc(grafo->numVertices * sizeof(Caminho));

  for (i = 0; i < grafo->numVertices; i++)
  {
    (*caminho)[i].custo = INT_MAX;
    (*caminho)[i].pai = UINT_MAX;
    (*caminho)[i].tamanho = 0;
    (*caminho)[i].cor = BRANCO;
  }

  (*caminho)[verticeOrigem].custo = 0;
  (*caminho)[verticeOrigem].pai = verticeOrigem;

  for (i = 0; i < grafo->numVertices; i++)
  {
    menor = INT_MAX;
    vertice = i;

    for (j = 0; j < grafo->numVertices; j++)
      if (((*caminho)[j].cor == BRANCO) && ((*caminho)[j].custo <= menor))
      {
        menor = (*caminho)[j].custo;
        vertice = j;
      }

    (*caminho)[vertice].cor = CINZA;

    for (j = 0; j < grafo->numVertices; j++)
    {
      obter_peso_aresta(grafo, vertice, j, &peso);

      if ((peso != 0) &&
          ((*caminho)[j].cor == BRANCO) &&
          ((*caminho)[vertice].custo != INT_MAX) &&
          (((*caminho)[vertice].custo + peso) < (*caminho)[j].custo))
      {
        (*caminho)[j].custo = (*caminho)[vertice].custo + peso;
        (*caminho)[j].pai = vertice;
      }
    }

    (*caminho)[vertice].cor = PRETO;
  }

  return true;
}

bool obtem_melhor_caminho(const TipoGrafo *grafo, unsigned verticeOrigem,
                          unsigned verticeDestino, Caminho *caminhos,
                          int *custo, unsigned **vertices, unsigned *tamanho)
{
  unsigned quantos, i, j;
  unsigned proximo;

  if ((verticeDestino > grafo->numVertices) || (verticeDestino < 0) ||
      (verticeOrigem == verticeDestino))
  {
    return false;
  }

  *vertices = (unsigned *) malloc(grafo->numVertices * sizeof(unsigned));
  quantos = 0;
  proximo = verticeDestino;
  (*vertices)[quantos++] = verticeDestino;

  do
  {
    proximo = caminhos[proximo].pai;
    (*vertices)[quantos++] = proximo;
  } while (proximo != verticeOrigem);

  *custo = caminhos[verticeDestino].custo;
  *tamanho = quantos;
  *vertices = realloc(*vertices, quantos * sizeof(unsigned));
  i = 0;
  j = quantos - 1;

  while (i < j)
  {
    swap((*vertices)[i], (*vertices)[j]);
    i++;
    j--;
  }

  return true;
}

bool colorir_grafo(const TipoGrafo *grafo, unsigned **vetorCores)
{
  unsigned i, j, k, cor;
  RegistroVertices *vertices;
  ListaVerticesAdjacentes naoadjacentes, adjacentes;

  if (grafo->numVertices == 0)
  {
    return false;
  }

  vertices = (RegistroVertices *) malloc(grafo->numVertices * sizeof(
      RegistroVertices));
  *vetorCores = (unsigned *) malloc(grafo->numVertices * sizeof(unsigned));

  for (i = 0; i < grafo->numVertices; i++)
  {
    vertices[i].vertice = i;
    obter_grau_vertice(grafo, i, NULL, &vertices[i].grauSaida);
    (*vetorCores)[i] = UINT_MAX;
  }

  ordenar_lista_vertices_grau(vertices, GRAU_SAIDA, grafo->numVertices, true);
  cor = UINT_MAX;

  for (i = 0; i < grafo->numVertices; i++)
  {
    // Pulando o vertice vertices[i].vertice, pois ja esta pintado
    if ((*vetorCores)[vertices[i].vertice] != UINT_MAX)
    {
      continue;
    }

    // Incrementando a cor
    cor++;
    // Pintando e processando vertice vertices[i].vertice da cor cor
    (*vetorCores)[vertices[i].vertice] = cor;
    obter_lista_adjacentes(grafo, vertices[i].vertice, &naoadjacentes,
                           true);

    for (j = 0; j < naoadjacentes.numAdjacentes; j++)
    {
      if (naoadjacentes.listaDeVertices[j].vertice == vertices[i].vertice)
      {
        continue;
      }

      // Processando nao-adjacentes
      obter_lista_adjacentes(grafo, naoadjacentes.listaDeVertices[j].vertice,
                             &adjacentes,
                             false);

      // Pulando este, pois ja esta pintado
      if ((*vetorCores)[naoadjacentes.listaDeVertices[j].vertice] != UINT_MAX)
      {
        continue;
      }

      // Procurando nos adjacentes por gente com a mesma cor
      for (k = 0; k < adjacentes.numAdjacentes; k++)
      {
        // Parando, pois tem gente com a mesma cor do lado
        if ((*vetorCores)[adjacentes.listaDeVertices[k].vertice] == cor)
        {
          break;
        }
      }

      // Os adjacentes nao tem a cor que eu quero pintar, entao pinta
      if (k == adjacentes.numAdjacentes)
      {
        (*vetorCores)[naoadjacentes.listaDeVertices[j].vertice] = cor;
      }

      destroi_lista_adjacentes(&adjacentes);
    }

    destroi_lista_adjacentes(&naoadjacentes);
  }

  return true;
}

bool ordenar_lista_vertices_grau(RegistroVertices *vertices,
                                 TipoOrdenacao chave,
                                 unsigned tamanho, bool invertido)
{
  unsigned i, j;
  RegistroVertices temp;

  // TODO: escolher algoritmo de ordenacao mais eficiente

  if (tamanho <= 0)
  {
    return false;
  }

  for (i = 1; i < tamanho; i++)
  {
    temp = vertices[i];
    j = i;

    switch (chave)
    {
      case GRAU_SAIDA:
        if (invertido)
          while ((j > 0) && (temp.grauSaida > vertices[j - 1].grauSaida))
          {
            vertices[j] = vertices[j - 1];
            j--;
          }
        else
          while ((j > 0) && (temp.grauSaida < vertices[j - 1].grauSaida))
          {
            vertices[j] = vertices[j - 1];
            j--;
          }

        break;

      case GRAU_ENTRADA:
        if (invertido)
          while ((j > 0) && (temp.grauEntrada > vertices[j - 1].grauEntrada))
          {
            vertices[j] = vertices[j - 1];
            j--;
          }
        else
          while ((j > 0) && (temp.grauEntrada < vertices[j - 1].grauEntrada))
          {
            vertices[j] = vertices[j - 1];
            j--;
          }

        break;

      default:
        return false;
    }

    vertices[j] = temp;
  }

  return true;
}
