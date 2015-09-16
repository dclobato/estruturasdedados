#include "pilha.h"

void inicializa_pilha (PILHA *p, int *s)
{
    p->topo = -1;
    *s = 1;
    return;
}

void PUSH (PILHA *p, TIPO_DADO v, int *s)
{
    if (p->topo == TAM-1)
    {
        *s = 0;
        return;
    }
    p->topo += 1;
    p->dados[p->topo] = v;
    *s = 1;
    return;
}

TIPO_DADO POP (PILHA *p, int *s)
{
    TIPO_DADO t;
    if (p->topo == -1)
    {
        *s = 0;
        return -1;
    }
    t = p->dados[p->topo];
    p->topo -= 1;
    *s = 1;
    return (t);
}
