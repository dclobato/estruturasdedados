#ifndef __GRAFOMATRIZ__
#define __GRAFOMATRIZ__

#include <stdbool.h>
#define MAXNUMVERTICES  100
#define MAXNUMARESTAS   4500

typedef struct __TipoGrafo
{
  int Mat[MAXNUMVERTICES][MAXNUMVERTICES];
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
  RegistroAdjacencia Lista[MAXNUMVERTICES];
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
  RegistroLargura vertex[MAXNUMVERTICES];
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
  RegistroProfundidade vertex[MAXNUMVERTICES];
  unsigned OrdemTopologica[MAXNUMVERTICES];
  bool DAG;
  unsigned Origem;
  unsigned NumDestinos;
} PercursoDFS;


bool CriaGrafo(TipoGrafo *, unsigned, bool);
bool InsereAresta(unsigned, unsigned, int, TipoGrafo *);
bool ExisteAresta(unsigned, unsigned, TipoGrafo *);
int  ObterPesoAresta(unsigned, unsigned, TipoGrafo *, int *);
bool RetiraAresta(unsigned, unsigned, int *, TipoGrafo *);
bool ObterListaAdjacencias(unsigned, TipoGrafo *, TipoListaAdjGrafo *);
void ImprimeGrafo(TipoGrafo *);
bool ObterGrauNo(unsigned, TipoGrafo *, unsigned *, unsigned *);
void PercursoLargura(unsigned, TipoGrafo *, PercursoBFS *);
void PercursoProfundidade(unsigned, TipoGrafo *, PercursoDFS *, bool);
void _PP(unsigned, TipoGrafo *, PercursoDFS *, unsigned *, unsigned);

#endif
