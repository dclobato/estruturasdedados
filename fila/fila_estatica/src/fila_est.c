#include <stdio.h>
#include <stdbool.h>
#include <fila_est.h>

bool inicializa_fila (FILA *fila)
{
  fila->inicio = fila->final = 0;
  return true;
}

bool destroi_fila (FILA *fila)
{
  fila->inicio = fila->final = 0;
  return true;
}

unsigned int tamanho_fila (const FILA *fila)
{
  unsigned int final;

  final = fila->final + (fila->final < fila->inicio ? TAM_FILA : 0);

  return (final - fila->inicio);
}

bool fila_vazia (const FILA *fila)
{
  return (fila->inicio == fila->final);
}

void imprime_fila (const FILA *fila)
{
  unsigned int i;

  for (i = 0; i < TAM_FILA; i++)
  {
    printf("[%03u]: %d", i, fila->dados[i]);

    if (i == fila->inicio)
    {
      printf(" (inicio)");
    }

    if (i == fila->final)
    {
      printf(" (final)");
    }

    printf("\n");
  }
}

bool enfileira (FILA *fila, const TIPO_DADO *valor)
{
  if ((!valor) || (((fila->final + 1) % TAM_FILA) == fila->inicio))
  {
    return false;
  }

  fila->dados[fila->final] = *valor;
  fila->final = (fila->final + 1) % TAM_FILA;
  return true;
}

bool enfileira_prioridade (FILA *fila, const TIPO_DADO *valor)
{
  unsigned int in, i;
  unsigned int limite;

  if ((!valor) || (tamanho_fila(fila) == TAM_FILA - 1))
  {
    return false;
  }

  if (fila_vazia(fila))
  {
    return enfileira(fila, valor);
  }

  in = (fila->final - 1 + TAM_FILA) % TAM_FILA;
  i = 0;
  limite = tamanho_fila(fila);

  while (i < limite)
  {
    if (fila->dados[in] <= *valor)
    {
      break;
    }

    fila->dados[(in + 1 + TAM_FILA) % TAM_FILA] = fila->dados[in];
    in = (in - 1 + TAM_FILA) % TAM_FILA;
    i++;
  }

  fila->dados[(in + 1 + TAM_FILA) % TAM_FILA] = *valor;
  fila->final = (fila->final + 1 + TAM_FILA) % TAM_FILA;
  return true;
}

bool desenfileira (FILA *fila, TIPO_DADO *valor)
{
  if (fila->inicio == fila->final)
  {
    return false;
  }

  *valor = fila->dados[fila->inicio];
  fila->inicio = (fila->inicio + 1) % TAM_FILA;
  return true;
}
