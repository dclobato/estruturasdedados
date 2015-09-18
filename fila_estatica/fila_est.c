#include "fila_est.h"

void inicializa_fila (FILA *f, int *s)
{
    f->inicio = f->final = 0;
    *s = 1;
    return;
}

void enfileirar (FILA *f, int v, int *s)
{
    if (((f->final+1)%TAM) == f->inicio)
    {
        *s = 0;
        return;
    }
    f->dados[f->final] = v;
    f->final = (f->final + 1)%TAM;
    *s = 1;
    return;
}

int desenfileirar (FILA *f, int *s)
{
    int v;
    if (f->inicio == f->final)
    {
        *s = 0;
        return -1;
    }
    v = f->dados[f->inicio];
    f->inicio = (f->inicio+1)%TAM;
    *s = 1;
    return (v);
}

int fila_vazia (FILA *f)
{
    return (f->inicio == f->final);
}

int tamanho_fila (FILA *f)
{
    int in, fi;
    in = f->inicio;
    fi = f->final;
    if (fi < in)
        fi = fi + TAM;
    return (fi - in);
}