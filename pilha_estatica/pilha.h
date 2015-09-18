#ifndef __PILHA__
#define __PILHA__
#define TAM 10                  // Capacidade de pilha
#define TIPO_DADO int
typedef struct __pilha
{
    TIPO_DADO dados[TAM];
    int topo;
} PILHA;

void inicializa_pilha (PILHA *, int *);
void PUSH (PILHA *, TIPO_DADO, int *);
TIPO_DADO POP (PILHA *, int *);
#endif
