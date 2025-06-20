#include <iostream>
#include "Cht.hpp"
using namespace std;

//criação da "classe" bolinha
struct Bolinha {
    std::string cor;
    float raio;
};

//sobrecarga do operador de igualdade para bolinhas
bool operator==(const Bolinha& b1, const Bolinha& b2) {
    return b1.cor == b2.cor && b1.raio == b2.raio;
}

//calculo do hash para as bolinhas
struct HashBolinha {
    size_t operator()(const Bolinha& ball) const {
        auto number1 = std::hash<string>()(ball.cor);
        auto number2 = std::hash<float>()(ball.raio); 
        return number1 ^ number2;
    }
};

int main() {
    // -------------------------------------------------------------------------------------
    // Teste 1: inserindo muitos elementos numa tabela hash
    Cht<float, int> tabela(5, 0.75);

    cout << "tamanho inicial da tabela = " << tabela.bucket_count() << endl;

    size_t current_bucket_count = tabela.bucket_count();

    for(int i = 0; i < 5000; ++i) {
        float key = i / 2.0f;
        int value = i;
        tabela[key] = value;
        if(tabela.bucket_count() != current_bucket_count) {
            current_bucket_count = tabela.bucket_count();
            cout << "tabela aumentou, novo tamanho = " << current_bucket_count << endl;
        }
    }

    tabela.clear();

    // -----------------------------------------------------------------------------------
    // Teste 2: reservando espaco previo
    Cht<std::string, int> novaTabela(5, 0.5);
    novaTabela.reserve(100);
    cout << "novaTabela.bucket_count = " << novaTabela.bucket_count() << endl;

    // ----------------------------------------------------------------------------------
    // Teste 3: criando uma tabela hash onde as chaves sao bolinhas
    Cht<Bolinha, int, HashBolinha> tabBolinha(13, 0.8);

    tabBolinha.add({"azul", 0.4}, 23);

    cout << "numero de bolinhas na tabela de bolinhas = " << tabBolinha.size() << endl;
}
