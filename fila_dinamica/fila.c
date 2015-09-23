#include <stdlib.h>
#include "fila.h"

void inicializa_fila (FILA *f, int *s)
{
    *f = NULL;
    *s = 1;
    return;
}

void enfileirar (FILA *f, TIPO_DADO v, int *s)
{
    FILA aux, ant, p;

    aux = (FILA) malloc (sizeof (NOH));
    if (aux == NULL)
    {
        *s = 0;
        return;
    }

    aux->dado = v;
    aux->prox = NULL;

    p = *f;
    ant = NULL;
    while (p != NULL)
    {
        ant = p;
        p = p->prox;
    }
    if (ant == NULL)
        *f = aux;
    else
        ant->prox = aux;
    *s = 1;
    return;
}

TIPO_DADO desenfileirar (FILA *f, int *s)
{
    TIPO_DADO v;
    FILA t;
    if (*f == NULL)
    {
        *s = 0;
        return -1;
    }
    t = *f;
    v = t->dado;
    *f = t->prox;
    free (t);
    *s = 1;
    return (v);
}

int fila_vazia (FILA *f)
{
    return (*f == NULL);
}

int tamanho_fila (FILA *f)
{
    int count;
    FILA p;

    count = 0;
    p = *f;

    while (p != NULL)
    {
        count++;
        p = p->prox;
    }

    return (count);
}
