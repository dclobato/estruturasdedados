#ifndef __PILHA__
#define __PILHA__
typedef struct __noh
{
	float dado;
	struct __noh* prox;
} NOH;

typedef NOH* PILHA;

void inicializa_pilha (PILHA *, int *);
void PUSH (PILHA *, float, int *);
float POP (PILHA *, int *);
#endif
