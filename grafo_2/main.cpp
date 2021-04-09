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

void construirGrafoNaoPonderado(GrafoListaAdj *grafo)
{
    //este é o grafo não ponderado usado
    //https://github.com/eduardolfalcao/edii/blob/master/conteudos/imgs/grafo-tad-rotulado.png

    grafo->inserirArestaNaoDirecionada("v1", "v2");
    grafo->inserirArestaNaoDirecionada("v1", "v3");
    grafo->inserirArestaNaoDirecionada("v2", "v4");
    grafo->inserirArestaNaoDirecionada("v3", "v4");
    grafo->inserirArestaNaoDirecionada("v3", "v5");
    grafo->inserirArestaNaoDirecionada("v4", "v6");
    grafo->inserirArestaNaoDirecionada("v4", "v7");
    grafo->inserirArestaNaoDirecionada("v5", "v9");
    grafo->inserirArestaNaoDirecionada("v6", "v8");
    grafo->inserirArestaNaoDirecionada("v8", "v9");
    grafo->inserirArestaNaoDirecionada("v9", "v9");
}

void construirGrafoCom5Componentes(GrafoListaAdj *grafo)
{
    //grafo colorido com 5 componentes exibido aqui
    //https://github.com/eduardolfalcao/edii/blob/master/conteudos/imgs/grafo-nao-conectado-dfs.png
    //https://github.com/eduardolfalcao/edii/blob/master/conteudos/imgs/grafo-nao-conectado-dfs-colorido.png

    //comp1
    grafo->inserirArestaNaoDirecionada("v0", "v4");
    grafo->inserirArestaNaoDirecionada("v0", "v8");
    grafo->inserirArestaNaoDirecionada("v0", "v13");
    grafo->inserirArestaNaoDirecionada("v0", "v14");

    //comp2
    grafo->inserirArestaNaoDirecionada("v1", "v5");
    grafo->inserirArestaNaoDirecionada("v5", "v16");
    grafo->inserirArestaNaoDirecionada("v5", "v17");

    //comp3
    grafo->inserirArestaNaoDirecionada("v3", "v9");
    grafo->inserirArestaNaoDirecionada("v9", "v2");
    grafo->inserirArestaNaoDirecionada("v15", "v9");
    grafo->inserirArestaNaoDirecionada("v15", "v2");
    grafo->inserirArestaNaoDirecionada("v15", "v10");

    //comp4
    grafo->inserirArestaNaoDirecionada("v6", "v7");
    grafo->inserirArestaNaoDirecionada("v6", "v11");
    grafo->inserirArestaNaoDirecionada("v7", "v11");

    //comp5: vértice "v12" (sem arestas)
}

int main(int argc, char const *argv[])
{
    GrafoListaAdj *grafo = new GrafoListaAdj();

    {
        grafo = new GrafoListaAdj();
        inserirVertices(grafo, 1, 9);
        construirGrafoNaoPonderado(grafo);

        cout << "Teste 1: v1\n";
        int *distancias = grafo->bfs("v1");
        // if (distancias[0] == 0)
        cout << "distancias[0] == " << distancias[0] << endl;
        // if (distancias[1] == 1)
        cout << "distancias[1] == " << distancias[1] << endl;
        // if (distancias[2] == 1)
        cout << "distancias[2] == " << distancias[2] << endl;
        // if (distancias[3] == 2)
        cout << "distancias[3] == " << distancias[3] << endl;
        // if (distancias[4] == 2)
        cout << "distancias[4] == " << distancias[4] << endl;
        // if (distancias[5] == 3)
        cout << "distancias[5] == " << distancias[5] << endl;
        // if (distancias[6] == 3)
        cout << "distancias[6] == " << distancias[6] << endl;
        // if (distancias[7] == 4)
        cout << "distancias[7] == " << distancias[7] << endl;
        // if (distancias[8] == 3)
        cout << "distancias[8] == " << distancias[8] << endl;
        free(distancias);

        cout << "Teste 1: v2\n";
        distancias = grafo->bfs("v2");
        // if (distancias[0] == 1)
        cout << "distancias[0] == " << distancias[0] << endl;
        // if (distancias[1] == 0)
        cout << "distancias[1] == " << distancias[1] << endl;
        // if (distancias[2] == 2)
        cout << "distancias[2] == " << distancias[2] << endl;
        // if (distancias[3] == 1)
        cout << "distancias[3] == " << distancias[3] << endl;
        // if (distancias[4] == 3)
        cout << "distancias[4] == " << distancias[4] << endl;
        // if (distancias[5] == 2)
        cout << "distancias[5] == " << distancias[5] << endl;
        // if (distancias[6] == 2)
        cout << "distancias[6] == " << distancias[6] << endl;
        // if (distancias[7] == 3)
        cout << "distancias[7] == " << distancias[7] << endl;
        // if (distancias[8] == 4)
        cout << "distancias[8] == " << distancias[8] << endl;
        free(distancias);
    }

    {
        cout << "Teste 3: v0\n";
        grafo = new GrafoListaAdj();
        inserirVertices(grafo, 0, 17);
        construirGrafoCom5Componentes(grafo);

        int *distancias = grafo->bfs("v0");
        // if (distancias[0] == 0)
        cout << "distancias[0]== " << distancias[0] << endl;
        // if (distancias[1] == 0)
        cout << "distancias[1]== " << distancias[1] << endl;
        // if (distancias[2] == 0)
        cout << "distancias[2]== " << distancias[2] << endl;
        // if (distancias[3] == 0)
        cout << "distancias[3]== " << distancias[3] << endl;
        // if (distancias[4] == 1)
        cout << "distancias[4]== " << distancias[4] << endl;
        // if (distancias[5] == 0)
        cout << "distancias[5]== " << distancias[5] << endl;
        // if (distancias[6] == 0)
        cout << "distancias[6]== " << distancias[6] << endl;
        // if (distancias[7] == 0)
        cout << "distancias[7]== " << distancias[7] << endl;
        // if (distancias[8] == 1)
        cout << "distancias[8]== " << distancias[8] << endl;
        // if (distancias[9] == 0)
        cout << "distancias[9]== " << distancias[9] << endl;
        // if (distancias[10] == 0)
        cout << "distancias[10]== " << distancias[10] << endl;
        // if (distancias[11] == 0)
        cout << "distancias[11]== " << distancias[11] << endl;
        // if (distancias[12] == 0)
        cout << "distancias[12]== " << distancias[12] << endl;
        // if (distancias[13] == 1)
        cout << "distancias[13]== " << distancias[13] << endl;
        // if (distancias[14] == 1)
        cout << "distancias[14]== " << distancias[14] << endl;
        // if (distancias[15] == 0)
        cout << "distancias[15]== " << distancias[15] << endl;
        // if (distancias[16] == 0)
        cout << "distancias[16]== " << distancias[16] << endl;
        // if (distancias[17] == 0)
        cout << "distancias[17]== " << distancias[17] << endl;
        free(distancias);

        cout << "Teste 3: v1\n";
        distancias = grafo->bfs("v1");
        // if (distancias[0] == 0)
        cout << "distancias[0]== " << distancias[0] << endl;
        // if (distancias[1] == 0)
        cout << "distancias[1]== " << distancias[1] << endl;
        // if (distancias[2] == 0)
        cout << "distancias[2]== " << distancias[2] << endl;
        // if (distancias[3] == 0)
        cout << "distancias[3]== " << distancias[3] << endl;
        // if (distancias[4] == 0)
        cout << "distancias[4]== " << distancias[4] << endl;
        // if (distancias[5] == 1)
        cout << "distancias[5]== " << distancias[5] << endl;
        // if (distancias[6] == 0)
        cout << "distancias[6]== " << distancias[6] << endl;
        // if (distancias[7] == 0)
        cout << "distancias[7]== " << distancias[7] << endl;
        // if (distancias[8] == 0)
        cout << "distancias[8]== " << distancias[8] << endl;
        // if (distancias[9] == 0)
        cout << "distancias[9]== " << distancias[9] << endl;
        // if (distancias[10] == 0)
        cout << "distancias[10]== " << distancias[10] << endl;
        // if (distancias[11] == 0)
        cout << "distancias[11]== " << distancias[11] << endl;
        // if (distancias[12] == 0)
        cout << "distancias[12]== " << distancias[12] << endl;
        // if (distancias[13] == 0)
        cout << "distancias[13]== " << distancias[13] << endl;
        // if (distancias[14] == 0)
        cout << "distancias[14]== " << distancias[14] << endl;
        // if (distancias[15] == 0)
        cout << "distancias[15]== " << distancias[15] << endl;
        // if (distancias[16] == 2)
        cout << "distancias[16]== " << distancias[16] << endl;
        // if (distancias[17] == 2)
        cout << "distancias[17]== " << distancias[17] << endl;
        free(distancias);

        cout << "Teste 3: v11\n";
        distancias = grafo->bfs("v11");
        // if (distancias[0] == 0)
        cout << "distancias[0]== " << distancias[0] << endl;
        // if (distancias[1] == 0)
        cout << "distancias[1]== " << distancias[1] << endl;
        // if (distancias[2] == 0)
        cout << "distancias[2]== " << distancias[2] << endl;
        // if (distancias[3] == 0)
        cout << "distancias[3]== " << distancias[3] << endl;
        // if (distancias[4] == 0)
        cout << "distancias[4]== " << distancias[4] << endl;
        // if (distancias[5] == 0)
        cout << "distancias[5]== " << distancias[5] << endl;
        // if (distancias[6] == 1)
        cout << "distancias[6]== " << distancias[6] << endl;
        // if (distancias[7] == 1)
        cout << "distancias[7]== " << distancias[7] << endl;
        // if (distancias[8] == 0)
        cout << "distancias[8]== " << distancias[8] << endl;
        // if (distancias[9] == 0)
        cout << "distancias[9]== " << distancias[9] << endl;
        // if (distancias[10] == 0)
        cout << "distancias[10]== " << distancias[10] << endl;
        // if (distancias[11] == 0)
        cout << "distancias[11]== " << distancias[11] << endl;
        // if (distancias[12] == 0)
        cout << "distancias[12]== " << distancias[12] << endl;
        // if (distancias[13] == 0)
        cout << "distancias[13]== " << distancias[13] << endl;
        // if (distancias[14] == 0)
        cout << "distancias[14]== " << distancias[14] << endl;
        // if (distancias[15] == 0)
        cout << "distancias[15]== " << distancias[15] << endl;
        // if (distancias[16] == 0)
        cout << "distancias[16]== " << distancias[16] << endl;
        // if (distancias[17] == 0)
        cout << "distancias[17]== " << distancias[17] << endl;
        free(distancias);

        cout << "Teste 3: v3\n";
        distancias = grafo->bfs("v3");
        // if (distancias[0] == 0)
        cout << "distancias[0]== " << distancias[0] << endl;
        // if (distancias[1] == 0)
        cout << "distancias[1]== " << distancias[1] << endl;
        // if (distancias[2] == 2)
        cout << "distancias[2]== " << distancias[2] << endl;
        // if (distancias[3] == 0)
        cout << "distancias[3]== " << distancias[3] << endl;
        // if (distancias[4] == 0)
        cout << "distancias[4]== " << distancias[4] << endl;
        // if (distancias[5] == 0)
        cout << "distancias[5]== " << distancias[5] << endl;
        // if (distancias[6] == 0)
        cout << "distancias[6]== " << distancias[6] << endl;
        // if (distancias[7] == 0)
        cout << "distancias[7]== " << distancias[7] << endl;
        // if (distancias[8] == 0)
        cout << "distancias[8]== " << distancias[8] << endl;
        // if (distancias[9] == 1)
        cout << "distancias[9]== " << distancias[9] << endl;
        // if (distancias[10] == 3)
        cout << "distancias[10]== " << distancias[10] << endl;
        // if (distancias[11] == 0)
        cout << "distancias[11]== " << distancias[11] << endl;
        // if (distancias[12] == 0)
        cout << "distancias[12]== " << distancias[12] << endl;
        // if (distancias[13] == 0)
        cout << "distancias[13]== " << distancias[13] << endl;
        // if (distancias[14] == 0)
        cout << "distancias[14]== " << distancias[14] << endl;
        // if (distancias[15] == 2)
        cout << "distancias[15]== " << distancias[15] << endl;
        // if (distancias[16] == 0)
        cout << "distancias[16]== " << distancias[16] << endl;
        // if (distancias[17] == 0)
        cout << "distancias[17]== " << distancias[17] << endl;
        free(distancias);
    }

    return 0;
}
