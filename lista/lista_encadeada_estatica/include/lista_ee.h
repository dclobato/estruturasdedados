#ifndef __LISTA__
#define __LISTA__

#include <stdbool.h>

//static const unsigned int TAM_LISTA = 10;  // Capacidade de lista
#define TAM_LISTA 10

typedef int TIPO_DADO;

typedef struct __st_reg
{
  TIPO_DADO dado;
  unsigned sucessor;
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
bool lista_inicializa(LISTA *lista);
bool lista_destroi(LISTA *lista);
unsigned int lista_tamanho(const LISTA *lista);
unsigned int lista_livres(const LISTA *lista);
bool __lista_obtem_no(LISTA *lista, unsigned int *posicao);
bool __lista_libera_no(LISTA *lista, unsigned int posicao);
bool lista_cheia(const LISTA *lista);
bool lista_vazia(const LISTA *lista);


/*
 * Operacoes de recuperacao de dados
 */
void __lista_imprime(const LISTA *lista);
void lista_imprime(const LISTA *lista);
bool lista_consulta_posicao(LISTA *lista, unsigned int posicao, TIPO_DADO *valor);
bool lista_busca_chave(const LISTA *lista, const TIPO_DADO *valor, unsigned int *posicao);
bool lista_obtem_inicio(const LISTA *lista, TIPO_DADO *valor);
bool lista_obtem_final(const LISTA *lista, TIPO_DADO *valor);

/*
 * Operacoes de insercao
 */
bool lista_insere(LISTA *lista, const TIPO_DADO *valor, unsigned int posicao);
bool lista_insere_ordenado(LISTA *lista, const TIPO_DADO *valor);
bool lista_insere_final(LISTA *lista, const TIPO_DADO *valor);
bool lista_insere_inicio(LISTA *lista, const TIPO_DADO *valor);
bool lista_definir_valor_posicao (LISTA *lista, unsigned int posicao, const TIPO_DADO *valor);

/*
 * Operacoes de remocao
 */
bool lista_remove_posicao(LISTA *lista, TIPO_DADO *valor, unsigned int posicao);
bool lista_remove_chave(LISTA *lista, TIPO_DADO *valor);
bool lista_remove_inicio(LISTA *lista, TIPO_DADO *valor);
bool lista_remove_final(LISTA *lista, TIPO_DADO *valor);
#endif
