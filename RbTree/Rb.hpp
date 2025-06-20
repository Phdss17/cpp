#ifndef RB_HPP
#define RB_HPP

template <typename Key, typename Value>
class Rb{
public:
    Rb(){
        T_nil = new Node(BLACK, std::pair<Key, Value>, nullptr, nullptr, nullptr);
        T_nil->left = T_nil->right = T_nil;
        _root = T_nil;
        _root->p = T_nil;
    }

    ~Rb(){
        _clear(_root);
    }

    void clear(){
        _clear(_root);
    }

    void insert(Key k, Value v){
        _insert(_root, k, v);
    }

    void remove(Key k){
        _remove(_root, k);
    }

    bool contains(Key k){
        return _contains(_root, k);
    }

    bool empty(){
        return _root == T_nil;
    }

    int size(){
        return _size(_root);
    }

    void show(){
        _show(_root);
    }

private:
    Node<Key, Value> *_root;
    Node<Key, Value> *T_nil;

    struct Node{
        bool color;
        std::pair(Key, value) pair;
        Node *right;
        Node *left;
        Node *parent;

        Node(bool cor, std::pair(Key, Value) P, Node *direita, Node *esquerda, Node *pai){
            this->color = cor;
            this->pair = P;
            this->right = direita;
            this->left = esquerda;
            this->parent = pai;
        }
    };

    void _insert(Node* node, Key k, Value v){
        node* x = node;
        Node* y = T_nil;
        while(x != T_nil){
            y = x;
            if(k < x->pair.first){
                x = x->left;
            }else if(k > x->pair.first){
                x = x->right;
            }else{
                return x;
            }
        }
        Node* z = new Node(RED, {k, v}, T_nil, T_nil, y);
        if(y == T_nil){
            _root = z;
        }else if(k < y->pair.first){
            y->left = z;
        }else{
            y->right = z; 
        }
        _insert_fixUp(_root, z);
    }

    void _remove(Node* _root, Key k){
        Node* p = _root;
        while(p != T_nil && p->pair.first != k){
            if(k < p->pair.first){
                p = p->left;
            }else{
                p = p->right;
            }
        }
        if(p != T_nil){
            _delete(_root, p);
        }
    }

    void delete(Node* _root, Node* node){
        Node* y = T_nil;
        Node* x = T_nil;
        if(node->left == T_nil || node->right == T_nil){
            y = node;
        }else{
            y = _Minumum(node->right);
        }
        if(y->left != T_nil){
            x = y->left;
        }else{
            x = y->right;
        }
        x->parent = y->parent;
        if(y->parent == T_nil){
            _root = x
        }else{
            if(y == y->parent->left){
                y->parent->left = x;
            }else{
                y->parent->right = x;
            }
        }
        if(y != node){
            node->pair.first = y->pair.first;
        }
        if(y->color == BLACK){
            delete_fixUp(_root, x);
        }
        delete y;
    }

    Node* _clear(Node *node){
        if (node != nullptr){
            node->left = _clear(node->left);
            node->right = _clear(node->right);
            delete node;
        }
        return nullptr;
    }

    bool _contains(Node* node) const{
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

    int _size(Node* node){
        if (node == nullptr)
            return 0;

        return _size(node->left) + _size(node->right) + 1;
    }

    void _show() const{
        if (node == nullptr)
            return;

        _show(node->left);
        std::cout << node->pair.first << "|" << node->pair.second << std::endl;
        _show(node->right);
    }

    Node* minumum(Node* node){
        while(node->left != T_nil){
            node = node->left;
        }
        return node;
    }

    void insert_fixUp(Node* _root, Node* node){
        while(node->parent->color == RED){
            if(node->parent == node->parent->parent->left){
                Node* aux = node->parent->parent->right;
                if(aux->color == RED){
                    node->parent->color = BLACK;
                    aux->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent;
                }else{
                    if(node == node->parent->right){
                        node = node->parent;
                        left_rotate(node);
                    }
                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    right_rotate(node->parent->parent);
                }
            }else{
                Node* aux = node->parent->parent->left;
                if(aux->color == RED){
                    node->parent->color = BLACK;
                    aux->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent;
                }else{
                    if(node == node->parent->left){
                        node = node->parent;
                        right_rotate(node);
                    }
                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    left_rotate(node->parent->parent);
                }
            }
        }
        _root->color = BLACK;
    }

    void delete_fixUp(Node* _root, Node* node){
        Node* w = T_nil;
        while(node != _root && node->color == BLACK){
            if(node == node->parent->left){
                w = node->parent->right;
                if(w->color == RED){
                    w->color = BLACK;
                    node->parent->color = RED;
                    left_rotate(_root, node->parent);
                    w = node->parent->right;
                }
                if(w->left->color == BLACK && w->right->color == BLACK){
                    w->color = RED;
                    node = node->parent;
                }else{
                    if(w->right->color == BLACK){
                        w->left->color = BLACK;
                        w->color = RED;
                        right_rotate(_root, w);
                    }
                    w->color = node->parent->color;
                    node->parent->color = BLACK;
                    w->right->color = BLACK;
                    left_rotate(_root, node->parent);
                    node = _root;
                }
            }else{
                w = node->parent->left;
                if(w->color == RED){
                    w->color = BLACK;
                    node->parent->color = RED;
                    right_rotate(_root, node->parent);
                    w = node->parent->left;
                }
                if(w->right->color == BLACK && w->left->color == BLACK){
                    w->color = RED;
                    node = node->parent;
                }else{
                    if(w->left->color == BLACK){
                        w->right->color = BLACK;
                        w->color = RED;
                        left_rotate(_root, w);
                    }
                    w->color = node->parent->color;
                    node->parent->color = BLACK;
                    w->left->color = BLACK;
                    right_rotate(_root, node->parent);
                    node = _root;
                }
            }
        }
        node->color = BLACK;
    }

    void left_rotate(Node* _root, Node* node){
        Node* y = node->right;
        node->right = y->left;
        if(y-> != T_nil){
            y->left->parent = node;
        }
        y->parent = node->parent;
        if(node->parent == T_nil){
            _root = y;
        }else if(node == node->parent->left){
            node->parent->left = y;
        }else{
            node->parent->right = y;
        }
        y->left = node;
        node->parent = y;
    }

    void right_rotate(Node* _root, Node* node){
        Node* y = node->left;
        node->left = y->right;
        if(y-> != T_nil){
            y->right->parent = node;
        }
        y->parent = node->parent;
        if(node->parent == T_nil){
            _root = y;
        }else if(node == node->parent->right){
            node->parent->right = y;
        }else{
            node->parent->left = y;
        }
        y->right = node;
        node->parent = y;
    }

};

#endif