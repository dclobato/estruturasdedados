#ifndef DEF_LISTA_CIRC
#define DEF_LISTA_CIRC
#include <stdbool.h>
typedef int TIPO_DADO;

typedef struct __noh
{
  TIPO_DADO dado;
  struct __noh *sucessor;
} NOH_CIRC;

/* Uma lista circular não tem, formalmente, um início, por ser circular,
 * mas precisamos ter alguma forma de saber onde comecar o percurso nela;
 * por isso, vamos ter um ponteiro para um dos nós, e uma lista vazia vai
 * ser indicada por um ponteiro vazio
 * Ao ter a lista apontando para o ULTIMO elemento, ao invés de o PRIMEIRO,
 * passamos a ter uma forma fácil de incluir um elemento no final ou no início
 * sem a necessidade de percorrer toda a lista
 */
typedef struct __lista_de
{
  unsigned int numElementos;
  NOH_CIRC *final;
} LISTA_CIRC;

/*
 * Operacoes de inicializacao, destruicao e metadados
 */
bool inicializa_lista_circ(LISTA_CIRC *lista);
bool destroi_lista_circ(LISTA_CIRC *lista);
bool obtem_no_lista_circ(NOH_CIRC **nodo);
bool libera_no_lista_circ(NOH_CIRC **nodo);
bool shift_right_lista_circ (LISTA_CIRC *lista);
unsigned int tamanho_lista_circ(const LISTA_CIRC *lista);

/*
 * Operacoes de recuperacao de dados
 */
void imprime_lista_circ(const LISTA_CIRC *lista);
void __imprime_lista_circ(const LISTA_CIRC *lista);
bool consulta_lista_circ(const LISTA_CIRC *lista, unsigned int posicao,
                         TIPO_DADO *valor);
bool busca_lista_circ(const LISTA_CIRC *lista, const TIPO_DADO *valor,
                      NOH_CIRC **nodo);
bool obtem_sucessor_circ(const NOH_CIRC *nodo, NOH_CIRC **sucessor);
bool obtem_inicio_circ(const LISTA_CIRC *lista, NOH_CIRC **nodo);
bool obtem_final_circ(const LISTA_CIRC *lista, NOH_CIRC **nodo);
bool obtem_valor_no(const NOH_CIRC *nodo, TIPO_DADO *valor);


/*
 * Operacoes de insercao
 */
bool insere_lista_circ(LISTA_CIRC *lista, const TIPO_DADO *valor,
                       unsigned int posicao);
bool insere_ordenado_circ(LISTA_CIRC *lista, const TIPO_DADO *valor);
bool insere_depois_do_nodo_circ(LISTA_CIRC *lista, const NOH_CIRC **nodo,
                                const TIPO_DADO *valor);
bool insere_inicio_circ(LISTA_CIRC *lista, const TIPO_DADO *valor);
bool insere_final_circ(LISTA_CIRC *lista, const TIPO_DADO *valor);
bool definir_valor_no(NOH_CIRC *nodo, const TIPO_DADO *valor);

/*
 * Operacoes de remocao
 */
bool remove_lista_circ(LISTA_CIRC *lista, TIPO_DADO *valor,
                       unsigned int posicao);
bool remove_chave_circ(LISTA_CIRC *lista, const TIPO_DADO *valor);
bool remove_nodo_circ(LISTA_CIRC *lista, NOH_CIRC **nodo);
bool remove_inicio_circ(LISTA_CIRC *lista, TIPO_DADO *valor);
bool remove_final_circ(LISTA_CIRC *lista, TIPO_DADO *valor);
#endif
