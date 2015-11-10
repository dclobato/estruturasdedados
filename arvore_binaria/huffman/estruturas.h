#ifndef __HUFFMAN__
#define __HUFFMAN__
typedef struct __node
{
    int freq;
    char simbolo[256];
    char codigo[128];
    struct __node *esq;
    struct __node *dir;
    struct __node *prox;
    struct __node *baseprox;
} NODO;

typedef NODO *ARVORE;
typedef NODO *LISTA;

void inicializa_lista (LISTA *);
int insere_ordenado (LISTA *, char *, int, ARVORE, ARVORE, int);
LISTA aloca_noh (void);
void _imprime_arvore (ARVORE, int *);
void imprime_arvore(ARVORE);

#endif
