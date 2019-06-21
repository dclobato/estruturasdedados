#ifndef DEF_PILHA_ESTATICA
#define DEF_PILHA_ESTATICA
#include <stdbool.h>

static const unsigned int TAM_PILHA = 10; // Capacidade de pilha
typedef int TIPO_DADO;

typedef struct __pilha
{
  TIPO_DADO dados[TAM_PILHA];
  unsigned int topo;
} PILHA;

bool inicializa_pilha(PILHA *pilha);
bool PUSH(PILHA *pilha, const TIPO_DADO *valor);
bool POP(PILHA *pilha, TIPO_DADO *valor);
bool destroi_pilha(PILHA *pilha);
#endif
