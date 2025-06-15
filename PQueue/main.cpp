#include "Pq.hpp"
#include <iostream>
#include <string>
using namespace std;

int main() {
    vector<int> vet {1,4,6,7,9};
    
    Pq<int, std::less<int>> fila(vet);

    while(!fila.empty()) {
        cout << fila.top() << " ";
        fila.pop();
    }
    cout << endl;

    Pq<float, std::greater<int>> fila2;

    for(int i = 1; i < 10; i++) {
        fila2.push(i/2.0);
    }

    while(!fila2.empty()) {
        cout << fila2.top() << " ";
        fila2.pop();
    }
    cout << endl;
    
    return 0;
}