/**
 * @file RbTree.hpp
 * @author Paulo Henrique (phenriquedss@alu.ufc.br)
 * @brief Arvore Rubro-Negra
 * Estrutura de dados avancada - 2025.1
 * @version 0.1
 * @date 2025-06-12
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef RBTREE_HPP
#define RBTREE_HPP
#include <utility>

/** 
 * @brief definição da coloração dos nós
 *
**/
#define RED true
#define BLACK false

/**
 * @brief Classe que implementa uma arvore rubro-negra (Red-Black Tree)
 * 
 * Os tipos Key e Value, caso sejam classes, devem ter um construtor default. 
 * Além disso, o tipo Key deve sobrecarregar o operador de igualdade (==).
 * 
 * @tparam Key key type
 * @tparam Value value type
 */
template <typename Key, typename Value>
class RbTree{
public:
    /**
    * @brief Construtor padrão da classe, cria uma arvore rubro-negra vazia.
    */
    RbTree(){
        count = 0;
        T_nil = new Node(BLACK, {Key(), Value()}, nullptr, nullptr, nullptr);
        T_nil->left = T_nil->right = T_nil;
        _root = T_nil;
        _root->parent = T_nil;
    }

    /**
    * @brief Destrutor padrao da classe, limpa os elementos e deleta o no T_nil.
    */   
    ~RbTree(){
        _clear(_root);
        delete T_nil;
    }

    /**
    * @brief Deleta cada um dos elementos da estrutura.
    */
    void clear(){
        _clear(_root);
    }

    /**
    * @brief Insere um par de chave e valor na estrutura.
    * 
    * @param k := Chave a ser inserida.
    * @param v := Valor associado a chave. 
    */
    void insert(Key k, Value v){
        _insert(k, v);
    }

    /**
    * @brief Remove um elemento baseado em uma chave.
    * 
    * @param k := Chave a ser removida.
    */
    void remove(Key k){
        _remove(k);
    }

    /**
    * @brief Procura na estrutura uma chave, caso ache retorna true, 
    * caso nao, false.
    * 
    * @param k := Chave a ser procurada.
    */
    bool contains(Key k){
        return _contains(_root, k);
    }

    /**
    * @brief Retorn true caso a estrutura esteja vazia, e false caso nao.
    * 
    */
    bool empty(){
        return _root == T_nil;
    }

    /** 
     * @brief retorna o a quantidade de elementos da arvore.
     **/
    int size(){
        return _size(_root);
    }

    void show(){
        _show(_root);
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


        Node *_root; //no rais da arvore
        Node *T_nil; //no T_nil
        mutable size_t count; //contador de comparacoes

    /**
    * @brief Insere um novo par de chave e valor na arvore. 
    * caminha pela arvore na direcao onde a chave estaria, se ela estiver presente
    * seu valor é atualizado, se nao um novo par eh criado e adicionado na posicao devida.
    * Apos eh chamado o fixUp para possiveis correcoes.
    * 
    * @param k := Chave a ser inserida.
    * @param v := Valor associado a chave.
    */
    void _insert(Key k, Value v){
        Node* x = _root;
        Node* y = T_nil;
        while(x != T_nil){
            y = x;
            if(k < x->pair.first){
                count++;
                x = x->left;
            }else if(k > x->pair.first){
                count += 2;
                x = x->right;
            }else{
                count += 2;
                x->pair.second = v;
                return;
            }
        }

        Node* z = new Node(RED, {k, v}, T_nil, T_nil, y);
        if(y == T_nil){
            _root = z;
            insert_fixUp(z);
        }else if(k < y->pair.first){
            count++;
            y->left = z;
            insert_fixUp(z);
        }else{
            count++;
            y->right = z; 
            insert_fixUp(z);
        }
    }

    /**
    * @brief Remove um elemento baseado em uma chave.
    * Caminha pela arvore na direcao onde a chave estaria, se encontra,
    * chama _delete no nodo da chave, se nao, nao age.
    * 
    * @param k := Chave a ser inserida.
    */
    void _remove(Key k){
        Node* p = _root;
        while(p != T_nil && p->pair.first != k){
            count += 2;
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

    /**
    * @brief Recebe um nodo e o deleta da estrutura.
    * Encontra um substituto para o nodo e o conecta no devido lugar, 
    * rebalanceia a arvore caso necessario.
    * 
    * @param node := No a ser deletado.
    */
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
            node->pair = y->pair;
        }
        if(y->color == BLACK){
            delete_fixUp(x);
        }
        delete y;
    }

    /**
    * @brief Recebe um nodo e o deleta junto de seus filhos da estrutura.
    * 
    * @param node := No a partir do qual se comeca a limpar a estrutura.
    */  
    Node* _clear(Node *node){
        if (node != T_nil){
            node->left = _clear(node->left);
            node->right = _clear(node->right);
            delete node;
        }
        return nullptr;
    }

    /**
    * @brief Verifica se um valor esta presente na estrutura.
    * Caminha pela estrutura, se encontrar o valor retorna true, caso nao, false.
    * 
    * @param node := No o qual a pesquisa tera inicio.
    * @param k := Chave a ser pesquisada.
    */
    bool _contains(Node* node, Key k) const{
        if (node == T_nil)
            return false;

        while(node != T_nil){
            if(k < node->pair.first){
                count++;
                node = node->left;
            }else if(k > node->pair.first){
                count += 2;
                node = node->right;
            }else{
                count += 2;
                return true;
            }
        }
        return false;
    }

    /**
    * @brief Recebe um nodo e conta quantos nos tem a partir dele.
    * 
    * @param node := no a partir do qual a contagem comeca.
    */
    int _size(Node* node){
        if (node == T_nil)
            return 0;

        return _size(node->left) + _size(node->right) + 1;
    }

    /**
    * @brief Recebe um nodo e retorna seu menor descendente.
    * 
    * @param node := no o qual se quer saber o menor descendente.
    */
    Node* minumum(Node* node){
        while(node->left != T_nil){
            node = node->left;
        }
        return node;
    }

    /**
    * @brief Funcao auxiliar que recebe um nodo e caso necessario realoca alguns elementos da tabela,
    * com a intencao de manter o balanceamento.
    * 
    * Faz verificacoes de paternidade repetidas vezesa,
    * de coloracao e modifica a arvore com base nos casos de debalanceamento.
    * 
    * @param node := no o qual vai receber possivel rebalanceamento.
    */   
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

    /**
    * @brief Funcao auxiliar que recebe um nodo e caso necessario realoca alguns elementos da tabela,
    * com a intencao de manter o balanceamento.
    * 
    * Faz verificacoes de paternidade repetidas vezesa,
    * de coloracao e modifica a arvore com base nos casos de debalanceamento.
    * 
    * @param node := no o qual vai receber possivel rebalanceamento.
    */    
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

    /**
    * @brief Funcao auxiliar que recebe um no e faz uma rotacao a esquerda usando ele de pivo.
    * 
    * Faz verificacoes de "existencia" de nodo e faz atribuicoes de ponteiro.
    * 
    * @param node := no pivo da rotacao
    */
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

    /**
    * @brief Funcao auxiliar que recebe um no e faz uma rotacao a direita usando ele de pivo.
    * 
    * Faz verificacoes de "existencia" de nodo e faz atribuicoes de ponteiro.
    * 
    * @param node := no pivo da rotacao
    */
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

    /**
     * @brief Recebe um nó e a partir dele imprime os campos chave e valor do nó.
     * 
     * @param node := nó a partir do qual se deseja mostrar na árvore.
     **/
    void _show(Node *node) const{
        if (node == T_nil)
            return;

        _show(node->left);
        std::cout << node->pair.first << "|" << node->pair.second << std::endl;
        _show(node->right);
    }

};

#endif