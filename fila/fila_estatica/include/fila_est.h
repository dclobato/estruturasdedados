#ifndef DEF_FILA_ESTATICA
#define DEF_FILA_ESTATICA
#include <stdbool.h>

static const unsigned int TAM_FILA = 10; // Capacidade da fila

typedef int TIPO_DADO;

typedef struct __fila
{
  int dados[TAM_FILA];
  int inicio;
  int final;
} FILA;

/*
 * Operacoes de inicializacao, destruicao e metadados
 */
bool inicializa_fila(FILA *fila);
bool destroi_fila(FILA *fila);
unsigned int tamanho_fila(const FILA *fila);
bool fila_vazia(const FILA *fila);
void imprime_fila(const FILA *fila);

/*
 * Insercao e remocao
 */
bool enfileira(FILA *fila, const TIPO_DADO *valor);
bool desenfileira(FILA *fila, TIPO_DADO *valor);

/*
 * Fila de prioridade implementada SEM uso de heap
 */
bool enfileira_prioridade(FILA *fila, const TIPO_DADO *valor);

#endif
