#include "pch.h"
#include "./grafolistaadj.h"
#include <climits>
using namespace std;

#define POS_INF 1000000000
#define NEG_INF -1000000000

class GrafoListaAdjTest : public ::testing::Test
{
protected:
    virtual void TearDown()
    {
        delete (grafo);
    }

    virtual void SetUp()
    {
        grafo = new GrafoListaAdj();
    }

    GrafoListaAdj *grafo;
};

TEST_F(GrafoListaAdjTest, InsercaoVertice)
{
    EXPECT_EQ(grafo->getVertices().size(), 0);
    EXPECT_EQ(grafo->getArestas().size(), 0);
    grafo->inserirVertice("v1");
    EXPECT_EQ(grafo->getVertices().size(), 1);
    EXPECT_EQ(grafo->getArestas().size(), 1);
    grafo->inserirVertice("v2");
    EXPECT_EQ(grafo->getVertices().size(), 2);
    EXPECT_EQ(grafo->getArestas().size(), 2);
}

TEST_F(GrafoListaAdjTest, InsercaoVerticeRepetido)
{
    EXPECT_EQ(grafo->getVertices().size(), 0);
    EXPECT_EQ(grafo->getArestas().size(), 0);
    grafo->inserirVertice("v1");
    EXPECT_EQ(grafo->getVertices().size(), 1);
    EXPECT_EQ(grafo->getArestas().size(), 1);
    grafo->inserirVertice("v1");
    EXPECT_EQ(grafo->getVertices().size(), 1);
    EXPECT_EQ(grafo->getArestas().size(), 1);
}

void inserirVertices(GrafoListaAdj *grafoNaoPonderado, int ini, int fim)
{
    for (int i = ini; i <= fim; i++)
    {
        string rotulo;
        std::stringstream sstm;
        sstm << "v" << i;
        rotulo = sstm.str();
        grafoNaoPonderado->inserirVertice(rotulo);
    }
}

TEST_F(GrafoListaAdjTest, InsercaoArestaNaoDirecionadaNaoPonderada)
{
    inserirVertices(grafo, 1, 9);
    EXPECT_EQ(grafo->getVertices().size(), 9);
    EXPECT_EQ(grafo->getArestas().size(), 9);

    grafo->inserirArestaNaoDirecionada("v1", "v2");
    grafo->inserirArestaNaoDirecionada("v3", "v4");

    /* verificando se v2 estah na lista de conexoes de v1 */
    vector<pair<int, int>> conexoesV1 = grafo->getArestas().at(0); //v1 estah no indice 0
    EXPECT_EQ(conexoesV1.at(0).first, 1);                          //indice de v2 eh 1
    EXPECT_EQ(conexoesV1.at(0).second, 1);                         //peso eh 1

    /* verificando se v1 estah na lista de conexoes de v2 */
    vector<pair<int, int>> conexoesV2 = grafo->getArestas().at(1); //v2 estah no indice 1
    EXPECT_EQ(conexoesV2.at(0).first, 0);                          //indice de v1 eh 0
    EXPECT_EQ(conexoesV2.at(0).second, 1);                         //peso eh 1

    /* verificando se v4 estah na lista de conexoes de v3 */
    vector<pair<int, int>> conexoesV3 = grafo->getArestas().at(2); //v3 estah no indice 2
    EXPECT_EQ(conexoesV3.at(0).first, 3);                          //indice de v4 eh 3
    EXPECT_EQ(conexoesV3.at(0).second, 1);                         //peso eh 1

    /* verificando se v3 estah na lista de conexoes de v4 */
    vector<pair<int, int>> conexoesV4 = grafo->getArestas().at(3); //v4 estah no indice 3
    EXPECT_EQ(conexoesV4.at(0).first, 2);                          //indice de v3 eh 1
    EXPECT_EQ(conexoesV4.at(0).second, 1);                         //peso eh 1
}

TEST_F(GrafoListaAdjTest, InsercaoArestaNaoDirecionadaPonderada)
{
    inserirVertices(grafo, 1, 9);
    grafo->inserirArestaNaoDirecionada("v1", "v2", 4);
    grafo->inserirArestaNaoDirecionada("v3", "v4", 9);

    /* verificando se v2 estah na lista de conexoes de v1 */
    vector<pair<int, int>> conexoesV1 = grafo->getArestas().at(0); //v1 estah no indice 0
    EXPECT_EQ(conexoesV1.at(0).first, 1);                          //indice de v2 eh 1
    EXPECT_EQ(conexoesV1.at(0).second, 4);                         //peso eh 4

    /* verificando se v1 estah na lista de conexoes de v2 */
    vector<pair<int, int>> conexoesV2 = grafo->getArestas().at(1); //v2 estah no indice 1
    EXPECT_EQ(conexoesV2.at(0).first, 0);                          //indice de v1 eh 0
    EXPECT_EQ(conexoesV2.at(0).second, 4);                         //peso eh 4

    /* verificando se v4 estah na lista de conexoes de v3 */
    vector<pair<int, int>> conexoesV3 = grafo->getArestas().at(2); //v3 estah no indice 2
    EXPECT_EQ(conexoesV3.at(0).first, 3);                          //indice de v4 eh 3
    EXPECT_EQ(conexoesV3.at(0).second, 9);                         //peso eh 9

    /* verificando se v3 estah na lista de conexoes de v4 */
    vector<pair<int, int>> conexoesV4 = grafo->getArestas().at(3); //v4 estah no indice 3
    EXPECT_EQ(conexoesV4.at(0).first, 2);                          //indice de v3 eh 1
    EXPECT_EQ(conexoesV4.at(0).second, 9);                         //peso eh 9
}

TEST_F(GrafoListaAdjTest, InsercaoArestaDirecionadaNaoPonderada)
{
    inserirVertices(grafo, 1, 9);

    grafo->inserirArestaDirecionada("v1", "v2");
    grafo->inserirArestaDirecionada("v3", "v4");

    /* verificando se v2 estah na lista de conexoes de v1 */
    vector<pair<int, int>> conexoesV1 = grafo->getArestas().at(0); //v1 estah no indice 0
    EXPECT_EQ(conexoesV1.at(0).first, 1);                          //indice de v2 eh 1
    EXPECT_EQ(conexoesV1.at(0).second, 1);                         //peso eh 1

    /* verificando se v1 NAO estah na lista de conexoes de v2 */
    vector<pair<int, int>> conexoesV2 = grafo->getArestas().at(1); //v2 estah no indice 1
    EXPECT_EQ(conexoesV2.size(), 0);                               //nao existe vertice nessa lista de conexoes

    /* verificando se v4 estah na lista de conexoes de v3 */
    vector<pair<int, int>> conexoesV3 = grafo->getArestas().at(2); //v3 estah no indice 2
    EXPECT_EQ(conexoesV3.at(0).first, 3);                          //indice de v4 eh 3
    EXPECT_EQ(conexoesV3.at(0).second, 1);                         //peso eh 1

    /* verificando se v3 NAO estah na lista de conexoes de v4 */
    vector<pair<int, int>> conexoesV4 = grafo->getArestas().at(3); //v4 estah no indice 3
    EXPECT_EQ(conexoesV4.size(), 0);                               //nao existe vertice nessa lista de conexoes
}

TEST_F(GrafoListaAdjTest, InsercaoArestaDirecionadaPonderada)
{
    inserirVertices(grafo, 1, 9);

    grafo->inserirArestaDirecionada("v1", "v2", 4);
    grafo->inserirArestaDirecionada("v3", "v4", 9);

    /* verificando se v2 estah na lista de conexoes de v1 */
    vector<pair<int, int>> conexoesV1 = grafo->getArestas().at(0); //v1 estah no indice 0
    EXPECT_EQ(conexoesV1.at(0).first, 1);                          //indice de v2 eh 1
    EXPECT_EQ(conexoesV1.at(0).second, 4);                         //peso eh 4

    /* verificando se v1 NAO estah na lista de conexoes de v2 */
    vector<pair<int, int>> conexoesV2 = grafo->getArestas().at(1); //v2 estah no indice 1
    EXPECT_EQ(conexoesV2.size(), 0);                               //nao existe vertice nessa lista de conexoes

    /* verificando se v4 estah na lista de conexoes de v3 */
    vector<pair<int, int>> conexoesV3 = grafo->getArestas().at(2); //v3 estah no indice 2
    EXPECT_EQ(conexoesV3.at(0).first, 3);                          //indice de v4 eh 3
    EXPECT_EQ(conexoesV3.at(0).second, 9);                         //peso eh 9

    /* verificando se v3 NAO estah na lista de conexoes de v4 */
    vector<pair<int, int>> conexoesV4 = grafo->getArestas().at(3); //v4 estah no indice 3
    EXPECT_EQ(conexoesV4.size(), 0);                               //nao existe vertice nessa lista de conexoes
}

TEST_F(GrafoListaAdjTest, SaoConectadosGrafoNaoDirecionado)
{
    inserirVertices(grafo, 1, 9);

    grafo->inserirArestaNaoDirecionada("v1", "v2");
    grafo->inserirArestaNaoDirecionada("v3", "v4");

    EXPECT_TRUE(grafo->saoConectados("v1", "v2"));
    EXPECT_TRUE(grafo->saoConectados("v2", "v1"));
    EXPECT_TRUE(grafo->saoConectados("v3", "v4"));
    EXPECT_TRUE(grafo->saoConectados("v4", "v3"));
}

TEST_F(GrafoListaAdjTest, SaoConectadosGrafoDirecionado)
{
    inserirVertices(grafo, 1, 9);

    grafo->inserirArestaDirecionada("v1", "v2");
    grafo->inserirArestaDirecionada("v3", "v4");

    EXPECT_TRUE(grafo->saoConectados("v1", "v2"));
    EXPECT_FALSE(grafo->saoConectados("v2", "v1"));
    EXPECT_TRUE(grafo->saoConectados("v3", "v4"));
    EXPECT_FALSE(grafo->saoConectados("v4", "v3"));
}

TEST_F(GrafoListaAdjTest, haCaminho)
{
    inserirVertices(grafo, 1, 9);

    //grafo usado: https://github.com/eduardolfalcao/edii/blob/master/conteudos/imgs/grafo-tad-rotulado.png

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

    EXPECT_FALSE(grafo->haCaminho("v1", "v1"));
    EXPECT_TRUE(grafo->haCaminho("v9", "v9"));
    EXPECT_TRUE(grafo->haCaminho("v1", "v2"));
    EXPECT_TRUE(grafo->haCaminho("v1", "v9"));

    //note que o nó 7 não está conectado, como mostrado no grafo da url acima!
    //logo, não existe caminhos chegando ou partindo de v7
    EXPECT_FALSE(grafo->haCaminho("v1", "v7"));
    EXPECT_FALSE(grafo->haCaminho("v7", "v5"));
}

TEST_F(GrafoListaAdjTest, colorirGrafo1Comp)
{
    inserirVertices(grafo, 1, 9);

    //grafo usado: https://github.com/eduardolfalcao/edii/blob/master/conteudos/imgs/grafo-tad-rotulado.png

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

    EXPECT_EQ(grafo->colorir(), 1);
    for (int i = 1; i <= 8; i++)
    {
        EXPECT_EQ(grafo->getVertices().at(i - 1), grafo->getVertices().at(i));
    }
}

TEST_F(GrafoListaAdjTest, colorirGrafo5Comp)
{
    inserirVertices(grafo, 0, 17);

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

    //comp5: vértice "v12"

    EXPECT_EQ(grafo->colorir(), 5);

    string corComp1 = grafo->getVertices().at(0);
    EXPECT_EQ(grafo->getVertices().at(4), corComp1);
    EXPECT_EQ(grafo->getVertices().at(8), corComp1);
    EXPECT_EQ(grafo->getVertices().at(13), corComp1);
    EXPECT_EQ(grafo->getVertices().at(14), corComp1);

    string corComp2 = grafo->getVertices().at(1);
    EXPECT_EQ(grafo->getVertices().at(5), corComp2);
    EXPECT_EQ(grafo->getVertices().at(16), corComp2);
    EXPECT_EQ(grafo->getVertices().at(17), corComp2);

    string corComp3 = grafo->getVertices().at(3);
    EXPECT_EQ(grafo->getVertices().at(9), corComp3);
    EXPECT_EQ(grafo->getVertices().at(15), corComp3);
    EXPECT_EQ(grafo->getVertices().at(2), corComp3);
    EXPECT_EQ(grafo->getVertices().at(10), corComp3);

    string corComp4 = grafo->getVertices().at(6);
    EXPECT_EQ(grafo->getVertices().at(7), corComp4);
    EXPECT_EQ(grafo->getVertices().at(11), corComp4);

    EXPECT_NE(grafo->getVertices().at(12), corComp1);
    EXPECT_NE(grafo->getVertices().at(12), corComp2);
    EXPECT_NE(grafo->getVertices().at(12), corComp3);
    EXPECT_NE(grafo->getVertices().at(12), corComp4);
}

TEST_F(GrafoListaAdjTest, bfsGrafo1CompNaoPonderado)
{
    inserirVertices(grafo, 1, 9);

    //grafo usado: https://github.com/eduardolfalcao/edii/blob/master/conteudos/imgs/grafo-tad-rotulado.png

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

    int *distancias = grafo->bfs("v1");
    EXPECT_EQ(distancias[0], 0);
    EXPECT_EQ(distancias[1], 1);
    EXPECT_EQ(distancias[2], 1);
    EXPECT_EQ(distancias[3], 2);
    EXPECT_EQ(distancias[4], 2);
    EXPECT_EQ(distancias[5], 3);
    EXPECT_EQ(distancias[6], 3);
    EXPECT_EQ(distancias[7], 4);
    EXPECT_EQ(distancias[8], 3);
    free(distancias);

    distancias = grafo->bfs("v2");
    EXPECT_EQ(distancias[0], 1);
    EXPECT_EQ(distancias[1], 0);
    EXPECT_EQ(distancias[2], 2);
    EXPECT_EQ(distancias[3], 1);
    EXPECT_EQ(distancias[4], 3);
    EXPECT_EQ(distancias[5], 2);
    EXPECT_EQ(distancias[6], 2);
    EXPECT_EQ(distancias[7], 3);
    EXPECT_EQ(distancias[8], 4);
    free(distancias);
}

TEST_F(GrafoListaAdjTest, bfsGrafo5CompNaoPonderado)
{
    inserirVertices(grafo, 0, 17);

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

    //comp5: vértice "v12"

    int *distancias = grafo->bfs("v0");
    EXPECT_EQ(distancias[0], 0);
    EXPECT_EQ(distancias[1], 0);
    EXPECT_EQ(distancias[2], 0);
    EXPECT_EQ(distancias[3], 0);
    EXPECT_EQ(distancias[4], 1);
    EXPECT_EQ(distancias[5], 0);
    EXPECT_EQ(distancias[6], 0);
    EXPECT_EQ(distancias[7], 0);
    EXPECT_EQ(distancias[8], 1);
    EXPECT_EQ(distancias[9], 0);
    EXPECT_EQ(distancias[10], 0);
    EXPECT_EQ(distancias[11], 0);
    EXPECT_EQ(distancias[12], 0);
    EXPECT_EQ(distancias[13], 1);
    EXPECT_EQ(distancias[14], 1);
    EXPECT_EQ(distancias[15], 0);
    EXPECT_EQ(distancias[16], 0);
    EXPECT_EQ(distancias[17], 0);
    free(distancias);

    distancias = grafo->bfs("v1");
    EXPECT_EQ(distancias[0], 0);
    EXPECT_EQ(distancias[1], 0);
    EXPECT_EQ(distancias[2], 0);
    EXPECT_EQ(distancias[3], 0);
    EXPECT_EQ(distancias[4], 0);
    EXPECT_EQ(distancias[5], 1);
    EXPECT_EQ(distancias[6], 0);
    EXPECT_EQ(distancias[7], 0);
    EXPECT_EQ(distancias[8], 0);
    EXPECT_EQ(distancias[9], 0);
    EXPECT_EQ(distancias[10], 0);
    EXPECT_EQ(distancias[11], 0);
    EXPECT_EQ(distancias[12], 0);
    EXPECT_EQ(distancias[13], 0);
    EXPECT_EQ(distancias[14], 0);
    EXPECT_EQ(distancias[15], 0);
    EXPECT_EQ(distancias[16], 2);
    EXPECT_EQ(distancias[17], 2);
    free(distancias);

    distancias = grafo->bfs("v11");
    EXPECT_EQ(distancias[0], 0);
    EXPECT_EQ(distancias[1], 0);
    EXPECT_EQ(distancias[2], 0);
    EXPECT_EQ(distancias[3], 0);
    EXPECT_EQ(distancias[4], 0);
    EXPECT_EQ(distancias[5], 0);
    EXPECT_EQ(distancias[6], 1);
    EXPECT_EQ(distancias[7], 1);
    EXPECT_EQ(distancias[8], 0);
    EXPECT_EQ(distancias[9], 0);
    EXPECT_EQ(distancias[10], 0);
    EXPECT_EQ(distancias[11], 0);
    EXPECT_EQ(distancias[12], 0);
    EXPECT_EQ(distancias[13], 0);
    EXPECT_EQ(distancias[14], 0);
    EXPECT_EQ(distancias[15], 0);
    EXPECT_EQ(distancias[16], 0);
    EXPECT_EQ(distancias[17], 0);
    free(distancias);

    distancias = grafo->bfs("v3");
    EXPECT_EQ(distancias[0], 0);
    EXPECT_EQ(distancias[1], 0);
    EXPECT_EQ(distancias[2], 2);
    EXPECT_EQ(distancias[3], 0);
    EXPECT_EQ(distancias[4], 0);
    EXPECT_EQ(distancias[5], 0);
    EXPECT_EQ(distancias[6], 0);
    EXPECT_EQ(distancias[7], 0);
    EXPECT_EQ(distancias[8], 0);
    EXPECT_EQ(distancias[9], 1);
    EXPECT_EQ(distancias[10], 3);
    EXPECT_EQ(distancias[11], 0);
    EXPECT_EQ(distancias[12], 0);
    EXPECT_EQ(distancias[13], 0);
    EXPECT_EQ(distancias[14], 0);
    EXPECT_EQ(distancias[15], 2);
    EXPECT_EQ(distancias[16], 0);
    EXPECT_EQ(distancias[17], 0);
    free(distancias);
}

TEST_F(GrafoListaAdjTest, BellmanFordGrafoSemCicloNegativo)
{
    inserirVertices(grafo, 1, 9);

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

    int *distancias = grafo->bellmanFord("v1");
    EXPECT_EQ(distancias[0], 0);
    EXPECT_EQ(distancias[1], 6);
    EXPECT_EQ(distancias[2], 4);
    EXPECT_EQ(distancias[3], 6);
    EXPECT_EQ(distancias[4], 8);
    EXPECT_EQ(distancias[5], 11);
    EXPECT_EQ(distancias[6], 11);
    EXPECT_EQ(distancias[7], 17);
    EXPECT_EQ(distancias[8], 17);
    free(distancias);

    distancias = grafo->bellmanFord("v7");
    EXPECT_EQ(distancias[0], 11);
    EXPECT_EQ(distancias[1], 10);
    EXPECT_EQ(distancias[2], 7);
    EXPECT_EQ(distancias[3], 5);
    EXPECT_EQ(distancias[4], 11);
    EXPECT_EQ(distancias[5], 10);
    EXPECT_EQ(distancias[6], 0);
    EXPECT_EQ(distancias[7], 16);
    EXPECT_EQ(distancias[8], 20);
    free(distancias);

    distancias = grafo->bellmanFord("v9");
    EXPECT_EQ(distancias[0], 17);
    EXPECT_EQ(distancias[1], 20);
    EXPECT_EQ(distancias[2], 13);
    EXPECT_EQ(distancias[3], 15);
    EXPECT_EQ(distancias[4], 9);
    EXPECT_EQ(distancias[5], 14);
    EXPECT_EQ(distancias[6], 20);
    EXPECT_EQ(distancias[7], 8);
    EXPECT_EQ(distancias[8], 0);
    free(distancias);
}

TEST_F(GrafoListaAdjTest, BellmanFordGrafoComLacoNegativo)
{
    inserirVertices(grafo, 1, 9);

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

    //grafo com aresta (laço) com peso negativo
    //como o grafo só tem um componente
    //então todas as distâncias podem ser diminuídas
    grafo->inserirArestaNaoDirecionada("v1", "v1", -2);
    int *distancias = grafo->bellmanFord("v1");

    EXPECT_EQ(distancias[0], NEG_INF);
    EXPECT_EQ(distancias[1], NEG_INF);
    EXPECT_EQ(distancias[2], NEG_INF);
    EXPECT_EQ(distancias[3], NEG_INF);
    EXPECT_EQ(distancias[4], NEG_INF);
    EXPECT_EQ(distancias[5], NEG_INF);
    EXPECT_EQ(distancias[6], NEG_INF);
    EXPECT_EQ(distancias[7], NEG_INF);
    EXPECT_EQ(distancias[8], NEG_INF);
    free(distancias);

    distancias = grafo->bellmanFord("v5");
    EXPECT_EQ(distancias[0], NEG_INF);
    EXPECT_EQ(distancias[1], NEG_INF);
    EXPECT_EQ(distancias[2], NEG_INF);
    EXPECT_EQ(distancias[3], NEG_INF);
    EXPECT_EQ(distancias[4], NEG_INF);
    EXPECT_EQ(distancias[5], NEG_INF);
    EXPECT_EQ(distancias[6], NEG_INF);
    EXPECT_EQ(distancias[7], NEG_INF);
    EXPECT_EQ(distancias[8], NEG_INF);
    free(distancias);

    distancias = grafo->bellmanFord("v9");
    EXPECT_EQ(distancias[0], NEG_INF);
    EXPECT_EQ(distancias[1], NEG_INF);
    EXPECT_EQ(distancias[2], NEG_INF);
    EXPECT_EQ(distancias[3], NEG_INF);
    EXPECT_EQ(distancias[4], NEG_INF);
    EXPECT_EQ(distancias[5], NEG_INF);
    EXPECT_EQ(distancias[6], NEG_INF);
    EXPECT_EQ(distancias[7], NEG_INF);
    EXPECT_EQ(distancias[8], NEG_INF);
    free(distancias);
}

TEST_F(GrafoListaAdjTest, BellmanFordGrafoCom2ComponentesECicloNegativo)
{
    inserirVertices(grafo, 1, 9);

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

    //grafo com aresta (laço) com peso negativo
    //como o grafo só tem um componente
    //então todas as distâncias podem ser diminuídas
    grafo->inserirArestaNaoDirecionada("v1", "v1", -2);

    //inserindo segundo componente, que nao tem
    //ciclo negativo
    inserirVertices(grafo, 10, 12);
    grafo->inserirArestaNaoDirecionada("v10", "v11", 10);
    grafo->inserirArestaNaoDirecionada("v10", "v12", 15);

    int *distancias = grafo->bellmanFord("v10");
    //componente com ciclos negativos
    EXPECT_EQ(distancias[0], NEG_INF);
    EXPECT_EQ(distancias[1], NEG_INF);
    EXPECT_EQ(distancias[2], NEG_INF);
    EXPECT_EQ(distancias[3], NEG_INF);
    EXPECT_EQ(distancias[4], NEG_INF);
    EXPECT_EQ(distancias[5], NEG_INF);
    EXPECT_EQ(distancias[6], NEG_INF);
    EXPECT_EQ(distancias[7], NEG_INF);
    EXPECT_EQ(distancias[8], NEG_INF);
    //componente sem ciclos negativos
    EXPECT_EQ(distancias[9], 0);
    EXPECT_EQ(distancias[10], 10);
    EXPECT_EQ(distancias[11], 15);
    //libera array
    free(distancias);

    distancias = grafo->bellmanFord("v11");
    //componente com ciclos negativos
    EXPECT_EQ(distancias[0], NEG_INF);
    EXPECT_EQ(distancias[1], NEG_INF);
    EXPECT_EQ(distancias[2], NEG_INF);
    EXPECT_EQ(distancias[3], NEG_INF);
    EXPECT_EQ(distancias[4], NEG_INF);
    EXPECT_EQ(distancias[5], NEG_INF);
    EXPECT_EQ(distancias[6], NEG_INF);
    EXPECT_EQ(distancias[7], NEG_INF);
    EXPECT_EQ(distancias[8], NEG_INF);
    //componente sem ciclos negativos
    EXPECT_EQ(distancias[9], 10);
    EXPECT_EQ(distancias[10], 0);
    EXPECT_EQ(distancias[11], 25);
    //libera array
    free(distancias);

    distancias = grafo->bellmanFord("v12");
    //componente com ciclos negativos
    EXPECT_EQ(distancias[0], NEG_INF);
    EXPECT_EQ(distancias[1], NEG_INF);
    EXPECT_EQ(distancias[2], NEG_INF);
    EXPECT_EQ(distancias[3], NEG_INF);
    EXPECT_EQ(distancias[4], NEG_INF);
    EXPECT_EQ(distancias[5], NEG_INF);
    EXPECT_EQ(distancias[6], NEG_INF);
    EXPECT_EQ(distancias[7], NEG_INF);
    EXPECT_EQ(distancias[8], NEG_INF);
    //componente sem ciclos negativos
    EXPECT_EQ(distancias[9], 15);
    EXPECT_EQ(distancias[10], 25);
    EXPECT_EQ(distancias[11], 0);
    //libera array
    free(distancias);

    distancias = grafo->bellmanFord("v1");
    //componente com ciclos negativos
    EXPECT_EQ(distancias[0], NEG_INF);
    EXPECT_EQ(distancias[1], NEG_INF);
    EXPECT_EQ(distancias[2], NEG_INF);
    EXPECT_EQ(distancias[3], NEG_INF);
    EXPECT_EQ(distancias[4], NEG_INF);
    EXPECT_EQ(distancias[5], NEG_INF);
    EXPECT_EQ(distancias[6], NEG_INF);
    EXPECT_EQ(distancias[7], NEG_INF);
    EXPECT_EQ(distancias[8], NEG_INF);
    //componente sem ciclos negativos
    EXPECT_EQ(distancias[9], POS_INF);
    EXPECT_EQ(distancias[10], POS_INF);
    EXPECT_EQ(distancias[11], POS_INF);
    //libera array
    free(distancias);

    distancias = grafo->bellmanFord("v5");
    //componente com ciclos negativos
    EXPECT_EQ(distancias[0], NEG_INF);
    EXPECT_EQ(distancias[1], NEG_INF);
    EXPECT_EQ(distancias[2], NEG_INF);
    EXPECT_EQ(distancias[3], NEG_INF);
    EXPECT_EQ(distancias[4], NEG_INF);
    EXPECT_EQ(distancias[5], NEG_INF);
    EXPECT_EQ(distancias[6], NEG_INF);
    EXPECT_EQ(distancias[7], NEG_INF);
    EXPECT_EQ(distancias[8], NEG_INF);
    //componente sem ciclos negativos
    EXPECT_EQ(distancias[9], POS_INF);
    EXPECT_EQ(distancias[10], POS_INF);
    EXPECT_EQ(distancias[11], POS_INF);
    //libera array
    free(distancias);
}

TEST_F(GrafoListaAdjTest, DijkstraGrafoSemCicloNegativo)
{
    inserirVertices(grafo, 1, 9);

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

    int *distancias = grafo->dijkstra("v1");
    EXPECT_EQ(distancias[0], 0);
    EXPECT_EQ(distancias[1], 6);
    EXPECT_EQ(distancias[2], 4);
    EXPECT_EQ(distancias[3], 6);
    EXPECT_EQ(distancias[4], 8);
    EXPECT_EQ(distancias[5], 11);
    EXPECT_EQ(distancias[6], 11);
    EXPECT_EQ(distancias[7], 17);
    EXPECT_EQ(distancias[8], 17);
    free(distancias);

    distancias = grafo->dijkstra("v7");
    EXPECT_EQ(distancias[0], 11);
    EXPECT_EQ(distancias[1], 10);
    EXPECT_EQ(distancias[2], 7);
    EXPECT_EQ(distancias[3], 5);
    EXPECT_EQ(distancias[4], 11);
    EXPECT_EQ(distancias[5], 10);
    EXPECT_EQ(distancias[6], 0);
    EXPECT_EQ(distancias[7], 16);
    EXPECT_EQ(distancias[8], 20);
    free(distancias);

    distancias = grafo->dijkstra("v9");
    EXPECT_EQ(distancias[0], 17);
    EXPECT_EQ(distancias[1], 20);
    EXPECT_EQ(distancias[2], 13);
    EXPECT_EQ(distancias[3], 15);
    EXPECT_EQ(distancias[4], 9);
    EXPECT_EQ(distancias[5], 14);
    EXPECT_EQ(distancias[6], 20);
    EXPECT_EQ(distancias[7], 8);
    EXPECT_EQ(distancias[8], 0);
    free(distancias);
}