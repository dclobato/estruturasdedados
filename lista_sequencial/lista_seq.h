#ifndef __LISTA__
#define __LISTA__
#define TIPO_DADO int
#define TAM 10

typedef struct
{
    int numElementos;
    int nos[TAM];
} LISTA;

int inicializa_lista (LISTA *);
int insere_inicio (LISTA *, TIPO_DADO);
int insere_final (LISTA *, TIPO_DADO);
int insere_lista (LISTA *, TIPO_DADO, int);
int remove_inicio (LISTA *);
int remove_final (LISTA *);
int remove_lista (LISTA *, int);
int consulta_lista (LISTA *, int*);
void imprime_lista (LISTA *);
#endif

