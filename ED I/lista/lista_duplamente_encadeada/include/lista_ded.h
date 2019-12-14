#ifndef DEF_LISTA_DUPLAMENTE_ENCADEADA_DINAMICA
#define DEF_LISTA_DUPLAMENTE_ENCADEADA_DINAMICA

#include <stdbool.h>

typedef int TIPO_DADO;

typedef struct __noh
{
  TIPO_DADO dado;
  struct __noh *sucessor;
  struct __noh *predecessor;
} NOH_LISTA;

typedef struct __lista
{
  unsigned int numElementos;
  NOH_LISTA *inicio;
  NOH_LISTA *final;
} LISTA;

/*
 * Operacoes de inicializacao, destruicao e metadados
 */
bool lista_inicializar(LISTA *lista);
bool lista_destruir(LISTA *lista);
bool lista_obter_no(NOH_LISTA **nodo);
bool lista_liberar_no(NOH_LISTA **nodo);
unsigned int lista_numero_de_elementos(const LISTA *lista);
bool lista_esta_vazia(const LISTA *lista);
bool lista_esta_cheia(const LISTA *lista);

/*
 * Operacoes de recuperacao de dados
 */
void lista_imprimir(const LISTA *lista);
void __lista_imprimir(const LISTA *lista);
bool lista_obter_sucessor_de_no(const NOH_LISTA *nodo, NOH_LISTA **sucessor);
bool lista_obter_predecessor_de_no(const NOH_LISTA *nodo, NOH_LISTA **predecessor);
bool lista_obter_chave_no(const NOH_LISTA *nodo, TIPO_DADO *valor);

bool lista_obter_no_posicao(const LISTA *lista, NOH_LISTA **nodo, unsigned int posicao);
bool lista_obter_no_inicio(const LISTA *lista, NOH_LISTA **nodo);
bool lista_obter_no_final(const LISTA *lista, NOH_LISTA **nodo);
bool lista_obter_no_chave(const LISTA *lista, const TIPO_DADO *valor, NOH_LISTA **nodo);

bool lista_obter_chave_posicao(const LISTA *lista, TIPO_DADO *valor, unsigned int posicao);
bool lista_obter_chave_inicio(const LISTA *lista, TIPO_DADO *valor);
bool lista_obter_chave_final(const LISTA *lista, TIPO_DADO *valor);
bool lista_obter_posicao_chave(const LISTA *lista, const TIPO_DADO *valor, unsigned int *posicao);

/*
 * Operacoes de insercao
 */
bool lista_inserir_chave_posicao(LISTA *lista, const TIPO_DADO *valor, unsigned int posicao);
bool lista_inserir_chave_antes_no(LISTA *lista, const TIPO_DADO *valor, const NOH_LISTA **nodo);
bool lista_inserir_chave_ordenado(LISTA *lista, const TIPO_DADO *valor);
bool lista_inserir_chave_inicio(LISTA *lista, const TIPO_DADO *valor);
bool lista_inserir_chave_final(LISTA *lista, const TIPO_DADO *valor);
bool lista_definir_chave_posicao(LISTA *lista, const TIPO_DADO *valor, unsigned int posicao); //
bool lista_definir_chave_no(NOH_LISTA *nodo, const TIPO_DADO *valor); //

/*
 * Operacoes de remocao
 */
bool lista_remover_posicao(LISTA *lista, TIPO_DADO *valor, unsigned int posicao);
bool lista_remover_nodo(LISTA *lista, NOH_LISTA **nodo);
bool lista_remover_chave(LISTA *lista, const TIPO_DADO *valor);
bool lista_remover_inicio(LISTA *lista, TIPO_DADO *valor);
bool lista_remover_final(LISTA *lista, TIPO_DADO *valor);
#endif
