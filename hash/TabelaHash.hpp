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

  int obterIndexBucket(Chave c, int total_buckets)
  {
    size_t chave = hash<Chave>{}(c); // usar abs()?
    return chave % total_buckets;
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
    Tupla<Chave, Valor> *nova_tupla = new Tupla<Chave, Valor>(c, v);

    int indexBucket = obterIndexBucket(c, this->qtde_buckets);

    Tupla<Chave, Valor> *tupla_inicial_bucket = this->tabela[indexBucket];

    // Adiciona nova tupla no ínicio da lista encadeada
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
    int i;
    int nova_qtde_buckets = this->qtde_buckets * 8;

    Tupla<Chave, Valor> **nova_tabela = new Tupla<Chave, Valor> *[nova_qtde_buckets];
    for (i = 0; i < nova_qtde_buckets; i++)
      nova_tabela[i] = NULL;

    // Faz a transferência dos primeiros elementos de cada bucket
    // da tabela antiga para a nova
    for (i = 0; i < this->qtde_buckets; i++)
    {
      if (this->tabela[i] == NULL)
        continue;

      Tupla<Chave, Valor> *primeiro_elem_bucket = this->tabela[i];
      int index_nova_tabela = obterIndexBucket(primeiro_elem_bucket->getChave(), nova_qtde_buckets);
      nova_tabela[index_nova_tabela] = primeiro_elem_bucket;
    }

    delete this->tabela;
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
    reset_tabela(); // reset_tabela() também é chamado em clear();
  }

  void reset_tabela()
  {
    this->tamanho = 0;
    this->qtde_buckets = 8;

    delete this->tabela;
    this->tabela = new Tupla<Chave, Valor> *[this->qtde_buckets];
    for (int i = 0; i < this->qtde_buckets; i++)
      this->tabela[i] = NULL;
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

    if (load_factor() >= 1.0)
      aumentaArray();

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
    int indexBucket = obterIndexBucket(chave, this->qtde_buckets); // O(1)

    Tupla<Chave, Valor> *tupla = this->tabela[indexBucket];

    while (tupla->getChave() != chave)
    {
      if (tupla->getProx() == NULL)
        return NULL;
      else
        tupla = tupla->getProx();
    }

    return tupla->getValor();
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
    int indexBucket = obterIndexBucket(chave, this->qtde_buckets);
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

    for (int i = 0; i < this->qtde_buckets; i++)
    {
      if (this->tabela[i] == NULL)
        continue;

      Tupla<Chave, Valor> *tupla = this->tabela[i];
      do
      {
        chaves.push_back(tupla->getChave());
        tupla = tupla->getProx();
      } while (tupla != NULL);
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

    reset_tabela();
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
    int index_bucket = obterIndexBucket(chave, this->qtde_buckets);

    Tupla<Chave, Valor> *tupla = this->tabela[index_bucket];

    if (tupla == NULL)
      return;
    // Para remover, basta fazer o próximo do anterior ser igual ao próximo do atual
    Tupla<Chave, Valor> *proximo;
    Tupla<Chave, Valor> *excluido;

    // Checa se a chave já está no primeiro
    if (tupla->getChave() == chave)
    {
      excluido = tupla;
      proximo = tupla->getProx();

      this->tabela[index_bucket] = proximo;
      delete excluido;

      this->tamanho--;
      return;
    }

    // Checa se a chave está nos elementos seguintes
    while (tupla->getProx() != NULL)
    {
      if (tupla->getProx()->getChave() == chave)
      {
        excluido = tupla;
        proximo = tupla->getProx()->getProx();

        tupla->setProx(proximo);
        delete excluido;

        this->tamanho--;
        return;
      }

      tupla = tupla->getProx();
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