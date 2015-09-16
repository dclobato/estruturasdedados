#include <stdlib.h>
#include "pilha.h"

void inicializa_pilha (PILHA *p, int *s)
{
	*p = NULL;
	*s = 1;
	return;
}

void PUSH (PILHA *p, TIPO_DADO v, int *s)
{
	PILHA t;

	t = (PILHA) malloc (sizeof(NOH));
	if (t == NULL)
	{
		*s=0;
		return;
	}
	t->dado = v;
	t->prox = *p;
	*p = t;
	*s = 1;
	return;
}

TIPO_DADO POP (PILHA *p, int *s)
{
	TIPO_DADO v;
	PILHA t;

	if (*p == NULL)
	{
		*s = 0;
		return -1;
	}
	v = (*p)->dado;
	t = *p;
	*p = t->prox;
	free (t);
	*s = 1;
	return (v);
}
