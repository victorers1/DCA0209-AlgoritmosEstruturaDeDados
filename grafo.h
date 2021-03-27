#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

struct GrafoMatrizAdj
{
    int **arestas;
    char **rotuloVertices;
    int verticesInseridos;
    int maxNumVertices;
};

/**
 * Para entrada i=1, retorna string "v1".
 * i = 0 até 999
 * rotulo = "v0" até "v999"
 */
char *getRotulo(int i)
{
    char indiceVertice[4];
    itoa(i, indiceVertice, 10);
    char *rotulo = (char *)malloc(sizeof(char) * 5);
    rotulo[0] = 'v';
    rotulo[1] = '\0';
    strcat(rotulo, indiceVertice);
    return rotulo;
}

/**
 * Se o grafo for ponderado, inicializamos cada posicao da matriz com INT_MAX.
 * Se o grafo for não ponderado, inicializamos cada posicao da matriz com 0.
 **/
struct GrafoMatrizAdj *inicializar(int maxNumVertices, bool ponderado)
{
    int i, j, peso = ponderado ? INT_MAX : 0;

    struct GrafoMatrizAdj *grafo_tmp = (struct GrafoMatrizAdj *)malloc(sizeof(struct GrafoMatrizAdj));
    grafo_tmp->verticesInseridos = 0;
    grafo_tmp->maxNumVertices = maxNumVertices;

    grafo_tmp->arestas = (int **)malloc(maxNumVertices * sizeof(int *));
    grafo_tmp->rotuloVertices = (char **)malloc(maxNumVertices * sizeof(char *));

    for (i = 0; i < maxNumVertices; i++)
    {
        int *linha = (int *)malloc(sizeof(int) * maxNumVertices);
        for (j = 0; j < maxNumVertices; j++)
        {
            linha[j] = peso;
        }

        grafo_tmp->arestas[i] = linha;
    }

    return grafo_tmp;
}

/**
 * A principio nao temos nenhuma ordenacao usando os rotulos.
 * Portanto, usaremos busca linear
 **/
int obterIndiceVertice(struct GrafoMatrizAdj *grafo, char *rotuloVertice)
{
    for (int i = 0; i < grafo->verticesInseridos; i++)
        if (strcmp(rotuloVertice, grafo->rotuloVertices[i]) == 0)
            return i;

    return -1;
}

/**
 * Se o grafo for ponderado, usamos a variavel peso para especificar o peso da aresta.
 * Se o grafo for não ponderado, passaremos o valor 1 para a variavel peso, de modo que represente existência da aresta.
 * Se um dos rotulos dos vertices nao existir, simplesmente nao faremos nada.
 **/
void inserirAresta(struct GrafoMatrizAdj *grafo, char *rotuloVOrigem, char *rotuloVDestino, int peso)
{
    int indiceOrigem = obterIndiceVertice(grafo, rotuloVOrigem);
    int indiceDestino = obterIndiceVertice(grafo, rotuloVDestino);

    grafo->arestas[indiceOrigem][indiceDestino] = peso;
}

/**
 * Usamos a variavel grafo->verticesInseridos para controlar a quantidade de vertices que ja foi inserido no grafo.
 * Logo, ela pode/deve ser usada para especificar em qual posicao o vertice a ser inserido sera alocado.
 **/
void inserirVertice(struct GrafoMatrizAdj *grafo, char *rotuloVertice)
{
    grafo->rotuloVertices[grafo->verticesInseridos] = rotuloVertice;
    grafo->verticesInseridos++;
}

/**
 * Tomar cuidado com as diferenças semânticas entre haver conexão entre dois vertices em um grafo ponderado,
 * e haver conexão entre dois vertices em um grafo nao-ponderado.
 **/
bool saoConectados(struct GrafoMatrizAdj *grafo, char *rotuloVOrigem, char *rotuloVDestino)
{
    int indiceOrigem = obterIndiceVertice(grafo, rotuloVOrigem);
    if (indiceOrigem == -1)
        return false;

    int indiceDestino = obterIndiceVertice(grafo, rotuloVDestino);
    if (indiceDestino == -1)
        return false;

    return grafo->arestas[indiceOrigem][indiceDestino] > 0 || indiceOrigem == indiceDestino;
}
