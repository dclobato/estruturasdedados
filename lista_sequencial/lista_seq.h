#ifndef __LISTA__
#define __LISTA__
#define TIPO_DADO int
#define TAM 10

typedef struct
{
    int numElementos;
    int nos[TAM];
} LISTA;

TIPO_DADO consulta_lista (LISTA *l, int p, int* status);
void imprime_lista (LISTA *l);
void inicializa_lista (LISTA *l, int *status);
void insere_final (LISTA *l, TIPO_DADO v, int *status);
void insere_inicio (LISTA * l, TIPO_DADO v, int *status);
void insere_lista (LISTA *l, TIPO_DADO v, int p, int *status);
void insere_ordenado (LISTA *l, TIPO_DADO v, int *status);
void remove_final (LISTA *l, int *status);
void remove_inicio (LISTA *l, int *status);
void remove_lista (LISTA *l, int p, int *status);
void remove_chave (LISTA *l, TIPO_DADO v, int *status);
#endif
