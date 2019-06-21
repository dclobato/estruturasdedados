#ifndef __LISTA__
#define __LISTA__
#include <stdbool.h>

static const unsigned int TAM_LISTA = 10;  // Capacidade de lista
typedef int TIPO_DADO;

typedef struct __st_reg
{
  TIPO_DADO dado;
  unsigned proximo;
} NOH;

typedef struct __st_listaee
{
  unsigned numElementos;
  unsigned numLivres;
  unsigned inicioElementos;
  unsigned inicioLivres;
  NOH dados[TAM_LISTA];
} LISTA;

/*
 * Operacoes de inicializacao, destruicao e metadados
 */
unsigned int tamanho_lista(const LISTA *lista);
unsigned int livres_lista(const LISTA *lista);
bool inicializa_lista(LISTA *lista);
bool destroi_lista(LISTA *lista);
bool obtem_no_lista(LISTA *lista, unsigned int *posicao);
bool libera_no_lista(LISTA *lista, unsigned int posicao);

/*
 * Operacoes de recuperacao de dados
 */
void __imprime_lista(const LISTA *lista);
void imprime_lista(const LISTA *lista);
bool consulta_lista(LISTA *lista, unsigned int posicao, TIPO_DADO *valor);

/*
 * Operacoes de insercao
 */
bool insere_lista(LISTA *lista, const TIPO_DADO *valor,
                  unsigned int posicao);
bool insere_ordenado(LISTA *lista, const TIPO_DADO *valor);
bool insere_final(LISTA *lista, const TIPO_DADO *valor);
bool insere_inicio(LISTA *lista, const TIPO_DADO *valor);

/*
 * Operacoes de remocao
 */
bool remove_lista(LISTA *lista, TIPO_DADO *valor, unsigned int posicao);
bool remove_chave(LISTA *lista, TIPO_DADO *valor);
bool remove_inicio(LISTA *lista, TIPO_DADO *valor);
bool remove_final(LISTA *lista, TIPO_DADO *valor);
#endif
