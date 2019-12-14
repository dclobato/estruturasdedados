#ifndef GRAFO_MATRIZ
#define GRAFO_MATRIZ
#include <stdbool.h>
#include <string.h>

static const unsigned MAXNUMVERTICES = 100;
static const unsigned MAXNUMARESTAS = 4500;
static const unsigned MAXTAMROTULO = 30;

// this snippet from stackoverflow
// http://stackoverflow.com/questions/3982348/implement-generic-swap-macro-in-c
#define swap(x,y) do \
  { unsigned char swap_temp[sizeof(x) == sizeof(y) ? (signed)sizeof(x) : -1]; \
    memcpy(swap_temp,&y,sizeof(x)); \
    memcpy(&y,&x,       sizeof(x)); \
    memcpy(&x,swap_temp,sizeof(x)); \
  } while(0)

typedef enum
{
  BRANCO,
  CINZA,
  PRETO
} TipoCor;

typedef enum
{
  VERTICE,
  GRAU_SAIDA,
  GRAU_ENTRADA,
  DESCOBERTA,
  TERMINO,
  DISTANCIA,
  COR_COLORIDA,
  PESO
} TipoOrdenacao;

typedef struct __TipoGrafo
{
  int **matriz;
  char **rotulos;
  unsigned maxVertices;
  unsigned numVertices;
  unsigned numArestas;
  bool direcionado;
} TipoGrafo;

typedef struct __RegistroVertices
{
  unsigned vertice;
  unsigned pai;
  unsigned descoberta;
  unsigned termino;
  unsigned cor;
  TipoCor  corTrabalho;
  unsigned distancia;
  unsigned grauEntrada;
  unsigned grauSaida;
  int peso;
} RegistroVertices;

typedef struct __TipoListaAdjGrafo
{
  RegistroVertices *listaDeVertices;
  unsigned numAdjacentes;
} ListaVerticesAdjacentes;

typedef struct __PercursoLargura
{
  RegistroVertices *vertex;
  unsigned verticeOrigem;
  unsigned numDestinos;
} PercursoBFS;

typedef struct __PercursoProfundidade
{
  RegistroVertices *vertex;
  unsigned *ordemTopologica;
  bool DAG;
  unsigned verticeOrigem;
  unsigned numDestinos;
} PercursoDFS;

typedef struct __AGM
{
  unsigned *pai;
  int *custo;
  unsigned numArestas;
  long int pesoTotal;
} ArvoreGeradoraMinima;

typedef struct
{
  unsigned custo;
  unsigned tamanho;
  unsigned pai;
  TipoCor cor;
} Caminho;

/*
 * Operacoes de inicializacao e destruicao do grafo
 */
bool cria_grafo(TipoGrafo *grafo, unsigned maximoVertices,
                bool direcionado);
bool destroi_grafo(TipoGrafo *grafo);
void imprime_grafo(const TipoGrafo *grafo);

/*
 * Insercao, remocao e consulta de vertices e arestas
 */
bool insere_vertice(TipoGrafo *grafo, char *rotulo, size_t tamanho,
                    unsigned *numeroVertice);
bool insere_aresta(TipoGrafo *grafo, unsigned verticeOrigem,
                   unsigned verticeDestino, int peso);
bool retira_aresta(TipoGrafo *grafo, unsigned verticeOrigem,
                   unsigned verticeDestino, int *peso);
bool existe_aresta(const TipoGrafo *grafo, unsigned verticeOrigem,
                   unsigned verticeDestino);
bool obter_peso_aresta(const TipoGrafo *grafo, unsigned verticeOrigem,
                       unsigned verticeDestino, int *peso);
bool obter_grau_vertice(const TipoGrafo *grafo, unsigned vertice,
                        unsigned *grauEntrada, unsigned *grauSaida);

/*
 * Lista de adjacencia
 */
bool obter_lista_adjacentes(const TipoGrafo *grafo, unsigned vertice,
                            ListaVerticesAdjacentes *listaAdjacentes, bool complemento);
bool destroi_lista_adjacentes(ListaVerticesAdjacentes *listaAdjacentes);

/*
 * Percursos
 */
bool percurso_largura(const TipoGrafo *grafo, unsigned vertice,
                      PercursoBFS *percurso);
bool destroi_percurso_largura(PercursoBFS *percurso);
bool percurso_profundidade(const TipoGrafo *grafo, unsigned vertice,
                           PercursoDFS *percurso, bool todos);
bool destroi_percurso_profundidade(PercursoDFS *percurso);
void __percurso_profundidade(const TipoGrafo *grafo, unsigned vertice,
                             unsigned pai, PercursoDFS *percurso, unsigned *relogio);

/*
 * Arvore geradora minima
 */
bool arvore_geradora_minima_prim(const TipoGrafo *grafo, unsigned vertice,
                                 ArvoreGeradoraMinima *arvore);
bool destroi_arvore_geradora_minima(ArvoreGeradoraMinima *arvore);
unsigned minKey(const int *custo, const bool *pertenceArvoreGeradora,
                unsigned numeroVertices);

/*
 * Melhores caminhos
 */
bool calcula_melhor_caminho_Dijkstra(const TipoGrafo *grafo,
                                     unsigned verticeOrigem, Caminho **caminho);
bool obtem_melhor_caminho(const TipoGrafo *grafo, unsigned verticeOrigem,
                          unsigned verticeDestino, Caminho *caminhos, int *custo, unsigned **vertices,
                          unsigned *tamanho);

/*
 * Coloracao de grafos
 */
bool colorir_grafo(const TipoGrafo *grafo, unsigned **vetorCores);
bool ordenar_lista_vertices_grau(RegistroVertices *vertices,
                                 TipoOrdenacao chave, unsigned tamanho, bool invertido);
#endif
