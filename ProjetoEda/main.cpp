#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <chrono>
#include <iomanip> // Para std::setw e std::left

// ICU 
#include <unicode/unistr.h>
#include <unicode/locid.h>   
#include <unicode/brkiter.h>
#include <unicode/uchar.h> 
#include <unicode/coll.h>
#include <algorithm> 

//estruturas de dados e Dictionario
#include "structures/AvlTree.hpp"
#include "structures/Chained_HashTable.hpp"
#include "structures/OpenAdress_HashTable.hpp"
#include "structures/RbTree.hpp"
#include "Dictionary.hpp"

using namespace std; 
using namespace icu;


UnicodeString string_treatment(UnicodeString str){
    UnicodeString treated_word;

    for(int i = 0; i < str.length(); ){
        UChar32 letter = str.char32At(i);


        if(u_isalpha(letter) || u_isdigit(letter)){
            treated_word.append(letter);
        }else if(letter == '-' && treated_word.charAt(treated_word.length()-1) != '-'){

        }
        i += U16_LENGTH(letter);  
    }
    return treated_word;
}

vector<UnicodeString> split_words(const UnicodeString txt){
    Locale locale("pt", "BR");
    UErrorCode status = U_ZERO_ERROR;

    BreakIterator* wordIterator = BreakIterator::createWordInstance(locale, status);
    vector<UnicodeString> words;

    if(U_FAILURE(status)) {
        std::cerr << "Erro ao criar BreakIterator: " << u_errorName(status) << std::endl;
        return words;
    }

    wordIterator->setText(txt);
    int32_t start = wordIterator->first();
    int32_t end = wordIterator->next();
    
    while(end != BreakIterator::DONE) {
        UnicodeString word;
        txt.extractBetween(start, end, word);

        if(word == "-" && !words.empty()){
            UnicodeString aux = word; 
            start = end;
            end = wordIterator->next();
            txt.extractBetween(start, end, word);
            word = string_treatment(word);
            if(!word.isEmpty()){
                aux.append(word);
                words.back().append(aux);
            }
        }else{
            word = string_treatment(word);
    
            if(!word.isEmpty()){
                words.push_back(word);
            }
        }
        
        start = end;
        end = wordIterator->next();
    }
    delete wordIterator;
    return words;
}

bool compareStrings(const pair<string, int>& a, const pair<string, int>& b){
    UErrorCode status = U_ZERO_ERROR;
    
    std::unique_ptr<icu::Collator> collator(
        icu::Collator::createInstance(icu::Locale("pt", "BR"), status)
    );
    
    if (U_FAILURE(status)) {
        std::cerr << "Erro ao criar collator: " << u_errorName(status) << std::endl;
        return a < b;  
    }
    
    collator->setStrength(icu::Collator::SECONDARY);

    UnicodeString u_a = UnicodeString::fromUTF8(a.first);
    UnicodeString u_b = UnicodeString::fromUTF8(b.first);
    
    icu::Collator::EComparisonResult result = collator->compare(u_a, u_b);
    
    return result == icu::Collator::LESS;
}

template <template<typename, typename...> class ClassType, typename KeyType, typename ValueType>
void process(Dictionary<ClassType, KeyType, ValueType>& dict, const string& structure, const string& in, string& out){

    ifstream entrada(in);

    if (!entrada) {
        throw runtime_error("Não foi possível abrir o arquivo para leitura.");
    }

    string conteudo;

    auto start = std::chrono::high_resolution_clock::now();
    while (getline(entrada, conteudo)) {
        UnicodeString aux = UnicodeString::fromUTF8(conteudo);
        
        vector<UnicodeString> individual_words = split_words(aux.toLower());
        
        for(UnicodeString str : individual_words){
            string word;
            str.toUTF8String(word);
            dict.insert(word);
        }  
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = end-start;

    entrada.close();
        
    if(out.empty()){
        out = structure + "_" + in;
    }

    ofstream saida(out);
    
    if (!saida) {
        throw runtime_error("Não foi possível criar o arquivo.");
    }

    vector<pair<string, int>> aux = dict.getAll();
    sort(aux.begin(), aux.end(), compareStrings);
    saida << "METRICAS PARA ANALISE: " << "\n " << dict.getParameters() << "\n Tempo de execucao em nano: " << duration.count() << "\n";
    saida << "PALAVRAS             FREQUENCIA\n";
    for(int i = 0; i < 30; i++){
        saida << "-";
    }
    saida << "\n";
    for(const auto& pair : aux){
        UnicodeString word = UnicodeString::fromUTF8(pair.first);
        int length = word.length();

        saida << pair.first << setw(25-length) << " | " << pair.second << "\n";
    }
    saida.close();
}

int main(int argc, char* argv[]){
    vector<string> argumentos;

    if(argc < 3 || argc > 4){
        std::cerr << "Erro: Numero incorreto de argumentos." << std::endl;
        return 1; 
    }

    string structure = argv[1]; 
    string in = argv[2];       
    string out;
    if(argc == 4){ 
        out = argv[3];
    }

    try{
        if(structure ==  "dictionary_avl"){
            Dictionary<AvlTree, string, int> dict;
            process(dict, "avl", in, out);
        }else if(structure ==  "dictionary_rb"){
            Dictionary<RbTree, string, int> dict;
            process(dict, "rb", in, out);
        }else if(structure ==  "dictionary_cht"){
            Dictionary<Chained_HashTable, string, int> dict;
            process(dict, "cht", in, out);
        }else if(structure ==  "dictionary_oah"){
            Dictionary<OpenAdress_HashTable, string, int> dict;
            process(dict, "oah", in, out);
        }else{
            throw runtime_error("Estrutura inexistente");
        }
    }catch (const exception& e) {
        cerr << "Erro: " << e.what() << endl;
        return 1;
    }


}