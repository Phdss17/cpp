//forma de receber args do terminal

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Exibe ajuda do programa
void mostrarAjuda(const string& nomePrograma) {
    cout << "Uso: " << nomePrograma << " [OPÇÕES] [ARGUMENTOS]\n";
    cout << "Opções:\n";
    cout << "  -h, --help     Mostra esta ajuda\n";
    cout << "  -v, --version  Mostra a versão do programa\n";
    cout << "  -f <arquivo>   Especifica um arquivo de entrada\n";
    cout << "  -o <arquivo>   Especifica um arquivo de saída\n";
}

// Função principal
int main(int argc, char* argv[]) {
    vector<string> argumentos;
    string arquivoEntrada, arquivoSaida;
    bool mostrarVersao = false;

    // Converter argv para vector<string> para facilitar manipulação
    for (int i = 1; i < argc; ++i) {
        argumentos.push_back(argv[i]);
    }

    // Processar argumentos
    for (size_t i = 0; i < argumentos.size(); ++i) {
        string arg = argumentos[i];
        
        if (arg == "-h" || arg == "--help") {
            mostrarAjuda(argv[0]);
            return 0;
        }
        else if (arg == "-v" || arg == "--version") {
            mostrarVersao = true;
        }
        else if (arg == "-f") {
            if (i + 1 < argumentos.size()) {
                arquivoEntrada = argumentos[++i];
            } else {
                cerr << "Erro: -f requer um nome de arquivo\n";
                return 1;
            }
        }
        else if (arg == "-o") {
            if (i + 1 < argumentos.size()) {
                arquivoSaida = argumentos[++i];
            } else {
                cerr << "Erro: -o requer um nome de arquivo\n";
                return 1;
            }
        }
        else {
            // Argumento não reconhecido
            cerr << "Erro: Argumento desconhecido '" << arg << "'\n";
            mostrarAjuda(argv[0]);
            return 1;
        }
    }

    // Lógica do programa
    if (mostrarVersao) {
        cout << "Meu Programa v1.0\n";
    }

    if (!arquivoEntrada.empty()) {
        cout << "Processando arquivo de entrada: " << arquivoEntrada << endl;
        // Aqui você processaria o arquivo
    }

    if (!arquivoSaida.empty()) {
        cout << "Saída será gravada em: " << arquivoSaida << endl;
    }

    return 0;
}
