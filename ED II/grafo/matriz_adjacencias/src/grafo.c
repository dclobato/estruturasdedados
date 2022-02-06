//
// Created by danie on 05/08/2020.
//
#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>

bool criar_grafo(GRAFO *grafo, unsigned int max_vertices, bool direcionado, bool ponderado)
{
  if (max_vertices < 1)
  {
    return false;
  }

  grafo->max_vertices = max_vertices;
  grafo->num_vertices = 0;
  grafo->num_arestas = 0;
  grafo->direcionado = direcionado;
  grafo->ponderado = ponderado;
  grafo->cores = NULL; // Inicialmente, sem o vetor com as cores dos vertices

  // Alocar dinamicamente a matriz de adjacencias
  grafo->matriz = (int **) malloc(max_vertices * sizeof(int *));
  if (!grafo->matriz)
  {
    return false;
  }

  for (unsigned int de = 0; de < max_vertices; ++de)
  {
    grafo->matriz[de] = (int *) malloc(max_vertices * sizeof(int));
    if (!grafo->matriz[de])
    {
      destruir_grafo(grafo);
    }
    for (int para = 0; para < max_vertices; ++para)
    {
      grafo->matriz[de][para] = 0;
    }
  }

  // Alocar dinamicamente o vetor de rotulos
  grafo->rotulos = (char **) malloc(grafo->max_vertices * sizeof(char *));
  if (!grafo->rotulos)
  {
    destruir_grafo(grafo);
  }
  for (unsigned int de = 0; de < max_vertices; ++de)
  {
    grafo->rotulos[de] = NULL;
  }

  return true;
}

bool destruir_grafo(GRAFO *grafo)
{
  for (unsigned int de = 0; de < grafo->max_vertices; ++de)
  {
    if (grafo->rotulos[de])
    {
      free(grafo->rotulos[de]);
      grafo->rotulos[de] = NULL;
    }
    if (grafo->matriz[de])
    {
      free(grafo->matriz[de]);
      grafo->matriz[de] = NULL;
    }
  }

  if (grafo->matriz)
  {
    free(grafo->matriz);
    grafo->matriz = NULL;
  }

  if (grafo->rotulos)
  {
    free(grafo->rotulos);
    grafo->rotulos = NULL;
  }

  if (grafo->cores)
  {
    free(grafo->cores);
    grafo->cores = NULL;
  }

  return true;
}

bool adicionar_vertice(GRAFO *grafo, char *rotulo, size_t tamanho, unsigned int *numeroVerticeInserido)
{
  if (grafo->num_vertices == grafo->max_vertices)
  {
    return false;
  }

  if (numeroVerticeInserido)
  {
    *numeroVerticeInserido = grafo->num_vertices;
  }

  if (tamanho > 1)
  {
    grafo->rotulos[grafo->num_vertices] = (char *) malloc((tamanho + 1) * sizeof(char));
    if (!grafo->rotulos[grafo->num_vertices])
    {
      return false;
    }
    strncpy(grafo->rotulos[grafo->num_vertices], rotulo, tamanho);
  }

  grafo->num_vertices = grafo->num_vertices + 1;
  return true;
}

bool renomear_vertice(GRAFO *grafo, char *rotulo, size_t tamanho, unsigned int num_vertice)
{
  char *temp;

  if (num_vertice >= grafo->num_vertices)
  { // renomear vertice que nao existe, erro
    return false;
  }

  temp = (char *) malloc((tamanho + 1) * sizeof(char));
  if (!temp)
  {
    return false;
  }
  memset(temp, 0, tamanho + 1);

  strncpy(temp, rotulo, tamanho);
  if (grafo->rotulos[num_vertice])
  {
    free(grafo->rotulos[num_vertice]);
    grafo->rotulos[num_vertice] = NULL;
  }

  grafo->rotulos[num_vertice] = temp;
  return true;
}

void mostrar_rotulos(const GRAFO *grafo)
{
  printf("Vertice Rotulo\n");
  printf("------- ---- - -  -  -    -\n");
  for (unsigned int vertice = 0; vertice < grafo->num_vertices; vertice++)
  {
    printf("%7u %s\n", vertice, grafo->rotulos[vertice] ? grafo->rotulos[vertice] : "-- Nao definido --");
  }
  printf("------- ---- - -  -  -    -\n");
}

bool adicionar_aresta(GRAFO *grafo, unsigned int de, unsigned int para, int peso)
{
  if ((de > grafo->num_vertices) || (para > grafo->num_vertices) || (peso == 0))
  {
    return false;
  }

  // Grafo nao direcionado nao pode ter ciclo
  if ((de == para) && (!grafo->direcionado))
  {
    return false;
  }

  // ja existe a aresta. Mude o peso, e nao crie
  if (existe_aresta(grafo, de, para, NULL))
  {
    return false;
  }

  grafo->matriz[de][para] = peso;
  grafo->num_arestas = grafo->num_arestas + 1;
  if (!grafo->direcionado)
  {
    grafo->matriz[para][de] = peso;
  }
  return true;
}

bool remover_aresta(GRAFO *grafo, unsigned int de, unsigned int para)
{
  if ((de > grafo->num_vertices) || (para > grafo->num_vertices))
  {
    return false;
  }

  if (!existe_aresta(grafo, de, para, NULL))
  {
    return false;
  }

  grafo->matriz[de][para] = 0;
  grafo->num_arestas = grafo->num_arestas - 1;
  if (!grafo->direcionado)
  {
    grafo->matriz[para][de] = 0;
  }

  return true;
}

bool existe_aresta(const GRAFO *grafo, unsigned int de, unsigned int para, int *peso)
{
  if ((de > grafo->num_vertices) || (para > grafo->num_vertices))
  {
    return false;
  }

  if (peso)
  {
    *peso = grafo->matriz[de][para];
  }
  return (grafo->matriz[de][para] != 0);
}

bool buscar_em_largura(const GRAFO *grafo, int origem, RSLT_BUSCA *resultado_busca)
{
  unsigned int *fila;
  int inicio, final;
  unsigned int de;
  inicio = 0;
  final = 0;

  if (origem > grafo->num_vertices)
  {
    return false;
  }

  if (grafo->num_vertices < 1)
  {
    return false;
  }

  fila = (unsigned int *) malloc(grafo->num_vertices * sizeof(unsigned int));
  if (!fila)
  {
    return false;
  }

  for (int i = 0; i < grafo->num_vertices; i++)
  {
    resultado_busca->vertices[i].estadoVertice = NAO_PROCESSADO;
    resultado_busca->vertices[i].descoberta = UINT_MAX;
    resultado_busca->vertices[i].pai = UINT_MAX;
  }
  resultado_busca->num_vertices = 0;

  resultado_busca->vertices[origem].estadoVertice = EM_PROCESSAMENTO;
  resultado_busca->vertices[origem].descoberta = 0;

  // enfileirar
  fila[final++] = origem;

  while (inicio != final)
  {
    // desenfileirar
    de = fila[inicio];
    inicio = inicio + 1;
    for (unsigned int para = 0; para < grafo->num_vertices; para++)
    {
      // é adjacente
      if (existe_aresta(grafo, de, para, NULL))
      {
        if (resultado_busca->vertices[para].estadoVertice == NAO_PROCESSADO)
        {
          resultado_busca->vertices[para].estadoVertice = EM_PROCESSAMENTO;
          resultado_busca->vertices[para].descoberta = resultado_busca->vertices[de].descoberta + 1;
          resultado_busca->vertices[para].pai = de;
          // enfileirar
          fila[final++] = para;
        }
      }
    }
    resultado_busca->vertices[de].estadoVertice = PROCESSADO;
    resultado_busca->num_vertices = resultado_busca->num_vertices + 1;
  }
  free(fila);
  return true;
}

bool buscar_em_profundidade(const GRAFO *grafo, RSLT_BUSCA *resultado_busca)
{
  unsigned int tempo_global;

  // Preparacao dos nos, colocando todos nao processados e sem pai
  for (int vertice = 0; vertice < grafo->num_vertices; vertice++)
  {
    resultado_busca->vertices[vertice].estadoVertice = NAO_PROCESSADO;
    resultado_busca->vertices[vertice].pai = UINT_MAX;
  }
  resultado_busca->num_vertices = 0;
  resultado_busca->DAG = true;
  tempo_global = 0;

  for (unsigned int vertice = 0; vertice < grafo->num_vertices; vertice++)
  {
    if (resultado_busca->vertices[vertice].estadoVertice == NAO_PROCESSADO)
    {
      buscar_em_profundidade_visita(grafo, vertice, &tempo_global, resultado_busca);
    }
  }

  return true;
}

void buscar_em_profundidade_visita(const GRAFO *grafo, unsigned int de, unsigned int *relogio_global,
                                   RSLT_BUSCA *resultado_busca)
{
  *relogio_global = *relogio_global + 1;
  resultado_busca->vertices[de].descoberta = *relogio_global;
  resultado_busca->vertices[de].estadoVertice = EM_PROCESSAMENTO;

  // Varrer todos os vertices procurando adjacencia
  for (unsigned int para = 0; para < grafo->num_vertices; para++)
  {
    // eh adjacente
    if (existe_aresta(grafo, de, para, NULL))
    {
      if (resultado_busca->vertices[para].estadoVertice == EM_PROCESSAMENTO)
      {
        resultado_busca->DAG = false;
      }

      if (resultado_busca->vertices[para].estadoVertice == NAO_PROCESSADO)
      {
        resultado_busca->vertices[para].pai = de;
        buscar_em_profundidade_visita(grafo, para, relogio_global, resultado_busca);
      }
    }
  }
  resultado_busca->vertices[de].estadoVertice = PROCESSADO;
  resultado_busca->num_vertices = resultado_busca->num_vertices + 1;
  *relogio_global = *relogio_global + 1;
  resultado_busca->vertices[de].final = *relogio_global;
}

bool criar_ordenacao_topologica(const GRAFO *grafo, unsigned int **vertices)
{
  RSLT_BUSCA resultado;
  VERTEX temp;

  buscar_em_profundidade(grafo, &resultado);

  if (!resultado.DAG)
  {
    return false;
  }

  for (unsigned int vertice = 0; vertice < resultado.num_vertices; vertice++)
  {
    resultado.vertices[vertice].numeroDoVertice = vertice;
  }

  for (unsigned int ex = resultado.num_vertices - 1; ex > 0; ex--)
  {
    for (unsigned int in = 0; in < ex; in++)
    {
      if (resultado.vertices[in + 1].final >= resultado.vertices[in].final)
      {
        temp = resultado.vertices[in + 1];
        resultado.vertices[in + 1] = resultado.vertices[in];
        resultado.vertices[in] = temp;
      }
    }
  }

  *vertices = (unsigned int *) malloc(resultado.num_vertices * sizeof(unsigned int));
  if (!(*vertices))
  {
    return false;
  }
  for (unsigned int vertice = 0; vertice < resultado.num_vertices; vertice++)
  {
    *vertices[vertice] = resultado.vertices[vertice].numeroDoVertice;
  }
  return true;
}

void imprimir_grafo(const GRAFO *grafo)
{
  printf("%sgraph G {\n", grafo->direcionado ? "di" : "");
  printf("   node [shape = ellipse];\n");
  for (unsigned int vertice = 0; vertice < grafo->num_vertices; vertice++)
  {
    if (grafo->rotulos[vertice] == NULL)
    {
      printf("   %u", vertice);
    }
    else
    {
      printf("   \"%s\"", grafo->rotulos[vertice]);
    }

    if (grafo->cores)
    {
      printf(" [color = \"%s\"]", GRAFO_H_LISTA_CORES[grafo->cores[vertice] % GRAFO_H_TOTAL_DE_CORES]);
    }
    printf(";\n");
  }

  if (grafo->direcionado)
  {
    for (unsigned int linha = 0; linha < grafo->num_vertices; linha++)
    {
      for (unsigned int coluna = 0; coluna < grafo->num_vertices; coluna++)
      {
        if (existe_aresta(grafo, linha, coluna, NULL))
        {
          if (grafo->rotulos[linha])
          {
            printf("   \"%s\" -> ", grafo->rotulos[linha]);
          }
          else
          {
            printf("   %u -> ", linha);
          }

          if (grafo->rotulos[coluna] == NULL)
          {
            printf("\"%s\"", grafo->rotulos[coluna]);
          }
          else
          {
            printf("%u", coluna);
          }

          if (grafo->ponderado)
          {
            printf(" [label=\"%d\"];\n", grafo->matriz[linha][coluna]);
          }
          else
          {
            printf(";\n");
          }
        }
      }
    }
  }
  else
  {
    for (int linha = 0; linha < grafo->num_vertices; linha++)
    {
      for (int coluna = linha; coluna < grafo->num_vertices; coluna++)
      {
        if (existe_aresta(grafo, linha, coluna, NULL))
        {
          if (grafo->rotulos[linha])
          {
            printf("   \"%s\" -- ", grafo->rotulos[linha]);
          }
          else
          {
            printf("   %u -- ", linha);
          }

          if (grafo->rotulos[coluna])
          {
            printf("\"%s\"", grafo->rotulos[coluna]);
          }
          else
          {
            printf("%u", coluna);
          }

          if (grafo->ponderado)
          {
            printf(" [label=\"%d\"];\n", grafo->matriz[linha][coluna]);
          }
          else
          {
            printf(";\n");
          }
        }
      }
    }
  }
  printf("}\n");
}

bool criar_agm_prim(const GRAFO *grafo, unsigned int origem, ArvoreGeradoraMinima *arvore)
{
  bool *pertenceAGM;
  unsigned int de;
  int peso;

  if ((grafo->num_vertices == 0) || (origem > grafo->num_vertices))
  {
    return false;
  }

  pertenceAGM = (bool *) malloc(sizeof(bool) * grafo->num_vertices);
  if (!pertenceAGM)
  {
    return false;
  }

  arvore->pai = (unsigned int *) malloc(sizeof(unsigned int) * grafo->num_vertices);
  if (!arvore->pai)
  {
    free(pertenceAGM);
    return false;
  }

  arvore->custo = (int *) malloc(sizeof(int) * grafo->num_vertices);
  if (!arvore->custo)
  {
    free(pertenceAGM);
    free(arvore->pai);
    return false;
  }

  for (unsigned int vertice = 0; vertice < grafo->num_vertices; vertice++)
  {
    arvore->pai[vertice] = UINT_MAX;
    arvore->custo[vertice] = INT_MAX;
    pertenceAGM[vertice] = false;
  }

  arvore->custo[origem] = 0;
  arvore->numArestas = 0;

  for (unsigned int contador = 0; contador < grafo->num_vertices; contador++)
  {
    de = minKey(arvore->custo, pertenceAGM, grafo->num_vertices);
    pertenceAGM[de] = true;
    arvore->numArestas++;

    for (unsigned int vertice = 0; vertice < grafo->num_vertices; vertice++)
    {
      if (existe_aresta(grafo, de, vertice, &peso) && !pertenceAGM[vertice] && (arvore->custo[vertice] > peso))
      {
        arvore->pai[vertice] = de;
        arvore->custo[vertice] = peso;
      }
    }
  }
  free(pertenceAGM);

  arvore->pesoTotal = 0;
  for (unsigned int vertice = 0; vertice < grafo->num_vertices; vertice++)
  {
    arvore->pesoTotal = arvore->pesoTotal + arvore->custo[vertice];
  }
  return (arvore->numArestas == grafo->num_vertices);
}

unsigned int minKey(const int *custo, const bool *pertence, unsigned int numvertices)
{
  unsigned menor, indice;
  menor = INT_MAX;

  for (unsigned int vertice = 0; vertice < numvertices; vertice++)
  {
    if (!pertence[vertice] && (custo[vertice] <= menor))
    {
      indice = vertice;
      menor = custo[vertice];
    }
  }
  return indice;
}

bool obter_melhor_caminho(const GRAFO *grafo, unsigned int origem, CAMINHO **caminho)
{
  int menor, peso;
  unsigned int u;

  if ((grafo->num_vertices == 0) || (origem > grafo->num_vertices))
  {
    return false;
  }

  *caminho = (CAMINHO *) malloc(sizeof(CAMINHO) * grafo->num_vertices);
  if (!(*caminho))
  {
    return false;
  }

  for (unsigned int vertice = 0; vertice < grafo->num_vertices; vertice++)
  {
    (*caminho)[vertice].pai = UINT_MAX;
    (*caminho)[vertice].custo = INT_MAX;
    (*caminho)[vertice].estadoVertice = NAO_PROCESSADO;
  }

  // Custo para sair e chegar no mesmo lugar eh zero
  (*caminho)[origem].custo = 0;

  for (unsigned int vertice = 0; vertice < grafo->num_vertices; vertice++)
  {
    menor = INT_MAX;

    // Procurando o vertice de menor custo ainda nao processado
    for (unsigned int i = 0; i < grafo->num_vertices; i++)
    {
      if (((*caminho)[i].estadoVertice == NAO_PROCESSADO) && ((*caminho)[i].custo <= menor))
      {
        menor = (*caminho)[i].custo;
        u = i;
      }
    }

    // Aqui temos em u o vertice de menor custo ainda nao processado
    // Na primeira vez, eh o vertice de origem
    (*caminho)[u].estadoVertice = EM_PROCESSAMENTO;
    for (unsigned int i = 0; i < grafo->num_vertices; i++)
    {
      if (!existe_aresta(grafo, u, i, &peso))
      {
        continue;
      }

      if (((*caminho)[i].estadoVertice == NAO_PROCESSADO) && (*caminho)[i].custo > ((*caminho)[u].custo + peso))
      {
        (*caminho)[i].custo = (*caminho)[u].custo + peso;
        (*caminho)[i].pai = u;
      }
    }
    (*caminho)[u].estadoVertice = PROCESSADO;
  }
  return true;
}

bool colorir_grafo(const GRAFO *grafo, unsigned int **cores)
{
  VERTEX *Vertex, temp;
  unsigned int corAtual;
  unsigned int adjacente;

  if (grafo->num_vertices == 0)
  {
    return false;
  }

  Vertex = (VERTEX *) malloc(sizeof(VERTEX) * grafo->num_vertices);
  if (!Vertex)
  {
    return false;
  }

  *cores = (unsigned int *) malloc(sizeof(unsigned int) * grafo->num_vertices);
  if (!(*cores))
  {
    free(Vertex);
    return false;
  }

  // Obter o grau de cada vertice
  for (unsigned int vertice = 0; vertice < grafo->num_vertices; vertice++)
  {
    Vertex[vertice].numeroDoVertice = vertice;
    (*cores)[vertice] = UINT_MAX;
    obter_grau_saida_vertice(grafo, vertice, &(Vertex[vertice].grauSaida));
  }

  // Ordernar os vertices de forma decrescente pelo grau de saida
  for (unsigned int vertice = grafo->num_vertices; vertice >= 0; vertice--)
  {
    for (unsigned int j = 1; j < vertice; j++)
    {
      if (Vertex[j - 1].grauSaida < Vertex[j].grauSaida)
      {
        temp = Vertex[j - 1];
        Vertex[j - 1] = Vertex[j];
        Vertex[j] = temp;
      }
    }
    if (vertice == 0)
    { // para nao dar underflow no vertice--
      break;
    }
  }

  corAtual = 0;
  for (unsigned int vertice = 0; vertice < grafo->num_vertices; vertice++)
  {
    // Se o vertice ja estiver pintado, pega o proximo
    if ((*cores)[Vertex[vertice].numeroDoVertice] != UINT_MAX)
    {
      continue;
    }

    (*cores)[Vertex[vertice].numeroDoVertice] = corAtual;

    for (unsigned int naoAdjacente = 0; naoAdjacente < grafo->num_vertices; naoAdjacente++)
    {
      // Se for o proprio vertice, pega o proximo
      if (naoAdjacente == Vertex[vertice].numeroDoVertice)
      {
        continue;
      }
      // Se for adjacente, pega o proximo
      if (existe_aresta(grafo, Vertex[vertice].numeroDoVertice, naoAdjacente, NULL))
      {
        continue;
      }
      for (adjacente = 0; adjacente < grafo->num_vertices; adjacente++)
      {
        if (existe_aresta(grafo, naoAdjacente, adjacente, NULL))
        {
          if ((*cores)[adjacente] == corAtual)
          {
            break;
          }
        }
      }

      if ((adjacente == grafo->num_vertices) && ((*cores)[naoAdjacente] == UINT_MAX))
      {
        (*cores)[naoAdjacente] = corAtual;
      }
    }
    corAtual++;
  }
  return true;
}

void aplicar_cores(GRAFO *grafo, const unsigned int *cores)
{
  remover_cores(grafo);

  grafo->cores = (unsigned int *) malloc(grafo->num_vertices * sizeof(unsigned int));
  if (!grafo->cores)
  {
    return;
  }
  for (unsigned int vertice = 0; vertice < grafo->num_vertices; ++vertice)
  {
    grafo->cores[vertice] = cores[vertice];
  }
}

void remover_cores(GRAFO *grafo)
{
  if (grafo->cores)
  {
    free(grafo->cores);
    grafo->cores = NULL;
  }
}

bool obter_grau_saida_vertice(const GRAFO *grafo, unsigned int de, unsigned int *grau)
{
  if (grafo->num_vertices == 0)
  {
    return false;
  }

  if (!grau)
  {
    return false;
  }

  *grau = 0;
  for (unsigned int para = 0; para < grafo->num_vertices; para++)
  {
    if (existe_aresta(grafo, de, para, NULL))
    {
      *grau = *grau + 1;
    }
  }
  return true;
}

bool obter_grau_entrada_vertice(const GRAFO *grafo, unsigned int para, unsigned int *grau)
{
  if (grafo->num_vertices == 0)
  {
    return false;
  }

  if (!grau)
  {
    return false;
  }

  *grau = 0;
  for (unsigned int de = 0; de < grafo->num_vertices; de++)
  {
    if (existe_aresta(grafo, de, para, NULL))
    {
      *grau = *grau + 1;
    }
  }
  return true;
}