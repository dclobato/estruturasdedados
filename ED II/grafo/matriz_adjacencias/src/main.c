#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#include "utilitarios.h"

int main()
{
  GRAFO grafo;
  char rotulo[80];
  RSLT_BUSCA RsltBusca;
  unsigned int num_vertices;
  unsigned int de, para;
  bool direcionado;
  bool ponderado;
  int peso;
  ArvoreGeradoraMinima arvore;
  CAMINHO *caminho;
  unsigned int *cores;

  ler_InteiroLongoSemSinal((unsigned long *) &num_vertices, "Digite o numero de vertices", 1, 100);
  direcionado = ler_SimNao("Direcionado?");
  ponderado = ler_SimNao("Ponderado?");

  if (!criar_grafo(&grafo, num_vertices, direcionado, ponderado))
  {
    printf("Nao deu para criar o grafo\n");
    exit(1);
  }
  else
  {
    printf("Criado um grafo %s %s\n", direcionado ? "direcionado" : "nao direcionado",
           ponderado ? "ponderado" : "nao ponderado");
  }

  for (unsigned int vertice = 0; vertice < num_vertices; ++vertice)
  {
    if (!adicionar_vertice(&grafo, NULL, 0, NULL))
    {
      printf("Impossivel adicionar vertice %u\n", vertice);
      exit(1);
    }
  }

  mostrar_rotulos(&grafo);

  printf("Renomeando vertices...\n");
  do
  {
    printf("Digite %u para parar\n", grafo.max_vertices);
    ler_InteiroLongoSemSinal((unsigned long *) &de, "Mudar rotulo de qual vertice?", 0, grafo.max_vertices);
    if (de == grafo.max_vertices)
      break;
    printf("Rotulo do vertice %u: ", de);
    ler_String(rotulo, NULL, 80);
    renomear_vertice(&grafo, rotulo, strlen(rotulo), de);
    mostrar_rotulos(&grafo);
  } while (1);


  printf("Adicionando arestas...\n");
  do
  {
    printf("Digite %u para parar\n", grafo.max_vertices);
    ler_InteiroLongoSemSinal((unsigned long *) &de, "Vertice de origem", 0, grafo.max_vertices);
    if (de == grafo.max_vertices)
      break;
    ler_InteiroLongoSemSinal((unsigned long *) &para, "Vertice de destino", 0, grafo.max_vertices);
    if (para == grafo.max_vertices)
      break;
    peso = 1;
    if (ponderado)
    {
      printf("Peso da aresta entre %u e %u: ", de, para);
      ler_InteiroLongo((long *) &peso, NULL, INT_MIN, INT_MAX);
    }

    if (adicionar_aresta(&grafo, de, para, peso))
    {
      printf("Aresta criada\n");
    }
    else
    {
      printf("Impossivel criar a aresta\n");
    }
  } while (1);

  mostrar_rotulos(&grafo);
  imprimir_grafo(&grafo, NULL);

  printf("Removendo arestas...\n");
  do
  {
    printf("Digite %u para parar\n", grafo.max_vertices);
    ler_InteiroLongoSemSinal((unsigned long *) &de, "Vertice de origem", 0, grafo.max_vertices);
    if (de == grafo.max_vertices)
      break;
    ler_InteiroLongoSemSinal((unsigned long *) &para, "Vertice de destino", 0, grafo.max_vertices);
    if (para == grafo.max_vertices)
      break;

    if (remover_aresta(&grafo, de, para))
    {
      printf("Aresta removida\n");
    }
    else
    {
      printf("Impossivel remover a aresta\n");
    }
  } while (1);

  colorir_grafo(&grafo, &cores);
  imprimir_grafo(&grafo, cores);
  free(cores);

  destruir_grafo(&grafo);

  return 0;
}
