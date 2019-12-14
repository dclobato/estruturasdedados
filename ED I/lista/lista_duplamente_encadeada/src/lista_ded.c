#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <lista_ded.h>

bool lista_inicializar(LISTA *lista)
{
  lista->numElementos = 0;
  lista->final = NULL;
  lista->inicio = NULL;
  return true;
}

bool lista_esta_vazia(const LISTA *lista)
{
  return (lista->numElementos == 0);
}

bool lista_esta_cheia(const LISTA *lista)
{
  // Como estamos com alocacao dinamica, nao ha como saber se a lista
  // esta cheia antes de tentar inserir um novo elemento
  return false;
}

void lista_imprimir(const LISTA *lista)
{

  NOH_LISTA *aux;
  unsigned int i;

  printf("Posicoes ocupadas: %u\n", lista_numero_de_elementos(lista));
  aux = lista->inicio;
  i = 0;

  while (aux != NULL)
  {
    printf("[%03u]: %d\n", i, aux->dado);
    aux = aux->sucessor;
    i++;
  }

  printf("\n");
}

void __lista_imprimir(const LISTA *lista)
{
  NOH_LISTA *aux;
  unsigned int i;

  printf("Posicoes ocupadas........: %u\n", lista_numero_de_elementos(lista));
  printf("Posicao primeiro elemento: %p\n", lista->inicio);
  printf("Posicao ultimo elemento..: %p\n", lista->final);

  aux = lista->inicio;
  i = 0;
  while (aux != NULL)
  {
    printf("[%03u]: %d   (predecessor: %14p, p: %14p, sucessor: %14p)\n", i, aux->dado, aux->predecessor, aux,
           aux->sucessor);
    aux = aux->sucessor;
    i++;
  }

  printf("\n");
}

unsigned int lista_numero_de_elementos(const LISTA *lista)
{
  return (lista->numElementos);
}

bool lista_destruir(LISTA *lista)
{
  NOH_LISTA *aux, *ant;

  aux = lista->inicio;
  while (aux != NULL)
  {
    ant = aux;
    aux = aux->sucessor;
    lista_liberar_no(&ant);
  }

  lista->numElementos = 0;
  lista->inicio = NULL;
  lista->final = NULL;
  return true;
}

bool lista_obter_no(NOH_LISTA **nodo)
{
  NOH_LISTA *aux;
  aux = (NOH_LISTA *) malloc(sizeof(NOH_LISTA));

  if (aux == NULL)
  {
    return false;
  }

  aux->sucessor = NULL;
  aux->predecessor = NULL;
  *nodo = aux;
  return true;
}

bool lista_liberar_no(NOH_LISTA **nodo)
{
  if (*nodo == NULL)
  {
    return false;
  }

  free(*nodo);
  *nodo = NULL;
  return true;
}

bool lista_inserir_chave_inicio(LISTA *lista, const TIPO_DADO *valor)
{
  return lista_inserir_chave_posicao(lista, valor, 0);
}

bool lista_inserir_chave_final(LISTA *lista, const TIPO_DADO *valor)
{
  return lista_inserir_chave_posicao(lista, valor, lista_numero_de_elementos(lista));
}

bool lista_remover_inicio(LISTA *lista, TIPO_DADO *valor)
{
  if (lista_esta_vazia(lista))
  {
    return false;
  }

  return lista_remover_posicao(lista, valor, 0);
}

bool lista_remover_final(LISTA *lista, TIPO_DADO *valor)
{
  if (lista_esta_vazia(lista))
  {
    return false;
  }

  return lista_remover_posicao(lista, valor, lista_numero_de_elementos(lista) - 1);
}

bool lista_inserir_chave_posicao(LISTA *lista, const TIPO_DADO *valor, unsigned int posicao)
{
  NOH_LISTA *t;
  NOH_LISTA *aux, *ant;
  unsigned int contador;

  if (posicao > lista_numero_de_elementos(lista))
  {
    return false;
  }

  if (valor == NULL || !lista_obter_no(&t))
  {
    return false;
  }

  t->dado = *valor;
  t->sucessor = NULL;
  t->predecessor = NULL;

  aux = lista->inicio;
  ant = NULL;
  contador = 0;

  while (contador < posicao)
  {
    ant = aux;
    aux = aux->sucessor;
    contador++;
  }

  // inicio da lista ou lista vazia?
  if (ant == NULL)
  {
    t->sucessor = lista->inicio;
    lista->inicio = t;

    if (t->sucessor != NULL)
    {
      t->sucessor->predecessor = t;
    }

    if (lista->final == NULL)
    {
      lista->final = t;
    }
  }
  else
  {
    ant->sucessor = t;
    t->predecessor = ant;

    // Final da lista?
    if (aux == NULL)
    {
      lista->final = t;
    }
    else
    {
      t->sucessor = aux;
      aux->predecessor = t;
    }
  }

  lista->numElementos++;
  return true;
}

bool lista_remover_posicao(LISTA *lista, TIPO_DADO *valor, unsigned int posicao)
{
  NOH_LISTA *aux, *ant;
  unsigned int contador;

  if (lista_esta_vazia(lista))
  {
    return false;
  }

  if (posicao > (lista_numero_de_elementos(lista) - 1))
  {
    return false;
  }

  aux = lista->inicio;
  ant = NULL;
  contador = 0;

  while (contador < posicao)
  {
    ant = aux;
    aux = aux->sucessor;
    contador++;
  }

  if (ant == NULL)
  {
    lista->inicio = aux->sucessor;

    if (aux->sucessor != NULL)
    {
      aux->sucessor->predecessor = NULL;
    }
  }
  else
  {
    ant->sucessor = aux->sucessor;

    if (aux->sucessor != NULL)
    {
      aux->sucessor->predecessor = ant;
    }
  }

  if (valor)
  {
    *valor = aux->dado;
  }

  if (aux == lista->final)
  {
    lista->final = ant;
  }

  if (lista->inicio == NULL)
  {
    lista->final = NULL;
  }

  lista_liberar_no(&aux);
  lista->numElementos--;
  return true;
}

bool lista_obter_chave_posicao(const LISTA *lista, TIPO_DADO *valor, unsigned int posicao)
{
  NOH_LISTA *temp;

  if (lista_esta_vazia(lista))
  {
    return false;
  }

  if (lista_obter_no_posicao(lista, &temp, posicao))
  {
    return (lista_obter_chave_no(temp, valor));
  }
  else
  {
    return false;
  }
}

bool lista_inserir_chave_ordenado(LISTA *lista, const TIPO_DADO *valor)
{
  NOH_LISTA *t;
  NOH_LISTA *aux, *ant;

  if (!valor || !lista_obter_no(&t))
  {
    return false;
  }

  t->dado = *valor;
  t->sucessor = NULL;
  t->predecessor = NULL;

  aux = lista->inicio;
  ant = NULL;

  while (aux != NULL)
  {
    if (*valor <= aux->dado)
    {
      break;
    }
    ant = aux;
    aux = aux->sucessor;
  }

  // inicio da lista ou lista vazia?
  if (ant == NULL)
  {
    t->sucessor = lista->inicio;
    lista->inicio = t;

    if (t->sucessor != NULL)
    {
      t->sucessor->predecessor = t;
    }

    if (lista->final == NULL)
    {
      lista->final = t;
    }
  }
  else
  {
    ant->sucessor = t;
    t->predecessor = ant;

    // Final da lista?
    if (aux == NULL)
    {
      lista->final = t;
    }
    else
    {
      t->sucessor = aux;
      aux->predecessor = t;
    }
  }

  lista->numElementos++;
  return true;
}

bool lista_remover_chave(LISTA *lista, const TIPO_DADO *valor)
{
  NOH_LISTA *aux, *ant;

  if (lista_esta_vazia(lista))
  {
    return false;
  }

  if (valor == NULL)
  {
    return false;
  }

  aux = lista->inicio;
  ant = NULL;
  while (aux != NULL)
  {
    if (aux->dado == *valor)
    {
      break;
    }
    ant = aux;
    aux = aux->sucessor;
  }

  // Nao achou
  if (aux == NULL)
  {
    return false;
  }

  if (ant == NULL)
  {
    lista->inicio = aux->sucessor;

    if (aux->sucessor != NULL)
    {
      aux->sucessor->predecessor = NULL;
    }
  }
  else
  {
    ant->sucessor = aux->sucessor;

    if (aux->sucessor != NULL)
    {
      aux->sucessor->predecessor = ant;
    }
  }

  if (aux == lista->final)
  {
    lista->final = ant;
  }

  if (lista->inicio == NULL)
  {
    lista->final = NULL;
  }

  lista_liberar_no(&aux);
  lista->numElementos--;
  return true;
}

bool lista_obter_sucessor_de_no(const NOH_LISTA *nodo, NOH_LISTA **sucessor)
{
  if ((nodo == NULL) || (nodo->sucessor == NULL))
  {
    return false;
  }

  *sucessor = nodo->sucessor;
  return true;
}

bool lista_obter_predecessor_de_no(const NOH_LISTA *nodo, NOH_LISTA **predecessor)
{
  if ((nodo == NULL) || (nodo->predecessor == NULL))
  {
    return false;
  }

  *predecessor = nodo->predecessor;
  return true;
}

bool lista_obter_no_inicio(const LISTA *lista, NOH_LISTA **nodo)
{
  if (lista_esta_vazia(lista))
  {
    return false;
  }

  *nodo = lista->inicio;
  return true;
}

bool lista_obter_no_final(const LISTA *lista, NOH_LISTA **nodo)
{
  if (lista_esta_vazia(lista))
  {
    return false;
  }

  *nodo = lista->final;
  return true;
}

bool lista_obter_no_chave(const LISTA *lista, const TIPO_DADO *valor, NOH_LISTA **nodo)
{
  NOH_LISTA *aux;
  aux = lista->inicio;

  if (valor == NULL)
  {
    return false;
  }

  while (aux != NULL)
  {
    if (aux->dado == *valor)
    {
      break;
    }
    aux = aux->sucessor;
  }

  *nodo = aux;
  return (aux != NULL);
}

bool lista_inserir_chave_antes_no(LISTA *lista, const TIPO_DADO *valor, const NOH_LISTA **nodo)
{
  NOH_LISTA *t;
  NOH_LISTA *aux, *ant;

  if (*nodo == NULL)
  {
    return false;
  }

  if (valor == NULL || !lista_obter_no(&t))
  {
    return false;
  }

  t->dado = *valor;
  t->sucessor = NULL;
  t->predecessor = NULL;

  aux = lista->inicio;
  ant = NULL;
  while (aux != NULL)
  {
    if (aux == *nodo)
    {
      break;
    }
    ant = aux;
    aux = aux->sucessor;
  }

  // inicio da lista ou lista vazia?
  if (ant == NULL)
  {
    t->sucessor = lista->inicio;
    lista->inicio = t;

    if (t->sucessor != NULL)
    {
      t->sucessor->predecessor = t;
    }

    if (lista->final == NULL)
    {
      lista->final = t;
    }
  }
  else
  {
    ant->sucessor = t;
    t->predecessor = ant;

    // Final da lista?
    if (aux == NULL)
    {
      lista->final = t;
    }
    else
    {
      t->sucessor = aux;
      aux->predecessor = t;
    }
  }

  lista->numElementos++;
  return true;
}

bool lista_remover_nodo(LISTA *lista, NOH_LISTA **nodo)
{
  NOH_LISTA *aux, *ant;

  if (*nodo == NULL)
  {
    return false;
  }

  aux = lista->inicio;
  ant = NULL;

  while (aux != NULL)
  {
    if (aux == *nodo)
    {
      break;
    }
    ant = aux;
    aux = aux->sucessor;
  }

  // Nao achou
  if (aux == NULL)
  {
    return false;
  }

  if (ant == NULL)
  {
    lista->inicio = aux->sucessor;

    if (aux->sucessor != NULL)
    {
      aux->sucessor->predecessor = NULL;
    }
  }
  else
  {
    ant->sucessor = aux->sucessor;

    if (aux->sucessor != NULL)
    {
      aux->sucessor->predecessor = ant;
    }
  }

  if (aux == lista->final)
  {
    lista->final = ant;
  }

  if (lista->inicio == NULL)
  {
    lista->final = NULL;
  }

  lista_liberar_no(&aux);
  lista->numElementos--;
  return true;
}

bool lista_obter_chave_no(const NOH_LISTA *nodo, TIPO_DADO *valor)
{
  if (nodo == NULL)
  {
    return false;
  }
  *valor = nodo->dado;
  return true;
}

bool lista_definir_chave_no(NOH_LISTA *nodo, const TIPO_DADO *valor)
{
  if (nodo == NULL)
  {
    return false;
  }
  nodo->dado = *valor;
  return true;
}

bool lista_obter_no_posicao(const LISTA *lista, NOH_LISTA **nodo, unsigned int posicao)
{
  NOH_LISTA *aux;
  unsigned int contador;

  if (lista_esta_vazia(lista))
  {
    return false;
  }

  if (posicao > (lista_numero_de_elementos(lista) - 1))
  {
    return false;
  }

  aux = lista->inicio;

  for (contador = 0; contador < posicao; contador++)
  {
    aux = aux->sucessor;
  }

  *nodo = aux;
  return true;
}

bool lista_obter_chave_inicio(const LISTA *lista, TIPO_DADO *valor)
{
  NOH_LISTA *temp;

  if (lista_esta_vazia(lista))
  {
    return false;
  }

  if (lista_obter_no_inicio(lista, &temp))
  {
    return (lista_obter_chave_no(temp, valor));
  }
  else
  {
    return false;
  }
}

bool lista_obter_chave_final(const LISTA *lista, TIPO_DADO *valor)
{
  NOH_LISTA *temp;

  if (lista_esta_vazia(lista))
  {
    return false;
  }

  if (lista_obter_no_final(lista, &temp))
  {
    return (lista_obter_chave_no(temp, valor));
  }
  else
  {
    return false;
  }
}

bool lista_obter_posicao_chave(const LISTA *lista, const TIPO_DADO *valor, unsigned int *posicao)
{
  NOH_LISTA *aux;

  if (lista_esta_vazia(lista))
  {
    return false;
  }

  if (valor == NULL)
  {
    return false;
  }

  *posicao = 0;
  aux = lista->inicio;
  while (aux != NULL)
  {
    if (aux->dado == *valor)
    {
      break;
    }
    aux = aux->sucessor;
    *posicao = *posicao + 1;
  }
  return (aux != NULL);
}

bool lista_definir_chave_posicao(LISTA *lista, const TIPO_DADO *valor, unsigned int posicao)
{
  NOH_LISTA *temp;

  if (lista_obter_no_posicao(lista, &temp, posicao))
  {
    return (lista_definir_chave_no(temp, valor));
  }
  else
  {
    return false;
  }
}