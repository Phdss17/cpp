#ifndef NODE.HPP
#define NODE.HPP

struct Node{
    bool color;
    int key;
    Node* right;
    Node* left;
    Node* parent;

    Node(bool cor, int chave, Node* direita, Node* esquerda, Node* pai){
        this->color = cor;
        this->key = chave;
        this->right = direita;
        this->left = esquerda;
        this->parent = pai;
    }
};

#endif