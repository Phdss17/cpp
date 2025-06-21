/**
 * @file AvlTree.hpp
 * @author Paulo Henrique (phenriquedss@alu.ufc.br)
 * @brief Uma Árvore AVL
 * Estrutura de dados avancada - 2025.1
 * @version 0.1
 * @date 2025-04-06
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef AVLTREE_HPP
#define AVLTREE_HPP
#include <iostream>
#include <queue>
#include <utility>


/**
 * @brief Classe que implementa uma Árvore AVL
 * 
 * Os tipos Key e Value, caso sejam classes, devem ter um construtor default. 
 * Além disso, o tipo Key deve sobrecarregar o operador de igualdade (==) e 
 * de comparação (<) (>).
 * 
 * @tparam Key key type
 * @tparam Value value type
 */
template <typename Key, typename Value>
class AvlTree{
public:
    /**
     * @brief Construtor: Cria uma árvore AVL vazia.
     *  
     */
    AvlTree(){
        _root = nullptr;
    }
    
    /**
     * @brief Destrutor: Remove cada elemento da árvore e então a destrói.
     *  
     */
    ~AvlTree(){
        _root = _clear(_root);
    }
    
    /**
     * @brief insert privado que caminha pela arvore fazendo comparações com a chave e 
     * caso ache, incrementa o valor da chave, se não, cria um novo par e adiciona na arvore
     * 
     * @param k := chave
     * @param v := valor 
     */
    void insert(Key k, Value v){
        _root = _insert(_root, k, v);
    }

    /**
     * @brief Procura por uma chave e retorna o valor associado.
     * 
     * @param k := chave
     * @return v := Valor associado a chave
     */
    Value getKey(Key k){
        return _get(_root, k);
    }

    /**
     * @brief Limpa todos os elementos da árvore.
     * 
     */
    void clear(){
        _root = _clear(_root);
    }

    /**
     * @brief Recebe como entrada uma chave k e caso exista,
     *  remove o elemento com essa chave da árvore.
     * 
     * @param k := chave a ser removida
     */
    void erase(Key k){
        _root = _remove(_root, k);
    }

    /**
     * @brief Recebe como entrada uma chave k e retorna true
     * se e somente se q chave k estiver presente na árvore. 
     * 
     * @param k := chave a ser pesquisada
     */
    bool contains(Key k) const{
        return _contains(_root, k);
    }

    /**
     * @brief Retorna true se a árvore estiver vazia.
     * 
     */
    bool empty() const{
        return _root == nullptr;
    }

    /**
     * @brief Retorna o tamanho da árvore. 
     * 
     */
    size_t size() const{
        return _size(_root);
    }

    /**
     * @brief Imprime a árvore usando pré-ordem.
     * 
     */
    void show() const{
        _show(_root);
        std::cout << std::endl;
    }

private:
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
        Node *left;
        Node *right;
        int height;

        Node(std::pair<Key, Value> pair, Node *Esquerda = nullptr, Node *Direita = nullptr, int Altura = 1){
            this->pair = pair;
            this->left = Esquerda;
            this->right = Direita;
            this->height = Altura;
        }
    };
    //Nó raiz e contador do tipo size_t para suportar tamanhos imensos.
    Node *_root;
    size_t cont;

    /**
     * @brief insert privado que caminha recursivamente pela arvore fazendo comparações com a chave e 
     * caso ache, incrementa o valor da chave, se não, cria um novo par e adiciona na arvore
     * 
     * @param node := nó a partir do qual será iniciada a procura.
     * @param k := chave
     * @param v := valor 
     */
    Node* _insert(Node *node, Key k, Value v){
        if (node == nullptr){
            return new Node(std::make_pair(k, v), nullptr, nullptr);
        }

        if (node->pair.first == k){
            node->pair.second++;
            return node;
        }

        if (k < node->pair.first){
            node->left = _insert(node->left, k, v);
        }else if (k > node->pair.first){
            node->right = _insert(node->right, k, v);
        }
        node = _fixupNode(node, k);
        return node;
    }

    /**
     * @brief Procura recursivamente por uma chave e retorna o valor associado.
     * 
     * @param node := nó a partir do qual será iniciada a procura.
     * @param k := chave.
     * @return v := Valor associado a chave.
     */
    Value _get(Node* node, Key k) {
        if (node == nullptr)
            throw std::runtime_error("Key not found");

        if (node->pair.first == k){
            return node->pair;
        }else if (node->pair.first > k){
            return _get(node->left, k);
        }else{
            return _get(node->right, k);
        }
    }

    /**
     * @brief Limpa todos os elementos da árvore recursivamente.
     * 
     * @param node := nó que será removido junto de seus filhos.
     */
    Node* _clear(Node *node){
        if (node != nullptr){
            node->left = _clear(node->left);
            node->right = _clear(node->right);
            delete node;
        }
        return nullptr;
    }

    /**
     * @brief Recebe como entrada um nó e uma chave k.
     *  Se chegar em nullptr, retorna nullptr, caso contrário, 
     *  verifica se k é menor ou maior e caminha nessa direção na árvore recursivamente,
     *  caso não, verifica se o nó a direita é nullptr, se for guarda o nó a esquerda, deleta 
     *  o nó atual retorna o nó guardado, se não o nó a direita recebe remove_sucessor mandando o node
     *  e o nó a direita, então o node recebe fixUp deletion node e é retornado. 
     * 
     * @param node := nó que a partir do qual será procurado a chave.
     * @param k := chave a ser removida.
     */
    Node* _remove(Node *node, Key key){
        if (node == nullptr)
            return nullptr;

        if (key < node->pair.first)
            node->left = _remove(node->left, key);
        else if (key > node->pair.first)
            node->right = _remove(node->right, key);
        else if (node->right == nullptr){
            Node *child = node->left;
            delete node;
            return child;
        }else{
            node->right = remove_successor(node, node->right);
            node = fixup_deletion(node);
            return node;
        }

        node = fixup_deletion(node);
        return node;
    }

    /**
     * @brief Recebe um nó root e um nó node.
     *  Se o nó a esquerda do node for diferente de nullptr, chama recursivamente a função,
     *  atribui ao node->left e chama fixUp deletion e retorna o node.
     *  Se não atribui a chave do node a chave da raiz, guarda o node->right em um aux, 
     *  então deleta o node e retorna o aux. 
     * 
     * @param _root := nó o qual vai ser removido.
     * @param node := nó de substituição.
     */
    Node* remove_successor( Node * root , Node * node ) {
        if( node -> left != nullptr ){
            node -> left = remove_successor( root , node -> left );
            node = fixup_deletion(node);
            return node;
        }else{
            root -> pair.first = node -> pair.first;
            Node * aux = node -> right;
            delete node;
            return aux;
        }

        node = fixup_deletion(node);
        return node ;
    }

    /**
     * @brief Recebe um nó e rebalanceia o nó caso esteja desbalanceado.
     *  Redefine a altura do nó com base nos filhos.
     *  Inicializa a variavél bal usando a função balance, então verifica os casos de rebalanceamento 
     *  e faz as rotações nécessarias, então retorna o node. 
     * 
     * @param node := nó possivelmente desbalanceado.
     */
    Node *fixup_deletion(Node *node){
        node->height = 1 + std::max(_height(node->left), _height(node->right));
        int bal = _balance(node);

        if (bal > 1 && _balance(node->right) >= 0){
            return left_rotation(node);
        }else if (bal > 1 && _balance(node->right) < 0){
            node->right = right_rotation(node->right);
            return left_rotation(node);
        }else if (bal < -1 && _balance(node->left) <= 0){
            return right_rotation(node);
        }else if (bal < -1 && _balance(node->left) > 0){
            node->left = left_rotation(node->left);
            return right_rotation(node);
        }

        return node;
    }

    /**
     * @brief Recebe um nó e uma chave k, se a recursão cheagar em null, retorna false
     *  se a chave do nó atual da recursão for igual a chave procurada, retorna true,
     *  caso contrário caminha pela árvore recursivamente na direção indicada pela comparação com a chave do nó atual. 
     * 
     * @param node := nó "base" da busca.
     * @param k := chave buscada.
     */
    bool _contains(Node *node, Key k) const{
        if (node == nullptr)
            return false;

        if (node->pair.first == k){
            return true;
        }else if (node->pair.first > k){
            return _contains(node->left, k);
        }else{
            return _contains(node->right, k);
        }
    }

    /**
     * @brief Recebe um nó e retorna sua altura com base nos seus filhos.
     *  verifica se o nó é nullptr, se for retorna 0, caso não,
     *  retorna o campo height do nó. 
     * 
     * @param node := nó que se deseja saber a altura.
     **/
    size_t _height(Node *node) const{
        if (node == nullptr){
            return 0;
        }else{
            return node->height;
        }
    }

    /**
     * @brief Recebe um nó e retorna a quantidade de nós a partir dele.
     *  verifica se o nó é nullptr, se for retorna 0, caso não,
     *  retorna 1 + a recursão da função para os nós filhos. 
     * 
     * @param node := nó a partir do qual se deseja saber a quantidade de nós.
     **/
    size_t _size(Node *node) const{
        if (node == nullptr)
            return 0;

        return _size(node->left) + _size(node->right) + 1;
    }

    /**
     * @brief Recebe um nó e retorna o nó resultado da rotação a direita.
     *  guarda o filho esquerdo do nó em um aux, guarda o filho direito no esquerdo e o nó no seu filho direito,
     *  então recalcula as alturas e retorna o aux. 
     * 
     * @param node := nó pivô da rotação.
     **/
    Node *right_rotation(Node *node){
        Node *aux = node->left;
        node->left = aux->right;
        aux->right = node;

        node->height = 1 + std::max(_height(node->left), _height(node->right));
        aux->height = 1 + std::max(_height(aux->left), _height(aux->right));
        return aux;
    }

    /**
     * @brief Recebe um nó e retorna o nó resultado da rotação a esquerda.
     *  guarda o filho direito do nó em um aux, guarda o filho esquerdo no direito e o nó no seu filho esquerdo,
     *  então recalcula as alturas e retorna o aux. 
     * 
     * @param node := nó pivô da rotação.
     **/
    Node *left_rotation(Node *node){
        Node *aux = node->right;
        node->right = aux->left;
        aux->left = node;

        node->height = 1 + std::max(_height(node->left), _height(node->right));
        aux->height = 1 + std::max(_height(aux->left), _height(aux->right));
        return aux;
    }

    /**
     * @brief Recebe um nó e retorna  seu balanço com base na altura dos filhos.
     * 
     * @param node := nó o qual se deseja saber o balanço.
     **/
    int _balance(Node *node) const{
        return _height(node->right) - _height(node->left);
    }

     /**
     * @brief Recebe um nó e uma chave k e retorna um nó balanceado.
     *  Recebe o balanço do nó em uma variável e faz as rotações nécessarias com base 
     *  no valor do balanço e na comparação das chaves, ao final atualiza o campo altura do nó e o retorna.
     * 
     * @param node := nó o qual se deseja rebalancear.
     * @param k := chave do nó o qual se deseja rebalancear.
     **/
    Node *_fixupNode(Node *node, Key k){
        int bal = _balance(node);

        // Caso 1(a)
        if (bal == -2 && k < node->left->pair.first){
            return right_rotation(node);
        }
        // Caso 1(b)
        if (bal == -2 && k > node->left->pair.first){
            node->left = left_rotation(node->left);
            return right_rotation(node);
        }
        // Caso 2(a)
        if (bal == 2 && k > node->right->pair.first){
            return left_rotation(node);
        }
        // Caso 2(b)
        if (bal == 2 && k < node->right->pair.first){
            node->right = right_rotation(node->right);
            return left_rotation(node);
        }

        // Caso node balanceado
        node->height = std::max(_height(node->left), _height(node->right)) + 1;
        return node;
    }

    /**
     * @brief Recebe um nó e a partir dele imprime os campos chave e valor do nó.
     * 
     * @param node := nó a partir do qual se deseja mostrar na árvore.
     **/
    void _show(Node *node) const{
        if (node == nullptr)
            return;

        _show(node->left);
        std::cout << node->pair.first << "|" << node->pair.second << std::endl;
        _show(node->right);
    }
};

#endif //END of AVLTREE_HPP