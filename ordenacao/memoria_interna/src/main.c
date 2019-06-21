#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ordenacaointerna.h>

void mostrar(int *, int);
void copiar(int *, int *, int);

int main()
{
  const int TAM = 13;
  int i;
  int *arquivo_original;
  int *arquivo_para_ordenar;
  srand(time(NULL));
  arquivo_original = (int *) malloc(TAM * sizeof(int));
  arquivo_para_ordenar = (int *) malloc(TAM * sizeof(int));

  for (i = 0 ; i < TAM; i++)
  {
    arquivo_original[i] = rand() % 1000;
  }

  printf("  Original: ");
  mostrar(arquivo_original, TAM);
  copiar(arquivo_original, arquivo_para_ordenar, TAM);
  bubblesort(arquivo_para_ordenar, TAM);
  printf("Bubblesort: ");
  mostrar(arquivo_para_ordenar, TAM);
  copiar(arquivo_original, arquivo_para_ordenar, TAM);
  insertsort(arquivo_para_ordenar, TAM);
  printf("Insertsort: ");
  mostrar(arquivo_para_ordenar, TAM);
  copiar(arquivo_original, arquivo_para_ordenar, TAM);
  selectsort(arquivo_para_ordenar, TAM);
  printf("Selectsort: ");
  mostrar(arquivo_para_ordenar, TAM);
  copiar(arquivo_original, arquivo_para_ordenar, TAM);
  printf(" Quicksort: ");
  quicksort(arquivo_para_ordenar, TAM);
  mostrar(arquivo_para_ordenar, TAM);
  copiar(arquivo_original, arquivo_para_ordenar, TAM);
  printf(" Shellsort: ");
  shellsort(arquivo_para_ordenar, TAM);
  mostrar(arquivo_para_ordenar, TAM);
  copiar(arquivo_original, arquivo_para_ordenar, TAM);
  printf("  Heapsort: ");
  heapsort_(arquivo_para_ordenar, TAM);
  mostrar(arquivo_para_ordenar, TAM);
  return 0;
}


void mostrar(int *a, int n)
{
  int i;

  for (i = 0; i < n; i++)
  {
    printf("%4d ", a[i]);
  }

  printf("\n");
}


void copiar(int *a, int *b, int n)
{
  memcpy(b, a, n * sizeof(int));
}
