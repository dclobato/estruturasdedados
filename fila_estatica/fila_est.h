#ifndef __FILA__
#define __FILA__
#define TAM 10


typedef struct __fila
{
    int dados[TAM];
    int inicio;
    int final;
} FILA;

void inicializa_fila (FILA *, int *);
void enfileirar (FILA *, int, int *);
int desenfileirar (FILA *, int *);
int fila_vazia (FILA *);
int tamanho_fila (FILA *);
#endif
