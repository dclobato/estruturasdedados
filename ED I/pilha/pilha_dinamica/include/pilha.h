#ifndef DEF_PILHA_DINAMICA
#define DEF_PILHA_DINAMICA

#include <stdbool.h>

typedef int TIPO_DADO;

typedef struct st_noh_pilha
{
  TIPO_DADO dado;
  struct st_noh_pilha *sucessor;
} NOH_PILHA;

typedef NOH_PILHA *PILHA;

bool pilha_inicializar(PILHA *pilha);
bool pilha_destruir(PILHA *pilha);
bool pilha_PUSH(PILHA *pilha, const TIPO_DADO *valor);
bool pilha_POP(PILHA *pilha, TIPO_DADO *valor);
bool pilha_PEEK(PILHA *pilha, TIPO_DADO *valor);
bool pilha_esta_vazia(const PILHA *pilha);
bool pilha_esta_cheia(const PILHA *pilha);
unsigned int pilha_numero_de_elementos(const PILHA *pilha);
#endif
