#include <iostream>
#include "AvlTree.hpp"
using namespace std;

int main(){
    AvlTree<string, int> arvore;

    for(int i = 0; i < 6; i++){
        string tomele;
        cin >> tomele;
        arvore.insert(tomele);
    }

    arvore.show();
}