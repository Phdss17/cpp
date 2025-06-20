#ifndef NODE.HPP
#define NODE.HPP
#include <utility>  

template <typename T>
struct Node{
    bool color;
    std:: pair(T, int) pair;
    Node* right;
    Node* left;
    Node* parent;

    Node(bool cor, std::pair(T, int) P, Node* direita, Node* esquerda, Node* pai){
        this->color = cor;
        this->pair = P;
        this->right = direita;
        this->left = esquerda;
        this->parent = pai;
    }
};

#endif