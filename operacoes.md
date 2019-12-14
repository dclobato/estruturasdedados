# Operações

## Lista sequencial
- Inicialização, destruição e metadados
  + Inicializa lista
  + Destrói lista
  + Número de elementos na lista
  + Número de nodos disponíveis
  + Lista vazia?
  + Lista cheia?

- Recuperação de informação  
  + Mostrar a lista
  + Recupera chave em posição específica (_getter_)
  + Obter chave do primeiro nó
  + Obter chave do último nó
  + Obter posição da chave

- Inserção de chaves
  + Insere chave em posição específica
  + Insere chave ordenado
  + Insere chave no início da lista
  + Insere chave no final da lista
  + Definir o valor da chave de uma posição específica (_setter_)

- Remoção de chaves
  + Remove nodo em posição específica
  + Remove nodo com determinada chave
  + Remove o início da lista
  + Remove o final da lista

## Lista encadeada com alocações estática e dinâmica
- Inicialização, destruição e metadados
  + Inicializa lista
  + Destrói lista
  + Inicializa nodo de lista
  + Destrói nodo de lista
  + Número de elementos na lista
  + Número de nodos disponíveis
  + Lista vazia?
  + Lista cheia?

- Recuperação de informação  
  + Mostrar a lista (simples e _debug_)
  + Recupera chave em posição específica
  + Busca por chave em lista e retorna o nodo
  + Obtém nodo sucessor de nodo
  + Obtém nodo início de lista
  + Obter o valor da chave em um nó específico

- Inserção de chaves
  + Insere chave em posição específica
  + Insere chave ordenado
  + Insere chave antes de um nodo
  + Insere chave no início da lista
  + Insere chave no final da lista
  + Definir o valor da chave em um nó específico

- Remoção de chaves
  + Remove nodo em posição específica
  + Remove nodo com determinada chave
  + Remove nodo indicado
  + Remove o início da lista
  + Remove o final da lista

## Lista duplamente encadeada com alocação dinâmica
- Inicialização, destruição e metadados
  + Inicializa lista
  + Destrói lista
  + Inicializa nodo de lista
  + Destrói nodo de lista
  + Número de elementos na lista
  + Lista vazia?
  + Lista cheia?

- Recuperação de informação  
  + Mostrar a lista (simples e _debug_)
  + Recupera chave em posição específica
  + Busca por chave em lista e retorna o nodo
  + Obtém nodo sucessor de nodo
  + Obtém nodo predecessor de nodo
  + Obtém nodo início de lista
  + Obtém nodo final de lista
  + Obter o valor da chave em um nó específico

- Inserção de chaves
  + Insere chave em posição específica
  + Insere chave ordenado
  + Insere chave antes de um nodo
  + Insere chave no início da lista
  + Insere chave no final da lista
  + Definir o valor da chave em um nó específico

- Remoção de chaves
  + Remove nodo em posição específica
  + Remove nodo com determinada chave
  + Remove nodo indicado
  + Remove o início da lista
  + Remove o final da lista

## Lista encadeada circular com alocação dinâmica
- Inicialização, destruição e metadados
  + Inicializa lista
  + Destrói lista
  + Inicializa nodo de lista
  + Destrói nodo de lista
  + Número de elementos na lista
  + Avança início da lista em sentido horário ( _shift right_ )
  + Avança início da lista em sentido anti-horário ( _shift left_ )

- Recuperação de informação
  + Mostrar a lista (simples e _debug_)
  + Recupera chave em posição específica
  + Busca por chave em lista e retorna o nodo
  + Obtém nodo sucessor de nodo
  + Obtém nodo inicial de lista
  + Obtém nodo final de lista
  + Obter o valor da chave em um nó específico

- Inserção de chaves
  + Insere chave em posição específica
  + Insere chave ordenado
  + Insere chave antes de um nodo
  + Insere chave no início da lista
  + Insere chave no final da lista
  + Definir o valor da chave em um nó específico

- Remoção de chaves
  + Remove nodo em posição específica
  + Remove nodo com determinada chave
  + Remove nodo indicado
  + Remove o início da lista
  + Remove o final da lista

## Lista duplamente encadeada circular com alocação dinâmica
- [Inicialização, destruição e metadados][notyet]
  + Inicializa lista
  + Destrói lista
  + Inicializa nodo de lista
  + Destrói nodo de lista
  + Número de elementos na lista
  + Avança início da lista em sentido horário
  + Avança início da lista em sentido anti-horário

- [Recuperação de informação][notyet]
  + Mostrar a lista (simples e _debug_)
  + Recupera chave em posição específica
  + Busca por chave em lista e retorna o nodo
  + Obtém nodo sucessor de nodo
  + Obtém nodo predecessor de nodo
  + Obtém nodo início de lista
  + Obtém nodo final de lista

- [Inserção de chaves][notyet]
  + Insere chave em posição específica
  + Insere chave ordenado
  + Insere chave antes de um nodo
  + Insere chave no início da lista
  + Insere chave no final da lista

- [Remoção de chaves][notyet]
  + Remove nodo em posição específica
  + Remove nodo com determinada chave
  + Remove nodo indicado
  + Remove o início da lista
  + Remove o final da lista

## Pilha com alocações estática e dinâmica
- Inicialização, destruição e metadados
  + Inicializa pilha
  + Destrói pilha
  + Pilha vazia?
  + Pilha cheia?
  + Número de elementos na pilha
  + Topo da pilha

- Inserção de chaves
  + _Push_ chave

- Remoção de chaves
  + _Pop_ chave

## Fila com alocações estática e dinâmica
- Inicialização, destruição e metadados
  + Inicializa fila
  + Destrói fila
  + Inicializa nodo de fila
  + Destrói nodo de fila
  + Número de elementos na fila
  + Número de nodos disponíveis
  + Fila vazia?
  + Fila cheia?

- Recuperação de informação  
  + Mostrar a fila (simples e _debug_)
  + Obtém cabeça da fila
  + Obtém cauda da fila

- Inserção de chaves
  + Enfileira chave
  + [Enfileira com prioridade][noheap]

- Remoção de chaves
  + Desenfileira chave

## Heap
- Inicialização, destruição e metadados
  + Inicializa _heap_
  + Destrói _heap_
  + Constrói _heap_
  + Número de elementos na _heap_
  + Inverte _heap_
  + _Heap_ vazia?
  + _Heap_ cheia?
  + Qual o tipo da _heap_?

- Recuperação de informação
  + Encontrar maior/menor elemento
  + Extrair maior/menor elemento, mantendo a _heap_

- Inserção de chaves
  + Insere chave, mantendo a _heap_
  + Trocar raíz por nova chave, mantendo a _heap_

- Remoção de chaves
  + Remove chave, mantendo a _heap_  

## Grafo (representado como matriz de adjacência)
- Inicialização, destruição e metadados
  + Inicializa grafo
  + Destrói grafo
  + Mostra grafo
  + [Gera arquivo graphviz do grafo][notyet]
  + Existe aresta entre dois vertices?
  + Obter peso da aresta
  + Obter grau de vértice
  + Obter lista de adjacencias (e detruir a lista)

- Inserção
  + Insere vértice
  + Insere aresta

- Remoção
  + [Remove vertice][notyet]
  + Remove aresta
  
- Percursos
  + Percurso em largura (e destruir percurso)
  + Percurso em profundidade (e destruir percurso)

- Ordenação topológica
  + A partir do percurso em profundidade
  + [Algoritmo de Kahn][notyet]

- Árvore geradora mínima
  + Prim
  + [Kruskal][notyet]
  
- Melhor caminho
  + Dijkstra

- Diversos  
  + Colorir grafo (Welsh-Powell)
  + [Complexidade ciclomática][notyet]

## Hash (tratamento de colisao por encadeamento)
- [Inicialização, destruição e metadados][notyet]
  + Inicializar tabela
  + Destrói tabela
  + Obter fator de carga

- [Recuperação de informação][notyet]
  + Consultar chave

- [Inserção de chaves][notyet]
  + Inserir chave

- [Remoção de chaves][notyet]
  + Remover chave
  
## Filtro de Bloom
- [Inicialização, destruição e metadados][notyet]
  + Inicializar tabela
  + Destrói tabela
  + Obter fator de carga

- [Recuperação de informação][notyet]
  + Consultar chave

- [Inserção de chaves][notyet]
  + Inserir chave

- [Remoção de chaves][notyet]
  + Remover chave

## Ordenação
- Memória interna
  + Bubble sort
  + Select sort
  + Insert sort
  + Quick sort
  + Heap short
  + Shell short
  + [Radix sort][notyet]
  + [Bucket sort][notyet]

- Memória externa
  + [Merge sort][notyet]

## Arvores-B
- [Inicialização, destruição e metadados][notyet]
- [Recuperação de informação][notyet]
- [Inserção de chaves][notyet]
- [Remoção de chaves][notyet]

## Arvores AVL
- [Inicialização, destruição e metadados][notyet]
  + Inicializa árvore
  + Destrói árvore
  + Inicializa nodo de árvore
  + Destrói nodo de árvore
  + Altura da árvore
  + Numero de nodos
  + Rotação R
  + Rotação L

- [Recuperação de informação][notyet]
  + Busca por chave
  
- [Inserção de chaves][notyet]
  + Inserção de chave
  
- [Remoção de chaves][notyet]
  + Remoção de chave

## Arvores binarias (de busca)
- Inicialização, destruição e metadados
  + Inicializa árvore
  + Destrói árvore
  + Inicializa nodo de árvore
  + Destrói nodo de árvore
  + Altura da árvore
  + Numero de nodos
  + Nivel de nodo com valor
  + [Nivel de determinado nodo][notyet]

- Recuperação de informação
  + Imprimir árvore
  + Busca por chave
  
- Inserção de chaves
  + Inserção de chave
  
- [Remoção de chaves][notyet]
  + Remoção de chave

- Percursos
  + Percurso em pre-ordem
  + Percurso em in-ordem
  + Percurso em pos-ordem
  + Percurso em largura
  + Destrói percurso

## Aplicacoes 
- Codigo de Huffman

[notyet]: # "Ainda não implementado"
[noheap]: # "Sem utilizar _heap_"
