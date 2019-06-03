#ifndef __GRAFOMATRIZ__
#define __GRAFOMATRIZ__

#include <stdbool.h>
#define MAXNUMVERTICES  100
#define MAXNUMARESTAS   4500
#define MAXTAMROTULO    30

typedef struct __TipoGrafo
{
  int **Mat;
  char **Rotulos;
  unsigned MaxVertices;
  unsigned NumVertices;
  unsigned NumArestas;
  bool Direcionado;
} TipoGrafo;

typedef struct __RegistroAdjacencia
{
  unsigned vertice;
  int peso;
} RegistroAdjacencia;

typedef struct __TipoListaAdjGrafo
{
  RegistroAdjacencia *Lista;
  unsigned NumAdjacentes;
} TipoListaAdjGrafo;

typedef enum
{
  BRANCO,
  CINZA,
  PRETO
} TipoCor;

typedef struct __RegistroLargura
{
  TipoCor cor;
  unsigned pai;
  unsigned distancia;
} RegistroLargura;

typedef struct __PercursoLargura
{
  RegistroLargura *vertex;
  unsigned Origem;
  unsigned NumDestinos;
} PercursoBFS;

typedef struct __RegistroProfundidade
{
  TipoCor cor;
  unsigned pai;
  unsigned descoberta;
  unsigned termino;
} RegistroProfundidade;

typedef struct __PercursoProfundidade
{
  RegistroProfundidade *vertex;
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

typedef struct __Coloracao
{
  unsigned vertice;
  unsigned grau;
  bool colorido;
  unsigned cor;
} Cores;

bool CriaGrafo(TipoGrafo *, unsigned, bool);
bool DestroiGrafo(TipoGrafo *);
bool InsereAresta(unsigned, unsigned, int, TipoGrafo *);
bool RetiraAresta(unsigned, unsigned, int *, TipoGrafo *);
bool InsereRotulo(char *, size_t, TipoGrafo *, unsigned *);
void ImprimeGrafo(TipoGrafo *);


bool ObterGrauNo(unsigned, TipoGrafo *, unsigned *, unsigned *);
bool ExisteAresta(unsigned, unsigned, TipoGrafo *);
bool ObterPesoAresta(unsigned, unsigned, TipoGrafo *, int *);

bool ObterListaAdjacencias(unsigned, TipoGrafo *, TipoListaAdjGrafo *);
bool DestroiListaAdjacencias(TipoListaAdjGrafo *);
void PercursoLargura(unsigned, TipoGrafo *, PercursoBFS *);
bool DestroiPercursoLargura(PercursoBFS *);
void PercursoProfundidade(unsigned, TipoGrafo *, PercursoDFS *, bool);
bool DestroiPercursoProfundidade(PercursoDFS *);
void _PP(unsigned, TipoGrafo *, PercursoDFS *, unsigned *, unsigned);

bool AGMPrim(unsigned, TipoGrafo *, AGM *);
bool DestroiAGM(AGM *);
unsigned minKey(int *, bool *, unsigned);

#endif
