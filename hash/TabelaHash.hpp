#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

template <typename K, typename V>
class Tupla
{
private:
  K chave;
  V valor;
  Tupla *prox;

public:
  Tupla(K c, V v)
  {
    chave = c;
    valor = v;
    prox = NULL;
  }

  K getChave()
  {
    return chave;
  }

  V getValor()
  {
    return valor;
  }

  Tupla *getProx()
  {
    return prox;
  }

  void setProx(Tupla *prox)
  {
    Tupla::prox = prox;
  }
};

template <typename Chave, typename Valor>
class TabelaHash
{

private:
  Tupla<Chave, Valor> **tabela;

  //tamanho atual do array
  int qtde_buckets;
  //qtdade de elementos já inseridos na tabela hash
  int tamanho;

  int obterIndexBucket(Chave c)
  {
    size_t chave = abs(hash<Chave>{}(c));
    return chave % this->qtde_buckets;
  }

  /**
		* Função para inserir a tupla <c,v> na tabela.
		* É preciso calcular o código hash a partir da chave c.
		* Em seguida, usamos qtde_buckets para descobrir o índice
		* dessa tupla. Prestar atenção na alocação de tupla quando
		* há colisões. A função hash às vezes retorna valores
		* negativos: use abs() para evitar índices negativos.
		**/
  void inserir(Chave c, Valor v, Tupla<Chave, Valor> **tabela)
  {
    // Tupla<Chave, Valor> *nova_tupla = (Tupla<Chave, Valor> *)malloc(sizeof(Tupla<Chave, Valor>));
    Tupla<Chave, Valor> *nova_tupla = new Tupla<Chave, Valor>(c, v);
    // *nova_tupla = Tupla<Chave, Valor>(c, v);

    // Tupla<Chave, Valor> nova_tupla(c, v);
    int indexBucket = obterIndexBucket(c);

    Tupla<Chave, Valor> *tupla_inicial_bucket = this->tabela[indexBucket];

    // Adiciona nova tupla no ínicio da lista
    nova_tupla->setProx(tupla_inicial_bucket);
    this->tabela[indexBucket] = nova_tupla;
  }

  /**
		* Função para aumentar o tamanho do array quando o
		* fator de carga for >= 1. O tamanho do array
		* (qtde_buckets) deve ser multiplicado por 8 para
		* que essa operação seja feita com pouca frequência.
		* Por fim, precisamos reposicionar as tuplas, considerando
		* que a posição nesse novo array com maior tamanho
		* será diferente.
		**/
  void aumentaArray()
  {
    int nova_qtde_buckets = this->qtde_buckets * 8;

    Tupla<Chave, Valor> **nova_tabela = new Tupla<Chave, Valor> *[nova_qtde_buckets]; //(Tupla<Chave, Valor> **)malloc(sizeof(Tupla<Chave, Valor> *) * this->qtde_buckets)

    for (int i = 0; i < this->qtde_buckets; i++)
    {
      if (this->tabela[i] == NULL)
        continue;

      Tupla<Chave, Valor> primeiro_elem_bucket = *(this->tabela[i]);
      inserir(primeiro_elem_bucket.getChave(),
              primeiro_elem_bucket.getValor(),
              nova_tabela);
    }

    vector<Chave> chaves = getChaves();
    for (Chave c : chaves)
      remover(c);

    this->tabela = nova_tabela;
    this->qtde_buckets = nova_qtde_buckets;
  }

public:
  /**
		* Inicializar o array de tuplas com capacidade = qtde_buckets.
		* Lembrar de setar todas as posições do array inicializado
		* para NULL.
		**/
  TabelaHash()
  {
    this->tamanho = 0;
    this->qtde_buckets = 8;
    this->tabela = new Tupla<Chave, Valor> *[this->qtde_buckets]; // (Tupla<Chave, Valor> **)malloc(sizeof(Tupla<Chave, Valor> *) * this->qtde_buckets);

    for (int i = 0; i < this->qtde_buckets; i++)
    {
      this->tabela[i] = NULL;
    }
  }

  /**
		* Essa é a função pública que nos permite inserir
		* uma tupla <c,v> na tabela. Nessa função nós
		* verificamos se é preciso aumentar o array de acordo
		* com o load factor. Essa função pode reusar sua versão
		* sobrecarregada para inserir a tupla na tabela.
		* Essa função também incrementa a quantidade de elementos
		* na tabela (variável tamanho).
		**/
  void inserir(Chave c, Valor v)
  {
    this->tamanho++;

    if (load_factor() >= 1)
    {
      aumentaArray();
    }

    inserir(c, v, this->tabela);
  }

  /**
		* Essa função retorna o fator de carga da Tabela Hash.
		**/
  double load_factor()
  {
    return this->tamanho / (double)this->qtde_buckets;
  }

  /**
		* Há apenas um valor associado a uma chave.
		* Essa função retorna esse valor, caso a chave exista.
		* Se a chave não existir a função retorna NULL.
		* Lembre-se: em caso de colisão, é preciso navegar
		* no bucket (lista ligada) para ter certeza se a chave
		* existe ou não.
		**/
  Valor getValor(Chave chave)
  {
    int indexBucket = obterIndexBucket(chave); // O(1)
    Tupla<Chave, Valor> *bucket = this->tabela[indexBucket];

    Tupla<Chave, Valor> elem_no_bucket = *bucket;

    while (elem_no_bucket.getChave() != chave)
    {
      if (elem_no_bucket.getProx() == NULL)
        return NULL;
      else
        elem_no_bucket = *(elem_no_bucket.getProx());
    }

    return elem_no_bucket.getValor();
  }

  /**
		* Essa função retorna true caso a chave exista,
		* false caso contrário.
		* Lembre-se: em caso de colisão, é preciso navegar
		* no bucket (lista ligada) para ter certeza se a chave
		* existe ou não.
		**/
  bool contemChave(Chave chave)
  {
    int indexBucket = obterIndexBucket(chave);
    if (this->tabela[indexBucket] == NULL)
      return false;
    Tupla<Chave, Valor> elem_no_bucket = *(this->tabela[indexBucket]);

    while (elem_no_bucket.getChave() != chave)
    {
      if (elem_no_bucket.getProx() == NULL)
        return false;
      else
        elem_no_bucket = *(elem_no_bucket.getProx());
    }

    return true;
  }

  /**
		* Essa função retorna um vetor com todas as chaves
		* já inseridas na tabela.
		**/
  vector<Chave> getChaves()
  {
    vector<Chave> chaves;

    // for (Tupla<Chave, Valor> *bucket : this->tabela)
    for (int i = 0; i < this->qtde_buckets; i++)
    {
      if (this->tabela[i] == NULL)
        continue;

      Tupla<Chave, Valor> tupla = *(this->tabela[i]);
      do
      {
        chaves.push_back(tupla.getChave());

        if (tupla.getProx() != NULL)
          tupla = *(tupla.getProx());

      } while (tupla.getProx() != NULL);
    }

    return chaves;
  }

  /**
		* Essa função desaloca os nós previamente alocados, e muda
		* o tamanho do array de tuplas para 8.
		**/
  void clear()
  {
    vector<Chave> chaves = getChaves();

    for (Chave c : chaves)
      remover(c);

    this->qtde_buckets = 8;
    this->tamanho = 0;

    Tupla<Chave, Valor> **nova_tabela = new Tupla<Chave, Valor> *[this->qtde_buckets];
    delete this->tabela;
    this->tabela = nova_tabela;

    // Percorre cada Tupla de cada bucket sequencialmente
    // for (int i = 0; i < this->qtde_buckets; i++)
    // {
    //   Tupla<Chave,Valor> *bucket = this->tabela[i];

    //   while ()
    //   {
    //     /* code */
    //   }
    // }
  }

  /**
		* Há apenas um nó associado com uma mesma chave.
		* Essa função remove esse nó da tabela, caso a chave exista.
		* Se a chave não existir a função não faz nada.
		* Lembre-se: em caso de colisão, é preciso navegar
		* no bucket (lista ligada) para ter certeza se a chave
		* existe ou não.
		* Dica: olhar algoritmo de remoção em lista ligada, pois
		* após a remoção de um nó a lista precisa permanecer íntegra,
		* ou seja, navegável.
		**/
  void remover(Chave chave)
  {
    int indexBucket = obterIndexBucket(chave);
    Tupla<Chave, Valor> tupla = *(this->tabela[indexBucket]);

    // Para remover, basta fazer o próximo do anterior ser igual ao próximo do atual
    Tupla<Chave, Valor> *proximo;
    Tupla<Chave, Valor> *excluido;

    // Checa se a chave já está no primeiro
    if (tupla.getChave() == chave)
    {
      excluido = &tupla;
      proximo = tupla.getProx();

      this->tabela[indexBucket] = proximo;
      delete excluido;
    }

    // Checa se a chave está nos elementos seguintes
    while (tupla.getProx() != NULL)
    {
      if (tupla.getProx()->getChave() == chave)
      {
        excluido = &tupla;
        proximo = tupla.getProx()->getProx();

        tupla.setProx(proximo);
        delete excluido;
      }

      tupla = *(tupla.getProx());
    }
  }

  /**
		* Essa função retorna a quantidade de pares
		* que já foram inseridos na Tabela Hash.
		**/
  int size()
  {
    return tamanho;
  }

  /**
		* Essa função retorna o tamanho atual do
		* array usado para armazenar a Tabela Hash.
		**/
  int bucket_count()
  {
    return qtde_buckets;
  }
};