#include <iostream>
#include <vector>
#include <set>

using namespace std;


void escribir(const vector<string>& v) {
    int n = v.size();
    cout << "(" << v[0];
    for (int i = 1; i < n; ++i) {
        cout << "," << v[i];
    }
    cout << ")" << endl;
}

void permutaciones(int numero, int i, vector<string> resultado, const  vector<string>& s, set<string> visitados) {
    if (i  == numero) escribir(resultado);
    else {
        for (int j = 0; j < numero; ++j) {
            auto it = visitados.find(s[j]);
            if (it == visitados.end()) {
                resultado.push_back(s[j]);
                visitados.insert(s[j]);
                permutaciones(numero, i + 1, resultado, s, visitados);
                resultado.pop_back();
                visitados.erase(s[j]);
            }    
        }
    }    
}
int main() {
    int n;
    cin >> n;
    vector<string> s(n);
    vector<string> resultado;
    for (int i = 0; i < n; ++i) cin >> s[i];
    //escribir(s);
    set<string> visitados;
    permutaciones(n, 0,resultado ,s, visitados);
}