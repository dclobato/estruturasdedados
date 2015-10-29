#include <stdio.h>
#include <stdlib.h>
#include "arvorebinaria.h"

void inicializa_arvore (ARVORE *t, int *status)
{
    *t = NULL;
    *status = 1;
    return;
}

ARVORE aloca_no_arvore (int v, int *status)
{
    ARVORE t;

    t = malloc (sizeof (NO_ARVORE));
    if (t == NULL)
    {
        *status = 0;
    }
    else
    {
        t->dado = v;
        t->esq = NULL;
        t->dir = NULL;
        *status = 1;
    }
    return (t);
}

void insere_abb (ARVORE *t, ARVORE *f, int *status)
{
    ARVORE p, antes;
    // Se arvore esta vazia, manda bala ai mesmo
    if (*t == NULL)
    {
        printf("Inserindo raiz da ABB\n");
        definir_arvore (t, RAIZ, f, status);
        return;
    }

    // Caso contrario, vamos procurar onde colocar
    p = *t;
    antes = NULL;
    while (p != NULL)
    {
        if (p->dado == (*f)->dado)
        {
            *status = 0;
            return;
        }
        antes = p;
        if ((*f)->dado < p->dado)
            p = p->esq;
        else
            p = p->dir;
    }
    if ((*f)->dado < antes->dado)
        definir_arvore (&antes, ESQ, f, status);
    else
        definir_arvore (&antes, DIR, f, status);
}

void definir_arvore (ARVORE *t, TipoNo tipono, ARVORE *f, int *status)
{
    *status = 0;
    if (((tipono == ESQ) || (tipono == DIR)) && (*t == NULL))
        return;
    if ((tipono == RAIZ) && (*t == NULL))
    {
        *t = *f;
        *status = 1;
    }
    if ((tipono == ESQ) && ((*t)->esq == NULL))
    {
        (*t)->esq = *f;
        *status = 1;
    }
    if ((tipono == DIR) && ((*t)->dir == NULL))
    {
        (*t)->dir = *f;
        *status = 1;
    }
    return;
}

void percurso_pre (ARVORE t)
{
    if (t != NULL)
    {
        printf("%d ", t->dado);
        percurso_pre (t->esq);
        percurso_pre (t->dir);
    }
    return;
}

void percurso_in (ARVORE t)
{
    if (t != NULL)
    {
        percurso_in (t->esq);
        printf("%d ", t->dado);
        percurso_in (t->dir);
    }
    return;
}

void percurso_pos (ARVORE t)
{
    if (t != NULL)
    {
        percurso_pos (t->esq);
        percurso_pos (t->dir);
        printf("%d ", t->dado);
    }
    return;
}

void _imprime_arvore( ARVORE treePtr, int *row)
{
    if (treePtr != NULL) {
        (*row)++;
        _imprime_arvore(treePtr->dir,row);
        int i;
        for(i=0; i<(3*(*row)); i++)
            printf(" ");

        printf("%d\n", treePtr->dado);
        _imprime_arvore(treePtr->esq,row);
        (*row)--;
    }
}

void imprime_arvore(ARVORE treePtr) {
    int row = 0;
    _imprime_arvore(treePtr,&row);
}
