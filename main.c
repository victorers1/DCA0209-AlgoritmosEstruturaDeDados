#include "grafo.h"
#include <stdio.h>
#include <string.h>

int main()
{
    int qtdVertice = 3, i, j, tmp;
    struct GrafoMatrizAdj *grafo = inicializar(qtdVertice, false);

    for (i = 0; i < qtdVertice; i++)
    {
        printf("Nó %s: \n", grafo->rotuloVertices[i]);

        for (j = 0; j < qtdVertice; j++)
        {
            printf("peso[%d][%d] = %d\n", i, j, *(*(grafo->arestas + i) + j));
        }
        printf("\n");
    }
    return 0;
}
