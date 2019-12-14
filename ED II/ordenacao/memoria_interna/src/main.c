#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include <ordenacaointerna.h>

void mostrar(int *a, unsigned n);
void copiar(int *, int *, unsigned);

int main()
{
  const unsigned int TAM = 5000;
  int i;
  int *arquivo_original;
  int *arquivo_para_ordenar;
  srand(time(NULL));
  arquivo_original = (int *) malloc(TAM * sizeof(int));
  arquivo_para_ordenar = (int *) malloc(TAM * sizeof(int));

  for (i = 0 ; i < TAM; i++)
  {
    arquivo_original[i] = rand() % 15000;
  }

  printf("  Original: ");
  mostrar(arquivo_original, TAM);
  printf("%s ordenado!\n", esta_ordenado(arquivo_original, TAM) ? "Esta" : "Nao esta");

  printf("Bubblesort: ");
  copiar(arquivo_original, arquivo_para_ordenar, TAM);
  bubblesort(arquivo_para_ordenar, TAM);
  mostrar(arquivo_para_ordenar, TAM);
  printf("%s ordenado!\n", esta_ordenado(arquivo_para_ordenar, TAM) ? "Esta" : "Nao esta");

  printf("Insertsort: ");
  copiar(arquivo_original, arquivo_para_ordenar, TAM);
  insertsort(arquivo_para_ordenar, TAM);
  mostrar(arquivo_para_ordenar, TAM);
  printf("%s ordenado!\n", esta_ordenado(arquivo_para_ordenar, TAM) ? "Esta" : "Nao esta");

  printf("Selectsort: ");
  copiar(arquivo_original, arquivo_para_ordenar, TAM);
  selectsort(arquivo_para_ordenar, TAM);
  mostrar(arquivo_para_ordenar, TAM);
  printf("%s ordenado!\n", esta_ordenado(arquivo_para_ordenar, TAM) ? "Esta" : "Nao esta");

  printf(" Quicksort: ");
  copiar(arquivo_original, arquivo_para_ordenar, TAM);
  quicksort(arquivo_para_ordenar, TAM);
  mostrar(arquivo_para_ordenar, TAM);
  printf("%s ordenado!\n", esta_ordenado(arquivo_para_ordenar, TAM) ? "Esta" : "Nao esta");

  printf(" Shellsort: ");
  copiar(arquivo_original, arquivo_para_ordenar, TAM);
  shellsort(arquivo_para_ordenar, TAM);
  mostrar(arquivo_para_ordenar, TAM);
  printf("%s ordenado!\n", esta_ordenado(arquivo_para_ordenar, TAM) ? "Esta" : "Nao esta");

  printf("  Heapsort: ");
  copiar(arquivo_original, arquivo_para_ordenar, TAM);
  heapsort_(arquivo_para_ordenar, TAM);
  mostrar(arquivo_para_ordenar, TAM);
  printf("%s ordenado!\n", esta_ordenado(arquivo_para_ordenar, TAM) ? "Esta" : "Nao esta");
  return 0;
}


void mostrar(int *a, unsigned n)
{
  printf ("[%d] --- [%d]\n", a[0], a[n-1]);
  return;
  unsigned i;

  for (i = 0; i < n; i++)
  {
    printf("%4d ", a[i]);
  }

  printf("\n");
}


void copiar(int *a, int *b, unsigned n)
{
  memcpy(b, a, n * sizeof(int));
}

