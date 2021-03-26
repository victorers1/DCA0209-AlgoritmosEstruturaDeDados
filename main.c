#include "grafo.h"
#include <stdio.h>
#include <string.h>

void graphToString(struct GrafoMatrizAdj *grafo, int qtdVertice)
{
    int i, j;
    for (i = 0; i < qtdVertice; i++)
    {
        printf("Nó %s: \n", grafo->rotuloVertices[i]);

        for (j = 0; j < qtdVertice; j++)
        {
            printf("peso[%d][%d] = %d\n", i, j, *(*(grafo->arestas + i) + j));
        }
        printf("\n");
    }
}

void graphToMatrix(struct GrafoMatrizAdj *grafo, int qtdVertice)
{
    int i, j;
    for (i = 0; i < qtdVertice; i++)
    {
        for (j = 0; j < qtdVertice; j++)
        {
            printf("%d ", *(*(grafo->arestas + i) + j));
        }
        printf("\n");
    }
}

int main()
{
    int qtdVertice = 3, i, j;
    struct GrafoMatrizAdj *grafo = inicializar(qtdVertice, false);

    printf("Inicialização:\n");
    graphToString(grafo, qtdVertice);

    printf("\n\nObter Indice Vertice:\n");
    printf("Índice de v0: %d\n", obterIndiceVertice(grafo, "v0"));
    printf("Índice de v1: %d\n", obterIndiceVertice(grafo, "v1"));
    printf("Índice de v2: %d\n", obterIndiceVertice(grafo, "v2"));

    printf("\n\nInserir Aresta:\n");
    printf("v0 - v1 : 1\n");
    inserirAresta(grafo, "v0", "v1", 1);
    printf("v1 - v2 : 2\n");
    inserirAresta(grafo, "v1", "v2", 2);
    printf("v2 - v0 : 3\n");
    inserirAresta(grafo, "v2", "v0", 3);
    graphToMatrix(grafo, qtdVertice);

    return 0;
}
