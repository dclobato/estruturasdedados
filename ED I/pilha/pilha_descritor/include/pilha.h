#ifndef DEF_PILHA_DINAMICA_DESCRITOR
#define DEF_PILHA_DINAMICA_DESCRITOR

#include <stdbool.h>

typedef int TIPO_DADO;

typedef struct __noh_pilha
{
  TIPO_DADO dado;
  struct __noh_pilha *sucessor;
} NOH_PILHA;

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

typedef DESCRITOR_PILHA PILHA;

bool pilha_inicializar(PILHA *pilha);
bool pilha_destruir(PILHA *pilha);
bool pilha_PUSH(PILHA *pilha, const TIPO_DADO *valor);
bool pilha_POP(PILHA *pilha, TIPO_DADO *valor);
bool pilha_PEEK(PILHA *pilha, TIPO_DADO *valor);
bool pilha_esta_vazia(const PILHA *pilha);
bool pilha_esta_cheia(const PILHA *pilha);
unsigned int pilha_numero_de_elementos(const PILHA *pilha);
#endif
