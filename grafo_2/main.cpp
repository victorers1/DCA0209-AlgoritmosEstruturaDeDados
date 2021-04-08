#include <iostream>
#include "./grafolistaadj.hpp"

using namespace std;

int main(int argc, char const *argv[])
{

    GrafoListaAdj grafo = GrafoListaAdj();

    grafo.inserirVertice("v1");
    grafo.inserirVertice("v2");
    grafo.inserirVertice("v3");
    grafo.inserirVertice("v1");

    cout << "Vertices:\n";
    for (auto v : grafo.getVertices())
        cout << v << " ";
    cout << endl
         << endl;

    grafo.inserirArestaNaoDirecionada("v1", "v2");
    grafo.inserirArestaNaoDirecionada("v1", "v3");
    grafo.inserirArestaDirecionada("v2", "v3", 2);

    cout << "Lista de arestas:\n";

    int qtdArestas = grafo.getArestas().size();
    for (int i = 0; i < qtdArestas; i++)
    {
        cout << "\nAresta " << i << ": ";
        for (pair<int, int> indexEPeso : grafo.getArestas()[i])
            cout << "<" << indexEPeso.first << ", " << indexEPeso.second << ">";
    }

    return 0;
}
