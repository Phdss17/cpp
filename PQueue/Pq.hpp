#ifndef PQ_HPP
#define PQ_HPP
#include <stdexcept>
#include <vector>

template <typename T, typename Comparator>
class Pq {
private:
    int m_heapSize;         // numero de elementos no heap
    std::vector<T> m_vec;   // heap
    Comparator compara;

public:
    // Construtor
    Pq();

    // Contrutor cria um heap a partir de um vector previo
    Pq(const std::vector<T>& v);

    // retorna o número de elementos na fila
    int size() const;

    // retorna true se e somente se a fila esta vazia
    bool empty() const;

    // retorna o valor do elemento prioritario
    const T& top() const;

    // remove o elemento prioritario
    void pop();

    // insere um elemento na fila
    void push(const T& element);

    //aumenta valor de uma chave e a reajusta
    void increaseKey(int i, int newKey);

    //diminui valor de uma chave e a reajusta
    void decreaseKey(int i, int newKey);

private:
    // recebe como entrada um indice e faz 
    // o elemento m_vec[index] descer no heap
    void fixDown(int index);

    // recebe como entrada um indice e faz
    // o elemento m_vec[index] subir no heap
    void fixUp(int index);

    // rearranja os elementos do vector m_vec de modo
    // a obter um heap
    void buildAbsoluteHeap(); 
};

// ----------------------------------------------------------------

// construtor default
template <typename T, typename Comparator>
Pq<T, Comparator>::Pq() {
    m_heapSize = 0;
    m_vec.push_back(T());
}

// Contrutor cria um heap a partir de um vector prévio
template <typename T, typename Comparator>
Pq<T, Comparator>::Pq(const std::vector<T>& v) : Pq(){
    // copia os elementos de v para m_vec
    for(const T& element : v) {
        m_vec.push_back(element);
    }
    // ajusta m_heapSize e rearranja os elementos de m_vec
    // de modo a torna-lo um heap!
    m_heapSize = v.size();
    buildAbsoluteHeap();
}

// retorna o número de elementos na fila
template <typename T, typename Comparator>
int Pq<T, Comparator>::size() const {
    return m_heapSize;
}

// retorna true se e somente se a fila esta vazia
template <typename T, typename Comparator>
bool Pq<T, Comparator>::empty() const {
    return m_heapSize == 0;
}

// retorna o valor do elemento prioritario
template <typename T, typename Comparator>
const T& Pq<T, Comparator>::top() const {
    if(empty()) {
        throw std::underflow_error("empty queue");
    }
    return m_vec[1];
}

// insere um elemento na fila
template <typename T, typename Comparator>
void Pq<T, Comparator>::push(const T& element) {
    m_vec.push_back(element);
    m_heapSize++;
    fixUp(m_heapSize);
}

// remove o elemento prioritario
template <typename T, typename Comparator>
void Pq<T, Comparator>::pop() {
    if(empty()) {
        throw std::underflow_error("empty queue");
    }
    m_vec[1] = m_vec[m_heapSize];
    m_heapSize--;
    fixDown(1);
}

//aumenta valor de uma chave e a reajusta
template <typename T, typename Comparator>
void Pq<T, Comparator>::increaseKey(int i, int newKey) {
    if(!compara(newKey, m_vec[i])){
        throw std::underflow_error("Invalid key");
    }
    m_vec[i] = newKey;
    fixUp(i);
}

//diminui valor de uma chave e a reajusta
template <typename T, typename Comparator>
void Pq<T, Comparator>::decreaseKey(int i, int newKey) {
    if(compara(newKey, m_vec[i])){
        throw std::underflow_error("Invalid key");
    }
    m_vec[i] = newKey;
    fixDown(i);
}

// recebe como entrada um indice e faz
// o elemento m_vec[index] subir no heap
template <typename T, typename Comparator>
void Pq<T, Comparator>::fixUp(int index) {
    while(index != 1 && compara(m_vec[index/2],m_vec[index])) {        
       Kaux = m_vec[index];
        m_vec[index] = m_vec[index/2];
        m_vec[index/2] = aux;
        index = index/2;
    }
}

// recebe como entrada um indice e faz 
// o elemento m_vec[index] descer no heap
template <typename T, typename Comparator>
void Pq<T, Comparator>::fixDown(int index) {
    while(2*index <= m_heapSize) {
        int ileft = 2*index;           
        int iright = ileft+1;
        int ipriority = index;
        if(compara(m_vec[index], m_vec[ileft]))
            ipriority = ileft;
        if(iright <= m_heapSize && compara(m_vec[ipriority], m_vec[iright]))
            ipriority = iright;
        if(ipriority != index) {
           Kaux = m_vec[index];
            m_vec[index] = m_vec[ipriority];
            m_vec[ipriority] = aux;
            index = ipriority;
        } 
        else break;
    }
}

// rearranja os elementos do vector m_vec de modo a obter um heap absoluto
template <typename T, typename Comparator>
void Pq<T, Comparator>::buildAbsoluteHeap() {
    for(int i = m_vec.size()/2; i >= 1; i--) {
        fixDown(i);
    }
}


#endif