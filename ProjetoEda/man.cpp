#include <iostream>
#include "AvlTree.hpp"
#include "RbTree.hpp"
#include "Chained_HashTable.hpp"
#include "OpenAdress_HashTable.hpp"
#include <vector>
#include <utility>

using namespace std;

int main(){
    AvlTree<string, int> avl;
    cout << "TESTES AVL" << endl;
    avl.insert("ph", 1);
    avl.insert("atilio", 10);
    avl.insert("eda", 7);  
    avl.insert("teste", 3);
    avl.insert("avl", -13);
    avl.insert("biblia", 100);
    avl.insert("biblia", 1000);

    avl.show();
    avl.erase("ph");
    avl.erase("teste");

    avl.show();
    cout << "comparacoes: "<< avl.getComparisons() << "\n";
    cout << "rotacoes: "<< avl.getRotation() << "\n\n";

    cout << "TESTES RUBRO-NEGRA" << endl;
    RbTree<float, char> rb;
    rb.insert(9.5, 'a');
    rb.insert(1, 'z');
    rb.insert(6.33, 'j');
    rb.insert(8.9, 'd');
    rb.insert(10.0, 'v');
    rb.insert(2.3, 'k');
    rb.insert(2.3, 'a');

    rb.show();

    rb.remove(9.5);
    rb.remove(1);
    rb.remove(2.3);

    rb.show();
    cout << "comparacoes: "<< rb.getComparisons() << "\n";
    cout << "rotacoes: "<< rb.getRotation() << "\n\n";

    
    cout << "TESTES CHAINED" << endl;
    Chained_HashTable<string, float> cht(7, 0.75);

    cht.add("abra", 9.13);
    cht.add("kadabra", 3.14);
    cht.add("alakazan", 912.9);
    cht.add("decadenza", 123.13);
    cht.add("dante", 12.12);
    cht.add("alighieri", 3.14);
    cht.add("comedia", 14);

    cht.show();
    cout << endl;

    cht.remove("abra");
    cht.remove("kadabra");
    cht.remove("dante");

    cht.show();
    cout << "comparacoes: "<< cht.getComparisons() << "\n";
    cout << "colisoes: "<< cht.getCollisions() <<"\n\n";

    cout << "TESTES OPEN" << endl;
    OpenAdress_HashTable<char, int> oah(7, 0.5);

    oah.add('a', 1);
    oah.add('z', 26);
    oah.add('b', 2);
    oah.add('x', 24);
    oah.add('c', 3);
    oah.add('p', 16);
    oah.add('y', 25);

    oah.show();

    oah.remove('p');
    oah.remove('a');
    oah.remove('c');

    oah.show();
    cout << "\n" << "comparacoes: "<< oah.getComparisons() << "\n";
    cout << "colisoes: "<< oah.getCollisions() << "\n\n";
}