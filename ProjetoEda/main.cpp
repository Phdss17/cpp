//main teste das estruturas genericas
#include <iostream>
#include <fstream>
#include <string>
#include "AvlTree.hpp"
#include "Chained_HashTable.hpp"
#include "RbTree.hpp"
using namespace std; 

int main(){
//o uso de string permite a manipulação de todos os outros tipos
//e ainda emprime por ordem de tamanho e alfabetica automaticamente
//no entanto leva em consideração a captularização das letras
AvlTree<string, int> avt;
Chained_HashTable<string, int> cht(5, 0.75);
RbTree<string, int> rb;

for(int i = 1; i <= 4; i++){
    string str;
    int x;
    cin >> str >> x;
    avt.insert(str, x);
    cht.add(str, x);
    rb.insert(str, x);
}

avt.show();
rb.show();
cht.show();

// string str;
// cin >> str;
// t.erase(str);
// t.show();

// cin >> str;
// auto result = t.getKey(str);
// cout << result.first << "|" << result.second;

return 0;
}