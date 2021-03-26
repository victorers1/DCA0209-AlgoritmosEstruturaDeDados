#include "grafo.h"

int main()
{
    int qtdVertice = 10;
    struct GrafoMatrizAdj *grafo = inicializar(qtdVertice, false);

    for (int i = 0; i < qtdVertice; i++)
    {
        for (int j = 0; j < qtdVertice; j++)
        {
            // grafo->arestas //TODO acessar posição de matriz com ponteiros
        }
    }
    return 0;
}
