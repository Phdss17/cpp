#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <string>
#include <utility>
#include <vector>

template <template<typename, typename...> class Class, typename Key, typename Value>
class Dictionary {
public:
    Dictionary() {}

    void insert(Key k) {
        if(contains(k)) {
            estrutura[k]++;
        } else {
            estrutura.insert(k,1);
        }
    }

    void clear() {
        estrutura.clear();
    }

    Value& at(Key k) {
        return estrutura.at(k);
    }

    bool contains(Key k) {
        return estrutura.contains(k);
    }

    std::string getParameters() {
        return estrutura.getParameters();
    }

    std::vector<std::pair<Key, Value>> getAll(){
        return estrutura.getAll();
    }

private:
    Class<Key, Value> estrutura;

};




#endif