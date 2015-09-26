#include <stdio.h>
#include <stdlib.h>
#include "lista_ed.h"

void inicializa_lista (LISTA_ED *l, int *status)
{
    *l = NULL;
    *status = 1;
    return;
}

void imprime_lista (LISTA_ED *l)
{
    LISTA_ED p;

    p = *l;
    while (p != NULL)
    {
        printf("%d ", p->dado);
        p = p->prox;
    }
    printf("\n");
    return;
}

// void void remove_final (LISTA_ED *l, int *status)


void insere_inicio (LISTA_ED * l, TIPO_DADO v, int *status)
{
    LISTA_ED t;

    t = malloc (sizeof(NOH));
    if (t == NULL)
    {
        *status = 0;
        return;
    }
    t->dado = v;
    t->prox = *l;
    *l = t;
    *status = 1;
    return;
}

void insere_lista (LISTA_ED *l, TIPO_DADO v, int p, int *status)
{
    LISTA_ED t;
    LISTA_ED ant, pt;
    int pos;

    t = malloc (sizeof(NOH));
    if (t == NULL)
    {
        *status = 0;
        return;
    }
    t->dado = v;
    ant = NULL;
    pt = *l;
    pos = 0;
    while ((pt != NULL) && (pos != p))
    {
        pos += 1;
        ant = pt;
        pt = pt->prox;
    }
    if (pos != p)   // Nao cheguei na posicao que eu queria
    {
        *status = 0;
        free (t);
        return;
    }
    if (ant == NULL) // Primeira posicao (ou lista vazia)
    {
        t->prox = *l;
        *l = t;
    }
    else            // Qualquer outra posicao
    {
        t->prox = ant->prox;
        ant->prox = t;
    }
    *status = 1;
    return;
}


// void insere_ordenado (LISTA_ED *l, TIPO_DADO v, int *status);
void insere_final (LISTA_ED *l, TIPO_DADO v, int *status)
{
    LISTA_ED t;
    LISTA_ED ant, p;

    t = malloc (sizeof(NOH));
    if (t == NULL)
    {
        *status = 0;
        return;
    }
    t->dado = v;
    t->prox = NULL;
    ant = NULL;
    p = *l;
    while (p != NULL)
    {
        ant = p;
        p = p->prox;
    }
    if (ant == NULL)
        *l = t;
    else
        ant->prox = t;
    *status = 1;
    return;
}
// void remove_inicio (LISTA_ED *l, int *status);
// void remove_lista (LISTA_ED *l, int p, int *status);
// void remove_chave (LISTA_ED *l, TIPO_DADO v, int *status);
// TIPO_DADO consulta_lista (LISTA_ED *l, int p, int* status);
