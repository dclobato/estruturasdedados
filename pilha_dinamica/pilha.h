#ifndef __PILHA__
#define __PILHA__
#define TIPO_DADO int
typedef struct __noh
{
	TIPO_DADO dado;
	struct __noh* prox;
} NOH;

typedef NOH* PILHA;

void inicializa_pilha (PILHA *, int *);
void PUSH (PILHA *, TIPO_DADO, int *);
TIPO_DADO POP (PILHA *, int *);
#endif
