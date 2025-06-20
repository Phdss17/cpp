//main teste das estruturas genericas
#include <iostream>
#include <fstream>
#include <string>
#include "AvlTree.hpp"
using namespace std; 

int main(){
//o uso de string permite a manipulação de todos os outros tipos
//e ainda emprime por ordem de tamanho e alfabetica automaticamente
//no entanto leva em consideração a captularização das letras
AvlTree<string, int> t;

for(int i = 1; i <= 4; i++){
    string str;
    cin >> str;
    t.insert(str);
}

t.show();

string str;
cin >> str;
t.erase(str);
t.show();

cin >> str;
auto result = t.getKey(str);
cout << result.first << "|" << result.second;

return 0;
}