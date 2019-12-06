#ifndef DEF_LISTA_DED
#define DEF_LISTA_DED
#include <stdbool.h>

typedef int TIPO_DADO;

typedef struct __noh
{
  TIPO_DADO dado;
  struct __noh *sucessor;
  struct __noh *predecessor;
} NOH_DE;

typedef struct __lista_de
{
  unsigned int numElementos;
  NOH_DE *inicio;
  NOH_DE *final;
} LISTA_DE;

/*
 * Operacoes de inicializacao, destruicao e metadados
 */
bool inicializa_lista_de(LISTA_DE *lista);
bool destroi_lista_de(LISTA_DE *lista);
bool obtem_no_lista_de(NOH_DE **nodo);
bool libera_no_lista_de(NOH_DE **nodo);
unsigned int tamanho_lista_de(const LISTA_DE *lista);
bool lista_vazia (const LISTA_DE *lista);
bool lista_cheia (const LISTA_DE *lista);

/*
 * Operacoes de recuperacao de dados
 */
void imprime_lista_de(const LISTA_DE *lista);
void __imprime_lista_de(const LISTA_DE *lista);
bool consulta_lista_de(const LISTA_DE *lista, unsigned int posicao,
                       TIPO_DADO *valor);
bool busca_lista_de(const LISTA_DE *lista, const TIPO_DADO *valor,
                    NOH_DE **nodo);
bool obtem_sucessor_de(const NOH_DE *nodo, NOH_DE **sucessor);
bool obtem_predecessor_de(const NOH_DE *nodo, NOH_DE **predecessor);
bool obtem_inicio_de(const LISTA_DE *lista, NOH_DE **nodo);
bool obtem_final_de(const LISTA_DE *lista, NOH_DE **nodo);
bool obtem_valor_no(const NOH_DE *nodo, TIPO_DADO *valor);

/*
 * Operacoes de insercao
 */
bool insere_lista_de(LISTA_DE *lista, const TIPO_DADO *valor,
                     unsigned int posicao);
bool insere_ordenado_de(LISTA_DE *lista, const TIPO_DADO *valor);
bool insere_antes_do_nodo_de(LISTA_DE *lista, const NOH_DE **nodo,
                             const TIPO_DADO *valor);
bool insere_inicio_de(LISTA_DE *lista, const TIPO_DADO *valor);
bool insere_final_de(LISTA_DE *lista, const TIPO_DADO *valor);
bool definir_valor_no(NOH_DE *nodo, const TIPO_DADO *valor);

/*
 * Operacoes de remocao
 */
bool remove_lista_de(LISTA_DE *lista, TIPO_DADO *valor,
                     unsigned int posicao);
bool remove_chave_de(LISTA_DE *lista, const TIPO_DADO *valor);
bool remove_nodo_de(LISTA_DE *lista, NOH_DE **nodo);
bool remove_inicio_de(LISTA_DE *lista, TIPO_DADO *valor);
bool remove_final_de(LISTA_DE *lista, TIPO_DADO *valor);
#endif
