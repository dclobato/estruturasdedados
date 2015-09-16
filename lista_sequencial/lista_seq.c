#include "lista_seq.h"

int inicializa_lista (LISTA *l)
{
    l->numElementos = 0;
    return 1;
}

int insere_inicio (LISTA * l, int v)
{
    int i;

    if (l->numElementos == TAM)
        return 0;

    for (i = l->numElementos; i > 0; i--)
        l->nos[i] = l->nos[i-1];

    l->nos[0] = v;
    l->numElementos = l->numElementos + 1;
    return 1;
}

int insere_final (LISTA *l, int v)
{
    if (l->numElementos == TAM)
        return 0;

    l->nos[l->numElementos] = v;
    l->numElementos = l->numElementos + 1;
    return 1;
}

int insere_lista (LISTA *l, int v, int p)
{
    int i;

    if ((l->numElementos == TAM) || (p > l->numElementos))
        return 0;

    for (i = l->numElementos; i > p; i--)
        l->nos[i] = l->nos[i-1];

    l->nos[p] = v;
    l->numElementos = l->numElementos + 1;
    return 1;
}

int remove_inicio (LISTA *l)
{
    int i;
    if (l->numElementos == 0)
        return 0;

    for (i = 1; i < l->numElementos; i++)
        l->nos[i-1] = l->nos[i];
    l->numElementos = l->numElementos - 1;
    return 1;
}

int remove_final (LISTA *l)
{
    if (l->numElementos == 0)
        return 0;

    l->numElementos = l->numElementos - 1;
    return 1;
}

int remove_lista (LISTA *l, int p)
{
    int i;
    if ((l->numElementos == 0) || (p > l->numElementos - 1) || (p < 0))
        return 0;

    for (i = p+1; i < l->numElementos; i++)
        l->nos[i-1] = l->nos[i];

    l->numElementos = l->numElementos - 1;
    return 1;
}

TIPO_DADO consulta_lista (LISTA *l, int* status)
{
    TIPO_DADO t;
    if ((l->numElementos == 0) || (p > l->numElementos - 1) || (p < 0))
    {
        *status = 0;
        return 0;
    }
    t = l->nos[p];
    *status = 1;
    return (t);
}

void imprime_lista (LISTA *l)
{
    int i;

    printf("Lista com %d elementos usados de %d disponiveis\n", l->numElementos, TAM);
    /* Faca o que for necessario aqui para mostrar o seu tipo de dado.
     * Por exemplo, se o TIPO_DADO for int, algo do tipo abaixo resolve
     *
     * for (i = 0; i < l->numElementos; i++)
     *   printf("[%03d]: %d\n", i, l->nos[i]);
     *
     */
    return;
}
