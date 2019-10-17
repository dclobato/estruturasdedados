#ifndef DEF_PILHA_DINAMICA
#define DEF_PILHA_DINAMICA

#include <stdbool.h>

typedef int TIPO_DADO;

typedef struct __noh_pilha
{
    TIPO_DADO dado;
    struct __noh_pilha *sucessor;
} NOH_PILHA;

typedef NOH_PILHA *PILHA;

typedef struct __descritor_pilha
{
    unsigned int numelementos;
    // qualquer outra informação que valha a pena manter armazenada
    // no descritor, para reduzir o tempo de processamento, como
    // por exemplo:
    // - maior valor
    // - menor valor
    // - valor medio
    // - posicao do ultimo elemento
    // ...
    NOH_PILHA *elementos_da_pilha;
} DESCRITOR_PILHA;

typedef DESCRITOR_PILHA PILHA_DESCRITOR;


bool pilha_inicializa (PILHA *pilha);
bool pilha_destroi (PILHA *pilha);
bool pilha_PUSH (PILHA *pilha, const TIPO_DADO *valor);
bool pilha_POP (PILHA *pilha, TIPO_DADO *valor);
bool pilha_estavazia (const PILHA *pilha);
bool pilha_estacheia (const PILHA *pilha);
unsigned int pilha_numelementos (const PILHA *pilha);

bool pilha_descritor_inicializa (PILHA_DESCRITOR *pilha);
bool pilha_descritor_destroi (PILHA_DESCRITOR *pilha);
bool pilha_descritor_PUSH (PILHA_DESCRITOR *pilha, const TIPO_DADO *valor);
bool pilha_descritor_POP (PILHA_DESCRITOR *pilha, TIPO_DADO *valor);
bool pilha_descritor_estavazia (const PILHA_DESCRITOR *pilha);
bool pilha_descritor_estacheia (const PILHA_DESCRITOR *pilha);
unsigned int pilha_descritor_numelementos (const PILHA_DESCRITOR *pilha);
#endif
