#include <iostream>
#include <vector>
using namespace std;

void escriure_rossers(vector<int>& v, vector<int>& sol_parcial, bool consecutivos, int index) {
    if (index == sol_parcial.size()) {
        if (consecutivos) {
            for (int i = 0; i < sol_parcial.size(); ++i) cout << sol_parcial[i];
            cout << endl;
        }    
    }
    else {
        for (int i = 1; i <= 3; ++i) {
            if (v[i] > 0 and (sol_parcial[index-1] != i or not consecutivos or index == 0)) { 
                sol_parcial[index] = i;
                --v[i];
                //*consecutivos or (index > 0 and sol_parcial[index-1] == i) la gracia de esto es que una vez que sea true siempre
                //*lo serà y como la primera vez siempre lo tengo como false
                escriure_rossers(v, sol_parcial, consecutivos or (index > 0 and sol_parcial[index-1] == i), index+1);
                ++v[i];
            }
        }
    }    
}

void escriure_rossers(int n) {
    vector<int> sol_parcial(3*n);
    vector<int> v(4, n); //*Basicamente tengo las tres rosas v[1], v[2], v[3]. y N es las veces que tienen que aparecer en la cadena.
    bool consecutivos = false;
    escriure_rossers(v, sol_parcial, consecutivos, 0);
}



int main() {
    int n;
    while (cin >> n) {
        escriure_rossers(n);
        cout << string(10, '*') << endl;
    }
}