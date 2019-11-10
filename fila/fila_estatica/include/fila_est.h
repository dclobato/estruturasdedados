#ifndef DEF_FILA_ESTATICA
#define DEF_FILA_ESTATICA

#include <stdbool.h>

// static const unsigned int TAM_FILA = 10; // Capacidade da fila
#define TAM_FILA 10

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
bool fila_inicializa(FILA *fila);
bool fila_destroi(FILA *fila);
unsigned int fila_tamanho(const FILA *fila);
bool fila_vazia(const FILA *fila);
bool fila_cheia(const FILA *fila);
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
