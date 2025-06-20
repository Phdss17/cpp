// avl generica
#ifndef AVLTREE_HPP
#define AVLTREE_HPP
#include <iostream>
#include <queue>
#include <utility>

template <typename Key, typename Value>
class AvlTree{
public:
    AvlTree(){
        _root = nullptr;
    }

    ~AvlTree(){
        _root = _clear(_root);
    }

    void insert(Key k){
        _root = _insert(_root, k);
    }

    std::pair<Key, Value> getKey(Key k){
        return _get(_root, k);
    }

    void clear(){
        _root = _clear(_root);
    }

    void erase(Key k){
        _root = _remove(_root, k);
    }

    bool contains(Key k) const{
        return _contains(_root, k);
    }

    bool empty() const{
        return _root == nullptr;
    }

    int size() const{
        return _size(_root);
    }

    void show() const{
        _show(_root);
        std::cout << std::endl;
    }

private:
    struct Node
    {
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

    Node *_root;
    size_t cont;

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

    std::pair<Key, Value> _get(Node* node, Key k) {
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

    Node* _clear(Node *node){
        if (node != nullptr){
            node->left = _clear(node->left);
            node->right = _clear(node->right);
            delete node;
        }
        return nullptr;
    }

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

    Node* remove_successor( Node * root , Node * node ) {

        if ( node -> left != nullptr ){
            node -> left = remove_successor( root , node -> left ) ;
            node = fixup_deletion(node);
            return node;
        }else {
            root -> pair.first = node -> pair.first;
            Node * aux = node -> right ;
            delete node ;
            return aux ;
        }

        node = fixup_deletion(node);
        return node ;
    }

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

    int _height(Node *node) const{
        if (node == nullptr){
            return 0;
        }else{
            return node->height;
        }
    }

    int _size(Node *node) const{
        if (node == nullptr)
            return 0;

        return _size(node->left) + _size(node->right) + 1;
    }

    Node *right_rotation(Node *node){
        Node *aux = node->left;
        node->left = aux->right;
        aux->right = node;

        node->height = 1 + std::max(_height(node->left), _height(node->right));
        aux->height = 1 + std::max(_height(aux->left), _height(aux->right));
        return aux;
    }

    Node *left_rotation(Node *node){
        Node *aux = node->right;
        node->right = aux->left;
        aux->left = node;

        node->height = 1 + std::max(_height(node->left), _height(node->right));
        aux->height = 1 + std::max(_height(aux->left), _height(aux->right));
        return aux;
    }

    int _balance(Node *node) const{
        return _height(node->right) - _height(node->left);
    }

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

    void _show(Node *node) const{
        if (node == nullptr)
            return;

        _show(node->left);
        std::cout << node->pair.first << "|" << node->pair.second << std::endl;
        _show(node->right);
    }
};

#endif