#ifndef DEF_FILA_DINAMICA
#define DEF_FILA_DINAMICA
#include <stdbool.h>

typedef int TIPO_DADO;

typedef struct __noh
{
  TIPO_DADO dado;
  struct __noh *prox;
} NOH_FILA;

typedef struct __lista
{
  int numElementos;
  NOH_FILA *final;
  NOH_FILA *dados;
} FILA;

/*
 * Operacoes de inicializacao, destruicao e metadados
 */
bool fila_inicializa(FILA *fila);
bool fila_destroi(FILA *fila);
unsigned int fila_tamanho(const FILA *fila);
bool fila_vazia(const FILA *fila);
bool fila_cheia(const FILA *fila);
bool __fila_obtem_no(NOH_FILA **nodo);
bool __fila_libera_no(NOH_FILA **nodo);
void fila_imprime(const FILA *fila);

/*
 * Insercao e remocao
 */
bool fila_enfileira(FILA *fila, const TIPO_DADO *valor);
bool fila_desenfileira(FILA *fila, TIPO_DADO *valor);

/*
 * Fila de prioridade implementada SEM uso de heap
 */
bool fila_enfileira_prioridade(FILA *fila, const TIPO_DADO *valor);
#endif

