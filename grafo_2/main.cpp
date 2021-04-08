#include <iostream>
#include <sstream>
#include "./grafolistaadj.hpp"

using namespace std;

void inserirVertices(GrafoListaAdj *grafoNaoPonderado, int ini, int fim)
{
    for (int i = ini; i <= fim; i++)
    {
        string rotulo;
        stringstream sstm;
        sstm << "v" << i;
        rotulo = sstm.str();
        grafoNaoPonderado->inserirVertice(rotulo);
    }
}

int main(int argc, char const *argv[])
{

    GrafoListaAdj *grafo = new GrafoListaAdj();

    grafo->inserirVertice("v1");
    grafo->inserirVertice("v2");
    grafo->inserirVertice("v3");
    grafo->inserirVertice("v1");

    cout << "Vertices:\n";
    for (auto v : grafo->getVertices())
        cout << v << " ";
    cout << endl
         << endl;

    grafo = new GrafoListaAdj();
    inserirVertices(grafo, 1, 9);

    grafo->inserirArestaNaoDirecionada("v1", "v2");
    grafo->inserirArestaNaoDirecionada("v3", "v4");

    /* verificando se v2 estah na lista de conexoes de v1 */
    vector<pair<int, int>> conexoesV1 = grafo->getArestas().at(0); //v1 estah no indice 0
    /* verificando se v1 estah na lista de conexoes de v2 */
    vector<pair<int, int>> conexoesV2 = grafo->getArestas().at(1); //v2 estah no indice 1
    /* verificando se v4 estah na lista de conexoes de v3 */
    vector<pair<int, int>> conexoesV3 = grafo->getArestas().at(2); //v3 estah no indice 2
    /* verificando se v3 estah na lista de conexoes de v4 */
    vector<pair<int, int>> conexoesV4 = grafo->getArestas().at(3); //v4 estah no indice 3

    cout << "Lista de arestas:\n";
    int i = 0;
    for (auto a : grafo->getArestas())
    {
        cout << "\nAresta " << i++ << ": ";
        for (pair<int, int> indexEPeso : a)
            cout << "<" << indexEPeso.first << ", " << indexEPeso.second << ">, ";
    }
    cout << endl;

    grafo = new GrafoListaAdj();
    inserirVertices(grafo, 1, 9);
    grafo->inserirArestaNaoDirecionada("v1", "v2", 4);
    grafo->inserirArestaNaoDirecionada("v3", "v4", 9);

    /* verificando se v2 estah na lista de conexoes de v1 */
    conexoesV1 = grafo->getArestas().at(0); //v1 estah no indice 0
    /* verificando se v1 estah na lista de conexoes de v2 */
    conexoesV2 = grafo->getArestas().at(1); //v2 estah no indice 1
    /* verificando se v4 estah na lista de conexoes de v3 */
    conexoesV3 = grafo->getArestas().at(2); //v3 estah no indice 2
    /* verificando se v3 estah na lista de conexoes de v4 */
    conexoesV4 = grafo->getArestas().at(3); //v4 estah no indice 3

    grafo = new GrafoListaAdj();
    inserirVertices(grafo, 1, 9);
    grafo->inserirArestaDirecionada("v1", "v2");
    grafo->inserirArestaDirecionada("v3", "v4");

    /* verificando se v2 estah na lista de conexoes de v1 */
    conexoesV1 = grafo->getArestas().at(0); //v1 estah no indice 0
    /* verificando se v1 NAO estah na lista de conexoes de v2 */
    conexoesV2 = grafo->getArestas().at(1); //v2 estah no indice 1
    /* verificando se v4 estah na lista de conexoes de v3 */
    conexoesV3 = grafo->getArestas().at(2); //v3 estah no indice 2
    /* verificando se v3 NAO estah na lista de conexoes de v4 */
    conexoesV4 = grafo->getArestas().at(3); //v4 estah no indice 3

    grafo = new GrafoListaAdj();
    grafo->inserirArestaNaoDirecionada("v1", "v2");
    grafo->inserirArestaNaoDirecionada("v1", "v3");
    grafo->inserirArestaNaoDirecionada("v2", "v4");
    grafo->inserirArestaNaoDirecionada("v3", "v4");
    grafo->inserirArestaNaoDirecionada("v3", "v5");
    grafo->inserirArestaNaoDirecionada("v4", "v6");
    grafo->inserirArestaNaoDirecionada("v5", "v9");
    grafo->inserirArestaNaoDirecionada("v6", "v8");
    grafo->inserirArestaNaoDirecionada("v8", "v9");
    grafo->inserirArestaNaoDirecionada("v9", "v9");

    cout << "grafo->haCaminho('v1', 'v1'): " << grafo->haCaminho("v1", "v1") << endl;
    cout << "grafo->haCaminho('v9', 'v9'): " << grafo->haCaminho("v9", "v9") << endl;
    cout << "grafo->haCaminho('v1', 'v2'): " << grafo->haCaminho("v1", "v2") << endl;
    cout << "grafo->haCaminho('v1', 'v9'): " << grafo->haCaminho("v1", "v9") << endl;

    delete (grafo);
    return 0;
}
