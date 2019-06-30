#ifndef DEF_PILHA_DINAMICA
#define DEF_PILHA_DINAMICA
#include <stdbool.h>

typedef int TIPO_DADO;

typedef struct __noh
{
  TIPO_DADO dado;
  struct __noh *sucessor;
} NOH;

typedef NOH *PILHA;

bool inicializa_pilha(PILHA *pilha);
bool destroi_pilha(PILHA *pilha);
bool PUSH(PILHA *pilha, const TIPO_DADO *valor);
bool POP(PILHA *pilha, TIPO_DADO *valor);
#endif
