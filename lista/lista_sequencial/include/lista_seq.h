#ifndef __LISTA__
#define __LISTA__
#include <stdbool.h>

// static const unsigned int TAM_LISTA = 100;
#define TAM_LISTA 100

typedef int TIPO_DADO;

typedef struct
{
  unsigned int numElementos;
  TIPO_DADO elementos[TAM_LISTA];
} LISTA;

/*
 * Operacoes de inicializacao, destruicao e metadados
 */
bool lista_inicializa(LISTA *lista);
bool lista_destroi(LISTA *lista);
unsigned int lista_tamanho(const LISTA *lista);
unsigned int lista_nos_livres(const LISTA *lista);
bool lista_vazia (const LISTA *lista);
bool lista_cheia (const LISTA *lista);


/*
 * Operacoes de recuperacao de dados
 */
void lista_imprime(const LISTA *lista);
bool lista_consulta_posicao(const LISTA *lista, unsigned int posicao, TIPO_DADO *valor);

/*
 * Operacoes de insercao
 */
bool lista_insere_posicao(LISTA *lista, const TIPO_DADO *valor,
                          unsigned int posicao);
bool lista_insere_ordenado(LISTA *lista, const TIPO_DADO *valor);
bool lista_insere_inicio(LISTA *lista, const TIPO_DADO *valor);
bool lista_insere_final(LISTA *lista, const TIPO_DADO *valor);
bool lista_definir_valor_posicao(LISTA* lista, const TIPO_DADO *valor, unsigned int posicao);

/*
 * Operacoes de remocao
 */
bool lista_remove_posicao(LISTA *lista, TIPO_DADO *valor, unsigned int posicao);
bool lista_remove_chave(LISTA *lista, const TIPO_DADO *valor);
bool lista_remove_inicio(LISTA *lista, TIPO_DADO *valor);
bool lista_remove_final(LISTA *lista, TIPO_DADO *valor);
#endif
