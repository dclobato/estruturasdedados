#ifndef DEF_LISTA_ED
#define DEF_LISTA_ED

#include <stdbool.h>

typedef int TIPO_DADO;

typedef struct __noh
{
  TIPO_DADO dado;
  struct __noh *sucessor;
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
bool lista_inicializa(LISTA *lista);
bool lista_destroi(LISTA *lista);
bool __lista_obtem_no(NOH_LISTA **nodo);
bool lista_libera_no(NOH_LISTA **nodo);
unsigned int lista_tamanho(const LISTA *lista);
bool lista_vazia (const LISTA *lista);
bool lista_cheia (const LISTA *lista);

/*
 * Operacoes de recuperacao de dados
 */
void lista_imprime(const LISTA *lista);
void __lista_imprime(const LISTA *lista);
bool lista_consulta_posicao(const LISTA *lista, unsigned int posicao, TIPO_DADO *valor);
bool lista_busca_chave(const LISTA *lista, const TIPO_DADO *valor, NOH_LISTA **nodo);
bool lista_obtem_sucessor(const NOH_LISTA *nodo, NOH_LISTA **proximo);
bool lista_obtem_inicio(const LISTA *lista, NOH_LISTA **nodo);
bool lista_obtem_final(const LISTA *lista, NOH_LISTA **nodo);


/*
 * Operacoes de insercao
 */
bool lista_insere(LISTA *lista, const TIPO_DADO *valor, unsigned int posicao);
bool lista_insere_ordenado(LISTA *lista, const TIPO_DADO *valor);
bool lista_insere_antes_do_nodo(LISTA *lista, const NOH_LISTA **nodo, const TIPO_DADO *valor);
bool lista_insere_inicio(LISTA *lista, const TIPO_DADO *valor);
bool lista_insere_final(LISTA *lista, const TIPO_DADO *valor);

/*
 * Operacoes de remocao
 */
bool lista_remove_posicao(LISTA *lista, TIPO_DADO *valor, unsigned int posicao);
bool lista_remove_chave(LISTA *lista, const TIPO_DADO *valor);
bool lista_remove_nodo(LISTA *lista, NOH_LISTA **nodo);
bool lista_remove_inicio(LISTA *lista, TIPO_DADO *valor);
bool lista_remove_final(LISTA *lista, TIPO_DADO *valor);
#endif
