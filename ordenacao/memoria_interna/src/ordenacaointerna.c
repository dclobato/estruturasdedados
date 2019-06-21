#include <string.h>
#include <stdbool.h>
#include <ordenacaointerna.h>

bool bubblesort (TIPO_DADO *arquivo, int tamanho)
{
  int i, j;

  for (i = (tamanho - 1); i > 0; i--)
  {
    for (j = 0; j < i; j++)
    {
      if (arquivo[j + 1] < arquivo[j])
      {
        swap(arquivo[j + 1], arquivo[j]);
      }
    }
  }

  return true;
}

bool heapsort_ (TIPO_DADO *arquivo, int tamanho)
{
  int inicio, fim;

  /* heapify */
  for (inicio = (tamanho - 1) / 2; inicio >= 0; inicio--)
  {
    criaHeap(arquivo, inicio, tamanho);
  }

  for (fim = tamanho - 1; fim > 0; fim--)
  {
    swap(arquivo[fim], arquivo[0]);
    criaHeap(arquivo, 0, fim);
  }

  return true;
}

void criaHeap (TIPO_DADO *arquivo, int inicio, int final)
{
  int raiz, filho;
  raiz = inicio;

  while ((raiz * 2 + 1) < final)
  {
    filho = 2 * raiz + 1;

    if (((filho + 1) < final) && (arquivo[filho + 1] > arquivo[filho]))
    {
      filho = filho + 1;
    }

    if (arquivo[raiz] < arquivo[filho])
    {
      swap(arquivo[filho], arquivo[raiz]);
      raiz = filho;
    }
    else
    {
      break;
    }
  }
}

bool insertsort (int *arquivo, int tamanho)
{
  int i, j;
  TIPO_DADO t;

  for (i = 1; i < tamanho; i++)
  {
    t = arquivo[i];
    j = i;

    while ((j > 0) && (t < arquivo[j - 1]))
    {
      arquivo[j] = arquivo[j - 1];
      j--;
    }

    arquivo[j] = t;
  }

  return true;
}

bool quicksort (TIPO_DADO *arquivo, int tamanho)
{
  particao(arquivo, 0, tamanho - 1);
  return true;
}

void particao (TIPO_DADO *arquivo, int inicio, int final)
{
  int p, i, j;
  p = arquivo[inicio + ((final - inicio) / 2)];
  i = inicio;
  j = final;

  do
  {
    while (arquivo[i] < p)
    {
      i++;
    }

    while (arquivo[j] > p)
    {
      j--;
    }

    if (i <= j)
    {
      swap(arquivo[i], arquivo[j]);
      i++;
      j--;
    }
  } while (i <= j);

  if (inicio < j)
  {
    particao(arquivo, inicio, j);
  }

  if (i < final)
  {
    particao(arquivo, i, final);
  }
}

bool selectsort (int *arquivo, int tamanho)
{
  int i, j, min;

  for (i = 0; i < (tamanho - 1); i++)
  {
    min = i;

    for (j = i + 1; j < tamanho; j++)
    {
      if (arquivo[j] < arquivo[min])
      {
        min = j;
      }
    }

    if (min != i)
    {
      swap(arquivo[i], arquivo[min]);
    }
  }

  return true;
}

bool shellsort (int *arquivo, int tamanho)
{
  int h, i, j;
  TIPO_DADO t;
  h = 1;

  while (h < (tamanho - 1))
  {
    h = 3 * h + 1;
  }

  while (h > 0)
  {
    for (i = h; i < tamanho; i++)
    {
      t = arquivo[i];
      j = i - h;

      while ((j >= 0) && (t < arquivo[j]))
      {
        arquivo[j + h] = arquivo[j];
        j = j - h;
      }

      arquivo[j + h] = t;
    }

    h /= 3;
  }

  return true;
}
