#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <grafo.h>
#include <stdbool.h>

bool cria_grafo(TipoGrafo *grafo, unsigned maximoVertices, bool direcionado, bool ponderado)
{
  if ((maximoVertices > MAXNUMVERTICES) || (maximoVertices < 1))
  {
    return false;
  }

  grafo->maxVertices = maximoVertices;
  grafo->numVertices = 0;
  grafo->numArestas = 0;
  grafo->direcionado = direcionado;
  grafo->ponderado = ponderado;
  // Alocando dinamicamente a matriz de adjacencias
  grafo->matriz = (int **) malloc(maximoVertices * sizeof(int *));

  for (unsigned i = 0; i < grafo->maxVertices; i++)
  {
    grafo->matriz[i] = (int *) malloc(maximoVertices * sizeof(int));

    for (unsigned j = 0; j < grafo->maxVertices; j++)
    {
      grafo->matriz[i][j] = 0;
    }
  }

  // Alocando dinamicamente o vetor de rotulos
  grafo->rotulos = (char **) malloc(grafo->maxVertices * sizeof(char *));

  for (unsigned i = 0; i < grafo->maxVertices; i++)
  {
    grafo->rotulos[i] = (char *) malloc((MAXTAMROTULO + 1) * sizeof(char));
    memset(grafo->rotulos[i], '\0', (size_t) MAXTAMROTULO + 1);
  }

  return true;
}

bool destroi_grafo(TipoGrafo *grafo)
{
  for (unsigned i = 0; i < grafo->maxVertices; i++)
  {
    free(grafo->rotulos[i]);
    free(grafo->matriz[i]);
  }

  free(grafo->rotulos);
  free(grafo->matriz);
  return true;
}

bool insere_aresta(TipoGrafo *grafo, unsigned verticeOrigem, unsigned verticeDestino, int peso)
{
  if ((grafo->numVertices == 0) || (verticeOrigem > grafo->numVertices) || (verticeDestino > grafo->numVertices) ||
      (grafo->numArestas == MAXNUMARESTAS))
  {
    return false;
  }

  if ((grafo->ponderado) && (peso == 0))
  {
    return false;
  }

  grafo->matriz[verticeOrigem][verticeDestino] = grafo->ponderado ? peso : 1;
  if (!grafo->direcionado)
  {
    grafo->matriz[verticeDestino][verticeOrigem] = grafo->ponderado ? peso : 1;
  }

  grafo->numArestas++;
  return true;
}

bool insere_vertice(TipoGrafo *grafo, char *rotulo, size_t tamanho, unsigned *numeroVerticeInserido)
{
  if ((grafo->numVertices == MAXNUMVERTICES) || (tamanho > MAXTAMROTULO))
  {
    return false;
  }

  *numeroVerticeInserido = grafo->numVertices;
  memset(grafo->rotulos[*numeroVerticeInserido], '\0', MAXTAMROTULO);
  strncpy(grafo->rotulos[*numeroVerticeInserido], rotulo, tamanho);
  grafo->numVertices++;
  return true;
}

bool remove_aresta(TipoGrafo *grafo, unsigned verticeOrigem, unsigned verticeDestino, int *peso)
{
  if ((grafo->numVertices == 0) || (verticeOrigem > grafo->numVertices) || (verticeDestino > grafo->numVertices))
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

bool existe_aresta(const TipoGrafo *grafo, unsigned verticeOrigem, unsigned verticeDestino)
{
  if ((grafo->numVertices == 0) || (verticeOrigem > grafo->numVertices) || (verticeDestino > grafo->numVertices))
  {
    return false;
  }

  return (grafo->matriz[verticeOrigem][verticeDestino] != 0);
}

void imprime_grafo(const TipoGrafo *grafo)
{
  printf("----------------------------------------\n");
  printf("Rotulos dos vertices\n");
  printf("--------------------\n");

  for (unsigned i = 0; i < grafo->numVertices; i++)
  {
    printf("Vertice %u: %s\n", i, grafo->rotulos[i]);
  }

  printf("--------------------\n");
  printf("\n");
  printf("   ");

  for (unsigned i = 0; i < grafo->numVertices; i++)
  {
    printf("%3d", i);
  }

  printf("\n");

  for (unsigned i = 0; i < grafo->numVertices; i++)
  {
    printf("%3d", i);

    for (unsigned j = 0; j < grafo->numVertices; j++)
    {
      printf("%3d", grafo->matriz[i][j]);
    }

    printf("\n");
  }

  printf("----------------------------------------\n");
}

void gera_graphviz(const TipoGrafo *grafo)
{
  int peso;

  if (grafo->direcionado)
  {
    printf("digraph G {\n");
  }
  else
  {
    printf("graph G {\n");
  }
  printf("  node [shape=circle];\n");

  for (unsigned i = 0; i < grafo->numVertices; i++)
  {
    printf("  \"%s\";\n", grafo->rotulos[i]);
  }
  for (unsigned de = 0; de < grafo->numVertices; de++)
  {
    for (unsigned para = 0; para < grafo->numVertices; para++)
    {
      if (grafo->matriz[de][para] != 0)
      {
        printf("  \"%s\" %s \"%s\"", grafo->rotulos[de], grafo->direcionado ? "->" : "--", grafo->rotulos[para]);
        if (grafo->ponderado)
        {
          obter_peso_aresta(grafo, de, para, &peso);
          printf(" [label=%d]", peso);
        }
        printf(";\n");
      }
    }
  }
  printf("}\n");
}

bool obter_peso_aresta(const TipoGrafo *grafo, unsigned verticeOrigem, unsigned verticeDestino, int *peso)
{
  if ((grafo->numVertices == 0) || (verticeOrigem > grafo->numVertices) || (verticeDestino > grafo->numVertices))
  {
    return false;
  }

  *peso = grafo->matriz[verticeOrigem][verticeDestino];
  return true;
}

bool alterar_peso_aresta(const TipoGrafo *grafo, unsigned verticeOrigem, unsigned verticeDestino, int peso)
{
  if ((grafo->numVertices == 0) || (verticeOrigem > grafo->numVertices) || (verticeDestino > grafo->numVertices) ||
      (peso == 0))
  {
    return false;
  }

  if (!existe_aresta(grafo, verticeOrigem, verticeDestino))
  {
    return false;
  }

  grafo->matriz[verticeOrigem][verticeDestino] = peso;
  return true;
}

bool obter_lista_adjacentes(const TipoGrafo *grafo, unsigned vertice, ListaVerticesAdjacentes *listaAdjacentes,
                            bool complemento)
{
  int peso;

  if ((grafo->numVertices == 0) || (vertice > grafo->numVertices))
  {
    return false;
  }

  listaAdjacentes->numAdjacentes = 0;
  listaAdjacentes->listaDeVertices = (RegistroVertices *) malloc(grafo->numVertices * sizeof(RegistroVertices));

  // complemento == true --> lista de NAO adjacentes
  if (!complemento)
  {
    for (unsigned i = 0; i < grafo->numVertices; i++)
    {
      if (existe_aresta(grafo, vertice, i))
      {
        obter_peso_aresta(grafo, vertice, i, &peso);
        listaAdjacentes->listaDeVertices[listaAdjacentes->numAdjacentes].vertice = i;
        listaAdjacentes->listaDeVertices[listaAdjacentes->numAdjacentes].peso = peso;
        listaAdjacentes->numAdjacentes++;
      }
    }
  }
  else
  {
    for (unsigned i = 0; i < grafo->numVertices; i++)
    {
      if (!existe_aresta(grafo, vertice, i))
      {
        listaAdjacentes->listaDeVertices[listaAdjacentes->numAdjacentes].vertice = i;
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

bool obter_grau_vertice(const TipoGrafo *grafo, unsigned vertice, unsigned *grauEntrada, unsigned *grauSaida)
{
  if ((grafo->numVertices == 0) || (vertice > grafo->numVertices))
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

  for (unsigned i = 0; i < grafo->numVertices; i++)
  {
    if (grauSaida)
    {
      if (existe_aresta(grafo, vertice, i))
      {
        *grauSaida = *grauSaida + 1;
      }
    }

    if (grauEntrada)
    {
      if (existe_aresta(grafo, i, vertice))
      {
        *grauEntrada = *grauEntrada + 1;
      }
    }
  }

  return true;
}

bool BFS(const TipoGrafo *grafo, unsigned vertice, PercursoBFS *percurso)
{
  unsigned verticeDeTrabalho, verticeAdjacente;
  unsigned *fila;
  unsigned int inicio, final;
  ListaVerticesAdjacentes adjacentes;

  if ((grafo->numVertices == 0) || (vertice > grafo->numVertices))
  {
    return false;
  }

  fila = (unsigned *) malloc(grafo->numVertices * sizeof(unsigned));
  inicio = final = 0;

  percurso->vertex = (RegistroVertices *) malloc(grafo->numVertices * sizeof(RegistroVertices));

  for (unsigned i = 0; i < grafo->numVertices; i++)
  {
    percurso->vertex[i].corTrabalho = NAO_PROCESSADO;
    percurso->vertex[i].pai = UINT_MAX;
    percurso->vertex[i].distancia = UINT_MAX;
  }

  percurso->verticeOrigem = vertice;
  percurso->numDestinos = 0;
  percurso->vertex[vertice].corTrabalho = EM_PROCESSAMENTO;
  percurso->vertex[vertice].distancia = 0;
  fila[final++] = vertice;

  while (inicio != final)
  {
    verticeDeTrabalho = fila[inicio++];
    obter_lista_adjacentes(grafo, verticeDeTrabalho, &adjacentes, false);

    for (unsigned i = 0; i < adjacentes.numAdjacentes; i++)
    {
      verticeAdjacente = adjacentes.listaDeVertices[i].vertice;

      if (percurso->vertex[verticeAdjacente].corTrabalho == NAO_PROCESSADO)
      {
        percurso->vertex[verticeAdjacente].corTrabalho = EM_PROCESSAMENTO;
        percurso->vertex[verticeAdjacente].distancia = percurso->vertex[verticeDeTrabalho].distancia + 1;
        percurso->vertex[verticeAdjacente].pai = verticeDeTrabalho;
        fila[final++] = verticeAdjacente;
      }
    }

    percurso->vertex[verticeDeTrabalho].corTrabalho = PROCESSADO;
    percurso->numDestinos = percurso->numDestinos + 1;
    destroi_lista_adjacentes(&adjacentes);
  }

  free(fila);
  return true;
}

bool destroi_BFS(PercursoBFS *percurso)
{
  free(percurso->vertex);
  return true;
}

bool DFS(const TipoGrafo *grafo, unsigned vertice, PercursoDFS *percurso, bool todos)
{
  unsigned relogio;
  unsigned delta;

  if ((grafo->numVertices == 0) || (vertice > grafo->numVertices) && (!todos))
  {
    return false;
  }

  percurso->vertex = (RegistroVertices *) malloc(grafo->numVertices * sizeof(RegistroVertices));
  percurso->ordemTopologica = (unsigned *) malloc(grafo->numVertices * sizeof(unsigned));

  for (unsigned i = 0; i < grafo->numVertices; i++)
  {
    percurso->vertex[i].corTrabalho = NAO_PROCESSADO;
    percurso->vertex[i].pai = UINT_MAX;
    percurso->vertex[i].descoberta = UINT_MAX;
    percurso->vertex[i].termino = UINT_MAX;
    percurso->ordemTopologica[i] = UINT_MAX;
  }

  relogio = 0;
  percurso->numDestinos = 0;
  percurso->DAG = true;

  if (!todos)
  {
    DFS_um_no(grafo, vertice, UINT_MAX, percurso, &relogio);
  }
  else
  {
    for (unsigned i = 0; i < grafo->numVertices; i++)
    {
      if (percurso->vertex[i].corTrabalho == NAO_PROCESSADO)
      {
        DFS_um_no(grafo, i, UINT_MAX, percurso, &relogio);
      }
    }
  }

  // Se for um DAG, tem ordem topologica
  // Entao, trazer os indices dos vertices para o inicio do vetor
  if (percurso->DAG)
  {
    delta = grafo->numVertices - percurso->numDestinos;

    // TODO: reescrever essa parte com realloc de dfs->OrdemTopologica
    unsigned i;
    for (i = 0; i < percurso->numDestinos; i++)
    {
      percurso->ordemTopologica[i] = percurso->ordemTopologica[i + delta];
    }
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

bool destroi_DFS(PercursoDFS *percurso)
{
  free(percurso->vertex);

  if (percurso->DAG)
  {
    free(percurso->ordemTopologica);
  }

  return true;
}

void DFS_um_no(const TipoGrafo *grafo, unsigned vertice, unsigned pai, PercursoDFS *percurso, unsigned *relogio)
{
  unsigned verticeAdjacente;
  ListaVerticesAdjacentes adjacentes;

  *relogio = *relogio + 1;
  percurso->vertex[vertice].corTrabalho = EM_PROCESSAMENTO;
  percurso->vertex[vertice].descoberta = *relogio;
  percurso->vertex[vertice].pai = pai;

  obter_lista_adjacentes(grafo, vertice, &adjacentes, false);
  for (unsigned i = 0; i < adjacentes.numAdjacentes; i++)
  {
    verticeAdjacente = adjacentes.listaDeVertices[i].vertice;

    switch (percurso->vertex[verticeAdjacente].corTrabalho)
    {
      case EM_PROCESSAMENTO: // Aresta de retorno
        // Se acho outro que esta sendo processado, o grafo
        // eh ciclico, entao deixa de ser um DAG
        percurso->DAG = false;
        break;

      case NAO_PROCESSADO: // Aresta de arvore
        percurso->vertex[verticeAdjacente].pai = vertice;
        DFS_um_no(grafo, verticeAdjacente, vertice, percurso, relogio);
        break;

      case PROCESSADO: // Aresta de avanco ou de cruzamento

      default:
        break;
    }
  }
  destroi_lista_adjacentes(&adjacentes);

  *relogio = *relogio + 1;
  percurso->vertex[vertice].corTrabalho = PROCESSADO;
  percurso->vertex[vertice].termino = *relogio;
  percurso->numDestinos = percurso->numDestinos + 1;

  // Insere o vertice na cabeca da lista de ordenacao topologica, se ainda for DAG
  if (percurso->DAG)
  {
    percurso->ordemTopologica[grafo->numVertices - percurso->numDestinos] = vertice;
  }
}

bool arvore_geradora_minima_prim(const TipoGrafo *grafo, unsigned vertice, ArvoreGeradoraMinima *arvore)
{
  unsigned nv;
  unsigned de, para;
  int peso;
  bool *pertenceMST;
  ListaVerticesAdjacentes adjacentes;

  if ((grafo->numVertices == 0) || (vertice > grafo->numVertices) || (grafo->direcionado))
  {
    return false;
  }

  pertenceMST = (bool *) malloc(grafo->numVertices * sizeof(bool));
  arvore->custo = (int *) malloc(grafo->numVertices * sizeof(int));
  arvore->pai = (unsigned *) malloc(grafo->numVertices * sizeof(unsigned));

  for (unsigned i = 0; i < grafo->numVertices; i++)
  {
    pertenceMST[i] = false;
    arvore->custo[i] = INT_MAX;
  }

  arvore->custo[vertice] = INT_MIN;
  arvore->pai[vertice] = UINT_MAX;
  arvore->numArestas = 0;
  nv = grafo->numVertices - 1;

  for (unsigned i = 0; i < nv; i++)
  {
    de = minKey(arvore->custo, pertenceMST, grafo->numVertices);
    pertenceMST[de] = true;
    arvore->numArestas++;

    obter_lista_adjacentes(grafo, de, &adjacentes, false);
    for (unsigned j = 0; j < adjacentes.numAdjacentes; j++)
    {
      para = adjacentes.listaDeVertices[j].vertice;
      peso = adjacentes.listaDeVertices[j].peso;

      if ((!pertenceMST[para]) && (peso < arvore->custo[para]))
      {
        arvore->pai[para] = de;
        arvore->custo[para] = peso;
      }
    }
    destroi_lista_adjacentes(&adjacentes);
  }

  arvore->pesoTotal = 0L;

  for (unsigned i = 0; i < grafo->numVertices; i++)
  {
    arvore->pesoTotal = arvore->pesoTotal + (arvore->pai[i] != UINT_MAX ? arvore->custo[i] : 0);
  }

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

unsigned minKey(const int *custo, const bool *pertenceArvoreGeradora, unsigned numeroVertices)
{
  int min;
  unsigned min_index, vertice;
  min = INT_MAX;
  min_index = UINT_MAX;

  for (vertice = 0; vertice < numeroVertices; vertice++)
  {
    if ((!pertenceArvoreGeradora[vertice]) && (custo[vertice] < min))
    {
      min = custo[vertice];
      min_index = vertice;
    }
  }

  return min_index;
}

bool calcula_melhor_caminho_Dijkstra(const TipoGrafo *grafo, unsigned verticeOrigem, Caminho **caminho)
{
  unsigned vertice;
  unsigned int menor;
  int peso;

  if ((grafo->numVertices == 0) || (verticeOrigem > grafo->numVertices))
  {
    return false;
  }

  *caminho = (Caminho *) malloc(grafo->numVertices * sizeof(Caminho));

  for (unsigned i = 0; i < grafo->numVertices; i++)
  {
    (*caminho)[i].custo = INT_MAX;
    (*caminho)[i].pai = UINT_MAX;
    (*caminho)[i].tamanho = 0;
    (*caminho)[i].cor = NAO_PROCESSADO;
  }

  (*caminho)[verticeOrigem].custo = 0;
  (*caminho)[verticeOrigem].pai = verticeOrigem;

  for (unsigned i = 0; i < grafo->numVertices; i++)
  {
    menor = INT_MAX;
    vertice = i;

    for (unsigned j = 0; j < grafo->numVertices; j++)
    {
      if (((*caminho)[j].cor == NAO_PROCESSADO) && ((*caminho)[j].custo <= menor))
      {
        menor = (*caminho)[j].custo;
        vertice = j;
      }
    }

    (*caminho)[vertice].cor = EM_PROCESSAMENTO;

    for (unsigned j = 0; j < grafo->numVertices; j++)
    {
      obter_peso_aresta(grafo, vertice, j, &peso);

      if ((peso != 0) && ((*caminho)[j].cor == NAO_PROCESSADO) && ((*caminho)[vertice].custo != INT_MAX) &&
          (((*caminho)[vertice].custo + peso) < (*caminho)[j].custo))
      {
        (*caminho)[j].custo = (*caminho)[vertice].custo + peso;
        (*caminho)[j].pai = vertice;
      }
    }

    (*caminho)[vertice].cor = PROCESSADO;
  }

  return true;
}

bool obtem_melhor_caminho(const TipoGrafo *grafo, unsigned verticeOrigem, unsigned verticeDestino, Caminho *caminhos,
                          unsigned int *custo, unsigned **vertices, unsigned *tamanho)
{
  unsigned quantos, i, j;
  unsigned proximo;

  if ((grafo->numVertices == 0) || (verticeDestino > grafo->numVertices) || (verticeOrigem == verticeDestino))
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
  unsigned cor;
  unsigned verticeAdjacente;
  RegistroVertices *vertices;
  ListaVerticesAdjacentes naoadjacentes, adjacentes;

  if (grafo->numVertices == 0)
  {
    return false;
  }

  vertices = (RegistroVertices *) malloc(grafo->numVertices * sizeof(RegistroVertices));
  *vetorCores = (unsigned *) malloc(grafo->numVertices * sizeof(unsigned));

  for (unsigned vertice = 0; vertice < grafo->numVertices; vertice++)
  {
    vertices[vertice].vertice = vertice;
    obter_grau_vertice(grafo, vertice, NULL, &vertices[vertice].grauSaida);
    (*vetorCores)[vertice] = UINT_MAX;
  }

  ordenar_lista_vertices_grau(vertices, GRAU_SAIDA, grafo->numVertices, true);
  cor = UINT_MAX;

  for (unsigned vertice = 0; vertice < grafo->numVertices; vertice++)
  {
    // Pulando o vertice vertices[vertice].vertice, pois ja esta pintado
    if ((*vetorCores)[vertices[vertice].vertice] != UINT_MAX)
    {
      continue;
    }

    // Incrementando a cor
    cor++;
    // Pintando e processando vertice vertices[vertice].vertice da cor cor
    (*vetorCores)[vertices[vertice].vertice] = cor;

    obter_lista_adjacentes(grafo, vertices[vertice].vertice, &naoadjacentes, true);
    for (unsigned verticeNaoAdjacente = 0; verticeNaoAdjacente < naoadjacentes.numAdjacentes; verticeNaoAdjacente++)
    {
      if (naoadjacentes.listaDeVertices[verticeNaoAdjacente].vertice == vertices[vertice].vertice)
      {
        continue;
      }

      // Pulando este, pois ja esta pintado
      if ((*vetorCores)[naoadjacentes.listaDeVertices[verticeNaoAdjacente].vertice] != UINT_MAX)
      {
        continue;
      }

      // Processando nao-adjacentes
      obter_lista_adjacentes(grafo, naoadjacentes.listaDeVertices[verticeNaoAdjacente].vertice, &adjacentes, false);

      // Procurando nos adjacentes por gente com a mesma cor
      for (verticeAdjacente = 0; verticeAdjacente < adjacentes.numAdjacentes; verticeAdjacente++)
      {
        // Parando, pois tem gente com a mesma cor do lado
        if ((*vetorCores)[adjacentes.listaDeVertices[verticeAdjacente].vertice] == cor)
        {
          break;
        }
      }

      // Os adjacentes nao tem a cor que eu quero pintar, entao pinta
      if (verticeAdjacente == adjacentes.numAdjacentes)
      {
        (*vetorCores)[naoadjacentes.listaDeVertices[verticeNaoAdjacente].vertice] = cor;
      }

      destroi_lista_adjacentes(&adjacentes);
    }

    destroi_lista_adjacentes(&naoadjacentes);
  }

  return true;
}

bool ordenar_lista_vertices_grau(RegistroVertices *vertices, TipoOrdenacao chave, unsigned tamanho, bool invertido)
{
  unsigned i, j;
  RegistroVertices temp;

  // TODO: escolher algoritmo de ordenacao mais eficiente
  if (tamanho < 1)
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
        {
          while ((j > 0) && (temp.grauSaida > vertices[j - 1].grauSaida))
          {
            vertices[j] = vertices[j - 1];
            j--;
          }
        }
        else
        {
          while ((j > 0) && (temp.grauSaida < vertices[j - 1].grauSaida))
          {
            vertices[j] = vertices[j - 1];
            j--;
          }
        }

        break;

      case GRAU_ENTRADA:
        if (invertido)
        {
          while ((j > 0) && (temp.grauEntrada > vertices[j - 1].grauEntrada))
          {
            vertices[j] = vertices[j - 1];
            j--;
          }
        }
        else
        {
          while ((j > 0) && (temp.grauEntrada < vertices[j - 1].grauEntrada))
          {
            vertices[j] = vertices[j - 1];
            j--;
          }
        }

        break;

      default:
        return false;
    }

    vertices[j] = temp;
  }

  return true;
}
