#include <unordered_map>
#include <iostream>
#include "./TabelaHash.hpp"
#include <chrono>

using namespace std::chrono;
using namespace std;

//& para forçar a passagem do objeto por referência
void criarTabela(TabelaHash<string, int> &tabela, int qtdadeRepeticoes, string itens[])
{
    for (int i = 0; i < 5; i++)
        for (int j = 1; j <= qtdadeRepeticoes; j++)
            tabela.inserir(itens[i] + to_string(j), 500);
}

int main()
{
    string itens[5] = {"cebola", "feijao", "tomate", "arroz", "macarrao"};
    TabelaHash<string, int> estoqueSupermercadoTabelaHash;

    {
        cout << "AdicionarEmTabelaVazia\n";
        criarTabela(estoqueSupermercadoTabelaHash, 1, itens);
        if (estoqueSupermercadoTabelaHash.contemChave("cebola1"))
            cout << "contemChave(cebola1)\n";
        if (estoqueSupermercadoTabelaHash.contemChave("tomate1"))
            cout << "contemChave(tomate1)\n";
        if (estoqueSupermercadoTabelaHash.contemChave("feijao1"))
            cout << "contemChave(feijao1)\n";
        if (estoqueSupermercadoTabelaHash.contemChave("arroz1"))
            cout << "contemChave(arroz1)\n";
        if (estoqueSupermercadoTabelaHash.contemChave("macarrao1"))
            cout << "contemChave(macarrao1)\n";
        if (estoqueSupermercadoTabelaHash.size(), 5)
            cout << "estoqueSupermercadoTabelaHash.size() == 5\n";
        if (estoqueSupermercadoTabelaHash.bucket_count() == 8)
            cout << "estoqueSupermercadoTabelaHash.bucket_count() == 8\n";
        estoqueSupermercadoTabelaHash.clear();
    }

    {
        cout << "ForcarAumentoDeTabela\n";
        int qtdadeRepeticoes = 2;
        criarTabela(estoqueSupermercadoTabelaHash, qtdadeRepeticoes, itens);
        for (int i = 0; i < 5; i++)
            for (int j = 1; j <= qtdadeRepeticoes; j++)
                estoqueSupermercadoTabelaHash.contemChave(itens[i] + to_string(j));

        if (estoqueSupermercadoTabelaHash.size() == 10)
            cout << "estoqueSupermercadoTabelaHash.size() == 10\n";
        //tamanho inicial do array é 8, e cada vez que precisamos aumentar
        //ele multiplica por 8
        if (estoqueSupermercadoTabelaHash.bucket_count() == 64)
            cout << "estoqueSupermercadoTabelaHash.bucket_count() == 64\n";

        estoqueSupermercadoTabelaHash.clear();
    }

    cout << "ForcarAumentoDeTabelaMultiplasVezes\n";
    {
        int qtdadeRepeticoes = 1000;
        criarTabela(estoqueSupermercadoTabelaHash, qtdadeRepeticoes, itens);
        for (int i = 0; i < 5; i++)
            for (int j = 1; j <= qtdadeRepeticoes; j++)
                estoqueSupermercadoTabelaHash.contemChave(itens[i] + to_string(j));

        if (estoqueSupermercadoTabelaHash.size(), 5 * qtdadeRepeticoes)
            cout << "estoqueSupermercadoTabelaHash.size() == 5 * qtdadeRepeticoes\n";
        //tamanho inicial do array é 8, e cada vez que precisamos aumentar
        //ele multiplica por 8
        if (estoqueSupermercadoTabelaHash.bucket_count() == 32768)
            cout << "estoqueSupermercadoTabelaHash.bucket_count(), 32768\n";

        estoqueSupermercadoTabelaHash.clear();
    }

    cout << "LoadFactorEmTabelaPequena\n";
    {
        criarTabela(estoqueSupermercadoTabelaHash, 1, itens);
        if (estoqueSupermercadoTabelaHash.load_factor() == 5.0 / 8.0)
            cout << "estoqueSupermercadoTabelaHash.load_factor() == 5.0 / 8.0\n";
        estoqueSupermercadoTabelaHash.clear();
    }

    cout << "LoadFactorEmTabelaGrande\n";
    {
        criarTabela(estoqueSupermercadoTabelaHash, 1000, itens);
        if (estoqueSupermercadoTabelaHash.load_factor() == 5000.0 / 32768.0)
            cout << "estoqueSupermercadoTabelaHash.load_factor() == 5000.0 / 32768.0\n";
        estoqueSupermercadoTabelaHash.clear();
    }

    cout << "GetValor\n";
    {
        criarTabela(estoqueSupermercadoTabelaHash, 1000, itens);
        if (estoqueSupermercadoTabelaHash.getValor("cebola1000") == 500)
            cout << "estoqueSupermercadoTabelaHash.getValor('cebola1000'), 500\n";
        // if (estoqueSupermercadoTabelaHash.getValor("cebola1001") == NULL)
        //     cout << "estoqueSupermercadoTabelaHash.getValor('cebola1001'), NULL\n";
        estoqueSupermercadoTabelaHash.clear();
    }

    cout << "ContemChave\n";
    {
        criarTabela(estoqueSupermercadoTabelaHash, 1000, itens);
        if (estoqueSupermercadoTabelaHash.contemChave("cebola1000"))
            cout << "estoqueSupermercadoTabelaHash.contemChave('cebola1000')\n";
        if (estoqueSupermercadoTabelaHash.contemChave("cebola1001"))
            cout << "estoqueSupermercadoTabelaHash.contemChave('cebola1001')\n";
        estoqueSupermercadoTabelaHash.clear();
    }

    cout << "GetChaves\n";
    {
        int qtdadeRepeticoes = 1000;
        criarTabela(estoqueSupermercadoTabelaHash, qtdadeRepeticoes, itens);
        vector<string> chaves = estoqueSupermercadoTabelaHash.getChaves();
        if (chaves.size() == 5000)
            cout << "chaves.size(), 5000\n";
        // for (int i = 0; i < 5; i++)
        // {
        //     for (int j = 1; j <= qtdadeRepeticoes; j++)
        //     {
        //         if (count(chaves.begin(), chaves.end(), itens[i] + to_string(j)))
        //             cout << "count(chaves.begin(), chaves.end(), itens[i] + to_string(j))\n";
        //     }
        // }
        estoqueSupermercadoTabelaHash.clear();
    }

    cout << "RemoverTuplaEmTabelaPequena\n";
    {
        criarTabela(estoqueSupermercadoTabelaHash, 1, itens);
        if (estoqueSupermercadoTabelaHash.contemChave("tomate1"))
            cout << "estoqueSupermercadoTabelaHash.contemChave('tomate1')\n";
        if (estoqueSupermercadoTabelaHash.contemChave("cebola1"))
            cout << "estoqueSupermercadoTabelaHash.contemChave('cebola1')\n";
        if (estoqueSupermercadoTabelaHash.contemChave("feijao1"))
            cout << "estoqueSupermercadoTabelaHash.contemChave('feijao1')\n";
        if (estoqueSupermercadoTabelaHash.contemChave("arroz1"))
            cout << "estoqueSupermercadoTabelaHash.contemChave('arroz1')\n";
        if (estoqueSupermercadoTabelaHash.contemChave("macarrao1"))
            cout << "estoqueSupermercadoTabelaHash.contemChave('macarrao1')\n";
        if (estoqueSupermercadoTabelaHash.size() == 5)
            cout << "estoqueSupermercadoTabelaHash.size(), 5\n";

        estoqueSupermercadoTabelaHash.remover("tomate1");
        if (estoqueSupermercadoTabelaHash.size() == 4)
            cout << "estoqueSupermercadoTabelaHash.size(), 4\n";
        vector<string> chaves = estoqueSupermercadoTabelaHash.getChaves();
        // if (count(chaves.begin(), chaves.end(), "tomate1"))
        //     cout << "count(chaves.begin(), chaves.end(), 'tomate1')";

        estoqueSupermercadoTabelaHash.remover("arroz1");
        if (estoqueSupermercadoTabelaHash.size() == 3)
            cout << "estoqueSupermercadoTabelaHash.size(), 3\n";
        chaves = estoqueSupermercadoTabelaHash.getChaves();
        // if (count(chaves.begin(), chaves.end(), "arroz1"))
        //     cout << "count(chaves.begin(), chaves.end(), 'arroz1')\n";
        estoqueSupermercadoTabelaHash.clear();
    }

    cout << "RemoverTodasAsTuplasEmTabelaGrande\n";
    {
        int qtdadeRepeticoes = 1000;
        criarTabela(estoqueSupermercadoTabelaHash, qtdadeRepeticoes, itens);

        for (int i = 0; i < 5; i++)
        {
            for (int j = 1; j <= qtdadeRepeticoes; j++)
            {
                estoqueSupermercadoTabelaHash.remover(itens[i] + to_string(j));
            }
        }

        vector<string> chaves = estoqueSupermercadoTabelaHash.getChaves();
        // for (int i = 0; i < 5; i++)
        //     for (int j = 1; j <= qtdadeRepeticoes; j++)
        //         if (count(chaves.begin(), chaves.end(), itens[i] + to_string(j)))
        //             cout << "count(chaves.begin(), chaves.end(), itens[i] + to_string(j))\n";

        if (estoqueSupermercadoTabelaHash.size() == 0)
            cout << "estoqueSupermercadoTabelaHash.size(), 0\n";
        estoqueSupermercadoTabelaHash.clear();
    }

    return 0;
}
