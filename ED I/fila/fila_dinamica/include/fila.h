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
  NOH_FILA *inicio;
} FILA;

/*
 * Operacoes de inicializacao, destruicao e metadados
 */
bool fila_inicializar(FILA *fila);
bool fila_destruir(FILA *fila);
unsigned int fila_numero_de_elementos(const FILA *fila);
bool fila_esta_vazia(const FILA *fila);
bool fila_esta_cheia(const FILA *fila);
bool fila_obtem_no(NOH_FILA **nodo);
bool fila_libera_no(NOH_FILA **nodo);

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

