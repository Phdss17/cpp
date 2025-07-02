#include <iostream>
#include "Rb.hpp"
using namespace std;

int main(){
    Rb<string, int> rb;
    
    rb.insert("ph", 10);
    rb.insert("vitoria", 5);
    rb.insert("amor", 100);
    rb.insert("teste", 1000);

    rb.show();

    Rb<float, char> rbb;
    rbb.insert(12.3, 'a');
}