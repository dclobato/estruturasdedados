#ifndef __PILHA__
#define __PILHA__
#define TAM 4
typedef struct __pilha
{
    float dados[TAM];
    int topo;
} PILHA;

void inicializa_pilha (PILHA *, int *);
void PUSH (PILHA *, float, int *);
float POP (PILHA *, int *);
#endif
