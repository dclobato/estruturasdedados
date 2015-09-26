#ifndef __LISTA_ED__
#define __LISTA_ED__
#define TIPO_DADO int

typedef struct __noh {
    TIPO_DADO dado;
    struct __noh *prox;
} NOH;

typedef NOH *LISTA_ED;

TIPO_DADO consulta_lista (LISTA_ED *l, int p, int* status);
void imprime_lista (LISTA_ED *l);
void inicializa_lista (LISTA_ED *l, int *status);
void insere_final (LISTA_ED *l, TIPO_DADO v, int *status);
void insere_inicio (LISTA_ED * l, TIPO_DADO v, int *status);
void insere_lista (LISTA_ED *l, TIPO_DADO v, int p, int *status);
void insere_ordenado (LISTA_ED *l, TIPO_DADO v, int *status);
void remove_final (LISTA_ED *l, int *status);
void remove_inicio (LISTA_ED *l, int *status);
void remove_lista (LISTA_ED *l, int p, int *status);
void remove_chave (LISTA_ED *l, TIPO_DADO v, int *status);
#endif