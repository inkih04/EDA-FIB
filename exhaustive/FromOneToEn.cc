#include <iostream>
#include <vector>

using namespace std;


void escribir(const vector<int>& v) {
    int n = v.size();
    cout << "(" << v[0];
    for (int i = 1; i < n; ++i) {
        cout << "," << v[i];
    }
    cout << ")" << endl;
}

void permutaciones(int numero, int i, vector<int> s, vector<bool> visitados) {
    if (i  == numero - 1) escribir(s);
    else {
        for (int j = 1; j < numero; ++j) {
            if (!visitados[j]) {
                s.push_back(j);
                visitados[j] = true;
                permutaciones(numero, i + 1, s, visitados);
                s.pop_back();
                visitados[j] = false;
            }    
        }
    }    
}
int main() {
    int n;
    cin >> n;
    ++n;
    vector<int> s;
    vector<bool> visitados(n, false);
    permutaciones(n, 0, s, visitados);
}