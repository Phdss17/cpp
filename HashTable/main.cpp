#include <iostream>
#include <functional>
#include "Cht.hpp"
using namespace std;

int main(){
    int idade = 98;
    std:hash<int> hash_code;
    hash_code(idade);
    cout << hash_code(idade) << endl;

    float salario = 45.67;
    cout << hash<float>()(salario) << endl;

    string str = "tome";
    string nome {"ph"};
    cout << hash<string>()(str) << endl;
}