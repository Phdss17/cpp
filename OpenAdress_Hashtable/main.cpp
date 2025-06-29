#include <iostream>
#include "Oah.hpp"
using namespace std;

int main(){
    Oah<float, int> oac(0.75);

    for(float i = 1; i < 24; i++){
        oac.add(i/2, i);
    }
    oac.show();
    cout << endl;

    for(float i = 1; i < 30; i+=2){
        oac.remove(i+0.5);
        oac.remove(i);
    }
    oac.show();
    cout << endl;
    size_t i = oac[10.5];
    cout << i << endl;

    for(float i = 1; i < 30; i++){
        oac[i] = 2*i;
    }
    oac.show();
    cout << endl;

    if(oac.contains(12)){
        cout << "tem 12" << endl;
    }

    if(!oac.contains(12314)){
        cout << "nao tem 123414" << endl;
     }

    oac.clear();
    oac.show();

}