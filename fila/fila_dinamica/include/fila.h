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
bool inicializa_fila (FILA *fila);
bool destroi_fila (FILA *fila);
unsigned int tamanho_fila (const FILA *fila);
bool fila_vazia (const FILA *fila);
bool obtem_no_fila (NOH_FILA **nodo);
bool libera_no_fila (NOH_FILA **nodo);
void imprime_fila (const FILA *fila);

/*
 * Insercao e remocao
 */
bool enfileira (FILA *fila, const TIPO_DADO *valor);
bool desenfileira (FILA *fila, TIPO_DADO *valor);

/*
 * Fila de prioridade implementada SEM uso de heap
 */
bool enfileira_prioridade (FILA *fila, const TIPO_DADO *valor);
#endif

