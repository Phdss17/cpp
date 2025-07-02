/**
 * @file OpenAdress_HashTable.hpp
 * @author Paulo Henrique (phenriquedss@alu.ufc.br)
 * @brief Uma tabela hash com tratamento de colisao por endereçamento aberto
 * Estrutura de dados avancada - 2025.1
 * @version 0.1
 * @date 2025-06-26
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef OPENADRESS_HASHTABLE_HPP
#define OPENADRESS_HASHTABLE_HPP

#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <utility>
#include <functional>

/**
 * @brief Classe que implementa uma tabela hash com tratamento de
 * colisao por endereçamento aberto (Open Adressing hash table).
 * 
 * Os tipos Key e Value, caso sejam classes, devem ter um construtor default. 
 * Além disso, o tipo Key deve sobrecarregar o operador de igualdade (==).
 * Por fim, o tipo Key deve também ter uma std::hash<Key> especificada no namespace std, ou 
 * caso contrario você deve fornecer uma.
 * 
 * @tparam Key key type
 * @tparam Value value type
 * @tparam Hash hash function type
 */
template <typename Key, typename Value = int, typename Hash = std::hash<Key>>
class OpenAdress_HashTable{
    private:

    /**
    * @brief Enum usado para a verificação de status.
    * 
    */
    enum class Status {
    EMPTY,
    ACTIVE,
    DELETED
    };

    /**
    * @brief Struct Node genérico.
    * 
    * Os tipos Key e Value, caso sejam classes, devem ter um construtor default. 
    * Além disso, o tipo Key deve sobrecarregar o operador de igualdade (==) e 
    * de comparação (<) (>).
    * 
    * @tparam Key key type
    * @tparam Value value type
    */
    struct Node{
        std::pair<Key, Value> pair;
        Status status;

        Node(std::pair<Key, Value> pair, Status status = Status::EMPTY){
            this->pair = pair;
            this->status = status;
        }
    };

    // quantidade de pares (chave,valor)
    size_t m_number_of_elements;

    // tamanho atual da tabela
    size_t m_table_size;

    mutable size_t count;

    // O maior valor que o fator de carga pode ter. 
    // Seja load_factor = m_number_of_elements/m_table_size.
    // Temos que load_factor <= m_max_load_factor.
    // Quando load_factor ultrapassa o valor de m_max_load_factor, 
    // eh preciso executar a operacao de rehashing.                   
    float m_max_load_factor;

    // tabela                               
    std::vector<Node*> m_table;

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
     * @brief funcao de hash auxiliar para calculo de posicao.
     * 
     * @param key := chave o qual o hash sera retornado.
     * @return size_t := hash da chave.
     */
    size_t hash1(const Key& key) const {
        return m_hashing(key) % m_table_size;
    }

    /**
     * @brief funcao de hash auxiliar para calculo de "salto".
     * 
     * @param key := chave o qual o "salto" sera retornado.
     * @return size_t := tamanho do salto da chave.
     */
    size_t hash2(const Key& key) const {
        return 1 + (m_hashing(key) % (m_table_size-1));
    }

    /**
     * @brief funcao de hash principal que calcula a posição considerando o salto.
     * 
     * @param key := chave a qual a posicao sera retornada.
     * @return size_t := posicao da chave.
     */
    size_t hash(const Key& key, const size_t& i)const{
        return (hash1(key) + i * hash2(key)) % m_table_size;
    }

    /**
     * @brief Retorna um inteiro no intervalo [0 ... m_table_size-1].
     * Esta funcao recebe uma chave k e um size_t e faz o seguinte:
     * (1) computa o codigo hash h(k) usando a 
     *     funcao no atributo privado m_hashing
     * (2) computa um indice no intervalo [0 ... m_table_size-1] 
     *     aplicando o metodo da divisao: h(k) % m_table_size
     * 
     * @param k := um valor de chave do tipo Key
     * @param i := valor modificador do hash.
     * @return size_t := um inteiro no intervalo [0 ... m_table_size-1]
     */
    size_t hash_code(const Key& key, const size_t& i)const{
        return hash(key, i);
    } 

    /**
     * @brief funcao auxililar de busca de chave, recebe uma chave e a procura
     * se for encontrada é retornado o index, caso nao -1.
     * 
     * @param key := chave a qual o index sera procurado.
     * @return size_t := index da chave;
     */    
    size_t aux_hashSearch(const Key& key){
        size_t i = 0;
        size_t j = 0;
        do{
            j = hash_code(key, i);
            count++;
            if(m_table[j]->status == Status::ACTIVE && m_table[j]->pair.first == key){
                return j;
            }
            i++;
        }while(m_table[j]->status != Status::EMPTY && i < m_table_size);
        return -1;
    }

    public:

    /**
     * @brief Construtor: cria uma tabela hash com um numero primo de slots.
     * 
     * @param tableSize := o numero de slots da tabela. 
     */
    OpenAdress_HashTable(size_t tableSize = 19, float load_factor = 1.0) {
        count = 0;
        m_number_of_elements = 0;
        m_table_size = get_next_prime(tableSize);
        m_table.resize(m_table_size);
        if(load_factor <= 0) {
            m_max_load_factor = 1.0;
        } else {
            m_max_load_factor = load_factor;
        }
        for(size_t i = 0; i < m_table_size; i++){
            m_table[i] = (new Node({Key(), Value()}));
        }
    }


    /**
     * @brief Retorna o numero de elementos na tabela hash.
     */
    size_t size() const {
        return m_number_of_elements;
    }


    /**
     * @brief Retorna um booleano indicando se a tabela esta vazia.
     */
    bool empty() const {
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
    size_t bucket_count() const {
        return m_table_size;
    }

    /**
     * @brief retorna o valor do fator de carga atual.
     */
    float load_factor() const {
        return static_cast<float>(m_number_of_elements) / m_table_size;
    }

    /**
     * @brief retorna o maior valor que o fator de carga pode ter.
     */
    float max_load_factor() const {
        return m_max_load_factor;
    }


    /**
     * @brief Todos os pares de (chave,valor) da tabela hash sao deletados: 
     * Todos os elementos recebem Status = EMPTY e a tabela recebe size = 0.
     */
    void clear() {
        count = 0;
        for(size_t i = 0; i < m_table_size; i++){
            m_table[i]->status = Status::EMPTY;
        }
        m_number_of_elements = 0;
    }


    /**
     * @brief Destroy the Hash Table object
     */
    ~OpenAdress_HashTable(){
        for(Node* node : m_table){
            delete node;
        }
    }


    /**
     * @brief Insere um novo elemento na tabela hash.
     * Se m_number_of_elements / m_table_size > m_max_load_factor entao a funcao
     * invoca a funcao rehash() passando o dobro do tamanho atual da tabela.
     * O elemento eh inserido somente se a chave dele ja nao estiver presente
     * na tabela (numa tabela hash, as chaves sao unicas).
     * Caso a insercao seja feita, isso incrementa o numero de elementos 
     * da tabela em 1 unidade.
     * Retorna true se e somente se a insercao for feita.
     * 
     * @param k := chave
     * @param v := valor 
     */
    bool add(const Key& k, const Value& v) {
        if(load_factor() >= m_max_load_factor) {
            rehash(2 * m_table_size);
        }

        size_t m = aux_hashSearch(k);
        if(m != static_cast<size_t>(-1)){
            m_table[m]->pair.second = v;
            return true;
        }
        size_t i = 0;
        size_t j = 0;
        do{
            j = hash_code(k, i);
            if(m_table[j]->status != Status::ACTIVE){
                m_table[j]->pair = {k, v};
                m_table[j]->status = Status::ACTIVE;
                m_number_of_elements++;
                return true;
            }
            i++; 
        }while(i < m_table_size);
        return false;
    }
    
    /**
     * @brief Recebe como entrada uma chave k e retorna true 
     * se e somente se a chave k estiver presente na tabela hash.
     * 
     * @param k := chave a ser pesquisada
     */
    bool contains(const Key& k) {
        return aux_hashSearch(k) != -1;
    }
    
    /**
     * @brief recebe uma chave k e procura por ela na tabela, se encontra
     * retorna seu valor, caso não, lança uma exececao.
     * 
     * @param key := chave a qual o valor sera procurado.
     * @return size_t := valor da chave;
     */  
    Value& hashSearch(const Key& k){
        size_t j = aux_hashSearch(k);

        if(j != -1){
            return m_table[j]->pair.second;
        }else{
            throw std::out_of_range("key is not in the table"); 
        }
    }

    const Value& hashSearch(const Key& k) const {
        size_t j = aux_hashSearch(k);

        if(j != -1){
            return m_table[j]->pair.second;
        }else{
            throw std::out_of_range("key is not in the table"); 
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
    void rehash(size_t m) {
        size_t new_table_size = get_next_prime(m);
        if(new_table_size > m_table_size) {
            std::vector<Node*> old_vec;
            old_vec = m_table; // copia as chaves para uma nova tabela
            m_table.resize(new_table_size); // tabela redimensionada com novo primo
            m_number_of_elements = 0;
            m_table_size = new_table_size;
            for(size_t i = 0; i < m_table_size; i++){
                m_table[i] = new Node({Key(), Value()});
            }       
            for(Node* node : old_vec){
                if(node->status == Status::ACTIVE){
                    add(node->pair.first, node->pair.second);
                }
                delete node;
            }
        }
    }

    /**
     * @brief Remove da tabela hash o elemento com chave k se ele existir.
     * Ao remover o elemento, o numero de elementos eh decrementado em 1 unidade.
     * Retorna um booleano indicando se a remocao foi realizada.
     * 
     * @param k := chave a ser removida
     */
    bool remove(const Key& k) {
        size_t slot = aux_hashSearch(k); // calcula o slot em que estaria a chave
        if(slot != -1){    
            m_table[slot]->status = Status::DELETED;
            m_number_of_elements--;
            return true;
        }
        return false; // se não encontrar, retorna falso
    }


    /**
     * @brief Redimensiona a tabela hash de modo que ela tenha 
     * o tamanho mais apropriado a fim de conter pelo menos n elementos.
     * Se n > m_table_size * m_max_load_factor, entao a operacao 
     * de rehash() eh executada sendo passado para ela o 
     * tamanho apropriado da nova tabela.
     * Se n <= m_table_size * m_max_load_factor, entao 
     * a funcao nao tem efeito, nao faz nada.   
     * 
     * @param n := numero de elementos 
     */
    void reserve(size_t n) {
        if(n > m_table_size * m_max_load_factor) {
            rehash( n / m_max_load_factor );
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
    void set_max_load_factor(float lf) {
        if(lf <= 0) {
            throw std::out_of_range("invalid load factor");
        }
        // se lf > 0, entao ok, ajusta o max_load_factor e chama reserve()
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
    Value& operator[](const Key& k) {
        if(load_factor() >= m_max_load_factor) {
            rehash(2 * m_table_size);
        }
        size_t i = aux_hashSearch(k);
        if(i!= -1){
            return m_table[i]->pair.second;
        }

        add(k, Value());
        i = aux_hashSearch(k);
        return m_table[i]->pair.second;
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
    const Value& operator[](const Key& k) const {
        return hashSearch(k);
    }

    void show(){
        for(auto Node : m_table){
            if(Node->status == Status::ACTIVE){
                std::cout << Node->pair.first << "|" << Node->pair.second << " ";
            }
        }
        std::cout << std::endl;
    }

    /**
     * @brief Retorna a quantidade de comparacoes de chave feitas na estrutura.
     * 
     * @return size_t := quantidade de comparacoes.
     **/    
    size_t getComparisons(){
        return count;
    }
};
 
#endif