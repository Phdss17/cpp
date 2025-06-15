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
AvlTree<string> t;

for(int i = 1; i <= 4; i++){
    string str;
    cin >> str;
    t.Insert(str);
}

if(t.Contains("-1")){
    t.Show();
}

return 0;
}