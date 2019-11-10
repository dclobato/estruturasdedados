#ifndef DEF_PILHA_ESTATICA
#define DEF_PILHA_ESTATICA
#include <stdbool.h>

// static const unsigned int TAM_PILHA = 10; // Capacidade de pilha
#define TAM_PILHA 10

typedef int TIPO_DADO;

typedef struct __pilha
{
  TIPO_DADO dados[TAM_PILHA];
  unsigned int topo;
} PILHA;

bool pilha_inicializa(PILHA *pilha);
bool pilha_PUSH(PILHA *pilha, const TIPO_DADO *valor);
bool pilha_POP(PILHA *pilha, TIPO_DADO *valor);
bool pilha_destroi(PILHA *pilha);
bool pilha_estavazia (const PILHA *pilha);
bool pilha_estacheia (const PILHA *pilha);
unsigned int pilha_numelementos (const PILHA *pilha);
#endif
