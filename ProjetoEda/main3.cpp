//forma de ler e criar arquivo txt

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    try {
        // Escrever no arquivo
        ofstream saida("exemplo.txt");
        if (!saida) {
            throw runtime_error("Não foi possível criar o arquivo.");
        }
        saida << "Primeira linha\n";
        saida << "Segunda linha\nTerceira linha";
        saida.close();
        
        // Ler do arquivo
        ifstream entrada("exemplo.txt");
        if (!entrada) {
            throw runtime_error("Não foi possível abrir o arquivo para leitura.");
        }
        
        string conteudo;
        cout << "Conteúdo do arquivo:\n";
        while (getline(entrada, conteudo)) {
            cout << conteudo << '\n';
        }
        entrada.close();
        
    } catch (const exception& e) {
        cerr << "Erro: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}