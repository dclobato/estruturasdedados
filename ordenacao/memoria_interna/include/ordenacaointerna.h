#ifndef DEF_ORDENACAOINTERNA
#define DEF_ORDENACAOINTERNA
#include <string.h>
#include <stdbool.h>

// this snippet from stackoverflow
// http://stackoverflow.com/questions/3982348/implement-generic-swap-macro-in-c
#define swap(x,y) do \
  { unsigned char swap_temp[sizeof(x) == sizeof(y) ? (signed)sizeof(x) : -1]; \
    memcpy(swap_temp,&y,sizeof(x)); \
    memcpy(&y,&x,       sizeof(x)); \
    memcpy(&x,swap_temp,sizeof(x)); \
  } while(0)

typedef int TIPO_DADO;

// TODO: Problema com o uso de unsigned para tamanho por causa  das operacoes
//       de subtracao podem dar underflow, e não parar o laço. Verificar como
//       mudar os algoritmos quicksort/shellsort/heapsort para  resolver isso
bool bubblesort (TIPO_DADO *arquivo, int tamanho);
bool insertsort (TIPO_DADO *arquivo, int tamanho);
bool selectsort (TIPO_DADO *arquivo, int tamanho);
bool quicksort (TIPO_DADO *arquivo, int tamanho);
bool shellsort (TIPO_DADO *arquivo, int tamanho);
bool heapsort_ (TIPO_DADO *arquivo, int tamanho);

void criaHeap (TIPO_DADO *arquivo, int inicio, int final);
void particao (TIPO_DADO *arquivo, int inicio, int final);
#endif
