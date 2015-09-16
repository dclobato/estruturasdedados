#ifndef __LISTA__
#define __LISTA__
#define TIPO_DADO int
#define TAM 30

typedef struct __st_reg
{
    TIPO_DADO dado;
    int proximo;
} NOH;

typedef struct __st_listaee
{
    int NumElementos;
    int NumLivres;
    int InicioElementos;
    int InicioLivres;
    NOH dados[TAM];
} LISTAee;

int tamanho_lee (LISTAee *);
int livres_lee (LISTAee *);
void inicializa_lee (LISTAee *, int *);
int obtem_no_lee (LISTAee *, int *);
void libera_no_lee (LISTAee *, int, int *);
void insere_elemento_lee (LISTAee *, int, int *, TIPO_DADO);
void imprime_lista_bruta (LISTAee *);
void remove_elemento_lee (LISTAee *, int, int *);
void imprime_lee (LISTAee *);

#endif