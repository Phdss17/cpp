//avl generica
#ifndef AVLTREE_HPP
#define AVLTREE_HPP
#include <iostream>
#include <queue>

template <typename T>
class AvlTree{
    public:
    AvlTree(){
        _root = nullptr;
    }
    
    ~AvlTree(){
        _root = _clear(_root);
    }

    void Insert(T k){
        _root = _insert(_root, k);
    }

    void Clear(){
        _root = _clear(_root);
    }

    void Erase(T k){
        _root = _remove(_root, k);
    }
    
    bool Contains(T k) const {
        return _contains(_root, k);
    }
    
    bool Empty() const {
        return _root == nullptr;
    }

    int Size() const {
        return _size(_root);
    }

    void Show() const {
		_Show(_root);
        std::cout << std::endl;
    }

    private:
    struct Node
    {
        T key;
        Node *left;
        Node *right;
        int height;
        int cont;

        Node(T Chave , Node *Esquerda = nullptr, Node *Direita = nullptr, int Altura = 1, int cont = 1)
        {
            this->key = Chave;
            this->left = Esquerda;
            this->right = Direita;
            this->height = Altura;
            this->cont = cont;
        }
    };

    Node* _root;
    size_t cont;

    Node* _insert(Node* node, T k){
        if(node == nullptr){
            return new Node(k, nullptr, nullptr);
        }
        
        if(node->key == k){
            node->cont++;
            return node;
        }
        
        if (k < node->key){
            node->left = _insert(node->left, k);
        }else if (k > node->key){
            node->right = _insert(node->right, k);
        }
        node = _fixupNode(node, k);
        return node;
    }
    
    Node* _clear(Node* node){
        if(node != nullptr) {
            node->left = _clear(node->left);
            node->right = _clear(node->right);
            delete node;
        }
        return nullptr;
    }
    
    Node* _remove( Node* node , T key){
        if ( node == nullptr )
            return nullptr ;

        if ( key < node -> key )
            node -> left = _remove( node -> left , key );
        else if ( key > node -> key )
            node -> right = _remove( node -> right , key );
        else if ( node -> right == nullptr ) { 
            Node* child = node -> left ;
            delete node ;
            return child ;
        }
        else {
               node -> right = remove_successor( node , node -> right ) ;
               node = fixup_deletion(node);
               return node;
        }
            
        node = fixup_deletion ( node ) ;
        return node ;
    }
    Node* fixup_deletion ( Node* node ) {
        node -> height = 1 + std::max ( _height( node -> left ) , _height( node -> right ) ) ;
        int bal = _balance ( node ) ;

        if ( bal > 1 && _balance ( node -> right ) >= 0) {
            return left_rotation( node ) ;
        }else if ( bal > 1 && _balance ( node -> right ) < 0) {
            node -> right = right_rotation( node -> right ) ;
            return left_rotation ( node ) ;
        }else if ( bal < -1 && _balance ( node -> left ) <= 0) {
            return right_rotation( node ) ;
        }else if ( bal < -1 && _balance ( node -> left ) > 0) {
            node -> left = left_rotation( node -> left ) ;
            return right_rotation( node ) ;
        }

        return node ;
    }

    bool _contains(Node* node, T k) const {
            if(node == nullptr)return false;

            if(node->key == k){ 
                return true;
            }else if(node->key > k){
                return _contains(node->left, k);
            }else{
                return _contains(node->right, k);
            }
        }

    int _height(Node* node) const {
            if(node == nullptr){
                return 0;
            }else{
                return node->height;
            }
        }

    int _size(Node* node) const {
        if(node == nullptr)return 0;

        return _size(node->left) + _size(node->right) + 1;
    }    

    Node* right_rotation(Node* node){
            Node* aux = node->left;
            node->left = aux->right;
            aux->right = node;

            node->height = 1 + std::max(_height(node->left), _height(node->right));
            aux->height = 1 + std::max(_height(aux->left), _height(aux->right));
            return aux;
        }
    
    Node* left_rotation(Node* node){
            Node* aux = node->right;
            node->right = aux->left;
            aux->left = node;

            node->height = 1 + std::max(_height(node->left), _height(node->right));
            aux->height = 1 + std::max(_height(aux->left), _height(aux->right));
            return aux;
        }
    
    int _balance(Node* node) const {
            return _height(node->right) - _height(node->left);
        }
    
    Node* _fixupNode(Node* node, T k){
            int bal = _balance(node);
            
            //Caso 1(a)
            if(bal == -2 && k < node->left->key){
                return right_rotation(node);
            }
            //Caso 1(b)
            if(bal == -2 && k > node->left->key){
                node->left = left_rotation(node->left);
                return right_rotation(node);
            }
            //Caso 2(a)
            if(bal == 2 && k > node->right->key){
                return left_rotation(node);
            }
            //Caso 2(b)
            if(bal == 2 && k < node->right->key){
                node->right = right_rotation(node->right);
                return left_rotation(node);
            }
        
            //Caso node balanceado
            node->height = std::max(_height(node->left), _height(node->right)) + 1;
            return node;
        }

        void _Show(Node* node) const {
        if(node == nullptr)return;
		
		_Show(node->left);
		std::cout << node->key << "|" << node->cont << std::endl;
		_Show(node->right);
    }
};

#endif