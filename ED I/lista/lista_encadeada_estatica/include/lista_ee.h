#ifndef DEF_LISTA_ENCADEADA_ESTATICA
#define DEF_LISTA_ENCADEADA_ESTATICA

#include <stdbool.h>

//static const unsigned int TAM_LISTA = 10;  // Capacidade de lista
#define TAM_LISTA 10

typedef int TIPO_DADO;

typedef struct __st_reg
{
  TIPO_DADO dado;
  unsigned int sucessor;
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
bool lista_inicializar(LISTA *lista);
bool lista_destruir(LISTA *lista);
unsigned int lista_numero_de_elementos(const LISTA *lista);
unsigned int lista_numero_de_nos_livres(const LISTA *lista);
bool lista_obter_no(LISTA *lista, unsigned int *posicao);
bool lista_liberar_no(LISTA *lista, unsigned int posicao);
bool lista_esta_cheia(const LISTA *lista);
bool lista_esta_vazia(const LISTA *lista);

/*
 * Operacoes de recuperacao de dados
 */
void __lista_imprime(const LISTA *lista);
void lista_imprime(const LISTA *lista);
bool lista_obter_chave_posicao(LISTA *lista, TIPO_DADO *valor, unsigned int posicao);
bool lista_obter_chave_inicio(const LISTA *lista, TIPO_DADO *valor);
bool lista_obter_chave_final(const LISTA *lista, TIPO_DADO *valor);
bool lista_obter_posicao_chave(const LISTA *lista, const TIPO_DADO *valor, unsigned int *posicao);

/*
 * Operacoes de insercao
 */
bool lista_inserir_chave_posicao(LISTA *lista, const TIPO_DADO *valor, unsigned int posicao);
bool lista_inserir_chave_ordenado(LISTA *lista, const TIPO_DADO *valor);
bool lista_inserir_chave_inicio(LISTA *lista, const TIPO_DADO *valor);
bool lista_inserir_chave_final(LISTA *lista, const TIPO_DADO *valor);
bool lista_definir_chave_posicao(LISTA *lista, const TIPO_DADO *valor, unsigned int posicao);

/*
 * Operacoes de remocao
 */
bool lista_remover_posicao(LISTA *lista, TIPO_DADO *valor, unsigned int posicao);
bool lista_remover_chave(LISTA *lista, const TIPO_DADO *valor);
bool lista_remover_inicio(LISTA *lista, TIPO_DADO *valor);
bool lista_remover_final(LISTA *lista, TIPO_DADO *valor);
#endif
