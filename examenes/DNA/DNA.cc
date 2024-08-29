#include <iostream>
#include <vector>

using namespace std;


void escribir(const vector<char>& v) {
    for (int i = 0; i < v.size(); ++i) cout << v[i];
    cout << endl;
}


void bactracking(int n, const vector<char>& v, int n_indice, vector<char> resultado) {
    if (n == n_indice) escribir(resultado);
    else {
        for (int i = 0; i < v.size(); ++i) {
            resultado[n_indice] = v[i];
            bactracking(n, v, n_indice + 1, resultado);
        }
    } 
}


int main () {
    int n;
    cin >> n;
    vector<char> v(4);
    vector<char> resultado(n, 0);
    v[0] = 'A'; v[1] = 'C'; v[2] = 'G'; v[3] = 'T';
    bactracking(n, v, 0, resultado);
}