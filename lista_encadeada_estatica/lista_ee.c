#include "lista_ee.h"

int tamanho_lee (LISTAee * lista)
{
    return (lista->NumElementos);
}

int livres_lee (LISTAee * lista)
{
    return (lista->NumLivres);
}

void inicializa_lee (LISTAee * lista, int *resultado)
{
    int i;

    lista->NumElementos = 0;
    lista->NumLivres = TAM;
    lista->InicioElementos = -1;
    lista->InicioLivres = 0;

    for (i = 0; i < TAM - 1; i++)
        lista->dados[i].proximo = i + 1;

    lista->dados[TAM - 1].proximo = -1;

    *resultado = 1;
    return;
}

int obtem_no_lee (LISTAee * lista, int *resultado)
{
    int posicao;
    posicao = -1;
    if (!livres_lee (lista))
        *resultado = 0;
    else
    {
        posicao = lista->InicioLivres;
        lista->InicioLivres = lista->dados[posicao].proximo;
        lista->NumLivres = lista->NumLivres - 1;
        lista->NumElementos = lista->NumElementos + 1;
        *resultado = 1;
    }
    return (posicao);
}

void libera_no_lee (LISTAee * lista, int posicao, int *resultado)
{
    lista->dados[posicao].proximo = lista->InicioLivres;
    lista->InicioLivres = posicao;
    lista->NumLivres = lista->NumLivres + 1;
    lista->NumElementos = lista->NumElementos - 1;
    *resultado = 1;
    return;
}

void insere_elemento_lee (LISTAee *lista, int posicao, int *resultado, TIPO_DADO valor)
{
    int nodo, aux, r;
    int contador, anterior;

    if ((posicao < 0) || (posicao > lista->NumElementos))
        *resultado = 0;
    else
    {
        nodo = obtem_no_lee (lista, &r);
        if (!r)
            *resultado = r;
        else
        {
            contador = 0;
            anterior = -1;
            lista->dados[nodo] = valor;
            aux = lista->InicioElementos;
            while (contador < posicao)
            {
                anterior = aux;
                aux = lista->registros[aux].proximo;
                contador++;
            }
            if (anterior == -1)
            {
                lista->dados[nodo].proximo = lista->InicioElementos;
                lista->InicioElementos = nodo;
            }
            else
            {
                lista->dados[nodo].proximo = aux;
                lista->dados[anterior].proximo = nodo;
            }
            *resultado = 1;
        }
    }
    return;
}

void imprime_lista_bruta (LISTAee *l)
{
    int i;
    for (i = 0; i < TAM; i++)
        printf("[%3d] -> [%3d]\n", i, l->dados[i].proximo);
    printf("InicioLivres: %d\n", l->InicioLivres);
    printf("InicioElementos: %d\n", l->InicioElementos);
    printf("\n\n");
    return;
}

void remove_elemento_lee (LISTAee *lista, int posicao, int *resultado)
{
    int contador, anterior, aux;

    if ((posicao < 0) || (posicao > (lista -> NumElementos - 1)))
        *resultado = 0;
    else
    {
        contador = 0;
        anterior = -1;
        aux = lista->InicioElementos;
        while (contador < posicao)
        {
            anterior = aux;
            aux = lista->dados[aux].proximo;
            contador++;
        }
        if (anterior == -1)
            lista->InicioElementos = lista->dados[aux].proximo;
        else
            lista->dados[anterior].proximo = lista->dados[aux].proximo;

        libera_no_lee (lista, aux, resultado);
    }
    return;
}

void imprime_lee (LISTAee *lista)
{
    int i, j;
    if (lista->InicioElementos == -1)
        printf("Lista Vazia\n");
    else
    {
        i = lista->InicioElementos;
        j = 0;
        do
        {
            /* Faca o que for necessario aqui para mostrar o seu tipo de dado.
             * Por exemplo, se o TIPO_DADO for int, algo do tipo abaixo resolve
             *
             *   printf("[%03d]: %d\n", i, lista->dados[i].dado);
             *
             */
            i = lista->dados[i].proximo;
            j++;
        } while (i != -1);
    }
    return;
}
