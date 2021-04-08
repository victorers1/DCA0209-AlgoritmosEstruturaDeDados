#include <iostream>
#include <vector>
#include <queue>
using namespace std;

using vecpair = vector<pair<int, int>>;

class GrafoListaAdj
{
private:
    //first é o indice do vertice vizinho, second é o peso (caso o grafo seja ponderado)
    vector<vector<pair<int, int>>> arestas;
    vector<string> vertices;

    /**
    * A principio nao temos nenhuma ordenacao usando os rotulos.
    * Portanto, usaremos busca linear.
    **/
    int obterIndiceVertice(string rotuloVertice)
    {
        int size = this->vertices.size();

        for (int i = 0; i < size; i++)
            if (this->vertices[i] == rotuloVertice)
                return i;

        return -1;
    }

    /**
    * O argumento indicesVerticesVisitados serve para controlar quais
    * vertices já foram visitados.
    * Lembrando que DFS é uma função recursiva.
    **/
    void dfs(string rotuloVOrigem, bool *indicesVerticesVisitados)
    {
        //IMPLEMENTAR
    }

public:
    /**
    * Lembrem-se:
    *       1) nao podemos inserir vertices com mesmo rotulo
    *       2) toda vez que inserirmos um novo vértice, precisaremos
    *          inserir um vetor para representar as conexões daquele
    *          vértice na lista de adjacências
    **/
    void inserirVertice(string rotuloVertice)
    {
        for (string v : this->vertices)
            if (v == rotuloVertice)
                return;

        this->vertices.push_back(rotuloVertice);
        this->arestas.push_back(vector<pair<int, int>>{});
    }

    /**
    * Sempre que o grafo for não ponderado, adicionaremos o peso 1,
    * por conveniência.
    **/
    void
    inserirArestaDirecionada(string rotuloVOrigem, string rotuloVDestino)
    {
        inserirArestaDirecionada(rotuloVOrigem, rotuloVDestino, 1);
    }

    void inserirArestaNaoDirecionada(string rotuloVOrigem, string rotuloVDestino)
    {
        inserirArestaDirecionada(rotuloVOrigem, rotuloVDestino, 1);
        inserirArestaDirecionada(rotuloVDestino, rotuloVOrigem, 1);
    }

    void inserirArestaNaoDirecionada(string rotuloVOrigem, string rotuloVDestino, int peso)
    {
        inserirArestaDirecionada(rotuloVOrigem, rotuloVDestino, peso);
        inserirArestaDirecionada(rotuloVDestino, rotuloVOrigem, peso);
    }

    /**
    * Inserir uma aresta entre rotuloVOrigem e rotuloVDestino com o peso
    * especificado.
    **/
    void inserirArestaDirecionada(string rotuloVOrigem, string rotuloVDestino, int peso)
    {
        int indexOrigem = this->obterIndiceVertice(rotuloVOrigem);
        int indexDestino = this->obterIndiceVertice(rotuloVDestino);

        if (indexOrigem == -1 || indexDestino == -1)
            return;

        this->arestas[indexOrigem].push_back(pair<int, int>(indexDestino, peso));
    }

    /**
    * Verifica se vértice rotuloVOrigem e vértice rotuloVDestino são
    * conectados (vizinhos).
    **/
    bool saoConectados(string rotuloVOrigem, string rotuloVDestino)
    {
        int indexOrigem = this->obterIndiceVertice(rotuloVOrigem);
        int indexDestino = this->obterIndiceVertice(rotuloVDestino);

        if (indexOrigem == -1 || indexDestino == -1)
            return false;

        for (pair<int, int> a : this->arestas[indexOrigem])
            if (a.first == indexDestino)
                return true;

        return false;
    }

    /**
    * Verifica se há algum caminho entre vértice rotuloVOrigem e 
    * vértice rotuloVDestino.
    * A melhor forma de fazer isto é reusando a função dfs.
    **/
    bool haCaminho(string rotuloVOrigem, string rotuloVDestino)
    {
        //IMPLEMENTAR
    }

    /**
    * Muda os rótulos do vértices dos diferentes componentes para
    * nomes que representam cores.
    * Dica: procura componentes partindo do vértice v0 ou v1, em ordem
    * crescente (mas você pode usar outra ordem se desejar). 
    * Retorna a quantidade de componentes.
    * A melhor forma de fazer isto é reusando a função dfs.
    **/
    int colorir()
    {
        //IMPLEMENTAR
    }

    /**
    * Usa a abordagem de navegação BFS para listar as distâncias
    * entre o vértice rotuloVOrigem e cada um dos demais vértices.
    * A função BFS consegue listar a menor distância entre um vértice
    * e os demais se o grafo for NÃO-PONDERADO.
    * Retorna um vetor de inteiros com a quantidade de arestas 
    * (distância) e o vértice rotuloVOrigem e cada um dos demais vértices.
    * Não é uma função recursiva. 
    * É necessário utilizar a ED fila.
    **/
    int *bfs(string rotuloVOrigem)
    {
        //IMPLEMENTAR
    }

    vector<string> getVertices()
    {
        return vertices;
    }

    vector<vector<pair<int, int>>> getArestas()
    {
        return arestas;
    }
};