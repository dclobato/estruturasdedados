#ifndef DEF_LISTA_CIRCULAR_ENCADEADA_DINAMICA
#define DEF_LISTA_CIRCULAR_ENCADEADA_DINAMICA

#include <stdbool.h>

typedef int TIPO_DADO;

typedef struct __noh_circular
{
  TIPO_DADO dado;
  struct __noh_circular *sucessor;
} NOH_CIRCULAR;

/* Uma lista circular não tem, formalmente, um início, por ser circular,
 * mas precisamos ter alguma forma de saber onde comecar o percurso nela;
 * por isso, vamos ter um ponteiro para um dos nós, e uma lista vazia vai
 * ser indicada por um ponteiro vazio
 * Ao ter a lista apontando para o ULTIMO elemento, ao invés de o PRIMEIRO,
 * passamos a ter uma forma fácil de incluir um elemento no final ou no início
 * sem a necessidade de percorrer toda a lista
 */
typedef struct __lista_circular
{
  unsigned int numElementos;
  NOH_CIRCULAR *final;
} LISTA_CIRCULAR;

/*
 * Operacoes de inicializacao, destruicao e metadados
 */
bool lista_circular_inicializar(LISTA_CIRCULAR *lista);
bool lista_circular_destruir(LISTA_CIRCULAR *lista);
bool list_cicular_obter_no(NOH_CIRCULAR **nodo);
bool lista_circular_liberar_no(NOH_CIRCULAR **nodo);
unsigned int lista_circular_numero_de_elementos(const LISTA_CIRCULAR *lista);
bool lista_circular_esta_vazia(const LISTA_CIRCULAR *lista);
bool lista_circular_esta_cheia(const LISTA_CIRCULAR *lista);

/*
 * Operacoes de recuperacao de dados
 */
void lista_circular_imprimir(const LISTA_CIRCULAR *lista);
void __lista_circular_imprimir(const LISTA_CIRCULAR *lista);
bool lista_circular_obter_sucessor_de_no(const NOH_CIRCULAR *nodo, NOH_CIRCULAR **sucessor);
bool lista_circular_obter_chave_no(const NOH_CIRCULAR *nodo, TIPO_DADO *valor);

bool lista_circular_obter_no_posicao(const LISTA_CIRCULAR *lista, NOH_CIRCULAR **nodo, unsigned int posicao);
bool lista_circular_obter_no_inicio(const LISTA_CIRCULAR *lista, NOH_CIRCULAR **nodo);
bool lista_circular_obter_no_final(const LISTA_CIRCULAR *lista, NOH_CIRCULAR **nodo);
bool lista_circular_obter_no_chave(const LISTA_CIRCULAR *lista, const TIPO_DADO *valor, NOH_CIRCULAR **nodo);

bool lista_circular_obter_chave_posicao(const LISTA_CIRCULAR *lista, TIPO_DADO *valor, unsigned int posicao);
bool lista_circular_obter_chave_inicio(const LISTA_CIRCULAR *lista, TIPO_DADO *valor);
bool lista_circular_obter_chave_final(const LISTA_CIRCULAR *lista, TIPO_DADO *valor);
bool lista_circular_obter_posicao_chave(const LISTA_CIRCULAR *lista, const TIPO_DADO *valor, unsigned int *posicao);

bool lista_circular_shift_right(LISTA_CIRCULAR *lista);
bool lista_circular_shift_left(LISTA_CIRCULAR *lista);

/*
 * Operacoes de insercao
 */
bool lista_circular_inserir_chave_posicao(LISTA_CIRCULAR *lista, const TIPO_DADO *valor, unsigned int posicao);
bool lista_circular_inserir_chave_antes_no(LISTA_CIRCULAR *lista, const TIPO_DADO *valor, const NOH_CIRCULAR **nodo);
bool lista_circular_inserir_chave_ordenado(LISTA_CIRCULAR *lista, const TIPO_DADO *valor);
bool lista_circular_inserir_chave_inicio(LISTA_CIRCULAR *lista, const TIPO_DADO *valor);
bool lista_circular_inserir_chave_final(LISTA_CIRCULAR *lista, const TIPO_DADO *valor);
bool lista_circular_definir_chave_posicao(LISTA_CIRCULAR *lista, const TIPO_DADO *valor, unsigned int posicao);
bool lista_circular_definir_chave_no(NOH_CIRCULAR *nodo, const TIPO_DADO *valor);

/*
 * Operacoes de remocao
 */
bool lista_circular_remover_posicao(LISTA_CIRCULAR *lista, TIPO_DADO *valor, unsigned int posicao);
bool lista_circular_remover_nodo(LISTA_CIRCULAR *lista, NOH_CIRCULAR **nodo);
bool lista_circular_remover_chave(LISTA_CIRCULAR *lista, const TIPO_DADO *valor);
bool lista_circular_remover_inicio(LISTA_CIRCULAR *lista, TIPO_DADO *valor);
bool lista_circular_remover_final(LISTA_CIRCULAR *lista, TIPO_DADO *valor);
#endif
