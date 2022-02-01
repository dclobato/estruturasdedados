#ifndef DEF_PILHA_ESTATICA
#define DEF_PILHA_ESTATICA

#include <stdbool.h>

// static const unsigned int TAM_PILHA = 10; // Capacidade de pilha
#define TAM_PILHA 10

typedef int TIPO_DADO;

typedef struct st_pilha
{
  TIPO_DADO dados[TAM_PILHA];
  unsigned int topo;
} PILHA;

bool pilha_inicializar(PILHA *pilha);
bool pilha_PUSH(PILHA *pilha, const TIPO_DADO *valor);
bool pilha_POP(PILHA *pilha, TIPO_DADO *valor);
bool pilha_PEEK(PILHA *pilha, TIPO_DADO *valor);
bool pilha_destruir(PILHA *pilha);
bool pilha_esta_vazia(const PILHA *pilha);
bool pilha_esta_cheia(const PILHA *pilha);
unsigned int pilha_numero_de_elementos(const PILHA *pilha);
#endif
