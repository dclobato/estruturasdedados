#ifndef DEF_ARVORE_BINARIA
#define DEF_ARVORE_BINARIA
#include <stdbool.h>
#include <string.h>

// this snippet from stackoverflow
// http://stackoverflow.com/questions/3982348/implement-generic-swap-macro-in-c
#define swap(x, y) do \
  { unsigned char swap_temp[sizeof(x) == sizeof(y) ? (signed)sizeof(x) : -1]; \
    memcpy(swap_temp,&y,sizeof(x)); \
    memcpy(&y,&x,       sizeof(x)); \
    memcpy(&x,swap_temp,sizeof(x)); \
  } while(0)

typedef int TIPO_DADO;

typedef enum
{
  RAIZ, ESQ, DIR
} TipoNo;

typedef enum
{
  PRE, POS, IN, LARGURA
} TipoPercurso;

typedef struct __noarvore
{
  int dado;
  struct __noarvore *esq;
  struct __noarvore *dir;
} NO_ARVORE;

typedef NO_ARVORE *ARVORE;

typedef struct
{
  unsigned tamanho;
  TIPO_DADO *nodos;
} PERCURSO;

/*
 * Operacoes de inicializacao e destruicao
 */
bool arvore_binaria_inicializar(ARVORE *arvore);
bool arvore_binaria_destruir(ARVORE *arvore);
bool arvore_binaria_obter_no(ARVORE *arvore);
bool arvore_binaria_liberar_no(ARVORE *arvore);

/*
 * Metadados
 */
unsigned arvore_binaria_altura(const ARVORE *arvore);
unsigned arvore_binaria_numero_nodos(const ARVORE *arvore);
unsigned arvore_binaria_nivel_nodo(const ARVORE *arvore, const TIPO_DADO *valor);
unsigned __nivel_do_nodo(const ARVORE *arvore, const TIPO_DADO *valor, unsigned nivel);

/*
 * Operacao de insercao e remocao
 */
bool arvore_binaria_inserir_chave(ARVORE *arvore, TipoNo tipo, const TIPO_DADO *valor);
bool arvore_binaria_sucessor_in_ordem(const ARVORE *raiz, ARVORE *sucessor, ARVORE *pai_sucessor);

/*
 * Operacoes de Arvore Binaria de Busca
 */
bool arvore_binaria_busca_inserir_chave(ARVORE *arvore, const TIPO_DADO *valor);
bool arvore_binaria_busca_pesquisar_chave(ARVORE *arvore, const TIPO_DADO *valor, ARVORE *nodo);
bool arvore_binaria_busca_remover_chave(ARVORE *arvore, const TIPO_DADO *valor);

/*
 * Percursos
 */
void arvore_binaria_imprimir(const ARVORE *arvore);
bool arvore_binaria_percorrer(const ARVORE *arvore, TipoPercurso tipo, PERCURSO *percurso);
bool arvore_binaria_destruir_percurso(PERCURSO *percurso);

/*
 * Funcoes internas
 */
void __imprime_arvore(const ARVORE *arvore, unsigned int *linha);
bool __percurso_pre(const ARVORE *arvore, PERCURSO *percurso);
bool __percurso_in(const ARVORE *arvore, PERCURSO *percurso);
bool __percurso_pos(const ARVORE *arvore, PERCURSO *percurso);
bool __percurso_largura(const ARVORE *arvore, PERCURSO *percurso);

/*
 * Estrutura de dados auxiliar para percurso em largura
 * Eh possivel fazer sem ela, com vetor, mas ja que esta pronta,
 * ficamos com ela
 */
struct __NOH_FILA_AB
{
  ARVORE item;
  struct __NOH_FILA_AB *prox;
};

typedef struct __NOH_FILA_AB *FILA;

bool __cria_fila(FILA *fila);
bool __insere_fila(FILA *fila, ARVORE nodo);
bool __remove_fila(FILA *fila, ARVORE *nodo);
#endif
