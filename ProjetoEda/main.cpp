//main atual com a leitura de argumentos pelo terminal e leitura e criação de arquivos 
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include "AvlTree.hpp"
#include "RbTree.hpp"
#include "Chained_HashTable.hpp"
using namespace std; 

int main(int argc, char* argv[]){
    vector<string> argumentos;

    for (int i = 1; i < argc; ++i) {
        argumentos.push_back(argv[i]);
    }

    if(argumentos[0] == "dictionary_avl"){
        try{
            ifstream entrada(argumentos[1]);

            if (!entrada) {
                throw runtime_error("Não foi possível abrir o arquivo para leitura.");
            }

            AvlTree<string, int> avl;
            string conteudo;
            while (getline(entrada, conteudo)) {
                avl.insert(conteudo, 1);
            }

            entrada.close();
        
            string txt;
            cin >> txt;
            ofstream saida(txt);
            if (!saida) {
                throw runtime_error("Não foi possível criar o arquivo.");
            }

            vector<pair<string, int>> p = avl.getAll();
            for(int i = 0; i < p.size(); i++){
                saida << p.at(i).first << "|" << p.at(i).second << endl;
            }
        
            saida.close();
        } catch (const exception& e) {
            cerr << "Erro: " << e.what() << endl;
            return 1;
        }
    }

    return 0;
}