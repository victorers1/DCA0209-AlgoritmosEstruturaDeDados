#include <iostream>
#include <sstream>
#include "./grafolistaadj.hpp"

using namespace std;

void construirGrafoPonderado(GrafoListaAdj *grafo)
{
    //este é o grafo ponderado
    //https://github.com/eduardolfalcao/edii/blob/master/conteudos/imgs/grafo-ponderado-representacao-matriz-preenchido.png
    //embora não estamos representando com matriz de adjacências

    grafo->inserirArestaNaoDirecionada("v1", "v2", 6);
    grafo->inserirArestaNaoDirecionada("v1", "v3", 4);
    grafo->inserirArestaNaoDirecionada("v2", "v4", 5);
    grafo->inserirArestaNaoDirecionada("v3", "v4", 2);
    grafo->inserirArestaNaoDirecionada("v3", "v5", 4);
    grafo->inserirArestaNaoDirecionada("v4", "v6", 5);
    grafo->inserirArestaNaoDirecionada("v4", "v7", 5);
    grafo->inserirArestaNaoDirecionada("v5", "v9", 9);
    grafo->inserirArestaNaoDirecionada("v6", "v8", 6);
    grafo->inserirArestaNaoDirecionada("v8", "v9", 8);
}

void inserirVertices(GrafoListaAdj *grafo, int ini, int fim)
{
    for (int i = ini; i <= fim; i++)
    {
        string rotulo;
        std::stringstream sstm;
        sstm << "v" << i;
        rotulo = sstm.str();
        grafo->inserirVertice(rotulo);
    }
}

int main()
{
    GrafoListaAdj *grafo;

    {
        cout << "BellmanFordGrafoSemCicloNegativo\n";
        grafo = new GrafoListaAdj();

        inserirVertices(grafo, 1, 9);
        construirGrafoPonderado(grafo);

        cout << "Partindo de v1\n";
        int *distancias = grafo->bellmanFord("v1");
        cout << "distancias[0]== " << distancias[0] << endl;
        cout << "distancias[1]== " << distancias[1] << endl;
        cout << "distancias[2]== " << distancias[2] << endl;
        cout << "distancias[3]== " << distancias[3] << endl;
        cout << "distancias[4]== " << distancias[4] << endl;
        cout << "distancias[5]== " << distancias[5] << endl;
        cout << "distancias[6]== " << distancias[6] << endl;
        cout << "distancias[7]== " << distancias[7] << endl;
        cout << "distancias[8]== " << distancias[8] << endl;
        free(distancias);

        cout << "Partindo de v7\n";
        distancias = grafo->bellmanFord("v7");
        cout << "distancias[0]== " << distancias[0] << endl;
        cout << "distancias[1]== " << distancias[1] << endl;
        cout << "distancias[2]== " << distancias[2] << endl;
        cout << "distancias[3]== " << distancias[3] << endl;
        cout << "distancias[4]== " << distancias[4] << endl;
        cout << "distancias[5]== " << distancias[5] << endl;
        cout << "distancias[6]== " << distancias[6] << endl;
        cout << "distancias[7]== " << distancias[7] << endl;
        cout << "distancias[8]== " << distancias[8] << endl;
        free(distancias);

        cout << "Partindo de v9\n";
        distancias = grafo->bellmanFord("v9");
        cout << "distancias[0]== " << distancias[0] << endl;
        cout << "distancias[1]== " << distancias[1] << endl;
        cout << "distancias[2]== " << distancias[2] << endl;
        cout << "distancias[3]== " << distancias[3] << endl;
        cout << "distancias[4]== " << distancias[4] << endl;
        cout << "distancias[5]== " << distancias[5] << endl;
        cout << "distancias[6]== " << distancias[6] << endl;
        cout << "distancias[7]== " << distancias[7] << endl;
        cout << "distancias[8]== " << distancias[8] << endl;
        free(distancias);
        delete (grafo);
    }

    {
        cout << "BellmanFordGrafoComLacoNegativo\n";
        grafo = new GrafoListaAdj();
        inserirVertices(grafo, 1, 9);
        construirGrafoPonderado(grafo);
        grafo->inserirArestaNaoDirecionada("v1", "v1", -2);

        //grafo com laço com peso negativo em v1
        //como o grafo só tem um componente
        //então todas as distâncias podem ser diminuídas

        cout << "Partindo de v1\n";
        int *distancias = grafo->bellmanFord("v1");
        for (int i = 0; i < 9; i++)
            cout << "distancias[" << i << "]== " << distancias[i] << endl;
        free(distancias);

        //não interessa o vértice de origem,
        //todas as distâncias sempre podem ser diminuídas
        cout << "Partindo de v5\n";
        distancias = grafo->bellmanFord("v5");
        for (int i = 0; i < 9; i++)
            cout << "distancias[" << i << "]== " << distancias[i] << endl;
        free(distancias);

        //não interessa o vértice de origem,
        //todas as distâncias sempre podem ser diminuídas
        cout << "Partindo de v9\n";
        distancias = grafo->bellmanFord("v9");
        for (int i = 0; i < 9; i++)
            cout << "distancias[" << i << "]== " << distancias[i] << endl;
        free(distancias);
        delete (grafo);
    }

    {
        cout << "BellmanFordGrafoCom2ComponentesECicloNegativo\n";
        grafo = new GrafoListaAdj();
        //componente 1
        inserirVertices(grafo, 1, 9);
        construirGrafoPonderado(grafo);
        grafo->inserirArestaNaoDirecionada("v1", "v1", -2);

        //grafo com laço com peso negativo em v1
        //como o grafo tem dois componentes
        //então NÃO SÃO todas as distâncias QUE podem ser diminuídas
        //as distâncias QUE podem ser diminuídas envolvem
        //todos os vértices que são alcancáveis a partir de v1
        //ou seja: v1, v2, v3, v4, v5, v6, v7, v8, v9

        //componente 2
        inserirVertices(grafo, 10, 12);
        grafo->inserirArestaNaoDirecionada("v10", "v11", 10);
        grafo->inserirArestaNaoDirecionada("v10", "v12", 15);

        cout << "Partindo de v10\n";
        int *distancias = grafo->bellmanFord("v10");
        //componente com ciclos negativos
        //{v1,v2,v3,v4,v5,v6,v7,v8,v9}
        for (int i = 0; i < 9; i++)
            cout << "distancias[" << i << "]== " << distancias[i] << endl;
        /* EXPLICAÇÃO PARA RESULTADO ACIMA */
        //infelizmente, o BellmanFord não retorna POS_INF
        //pois se o algoritmo encontrar um ciclo negativo
        //no grafo, então todos os nós do ciclo negativo
        //recebem NEG_INF
        //isso acontece mesmo que não exista caminho entre
        //v10 e {v1,v2,v3,v4,v5,v6,v7,v8,v9}
        //===============================================
        //componente sem ciclos negativos
        //{v10,v11,v12}
        cout << "distancias[9] == " << distancias[9] << endl;
        cout << "distancias[10] == " << distancias[10] << endl;
        cout << "distancias[11] == " << distancias[11] << endl;
        free(distancias);

        cout << "Partindo de v11\n";
        distancias = grafo->bellmanFord("v11");
        //componente com ciclos negativos
        //{v1,v2,v3,v4,v5,v6,v7,v8,v9}
        for (int i = 0; i < 9; i++)
            cout << "distancias[" << i << "]== " << distancias[i] << endl;
        //componente sem ciclos negativos
        //{v10,v11,v12}
        cout << "distancias[9] == " << distancias[9] << endl;
        cout << "distancias[10] == " << distancias[10] << endl;
        cout << "distancias[11] == " << distancias[11] << endl;
        free(distancias);

        cout << "Partindo de v12\n";
        distancias = grafo->bellmanFord("v12");
        //componente com ciclos negativos
        //{v1,v2,v3,v4,v5,v6,v7,v8,v9}
        for (int i = 0; i < 9; i++)
            cout << "distancias[" << i << "]== " << distancias[i] << endl;
        //componente sem ciclos negativos
        //{v10,v11,v12}
        cout << "distancias[9] == " << distancias[9] << endl;
        cout << "distancias[10] == " << distancias[10] << endl;
        cout << "distancias[11] == " << distancias[11] << endl;
        free(distancias);

        cout << "Partindo de v1\n";
        distancias = grafo->bellmanFord("v1");
        //componente com ciclos negativos
        //{v1,v2,v3,v4,v5,v6,v7,v8,v9}
        for (int i = 0; i < 9; i++)
            cout << "distancias[" << i << "]== " << distancias[i] << endl;
        //componente sem ciclos negativos
        //{v10,v11,v12}
        for (int i = 9; i < 12; i++)
            cout << "distancias[" << i << "]== " << distancias[i] << endl;
        free(distancias);

        cout << "Partindo de v5\n";
        distancias = grafo->bellmanFord("v5");
        //componente com ciclos negativos
        //{v1,v2,v3,v4,v5,v6,v7,v8,v9}
        for (int i = 0; i < 9; i++)
            cout << "distancias[" << i << "]== " << distancias[i] << endl;
        //componente sem ciclos negativos
        //{v10,v11,v12}
        for (int i = 9; i < 12; i++)
            cout << "distancias[" << i << "]== " << distancias[i] << endl;
        free(distancias);
        delete (grafo);
    }

    {
        cout << "DijkstraGrafoSemCicloNegativo\n";
        grafo = new GrafoListaAdj();
        inserirVertices(grafo, 1, 9);
        construirGrafoPonderado(grafo);

        cout << "Partindo de v1\n";
        int *distancias = grafo->dijkstra("v1");
        cout << "distancias[0]== " << distancias[0] << endl;
        cout << "distancias[1]== " << distancias[1] << endl;
        cout << "distancias[2]== " << distancias[2] << endl;
        cout << "distancias[3]== " << distancias[3] << endl;
        cout << "distancias[4]== " << distancias[4] << endl;
        cout << "distancias[5]== " << distancias[5] << endl;
        cout << "distancias[6]== " << distancias[6] << endl;
        cout << "distancias[7]== " << distancias[7] << endl;
        cout << "distancias[8]== " << distancias[8] << endl;
        free(distancias);

        cout << "Partindo de v7\n";
        distancias = grafo->dijkstra("v7");
        cout << "distancias[0]== " << distancias[0] << endl;
        cout << "distancias[1]== " << distancias[1] << endl;
        cout << "distancias[2]== " << distancias[2] << endl;
        cout << "distancias[3]== " << distancias[3] << endl;
        cout << "distancias[4]== " << distancias[4] << endl;
        cout << "distancias[5]== " << distancias[5] << endl;
        cout << "distancias[6]== " << distancias[6] << endl;
        cout << "distancias[7]== " << distancias[7] << endl;
        cout << "distancias[8]== " << distancias[8] << endl;
        free(distancias);

        cout << "Partindo de v9\n";
        distancias = grafo->dijkstra("v9");
        cout << "distancias[0]== " << distancias[0] << endl;
        cout << "distancias[1]== " << distancias[1] << endl;
        cout << "distancias[2]== " << distancias[2] << endl;
        cout << "distancias[3]== " << distancias[3] << endl;
        cout << "distancias[4]== " << distancias[4] << endl;
        cout << "distancias[5]== " << distancias[5] << endl;
        cout << "distancias[6]== " << distancias[6] << endl;
        cout << "distancias[7]== " << distancias[7] << endl;
        cout << "distancias[8]== " << distancias[8] << endl;
        free(distancias);
        delete (grafo);
    }

    return 0;
}

// priority_queue<pair<int, int>> q;
// for (int i = 1; i <= n; i++)
// {
//     distance[i] = INF;
// }
// distance[x] = 0;
// q.push({0, x});
// while (!q.empty())
// {
//     int a = q.top().second;
//     q.pop();
//     if (processed[a])
//         continue;
//     processed[a] = true;
//     for (auto u : adj[a])
//     {
//         int b = u.first, w = u.second;
//         if (distance[a] + w < distance[b])
//         {
//             distance[b] = distance[a] + w;
//             q.push({-distance[b], b});
//         }
//     }
// }
