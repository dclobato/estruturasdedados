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
bool fila_inicializar(FILA *fila);
bool fila_destruir(FILA *fila);
unsigned int fila_numero_de_elementos(const FILA *fila);
unsigned int fila_numero_de_nos_livres(const FILA *fila);
bool fila_esta_vazia(const FILA *fila);
bool fila_esta_cheia(const FILA *fila);

/*
 * Recuperação de informação
 */
bool fila_head(const FILA *fila, TIPO_DADO *valor);
bool fila_tail(const FILA *fila, TIPO_DADO *valor);
void fila_imprimir(const FILA *fila);

/*
 * Insercao e remocao
 */
bool fila_enfileirar(FILA *fila, const TIPO_DADO *valor);
bool fila_desenfileirar(FILA *fila, TIPO_DADO *valor);

/*
 * Fila de prioridade implementada SEM uso de heap
 */
bool fila_enfileirar_com_prioridade(FILA *fila, const TIPO_DADO *valor);

#endif
