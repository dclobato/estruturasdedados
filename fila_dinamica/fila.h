#ifndef __FILA__
#define __FILA__
#define TIPO_DADO int
typedef struct __noh
{
    TIPO_DADO dado;
    struct __noh* prox;
} NOH;

typedef NOH* FILA;

void inicializa_fila (FILA *, int *);
void enfileirar (FILA *, TIPO_DADO, int *);
TIPO_DADO desenfileirar (FILA *, int *);
int fila_vazia (FILA *);
int tamanho_fila (FILA *);
#endif

