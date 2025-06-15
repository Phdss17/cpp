#ifndef NODE_HPP
#define NODE_HPP
#include <iostream>


struct Node{
    int key;
    Node* left;
    Node* right;
    int height;

    Node(int Chave = 0, Node* Esquerda = nullptr, Node* Direita = nullptr, int Altura = 1){
        this->key = Chave;
        this->left = Esquerda;
        this->right = Direita;
        this->height = Altura;
    }
};

#endif