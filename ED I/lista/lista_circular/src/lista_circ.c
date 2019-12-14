#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <lista_circ.h>

bool lista_circular_inicializar(LISTA_CIRCULAR *lista)
{
  lista->numElementos = 0;
  lista->final = NULL;
  return true;
}

bool lista_circular_destruir(LISTA_CIRCULAR *lista)
{
  NOH_CIRCULAR *aux, *ant;

  if (lista_circular_esta_vazia(lista))
  {
    return true;
  }

  aux = lista->final;
  do
  {
    ant = aux;
    aux = aux->sucessor;
    lista_circular_liberar_no(&ant);
  } while (aux != lista->final);

  lista->numElementos = 0;
  lista->final = NULL;
  return true;
}

bool list_cicular_obter_no(NOH_CIRCULAR **nodo)
{
  NOH_CIRCULAR *aux;

  aux = (NOH_CIRCULAR *) malloc(sizeof(NOH_CIRCULAR));

  if (aux == NULL)
  {
    return false;
  }

  aux->sucessor = NULL;
  *nodo = aux;
  return true;
}
bool lista_circular_liberar_no(NOH_CIRCULAR **nodo)
{
  if (*nodo == NULL)
  {
    return false;
  }

  free(*nodo);
  *nodo = NULL;
  return true;
}

unsigned int lista_circular_numero_de_elementos(const LISTA_CIRCULAR *lista)
{
  return lista->numElementos;
}

bool lista_circular_esta_vazia(const LISTA_CIRCULAR *lista)
{
  return (lista->numElementos == 0);
}

bool lista_circular_esta_cheia(const LISTA_CIRCULAR *lista)
{
  // Como estamos com alocacao dinamica, nao ha como saber se a lista
  // esta cheia antes de tentar inserir um novo elemento
  return false;
}

void lista_circular_imprimir(const LISTA_CIRCULAR *lista)
{
  NOH_CIRCULAR *aux, *ant;
  unsigned int i;

  printf("Posicoes ocupadas: %d\n", lista_circular_numero_de_elementos(lista));

  if (lista_circular_esta_vazia(lista))
  {
    return;
  }

  ant = lista->final;
  aux = lista->final->sucessor;
  i = 0;
  do
  {
    printf("[%03u]: %d\n", i, aux->dado);
    i++;
    ant = aux;
    aux = aux->sucessor;
  } while (ant != lista->final);

  return;
}

void __lista_circular_imprimir(const LISTA_CIRCULAR *lista)
{
  NOH_CIRCULAR *aux, *ant;
  unsigned int i;

  printf("Posicoes ocupadas: %d\n", lista_circular_numero_de_elementos(lista));
  printf("Posicao do ultimo elemento: %p\n", lista->final);

  if (lista_circular_esta_vazia(lista))
  {
    return;
  }

  ant = lista->final;
  aux = lista->final->sucessor;
  i = 0;
  do
  {
    printf("[%03u - %p]: %d (sucessor: %p)\n", i, aux, aux->dado, aux->sucessor);
    i++;
    ant = aux;
    aux = aux->sucessor;
  } while (ant != lista->final);

  return;
}

bool lista_circular_obter_sucessor_de_no(const NOH_CIRCULAR *nodo, NOH_CIRCULAR **sucessor)
{
  if (nodo == NULL)
  {
    return false;
  }

  *sucessor = nodo->sucessor;
  return true;
}

bool lista_circular_obter_chave_no(const NOH_CIRCULAR *nodo, TIPO_DADO *valor)
{
  if (nodo == NULL)
  {
    return false;
  }
  *valor = nodo->dado;
  return true;
}

bool lista_circular_obter_no_posicao(const LISTA_CIRCULAR *lista, NOH_CIRCULAR **nodo, unsigned int posicao)
{
  NOH_CIRCULAR *aux;
  unsigned int contador;

  if (lista_circular_esta_vazia(lista))
  {
    return false;
  }

  if (posicao > lista_circular_numero_de_elementos(lista) - 1)
  {
    return false;
  }

  aux = lista->final->sucessor;
  for (contador = 0; contador < posicao; contador++)
  {
    aux = aux->sucessor;
  }

  *nodo = aux;
  return true;
}

bool lista_circular_obter_no_inicio(const LISTA_CIRCULAR *lista, NOH_CIRCULAR **nodo)
{
  if (lista_circular_esta_vazia(lista))
  {
    return false;
  }

  *nodo = lista->final->sucessor;
  return true;
}

bool lista_circular_obter_no_final(const LISTA_CIRCULAR *lista, NOH_CIRCULAR **nodo)
{
  if (lista_circular_esta_vazia(lista))
  {
    return false;
  }

  *nodo = lista->final;
  return true;
}

bool lista_circular_obter_no_chave(const LISTA_CIRCULAR *lista, const TIPO_DADO *valor, NOH_CIRCULAR **nodo)
{
  NOH_CIRCULAR *aux;

  if (lista_circular_esta_vazia(lista))
  {
    return false;
  }

  aux = lista->final->sucessor;
  do
  {
    if (aux->dado == *valor)
    {
      break;
    }
    aux = aux->sucessor;
  } while (aux != lista->final);

  *nodo = aux;
  return (aux != lista->final);
}

bool lista_circular_obter_chave_posicao(const LISTA_CIRCULAR *lista, TIPO_DADO *valor, unsigned int posicao)
{
  NOH_CIRCULAR *temp;

  if (lista_circular_esta_vazia(lista))
  {
    return false;
  }

  if (lista_circular_obter_no_posicao(lista, &temp, posicao))
  {
    return lista_circular_obter_chave_no(temp, valor);
  }
  else
  {
    return false;
  }
}

bool lista_circular_obter_chave_inicio(const LISTA_CIRCULAR *lista, TIPO_DADO *valor)
{
  if (lista_circular_esta_vazia(lista))
  {
    return false;
  }

  *valor = lista->final->sucessor->dado;
  return true;
}

bool lista_circular_obter_chave_final(const LISTA_CIRCULAR *lista, TIPO_DADO *valor)
{
  if (lista_circular_esta_vazia(lista))
  {
    return false;
  }

  *valor = lista->final->dado;
  return true;
}

bool lista_circular_obter_posicao_chave(const LISTA_CIRCULAR *lista, const TIPO_DADO *valor, unsigned int *posicao)
{
  NOH_CIRCULAR *aux;

  if (lista_circular_esta_vazia(lista))
  {
    return false;
  }

  if (valor == NULL)
  {
    return false;
  }

  *posicao = 0;
  aux = lista->final->sucessor;
  do
  {
    if (aux->dado == *valor)
    {
      break;
    }
    aux = aux->sucessor;
    *posicao = *posicao + 1;
  } while (aux != lista->final);

  return (aux != lista->final);
}

bool lista_circular_shift_right(LISTA_CIRCULAR *lista)
{
  NOH_CIRCULAR *aux, *ant;

  if (lista_circular_esta_vazia(lista))
  {
    return false;
  }

  ant = lista->final;
  aux = lista->final->sucessor;
  do
  {
    ant = aux;
    aux = aux->sucessor;
  } while (aux != lista->final);

  lista->final = ant;
  return true;
}

bool lista_circular_shift_left(LISTA_CIRCULAR *lista)
{
  if (lista_circular_esta_vazia(lista))
  {
    return false;
  }

  lista->final = lista->final->sucessor;
  return true;
}


bool lista_circular_inserir_chave_posicao(LISTA_CIRCULAR *lista, const TIPO_DADO *valor, unsigned int posicao)
{
  NOH_CIRCULAR *t;
  NOH_CIRCULAR *aux, *ant;
  unsigned int contador;

  if ((valor == NULL) || (posicao > lista_circular_numero_de_elementos(lista)))
  {
    return false;
  }

  if (!list_cicular_obter_no(&t))
  {
    return false;
  }

  t->dado = *valor;
  t->sucessor = t;

  if (lista_circular_esta_vazia(lista))
  {
    lista->final = t;
  }
  else
  {
    contador = 0;
    ant = lista->final;
    aux = lista->final->sucessor;
    while (contador < posicao)
    {
      ant = aux;
      aux = aux->sucessor;
      contador++;
    }

    ant->sucessor = t;
    t->sucessor = aux;
  }
  if (posicao == lista_circular_numero_de_elementos(lista))
  {
    lista->final = t;
  }

  lista->numElementos++;
  return true;
}

bool lista_circular_inserir_chave_antes_no(LISTA_CIRCULAR *lista, const TIPO_DADO *valor, const NOH_CIRCULAR **nodo)
{
  NOH_CIRCULAR *t;
  NOH_CIRCULAR *aux, *ant;
  unsigned int contador, limite;

  if (valor == NULL)
  {
    return false;
  }

  if (!list_cicular_obter_no(&t))
  {
    return false;
  }

  t->dado = *valor;
  t->sucessor = t;

  if (lista_circular_esta_vazia(lista))
  {
    lista->final = t;
  }
  else
  {
    ant = lista->final;
    aux = lista->final->sucessor;
    limite = lista_circular_numero_de_elementos(lista);
    contador = 0;
    do
    {
      if (*nodo == aux)
      {
        break;
      }
      ant = aux;
      aux = aux->sucessor;
      contador++;
    } while (contador < limite);

    ant->sucessor = t;
    t->sucessor = aux;

    if (contador == limite)
    {
      lista->final = t;
    }
  }

  lista->numElementos++;
  return true;
}

bool lista_circular_inserir_chave_ordenado(LISTA_CIRCULAR *lista, const TIPO_DADO *valor)
{
  NOH_CIRCULAR *t;
  NOH_CIRCULAR *aux, *ant;
  unsigned int contador, limite;

  if (valor == NULL)
  {
    return false;
  }

  if (!list_cicular_obter_no(&t))
  {
    return false;
  }

  t->dado = *valor;
  t->sucessor = t;

  if (lista_circular_esta_vazia(lista))
  {
    lista->final = t;
  }
  else
  {
    ant = lista->final;
    aux = lista->final->sucessor;
    limite = lista_circular_numero_de_elementos(lista);
    contador = 0;
    do
    {
      if (*valor <= aux->dado)
      {
        break;
      }
      ant = aux;
      aux = aux->sucessor;
      contador++;
    } while (contador < limite);

    ant->sucessor = t;
    t->sucessor = aux;

    if (contador == limite)
    {
      lista->final = t;
    }
  }

  lista->numElementos++;
  return true;
}

bool lista_circular_inserir_chave_inicio(LISTA_CIRCULAR *lista, const TIPO_DADO *valor)
{
  if (valor == NULL)
  {
    return false;
  }
  return (lista_circular_inserir_chave_posicao(lista, valor, 0));
}

bool lista_circular_inserir_chave_final(LISTA_CIRCULAR *lista, const TIPO_DADO *valor)
{
  if (valor == NULL)
  {
    return false;
  }
  return (lista_circular_inserir_chave_posicao(lista, valor, lista_circular_numero_de_elementos(lista)));
}

bool lista_circular_definir_chave_posicao(LISTA_CIRCULAR *lista, const TIPO_DADO *valor, unsigned int posicao)
{
  NOH_CIRCULAR *aux, *ant;
  unsigned int contador;

  if (lista_circular_esta_vazia(lista))
    return false;

  if ((valor == NULL) || (posicao > lista_circular_numero_de_elementos(lista) - 1))
  {
    return false;
  }

  contador = 0;
  ant = lista->final;
  aux = lista->final->sucessor;
  while (contador < posicao)
  {
    ant = aux;
    aux = aux->sucessor;
    contador++;
  }

  aux->dado = *valor;
  return true;
}

bool lista_circular_definir_chave_no(NOH_CIRCULAR *nodo, const TIPO_DADO *valor)
{
  if ((valor == NULL) || (nodo == NULL))
  {
    return false;
  }

  nodo->dado = *valor;
  return true;
}

bool lista_circular_remover_posicao(LISTA_CIRCULAR *lista, TIPO_DADO *valor, unsigned int posicao)
{
  NOH_CIRCULAR *aux, *ant;
  unsigned int contador;
  unsigned int limite;

  if (lista_circular_esta_vazia(lista))
  {
    return false;
  }

  limite = lista_circular_numero_de_elementos(lista) - 1;
  if (posicao > limite)
  {
    return false;
  }

  contador = 0;
  ant = lista->final;
  aux = lista->final->sucessor;
  while (contador < posicao)
  {
    ant = aux;
    aux = aux->sucessor;
    contador++;
  }

  ant->sucessor = aux->sucessor;

  if (valor != NULL)
  {
    *valor = aux->dado;
  }

  if (contador == limite)
  {
    lista->final = ant;
  }

  lista_circular_liberar_no(&aux);
  lista->numElementos--;
  if (lista_circular_esta_vazia(lista))
  {
    lista->final = NULL;
  }
  return true;
}

bool lista_circular_remover_nodo(LISTA_CIRCULAR *lista, NOH_CIRCULAR **nodo)
{
  NOH_CIRCULAR *aux, *ant;
  unsigned int contador;

  if (lista_circular_esta_vazia(lista))
  {
    return false;
  }

  ant = lista->final;
  aux = lista->final->sucessor;

  contador = 0;
  do
  {
    if (*nodo == aux)
    {
      break;
    }
    ant = aux;
    aux = aux->sucessor;
    contador++;
  } while (ant != lista->final);

  if (*nodo != aux)
  {
    return false;
  }

  ant->sucessor = aux->sucessor;

  if (contador == lista_circular_numero_de_elementos(lista) - 1)
  {
    lista->final = ant;
  }

  lista_circular_liberar_no(&aux);
  lista->numElementos--;
  if (lista_circular_esta_vazia(lista))
  {
    lista->final = NULL;
  }
  return true;
}

bool lista_circular_remover_chave(LISTA_CIRCULAR *lista, const TIPO_DADO *valor)
{
  NOH_CIRCULAR *aux, *ant;
  unsigned int contador;

  if (lista_circular_esta_vazia(lista))
  {
    return false;
  }

  ant = lista->final;
  aux = lista->final->sucessor;

  contador = 0;
  do
  {
    if (*valor == aux->dado)
    {
      break;
    }
    ant = aux;
    aux = aux->sucessor;
    contador++;
  } while (ant != lista->final);

  if (*valor != aux->dado)
  {
    return false;
  }

  ant->sucessor = aux->sucessor;

  if (contador == lista_circular_numero_de_elementos(lista) - 1)
  {
    lista->final = ant;
  }

  lista_circular_liberar_no(&aux);
  lista->numElementos--;
  if (lista_circular_esta_vazia(lista))
  {
    lista->final = NULL;
  }
  return true;
}

bool lista_circular_remover_inicio(LISTA_CIRCULAR *lista, TIPO_DADO *valor)
{
  if (lista_circular_esta_vazia(lista))
  {
    return false;
  }

  return (lista_circular_remover_posicao(lista, valor, 0));
}

bool lista_circular_remover_final(LISTA_CIRCULAR *lista, TIPO_DADO *valor)
{
  if (lista_circular_esta_vazia(lista))
  {
    return false;
  }

  return (lista_circular_remover_posicao(lista, valor, lista_circular_numero_de_elementos(lista) - 1));
}
