#include <iostream>
#include <vector>

using namespace std;


void concatenacio(int index, const vector<string>& paraules, vector<string>& solucio_parcial, vector<bool>& usada) {
    int n = paraules.size();
    if (index == n) {
        for (int i = 0; i < solucio_parcial.size(); ++i) cout << solucio_parcial[i];
        cout << endl;
        return;
    }
    for (int i = 0; i < n; ++i) {
        if (!usada[i] and (index == 0 or solucio_parcial[index-1][solucio_parcial[index-1].size()-1] != paraules[i][0])){
            solucio_parcial[index] = paraules[i];
            usada[i] = true;
            concatenacio(index+1, paraules, solucio_parcial, usada);
            usada[i] = false;
        }
    }
}


int main () {
    int n;
    cin >> n;
    vector<string> paraules(n);
    vector<string> solucio_parcial(n);
    vector<bool> usada(n, false);
    for (int i = 0; i < n; ++ i) cin >> paraules[i];
    concatenacio(0, paraules, solucio_parcial, usada);
}