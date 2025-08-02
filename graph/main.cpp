#include <iostream>
#include <unordered_set>
#include <vector>
#include <string>

using namespace std;

vector<vector<string>> graph;

void put(string find, string put){
    for(int i = 0; i < graph.size(); i++){
        if(graph[i][0] == find){
            graph[i].push_back(put);
        }
    }
}

bool dfs_find(const string &current, const string &target, unordered_set<string> &visited) {
    if (current == target) return true;
    visited.insert(current); 

    for (auto &node : graph) {
        if (!node.empty() && node[0] == current) {
            for (size_t j = 1; j < node.size(); j++) {
                const string &next = node[j];
                if (visited.find(next) == visited.end() && dfs_find(next, target, visited)) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool has_relacion(string a, string b) {
    unordered_set<string> visited; 
    return dfs_find(a, b, visited);
}

int main(){
    int quant_vertices, quant_relacoes, quant_finds;
    cin >> quant_vertices;
    graph.resize(quant_vertices);
    
    for(int i = 0; i < quant_vertices; i++){
        string aux;
        cin >> aux;
        graph[i].push_back(aux);
    }

    cin >> quant_relacoes;
    for(int i = 0; i < quant_relacoes; i++){
        string first, second;
        cin >> first >> second;
        put(first, second);
    }

    cin >> quant_finds;
    for(int i = 0; i < quant_finds; i++){
        string first, second;
        cin >> first >> second;
        cout << (has_relacion(first,second) ? "true" : "false") << " " << first << " " << second << endl;
    }
}