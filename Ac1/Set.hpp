#ifndef SET_HPP
#define SET_HPP
#include "Node.hpp"
#include <queue>

class Set{
    public:
    Set(){
        _root = nullptr;
    }
    
    ~Set(){
        _root = _clear(_root);
    }

    void Insert(int k){
        _root = _insert(_root, k);
    }

    void Clear(){
        _root = _clear(_root);
    }

    void Erase(int k){
        _root = _remove(_root, k);
    }
    
    bool Contains(int k) const {
        return _contains(_root, k);
    }
    
    bool Empty() const {
        return _root == nullptr;
    }

    int Size() const {
        return _size(_root);
    }

    int Minimum() const {
        return _minimum(_root);
    }

    int Maximum() const {
        return _maximum(_root);
    }

    int Successor(int x) const {
        if(!Contains(x)){
            throw std::runtime_error("The set does not contains this element.");
        }
        return _Successor(_root, nullptr, x);
    }

    int Predecessor(int x) const {
        if(!Contains(x)){
            throw std::runtime_error("The set does not contains this element.");
        }
        return _Predecessor(_root, nullptr, x);
    }

    void Swap(Set* x){
        _Swap(x);
    }

    void Union(Set* x, Set* y){
        _Union(x, y);
    }
    
    void Intersection(Set* x, Set* y){
        _Intersection(x, y);
    } 

    void Difference(Set* x, Set* y) {
        _Difference(x, y);
        _Show(this->_root);
    }

    void Show() const {
        _Show(_root);
    }

    void operator=(Set* x){
        if(x == nullptr){
            this->Clear();
        }else{
            std::queue<Node*> fila;
        
        if(x->_root != nullptr){
            fila.push(x->_root);
            while(!(fila.empty())){
                Node* aux = fila.front();
                if(aux->left != nullptr){
                    fila.push(aux->left);
                }
                
                if(aux->right != nullptr){
                    fila.push(aux->right);
                }
    
                Node* N = fila.front();
                this->Insert(N->key);
                fila.pop();
            }
        }
        }
    }

    private:
    Node* _root;
    
    Node* _insert(Node* node, int k){
        if(node == nullptr){
            return new Node(k, nullptr, nullptr);
        }
        
        if(node->key == k){
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
    
    Node* _remove( Node* node , int key){
        if ( node == nullptr )
            return nullptr ;

        if ( key < node -> key )
            node -> left = _remove( node -> left , key );
        else if ( key > node -> key )
            node -> right = _remove( node -> right , key );
        else if ( node -> right == nullptr ) { 
            Node * child = node -> left ;
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

    Node* remove_successor( Node * root , Node * node ) {

        if ( node -> left != nullptr ){
            node -> left = remove_successor( root , node -> left ) ;
            node = fixup_deletion(node);
            return node;
        }else {
            root -> key = node -> key ;
            Node * aux = node -> right ;
            delete node ;
            return aux ;
        }

        node = fixup_deletion(node);
        return node ;
    }

    Node* fixup_deletion ( Node * node ) {
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

    bool _contains(Node* node, int k) const {
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

    int _minimum(Node* node) const {
        if(Empty()){
            throw std::runtime_error("The provided set is empty.");
        }

        if(node == nullptr)return 0;

        if(node->left != nullptr){
            _minimum(node->left);
        }else{
            return node->key;
        }
    }

    int _maximum(Node* node) const {
        if(Empty()){
            throw std::runtime_error("The provided set is empty.");
        }

        if(node == nullptr)return 0;

        if(node->right != nullptr){
            _maximum(node->right);
        }else{
            return node->key;
        }
    }

    int _Successor(Node* x, Node* y, int z) const {
        if(x->key == z){
            if(x->right != nullptr){
                std::cout << "the successor is: ";
                return _minimum(x->right);
            }else if(y != nullptr && y->key > x->key){
                std::cout << "the successor is: ";
                return y->key;
            }
            throw std::runtime_error("The element does not have a Successor in the set.");
        }
        if(z < x->key){
            return _Successor(x->left, x, z);
        }else{
            return _Successor(x->right, x, z);
        } 
    }

    int _Predecessor(Node* x, Node* y, int z) const {
            if(x->key == z){
                if(x->right != nullptr){
                    std::cout << "the predecessor is: ";
                    return _minimum(x->right);
                }else if(y != nullptr && y->key < x->key){
                    std::cout << "the predecessor is: ";
                    return y->key;
                }
                throw std::runtime_error("The element does not have a Predecessor in the set.");
            }
            if(z > x->key){
                return _Predecessor(x->right, x, z);
            }else{
                return _Predecessor(x->left, x, z);
        }
    }

    void _Swap(Set* x){
        Node* l = x->_root->left;
        Node* r = x->_root->right;
        Node* lt = this->_root->left;
        Node* rt = this->_root->right;

        x->_root->left = nullptr;
        x->_root->right = nullptr;
        this->_root->left = nullptr;
        this->_root->right = nullptr;

        int aux = x->_root->key;
        x->_root->key = this->_root->key;
        this->_root->key = aux;

        this->_root->left = l;
        this->_root->right = r;
        x->_root->left = lt;
        x->_root->right = rt;
    }

    void _Union(Set* x, Set* y){
        std::queue<Node*> fila;
        
        if(x->_root != nullptr){
            fila.push(x->_root);
            while(!(fila.empty())){
                Node* aux = fila.front();
                if(aux->left != nullptr){
                    fila.push(aux->left);
                }
                
                if(aux->right != nullptr){
                    fila.push(aux->right);
                }
    
                Node* N = fila.front();
                this->Insert(N->key);
                fila.pop();
            }
        }

        if(y->_root != nullptr){
            fila.push(y->_root);
            while(!(fila.empty())){
                Node* aux = fila.front();
                if(aux->left != nullptr){
                    fila.push(aux->left);
                }
                
                if(aux->right != nullptr){
                    fila.push(aux->right);
                }
                
                Node* N = fila.front();
                this->Insert(N->key);
                fila.pop();
            }
        }

        this->Show();
    }
    
    void _Intersection(Set* x, Set* y){
        if(x->_root == nullptr || x->_root == nullptr){
            return;
        }
        std::queue<Node*> fila;
        while(!(fila.empty())){
            Node* aux = fila.front();
            if(aux->left != nullptr){
                fila.push(aux->left);
            }
                
            if(aux->right != nullptr){
                fila.push(aux->right);
            }
    
            Node* N = fila.front();
            if(y->Contains(N->key)){
                this->Insert(N->key);
            }
                
            fila.pop();
        }
        _Show(this->_root); 
    } 

    void _Difference(Set* x, Set* y){
        std::queue<Node*> fila;

        if(x->_root == nullptr){
            return;
        }

        fila.push(x->_root);
        while(!(fila.empty())){
            Node* aux = fila.front();
            if(aux->left != nullptr){
                fila.push(aux->left);
            }
            
            if(aux->right != nullptr){
                fila.push(aux->right);
            }

            if(!(y->Contains(aux->key))){
                this->Insert(aux->key);
            }
            fila.pop();
        }
    }

    void _Show(Node* node) const {
        if(node == nullptr)return;
		
		_Show(node->left);
		std::cout << node->key <<" ";
		_Show(node->right);
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
    
    Node* _fixupNode(Node* node, int k){
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
};

#endif