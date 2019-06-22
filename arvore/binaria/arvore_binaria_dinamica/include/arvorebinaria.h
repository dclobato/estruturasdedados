#ifndef __ARVORE_BINARIA__
#define __ARVORE_BINARIA__
#include <stdbool.h>

typedef int TIPO_DADO;

typedef enum
{
  RAIZ,
  ESQ,
  DIR
} TipoNo;

typedef enum
{
  PRE,
  POS,
  IN,
  LARGURA
} TipoPercurso;

typedef struct __noarvore
{
  int dado;
  struct __noarvore *esq;
  struct __noarvore *dir;
} NO_ARVORE;

typedef NO_ARVORE *ARVORE;

typedef struct __percurso
{
  unsigned tamanho;
  TIPO_DADO *nodos;
} PERCURSO;

/*
 * Operacoes de inicializacao e destruicao
 */
bool inicializa_arvore(ARVORE *arvore);
bool destroi_arvore(ARVORE *arvore);
bool cria_nodo_arvore(ARVORE *arvore);
bool destroi_nodo_arvore(ARVORE *arvore);

/*
 * Operacao de insercao e remocao
 */
bool insere_na_arvore(ARVORE *arvore, TipoNo tipo, const TIPO_DADO *valor);
// Falta operacao de remocao
// bool remove_da_arvore (ARVORE *arvore, ARVORE *nodo);

/*
 * Operacoes de Arvore Binaria de Busca
 */
bool insere_arvore_binaria_busca(ARVORE *arvore, const TIPO_DADO *valor);
bool pesquisa_abb(ARVORE *arvore, const TIPO_DADO *valor, ARVORE *nodo);

/*
 * Percursos
 */
void imprime_arvore(const ARVORE *arvore);
void __imprime_arvore(const ARVORE *arvore, unsigned int *linha);
bool percurso(ARVORE *arvore, TipoPercurso tipo, PERCURSO *percurso);
bool destroi_percurso(PERCURSO *percurso);
bool percurso_pre(ARVORE *arvore, PERCURSO *percurso);
bool percurso_in(ARVORE *arvore, PERCURSO *percurso);
bool percurso_pos(ARVORE *arvore, PERCURSO *percurso);
bool percurso_largura(ARVORE *arvore, PERCURSO *percurso);

/*
 * Estrutura de dados auxiliar para percurso em largura
 * Eh possivel fazer sem ela, com vetor, mas ja que esta pronta,
 * ficamos com ela
 */
struct NOH_FILA
{
  ARVORE item;
  struct NOH_FILA *prox;
};

typedef struct NOH_FILA *FILA;

bool cria_fila(FILA *fila);
bool insere_fila(FILA *fila, ARVORE nodo);
bool remove_fila(FILA *fila, ARVORE *nodo);
#endif
