#include <stdio.h>
#include "lista_seq.h"

void inicializa_lista (LISTA *l, int *status)
{
    l->numElementos = 0;
    *status = 1;
    return;
}

void insere_inicio (LISTA * l, TIPO_DADO v, int *status)
{
    int i;

    if (l->numElementos == TAM)
    {
        *status = 0;
        return;
    }

    for (i = l->numElementos; i > 0; i--)
        l->nos[i] = l->nos[i-1];

    l->nos[0] = v;
    l->numElementos = l->numElementos + 1;
    *status = 1;
    return;
}

void insere_final (LISTA *l, TIPO_DADO v, int *status)
{
    if (l->numElementos == TAM)
    {
        *status = 0;
        return;
    }

    l->nos[l->numElementos] = v;
    l->numElementos = l->numElementos + 1;
    *status = 1;
    return;
}

void insere_lista (LISTA *l, TIPO_DADO v, int p, int *status)
{
    int i;

    if ((l->numElementos == TAM) || (p > l->numElementos))
    {
        *status = 0;
        return;
    }

    for (i = l->numElementos; i > p; i--)
        l->nos[i] = l->nos[i-1];

    l->nos[p] = v;
    l->numElementos = l->numElementos + 1;
    *status = 1;
    return;
}

void insere_ordenado (LISTA *l, TIPO_DADO v, int *status)
{
    int i;

    if (l->numElementos == TAM)
    {
        *status = 0;
        return;
    }

    /* Ajustar o segundo predicado da condicao de parada do for para o
     * tipo de dado da lista. Como o exemplo aqui e de lista com valores
     * inteiros, um simples ">" resolve. Se fosse um campo de texto, seria
     * necessario utilizar strcmp, e por ai vai...
     */
    for (i = l->numElementos; ((i > 0) && (v < l->nos[i-1])); i--)
        l->nos[i] = l->nos[i-1];

    l->nos[i] = v;
    l->numElementos = l->numElementos + 1;
    *status = 1;
    return;
}

void remove_inicio (LISTA *l, int *status)
{
    int i;
    if (l->numElementos == 0)
    {
        *status = 0;
        return;
    }

    for (i = 1; i < l->numElementos; i++)
        l->nos[i-1] = l->nos[i];
    l->numElementos = l->numElementos - 1;
    *status = 1;
    return;
}

void remove_final (LISTA *l, int *status)
{
    if (l->numElementos == 0)
    {
        *status = 0;
        return;
    }

    l->numElementos = l->numElementos - 1;
    *status = 1;
    return;
}

void remove_lista (LISTA *l, int p, int *status)
{
    int i;
    if ((l->numElementos == 0) || (p > l->numElementos - 1) || (p < 0))
    {
        *status = 0;
        return;
    }

    for (i = p+1; i < l->numElementos; i++)
        l->nos[i-1] = l->nos[i];

    l->numElementos = l->numElementos - 1;
    *status = 1;
    return;
}

void remove_chave (LISTA *l, int v, int *status)
{
    int i;
    *status = 0;
 
    for (i=0; i<(l->numElementos); i++)
    {
        if (l->nos[i] == v)
        {
            remove_lista (l, i, status);
            i--;
        }
    }
    return;
}

TIPO_DADO consulta_lista (LISTA *l, int p, int* status)
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
     */

    for (i = 0; i < l->numElementos; i++)
        printf("[%03d]: %d\n", i, l->nos[i]);

    return;
}
