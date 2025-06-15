#ifndef CHT_HPP
#define CHT_HPP

#include <iostream>
#include <cmath>
#include <string>
#include <list>
#include <vector>
#include <utility>  
#include <functional>

/**
 * @brief Classe que implementa uma tabela hash com tratamento de
 * colisao por encadeamento exterior (chained hash table).
 * 
 * @tparam Key key type
 * @tparam Value value type
 * @tparam Hash hash function type
 */
template <typename Key, typename Value, typename Hash = std::hash<Key>>
class Cht {
private:
    // quantidade de pares (chave,valor)
    size_t m_number_of_elements;

    // tamanho atual da tabela
    size_t m_table_size;

    // O maior valor que o fator de carga pode ter. 
    // Seja load_factor = m_number_of_elements/m_table_size.
    // Temos que load_factor <= m_max_load_factor.
    // Quando load_factor ultrapassa o valor de m_max_load_factor, 
    // eh preciso executar a operacao de rehashing.                   
    float m_max_load_factor;

    // tabela                               
    std::vector<std::list<std::pair<Key,Value>>> m_table;

    // referencia para a funcao de codificacao
    Hash m_hashing;


    /**
     * @brief Retorna o menor numero primo que eh maior que ou igual
     * a x e maior que 2.
     * 
     * @param x := um numero nao negativo
     * @return size_t := um numero primo
     */
    size_t get_next_prime(size_t x) {
        if(x <= 2) return 3;
        x = (x % 2 == 0) ? x + 1 : x;
        bool not_prime = true;
        while(not_prime) {
            not_prime = false;
            for(int i = 3; i <= sqrt(x); i+=2) {
                if(x % i == 0) {
                    not_prime = true;
                    break;
                }
            }
            x += 2;
        }
        return x - 2;
    }

    /**
     * @brief Retorna um inteiro no intervalo [0 ... m_table_size-1].
     * Esta funcao recebe uma chave k e faz o seguinte:
     * (1) computa o codigo hash h(k) usando a 
     *     funcao no atributo privado m_hashing
     * (2) computa um indice no intervalo [0 ... m_table_size-1] 
     *     aplicando o metodo da divisao: h(k) % m_table_size
     * 
     * @param k := um valor de chave do tipo Key
     * @return size_t := um inteiro no intervalo [0 ... m_table_size-1]
     */
    size_t hash_code(const Key& k) const{
        return m_hashing(k) % m_table_size;
    }


public:
    /**
     * @brief Construtor: cria uma tabela hash com um numero primo de slots.
     * 
     * @param tableSize := o numero de slots da tabela. 
     */
    Cht(size_t tableSize = 19, float load_factor = 1.0){
        m_number_of_elements = 0;
        m_table_size = get_next_prime(tableSize);
        m_table.resize(m_table_size);
        if(load_factor <= 0){
            m_max_load_factor = 1.0;
        }else{
            m_max_load_factor = load_factor;
        }
    }


    /**
     * @brief Retorna o numero de elementos na tabela hash
     */
    size_t size() const{
        return m_number_of_elements;
    }


    /**
     * @brief Retorna um booleano indicando se a tabela esta vazia
     */
    bool empty() const{
        return m_number_of_elements == 0;
    }


    /**
     * @brief Retorna o numero de slots na HashTable (o tamanho da tabela).
     * Um slot eh um campo na tabela hash para o qual 
     * os elementos são atribuidos com base no valor de hashing de sua chave.
     * O numero de slots influencia diretamente no fator de carga da 
     * tabela hash (e, portanto, a probabilidade de colisao).
     * 
     * @return size_t := o numero de slots
     */
    size_t bucket_count() const{
        return m_table_size;
    }


    /**
     * @brief Retorna o numero de elementos armazenados no slot n da tabela.
     * O valor de n deve ser tal que 0 <= n <= m_table_size - 1
     * 
     * @param n := numero do slot
     * @return size_t := numero de elementos no slot n
     */
    size_t bucket_size(size_t n) const{
        if(n < 0 || n >= m_table_size){
            throw std::out_of_range("invalid index");
        }
        return m_table[n].size();
    }


    /**
     * @brief Retorna o numero do slot onde a chave k estaria localizada.
     * 
     * @param k := chave  
     * @return size_t := numero do slot
     */
    size_t bucket(const Key& k) const{
        return hash_code(k);
    }

    /**
     * @brief retorna o valor do fator de carga atual
     */
    float load_factor() const{
        return m_number_of_elements/m_table_size;
    }


    /**
     * @brief retorna o maior valor que o fator de carga pode ter
     */
    float max_load_factor() const{
        return m_max_load_factor;
    }


    /**
     * @brief Todos os pares de (chave,valor) da tabela hash sao deletados: 
     * os destrutores das listas encadeadas sao chamados e eles sao removidos da estrutura de dados, 
     * deixando-o com zero pares na tabela (size() == 0).
     */
    void clear(){
        for(int i = 0; i < m_table_size; i++){
            m_table[i].clear;
        }
    }


    /**
     * @brief Destroy the Hash Table object
     */
    ~Cht() = default;


    /**
     * @brief Insere um novo elemento na tabela hash.
     * Se m_number_of_elements / m_table_size > m_max_load_factor entao a funcao
     * invoca a funcao rehash() passando o dobro do tamanho atual da tabela.
     * O elemento eh inserido somente se a chave dele ja nao estiver presente
     * na tabela (numa tabela hash, as chaves sao unicas).
     * Caso a insercao seja feita, isso incrementa o numero de elementos da tabela em 1 unidade.
     * Retorna true se e somente se a insercao for feita.
     * 
     * @param k := chave
     * @param v := valor 
     */
    bool add(const Key& k, const Value& v){
        if(contains(k)){
            return false;
        }
        if(m_number_of_elements / m_table_size > m_max_load_factor){
            rehash(2*m_table_size);
        } 
        size_t slot = bucket(k);
        m_table[slot].push_back(std::pair{k, v});
        m_number_of_elements++;
        return true;
    }


    /**
     * @brief Recebe como entrada uma chave k e retorna true 
     * se e somente se a chave k estiver presente na tabela hash.
     * 
     * @param k := chave a ser pesquisada
     */
    bool contains(const Key& k){
        size_t slot = bucket(k);
        for(const auto& pair  : m_table[slot]){
            if(pair.first == k)
                return true;
        }
        return false;
    }


    /**
     * @brief Retorna uma referencia para o valor associado a chave k.
     * Se k nao estiver na tabela, a funcao lanca uma out_of_range exception.
     * 
     * @param k := chave
     * @return V& := valor associado a chave
     */
    Value& at(const Key& k){
        if(!contains(k)){
            throw std::out_of_range("invalid index");
        }
        for(const auto& pair  : m_table[bucket(k)]){
            if(pair.first == k)
                return pair.second;
        }
    }


    /**
     * @brief Recebe um inteiro nao negativo m e faz com que o tamanho
     * da tabela seja um numero primo maior ou igual a m.
     * Se m for maior que o tamanho atual da tabela, um rehashing eh realizado.
     * Se m for menor que o tamanho atual da tabela, a funcao nao tem nenhum efeito.
     * Um rehashing eh uma operacao de reconstrucao da tabela:
     * Todos os elementos no container sao rearranjados de acordo 
     * com o seu valor de hashing dentro na nova tabela.
     * Isto pode alterar a ordem de iteracao dos elementos dentro do container.
     * Operacoes de rehashing sao realizadas automaticamente pelo container 
     * sempre que load_factor() ultrapassa o m_max_load_factor.
     * 
     * @param m := o novo tamanho da tabela hash
     */
    void rehash(size_t m){
        m_table_size = get_next_prime(m);
        
    }


    /**
     * @brief Remove da tabela hash o elemento com chave k se ele existir.
     * Ao remover o elemento, o numero de elementos eh decrementado em 1 unidade.
     * Retorna um booleano indicando se a remocao foi realizada.
     * 
     * @param k := chave a ser removida
     */
    bool remove(const Key& k){
        if(!contains(k)){
            return false;
        }
        for(size_t i; i < m_table[bucket(k)].size(); i++){
            auto pair = m_table[bucket(k)].get(i);
            if(pair.first == k){
                m_table[bucket(k)].remove(i);
                m_number_of_elements--;
                return true;
            }
        }
    }


    /**
     * @brief Redimensiona a tabela hash de modo que ela tenha 
     * o tamanho mais apropriado a fim de conter pelo menos n elementos.
     * Se n > m_table_size * m_max_load_factor, entao a operacao 
     * de rehash() eh executada sendo passado para ela o tamanho apropriado da nova tabela.
     * Se n <= m_table_size * m_max_load_factor, entao 
     * a funcao nao tem efeito, nao faz nada.   
     * 
     * @param n := numero de elementos 
     */
    void reserve(size_t n){
        if(n > m_table_size * m_max_load_factor){
            rehash(2*m_table_size); 
        }
    }


    /**
     * @brief Recebe um float lf e muda o valor 
     * do atributo m_max_load_factor para esse valor.
     * Uma restricao eh que: 0 < m_max_load_factor.
     * Se lf nao estiver dentro desse intervalo entao uma 
     * out_of_range exception eh lancada
     * Ao mudar o fator de carga, eh possivel que a tabela hash tenha 
     * que ser redimensionada. Para isso, invocamos 
     * a funcao reserve(m_number_of_elements).
     * 
     * @param lf := novo fator de carga
     */
    void set_max_load_factor(float lf){
        if(lf <= 0){
            throw std::out_of_range("invalid index");
        }

        m_max_load_factor = lf;
        reserve(m_number_of_elements);
    }


    /**
     * @brief Sobrecarga do operador de indexacao.
     * Se k corresponder a chave de um elemento na tabela, a funcao
     * retorna uma referencia ao seu valor mapeado. Caso contrario, 
     * se k nao corresponder a chave de nenhum elemento na tabela, 
     * a funcao insere um novo elemento com essa chave e retorna um
     * referencia ao seu valor mapeado. Observe que isso sempre aumenta 
     * o tamanho da tabela em um, mesmo se nenhum valor mapeado for atribuido 
     * ao elemento (o elemento eh construido usando seu construtor padrao).
     * 
     * @param k := chave
     * @return Value& := valor associado a chave
     */
    Value& operator[](const Key& k){

    }


    /**
     * @brief Versao const da sobrecarga do operador de indexacao.
     * Se k corresponder a chave de um elemento na tabela, a funcao
     * retorna uma referencia ao seu valor mapeado. Caso contrario, 
     * se k nao corresponder a chave de nenhum elemento na tabela, 
     * a funcao lanca uma out_of_range exception.
     * 
     * @param k := chave
     * @return Value& := valor associado a chave
     */
    const Value& operator[](const Key& k) const{

    }

};


#endif // END of CHAINED_HASHTABLE_HPP