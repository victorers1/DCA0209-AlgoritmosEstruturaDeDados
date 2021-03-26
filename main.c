#include "grafo.h"
#include <stdio.h>

int main()
{
    int qtdVertice = 3, i, j, tmp;
    struct GrafoMatrizAdj *grafo = inicializar(qtdVertice, false);

    for (i = 0; i < qtdVertice; i++)
    {
        for (j = 0; j < qtdVertice; j++)
        {
            tmp = *(*(grafo->arestas + i) + j);
            // printf("acessing *(*(grafo->arestas + %d) + %d) = %d \n", i, j, tmp);
            printf("%d ", *(*(grafo->arestas + i) + j));
        }
        printf("\n");
    }
    return 0;
}
