#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm> // std::min

#define POS_INF 1000000000
#define NEG_INF -1000000000

using namespace std;

using vecpair = vector<pair<int, int>>;

class GrafoListaAdj
{
private:
    //first é o indice do vertice vizinho, second é o peso (caso o grafo seja ponderado)
    vector<vecpair> arestas;
    vector<string> vertices;

    /**
    * A principio nao temos nenhuma ordenacao usando os rotulos.
    * Portanto, usaremos busca linear.
    **/
    int obterIndiceVertice(string rotuloVertice)
    {
        int size = (int)this->vertices.size();

        for (int i = 0; i < size; i++)
            if (this->vertices[i] == rotuloVertice)
                return i;

        return -1;
    }

    /**
    * O argumento verticesVisitados serve para controlar quais
    * vertices já foram visitados.
    * Lembrando que DFS é uma função recursiva.
    **/
    void dfs(string rotuloVOrigem, bool *verticesVisitados)
    {
        int indexOrigem = this->obterIndiceVertice(rotuloVOrigem);
        if (indexOrigem != -1 && !verticesVisitados[indexOrigem])
        {
            verticesVisitados[indexOrigem] = true;

            vecpair arestasVizinhas = this->arestas[indexOrigem];
            for (auto a : arestasVizinhas)
                dfs(this->vertices[a.first], verticesVisitados);
        }
    }

public:
    int *bellmanFord(string rotuloVOrigem)
    {
        int qtdVertice = this->vertices.size();
        int *distancias = (int *)malloc(sizeof(int) * qtdVertice);
        for (int i = 0; i < qtdVertice; i++)
            distancias[i] = POS_INF;

        int indexOrigem = obterIndiceVertice(rotuloVOrigem);
        if (indexOrigem == -1)
            return distancias;

        distancias[indexOrigem] = 0;

        // Executa as qtdVertices - 1 varreduras
        for (int i = 0; i < qtdVertice - 1; i++)
        {
            for (int v = 0; v < qtdVertice; v++)
                for (pair<int, int> aresta : this->arestas[v])
                {
                    int distOrigem = distancias[v];
                    int distDestino = distancias[aresta.first];
                    int peso = aresta.second;
                    if (distOrigem != POS_INF)
                        distancias[aresta.first] = min(distOrigem + peso, distDestino);
                }
        }

        for (int v = 0; v < qtdVertice; v++)
            for (pair<int, int> aresta : this->arestas[v])
            {
                int distOrigem = distancias[v];
                int distDestino = distancias[aresta.first];
                int peso = aresta.second;
                if (distOrigem != POS_INF && distOrigem + peso < distDestino)
                    distancias[v] = NEG_INF;
            }

        /*
            for (pair<int, int> aresta : this->arestas[v])
                if (somaSemOverflow(distancias[v], aresta.second) < distancias[aresta.first])
                    distancias[v] = NEG_INF;
            */

        return distancias;
    }

    int *dijkstra(string rotuloVOrigem)
    {
    }

    // +inf somado com qualquer valor positivo resulta em +inf
    // -inf subtraído de qualquer valor negativo resulta em -inf
    // demais operações são realizadas normalmente
    int somaSemOverflow(int a, int b)
    {
        return a + b;

        if (a > POS_INF - b)
            return POS_INF;
        else
            return a + b;
    }

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
        this->arestas.push_back(vecpair{});
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
        // Se haCaminho é chamado no mesmo vértice, procura se há um laço
        if (rotuloVOrigem == rotuloVDestino)
        {
            int indexOrigem = this->obterIndiceVertice(rotuloVOrigem);
            if (indexOrigem == -1)
                return false;

            int indexDestino = this->obterIndiceVertice(rotuloVDestino);
            if (indexDestino == -1)
                return false;

            for (pair<int, int> v : this->arestas[indexOrigem])
                if (v.first == indexDestino)
                    return true;

            return false;
        }
        else // Se haCaminho for chamado em vértices diferentes, aplicar DFS
        {
            int indexDestino = this->obterIndiceVertice(rotuloVDestino);
            if (indexDestino == -1)
                return false;

            // Declara e preenche lista de vértices visitados
            bool *verticesVisitados = (bool *)malloc(this->vertices.size() * sizeof(bool));
            for (int i = 0; i < this->vertices.size(); i++)
                verticesVisitados[i] = false;

            // aplica DFS começando em rotuloVOrigem
            dfs(rotuloVOrigem, verticesVisitados);

            // Salva se vértice foi visitado para liberar memória de *verticesVisitados
            bool visitado = verticesVisitados[indexDestino];

            free(verticesVisitados);
            return visitado;
        }
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
        int qtdComponente = 0; // quantidade de grupos isolados de vértices
        int qtdVertice = this->vertices.size();
        bool *verticesVisitados = (bool *)malloc(qtdVertice * sizeof(bool)); // vértices visitados pela última execução da DFS
        bool *verticesColoridos = (bool *)malloc(qtdVertice * sizeof(bool)); // vértices já coloridos em todo grafo

        // Vértices começam sem pintura
        for (int i = 0; i < qtdVertice; i++)
            verticesColoridos[i] = false;

        for (int i = 0; i < qtdVertice; i++)
        {
            // Por causa desse IF, o FOR acima só executará a DFS uma vez em cada grupo isolado
            if (verticesColoridos[i])
                continue;

            // Reseta array de vizinhos visitados para aplicar a próxima execução da DFS
            for (int i = 0; i < qtdVertice; i++)
                verticesVisitados[i] = false;

            dfs(this->vertices[i], verticesVisitados);

            // Pinta vértices que foram visitados pela execução atual com o rótulo da origem da busca
            for (int j = 0; j < qtdVertice; j++)
                if (verticesVisitados[j])
                {
                    this->vertices[j] = this->vertices[i];
                    verticesColoridos[j] = true;
                }

            qtdComponente++;
        }
        return qtdComponente;
    }

    /**
    * Usa a abordagem de navegação BFS para listar as distâncias
    * entre o vértice rotuloVOrigem e cada um dos demais vértices.
    * A função BFS consegue listar a menor distância entre um vértice
    * e os demais se o grafo for NÃO-PONDERADO.
    * Retorna um vetor de inteiros com a quantidade de arestas 
    * (distância) entre o vértice rotuloVOrigem e cada um dos demais vértices.
    * Não é uma função recursiva. 
    * É necessário utilizar a ED fila.
    **/
    int *bfs(string rotuloVOrigem)
    {
        int indexOrigem = obterIndiceVertice(rotuloVOrigem);
        if (indexOrigem == -1)
            return NULL;

        int qtdVertice = this->vertices.size();

        queue<int> verticesAVisitar;
        verticesAVisitar.push(indexOrigem);

        int *distancias = (int *)malloc(sizeof(int) * qtdVertice);
        for (int i = 0; i < qtdVertice; i++)
            distancias[i] = 0;

        bool *verticesVisitados = (bool *)malloc(sizeof(bool) * qtdVertice);
        for (int i = 0; i < qtdVertice; i++)
        {
            verticesVisitados[i] = false;
        }
        verticesVisitados[indexOrigem] = true;

        while (!verticesAVisitar.empty())
        {
            int indexFrenteFila = verticesAVisitar.front();
            verticesAVisitar.pop();

            // for (int indexAresta = 0; indexAresta < this->arestas[indexFrenteFila].size(); indexAresta++)
            for (pair<int, int> v : this->arestas[indexFrenteFila])
            {
                if (!verticesVisitados[v.first])
                {
                    verticesVisitados[v.first] = true;

                    distancias[v.first] = distancias[indexFrenteFila] + 1;

                    verticesAVisitar.push(v.first);
                }
            }
        }

        return distancias;
    }

    vector<string> getVertices()
    {
        return vertices;
    }

    vector<vecpair> getArestas()
    {
        return arestas;
    }
};