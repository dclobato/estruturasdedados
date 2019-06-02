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


bool CriaGrafo(TipoGrafo *, unsigned, bool);
bool InsereAresta(unsigned, unsigned, int, TipoGrafo *);
bool RetiraAresta(unsigned, unsigned, int *, TipoGrafo *);
bool InsereRotulo(char *, int, TipoGrafo *, unsigned *);
void ImprimeGrafo(TipoGrafo *);

//bool DestroiGrafo(TipoGrafo *);
//bool DestroiListaAdjacencias(TipoGrafo *);
//bool DestroiPercursoLargura(PercursoBFS*);
//bool DestroiPercursoProfundidade(PercursoDFS *);

bool ObterGrauNo(unsigned, TipoGrafo *, unsigned *, unsigned *);
bool ExisteAresta(unsigned, unsigned, TipoGrafo *);
int  ObterPesoAresta(unsigned, unsigned, TipoGrafo *, int *);

bool ObterListaAdjacencias(unsigned, TipoGrafo *, TipoListaAdjGrafo *);
void PercursoLargura(unsigned, TipoGrafo *, PercursoBFS *);
void PercursoProfundidade(unsigned, TipoGrafo *, PercursoDFS *, bool);
void _PP(unsigned, TipoGrafo *, PercursoDFS *, unsigned *, unsigned);

#endif
