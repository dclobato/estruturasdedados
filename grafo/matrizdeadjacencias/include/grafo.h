#ifndef __GRAFOMATRIZ__
#define __GRAFOMATRIZ__

#include <stdbool.h>
#define MAXNUMVERTICES  100
#define MAXNUMARESTAS   4500
#define MAXTAMROTULO    30

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
  int **Mat;
  char **Rotulos;
  unsigned MaxVertices;
  unsigned NumVertices;
  unsigned NumArestas;
  bool Direcionado;
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
  unsigned gE;
  unsigned gS;
  int peso;
} RegistroVertices;

typedef struct __RegistroGraus
{
  unsigned vertice;
  unsigned gE;
  unsigned gS;
} RegistroGraus;

typedef struct __TipoListaAdjGrafo
{
  RegistroVertices *Lista;
  unsigned NumAdjacentes;
} TipoListaAdjGrafo;

typedef struct __PercursoLargura
{
  RegistroVertices *vertex;
  unsigned Origem;
  unsigned NumDestinos;
} PercursoBFS;

typedef struct __PercursoProfundidade
{
  RegistroVertices *vertex;
  unsigned *OrdemTopologica;
  bool DAG;
  unsigned Origem;
  unsigned NumDestinos;
} PercursoDFS;

typedef struct __AGM
{
  unsigned *pai;
  int *custo;
  unsigned NumArestas;
  long int pesoTotal;
} AGM;

typedef struct
{
  unsigned custo;
  unsigned tamanho;
  unsigned pai;
  TipoCor cor;
} Caminho;


bool CriaGrafo(TipoGrafo *, unsigned, bool);
bool DestroiGrafo(TipoGrafo *);
bool InsereAresta(unsigned, unsigned, int, TipoGrafo *);
bool RetiraAresta(unsigned, unsigned, int *, TipoGrafo *);
bool InsereVertice(char *, size_t, TipoGrafo *, unsigned *);
void ImprimeGrafo(TipoGrafo *);

bool ObterGrauNo(unsigned, TipoGrafo *, unsigned *, unsigned *);
bool ExisteAresta(unsigned, unsigned, TipoGrafo *);
bool ObterPesoAresta(unsigned, unsigned, TipoGrafo *, int *);

bool ObterListaAdjacencias(unsigned, TipoGrafo *, TipoListaAdjGrafo *,
                           bool);
bool DestroiListaAdjacencias(TipoListaAdjGrafo *);
void PercursoLargura(unsigned, TipoGrafo *, PercursoBFS *);
bool DestroiPercursoLargura(PercursoBFS *);
void PercursoProfundidade(unsigned, TipoGrafo *, PercursoDFS *, bool);
bool DestroiPercursoProfundidade(PercursoDFS *);
void _PP(unsigned, TipoGrafo *, PercursoDFS *, unsigned *, unsigned);

bool AGMPrim(unsigned, TipoGrafo *, AGM *);
bool DestroiAGM(AGM *);
unsigned minKey(int *, bool *, unsigned);

bool calculaMelhorCaminhoDijkstra(TipoGrafo *, unsigned, Caminho **);
bool obtemMelhorCaminho(TipoGrafo *, unsigned, unsigned, Caminho *, int *,
                        unsigned **, unsigned *);

bool colorirGrafo(TipoGrafo *, unsigned **);
bool ordenaListaVerticesGrau(RegistroGraus *, TipoOrdenacao, unsigned,
                             bool);

#endif
