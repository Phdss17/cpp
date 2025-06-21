#ifndef RBTREE_HPP
#define RBTREE_HPP
#include <utility>

#define RED true
#define BLACK false

template <typename Key, typename Value>
class RbTree{
public:
    RbTree(){
        T_nil = new Node(BLACK, {Key(), Value()}, nullptr, nullptr, nullptr);
        T_nil->left = T_nil->right = T_nil;
        _root = T_nil;
        _root->parent = T_nil;
    }

    ~RbTree(){
        _clear(_root);
        delete T_nil;
    }

    void clear(){
        _clear(_root);
    }

    void insert(Key k, Value v){
        _insert(k, v);
    }

    void remove(Key k){
        _remove(k);
    }

    bool contains(Key k){
        return _contains(k);
    }

    bool empty(){
        return _root == T_nil;
    }

    int size(){
        return _size(_root);
    }

    void show(){
        _show(_root);
        std::cout << std::endl;
        bshow(_root, "");
    }

private:
    struct Node{
        bool color;
        std::pair<Key, Value> pair;
        Node *right;
        Node *left;
        Node *parent;

        Node(bool cor, std::pair<Key, Value> P, Node *direita, Node *esquerda, Node *pai){
            this->color = cor;
            this->pair = P;
            this->right = direita;
            this->left = esquerda;
            this->parent = pai;
        }
    };
        Node *_root;
        Node *T_nil;

    void _insert(Key k, Value v){
        Node* x = _root;
        Node* y = T_nil;
        while(x != T_nil){
            y = x;
            if(k < x->pair.first){
                x = x->left;
            }else if(k > x->pair.first){
                x = x->right;
            }else{
                x->pair.second++;
                return;
            }
        }
        Node* z = new Node(RED, {k, v}, T_nil, T_nil, y);
        if(y == T_nil){
            _root = z;
            insert_fixUp(z);
        }else if(k < y->pair.first){
            y->left = z;
            insert_fixUp(z);
        }else{
            y->right = z; 
            insert_fixUp(z);
        }
    }

    void _remove(Key k){
        Node* p = _root;
        while(p != T_nil && p->pair.first != k){
            if(k < p->pair.first){
                p = p->left;
            }else{
                p = p->right;
            }
        }
        if(p != T_nil){
            _delete(p);
        }
    }

    void _delete(Node* node){
        Node* y = T_nil;
        Node* x = T_nil;
        if(node->left == T_nil || node->right == T_nil){
            y = node;
        }else{
            y = minumum(node->right);
        }
        if(y->left != T_nil){
            x = y->left;
        }else{
            x = y->right;
        }
        x->parent = y->parent;
        if(y->parent == T_nil){
            _root = x;
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
        if (node != T_nil){
            node->left = _clear(node->left);
            node->right = _clear(node->right);
            delete node;
        }
        return nullptr;
    }

    bool _contains(Node* node, Key k) const{
        if (node == T_nil)
            return false;

        while(node != T_nil){
            if(k < node->pair.first){
                node = node->left;
            }else if(k > node->pair.first){
                node = node->right;
            }else{
                return true;
            }
        }
        return false;
    }

    int _size(Node* node){
        if (node == T_nil)
            return 0;

        return _size(node->left) + _size(node->right) + 1;
    }

    void _show(Node* node) const{
        if (node == T_nil)
            return;

        _show(node->left);
        std::cout << node->pair.first << "|" << node->pair.second << std::endl;
        _show(node->right);
    }

    void bshow(Node *node, std::string heranca) {
        if(node != T_nil && (node->left != T_nil || node->right != T_nil))
            bshow(node->right , heranca + "r");

        for(int i = 0; i < (int) heranca.size() - 1; i++)
            std::cout << (heranca[i] != heranca[i + 1] ? "|   " : "    ");

        if(heranca != "")
            std::cout << (heranca.back() == 'r' ? "|-- " : "|-- ");
        
        if(node == T_nil){
            std::cout << "#" << std::endl;
            return;
        }

        std::cout << node->pair.first;
        if(node->color == RED){
            std::cout << " (red)" << std::endl;
        } else {
            std::cout << " (black)" << std::endl;
        }

        if(node != T_nil && (node->left != T_nil || node->right != T_nil))
            bshow(node->left, heranca + "l");
    }

    Node* minumum(Node* node){
        while(node->left != T_nil){
            node = node->left;
        }
        return node;
    }

    void insert_fixUp(Node* node){
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

    void delete_fixUp(Node* node){
        Node* w = T_nil;
        while(node != _root && node->color == BLACK){
            if(node == node->parent->left){
                w = node->parent->right;
                if(w->color == RED){
                    w->color = BLACK;
                    node->parent->color = RED;
                    left_rotate(node->parent);
                    w = node->parent->right;
                }
                if(w->left->color == BLACK && w->right->color == BLACK){
                    w->color = RED;
                    node = node->parent;
                }else{
                    if(w->right->color == BLACK){
                        w->left->color = BLACK;
                        w->color = RED;
                        right_rotate(w);
                    }
                    w->color = node->parent->color;
                    node->parent->color = BLACK;
                    w->right->color = BLACK;
                    left_rotate(node->parent);
                    node = _root;
                }
            }else{
                w = node->parent->left;
                if(w->color == RED){
                    w->color = BLACK;
                    node->parent->color = RED;
                    right_rotate(node->parent);
                    w = node->parent->left;
                }
                if(w->right->color == BLACK && w->left->color == BLACK){
                    w->color = RED;
                    node = node->parent;
                }else{
                    if(w->left->color == BLACK){
                        w->right->color = BLACK;
                        w->color = RED;
                        left_rotate(w);
                    }
                    w->color = node->parent->color;
                    node->parent->color = BLACK;
                    w->left->color = BLACK;
                    right_rotate(node->parent);
                    node = _root;
                }
            }
        }
        node->color = BLACK;
    }

    void left_rotate(Node* node){
        Node* y = node->right;
        node->right = y->left;
        if(y->left != T_nil){
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

    void right_rotate(Node* node){
        Node* y = node->left;
        node->left = y->right;
        if(y->right != T_nil){
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