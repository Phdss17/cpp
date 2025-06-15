#include <iostream>
#include "Set.hpp"
using namespace std;

void comands(){
    cout << "Actions:" << endl <<
            "Create" << endl << 
            "Insert" << endl << 
            "Erase" << endl << 
            "Contains" << endl << 
            "Clear" << endl << 
            "Swap" << endl << 
            "Minimum" << endl << 
            "Maximum" << endl << 
            "Successor" << endl << 
            "Predecessor" << endl << 
            "Empty" << endl << 
            "Size" << endl << 
            "Union" << endl << 
            "Intersection" << endl << 
            "Difference" << endl << 
            "Show_at" << endl <<
            "Show" << endl <<
            "Exit"<< endl << endl;
}

void Show(vector<Set*> x){
    for(int i = 0; i < x.size(); i++){
        cout << "Set " << i << ": ";
        x.at(i)->Show();
        cout << endl;
    }
}

int main(){
    vector<Set*> conjuntos;
 
    comands();
    while(true){
        string token;
        int a, b;
        cin >> token;
        if(token == "Exit" || token == "exit"){
            for(int n = conjuntos.size(); n > 0; n--){
                delete conjuntos.at(n-1);
            }
            conjuntos.clear();
            cout << "good bye" << endl;
            break;
        }else if(token == "Create" || token == "create"){
            Set* set = new Set();
            conjuntos.push_back(set);
            cout << "Set number " << conjuntos.size()-1 << " was created." << endl;
        }else if(token == "Insert" || token == "insert"){
            if(!conjuntos.empty()){
                cin >> a;
                cin >> b;
                conjuntos.at(a)->Insert(b);
                cout << "The number " << b << " was added to the set of number " << a << endl;
            }else{
                cout << "You do not have sets" << endl;
            }
        }else if(token == "Erase" || token == "erase"){   
            if(!conjuntos.empty()){
                cin >> a;
                cin >> b;
                if(!conjuntos.at(a)->Empty()){
                    conjuntos.at(a)->Erase(b);
                    cout << "The number " << b << " was removed from the set of number " << a << endl ;
                }else{
                    cout << "You do not have elements in the set" << endl;
                }
            }else{
                cout << "You do not have sets" << endl;
            }
        }else if(token == "Contains" || token == "contains"){   
            if(!conjuntos.empty()){
                cin >> a;
                cin >> b;
                if(conjuntos.at(a)->Contains(b)){
                    cout << "True: Set " <<  a << " Contains number " << b << endl;
                }else{
                    cout << "False: Set " << a << " do not Contains number " << b << endl;
                }
            }else{
                cout << "You do not have sets" << endl;
            }      
        }else if(token == "Clear" || token == "clear"){     
            if(!conjuntos.empty()){
                cin >> a;
                conjuntos.at(a)->Clear();
                cout << "The set of number " << a << " was has been cleared " << endl;
            }else{
                cout << "You do not have sets" << endl;
            }    
        }else if(token == "Swap" || token == "swap"){  
            if(conjuntos.size() > 1){
                cin >> a;
                cin >> b;
                conjuntos.at(a)->Swap(conjuntos.at(b));
                cout << "The sets " << a << " and " << b << " have been swapped" << endl;
            }else{
                cout << "You need to have more than one set" << endl;
            }
        }else if(token == "Minimum" || token == "minimum"){
            if(!conjuntos.empty()){
                int a;
                cin >> a;
                cout << "the smallest element of the set " << a << " is " << conjuntos.at(a)->Minimum() << endl;
            }else{
                cout << "You do not have sets" << endl;
            }
        }else if(token == "Maximum" || token == "maximum"){
            if(!conjuntos.empty()){
                int a;
                cin >> a;
                cout << "the biggest element of the set " << a << " is " << conjuntos.at(a)->Maximum() << endl;
            }else{
                cout << "You do not have sets" << endl;
            }
        }else if(token == "Successor" || token == "successor"){
            if(!conjuntos.empty()){
                cin >> a;
                cin >> b;
                cout << conjuntos.at(a)->Successor(b) << endl;
            }else{
                cout << "You do not have sets" << endl;
            }
        }else if(token == "Predecessor" || token == "predecessor"){
            if(!conjuntos.empty()){
                cin >> a;
                cin >> b;
                cout << conjuntos.at(a)->Predecessor(b) << endl;
            }else{
                cout << "You do not have sets" << endl;
            }
        }else if(token == "Empty" || token == "empty"){
            if(!conjuntos.empty()){
                cin >> a;
                if(conjuntos.at(a)->Empty()){
                    cout << "True: Set " <<  token << " is empty" << endl;
                }else{
                    cout << "False: Set " << token << " is not empty" << endl;
                }
            }else{
                cout << "You do not have sets" << endl;
            }
        }else if(token == "Size" || token == "size"){
            if(!conjuntos.empty()){
                cin >> a;
                cout << "The size of the set number  " << a << "is: " << conjuntos.at(a)->Size() << endl;
            }else{
                cout << "You do not have sets" << endl;
            }
        }else if(token == "Union" || token == "union"){
            if(conjuntos.size() > 1){
                cin >> a >> b;
                cout << "the union of the sets " << a << " and " << b << " is: ";
                Set* set = new Set();
                set->Union(conjuntos.at(a), conjuntos.at(b));
                conjuntos.push_back(set);
                cout << endl << "and was created in the " << conjuntos.size()-1 << " position" << endl;
            }else{
                cout << "You need to have more than one set" << endl;
            }
        }else if(token == "Intersection" || token == "intersection"){
            if(conjuntos.size() > 1){
                cin >> a >> b;
                cout << "the intersection of the sets " << a << " and " << b << " is: ";
                Set* set = new Set();
                set->Intersection(conjuntos.at(a), conjuntos.at(b));
                conjuntos.push_back(set);
                cout << endl << "and was created in the " << conjuntos.size()-1 << " position" << endl;
            }else{
                cout << "You need to have more than one set" << endl;
            }
        }else if(token == "Difference" || token == "difference"){
            if(conjuntos.size() > 1){
                cin >> a >> b;
                cout << "the difference of the sets " << a << " and " << b << " is: ";
                Set* set = new Set();
                set->Difference(conjuntos.at(a), conjuntos.at(b));
                conjuntos.push_back(set);
                cout << endl << "and was created in the " << conjuntos.size()-1 << " position" << endl;
            }else{
                cout << "You need to have more than one set" << endl;
            }
        }else if(token == "Show_at" || token == "show_at"){
            if(!conjuntos.empty()){
                cin >> a;
                if(!conjuntos.at(a)->Empty()){
                    conjuntos.at(a)->Show();
                }else{
                    cout << "That set is empty" << endl;
                }
                cout << endl;
            }else{
                cout << "You do not have sets" << endl;
            }
        }else if(token == "Show" || token == "show"){
            cout << "Sets:" << endl;
            Show(conjuntos);
        }else if(token == "Igualar" || token == "igualar"){
            if(conjuntos.size() > 1){
                cin >> a >> b;
                Set* set = new Set();
                conjuntos.at(a) = conjuntos.at(b);
                cout << "Now they are equal " << endl;
            }else{
                cout << "You need to have more than one set" << endl;
            }
        }else{
            cout << "Comando invalido" << endl;
        }
    }

    return 0;
}