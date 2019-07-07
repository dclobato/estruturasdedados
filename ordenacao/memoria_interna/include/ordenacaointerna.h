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

bool bubblesort (TIPO_DADO *arquivo, unsigned int tamanho);
bool insertsort (TIPO_DADO *arquivo, unsigned int tamanho);
bool selectsort (TIPO_DADO *arquivo, unsigned int tamanho);
bool quicksort (TIPO_DADO *arquivo, unsigned int tamanho);
void particao (TIPO_DADO *arquivo, unsigned int inicio, unsigned int final);
bool shellsort (TIPO_DADO *arquivo, unsigned int tamanho);
bool heapsort_ (TIPO_DADO *arquivo, unsigned int tamanho);
void criaHeap (TIPO_DADO *arquivo, unsigned int inicio, unsigned int final);
bool esta_ordenado(TIPO_DADO *arquivo, unsigned int tamanho);
#endif
