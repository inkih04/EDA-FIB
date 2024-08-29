#include <iostream>
#include <vector>

using namespace std;


const vector<char> movimientos = {'x', 'y', 'z'};

void combinacions(int n, int c, int consecutivos, vector<char>& respuesta_parcial, int indice) {
    if (indice == n) {
        for (int i = 0; i < n; ++i) cout << respuesta_parcial[i];
        cout << endl;
        return;
    }
    for (int i = 0; i < 3; ++i) {
        int newConsec; 
        if (indice > 0 and respuesta_parcial[indice - 1] == movimientos[i]) newConsec = consecutivos +1;
        else newConsec = 1;
        if (newConsec <= c) {
            respuesta_parcial[indice] = movimientos[i];
            combinacions(n,c, newConsec, respuesta_parcial, indice+1);
        }
    }
}


int main() {
    int n, c;
    while(cin >> n >> c) {
        int consecutivos = 1;
        int indice = 0;
        vector<char>respuesta_parcial(n) ;
        combinacions(n, c, consecutivos, respuesta_parcial, indice);
        cout << "--------------------" << endl;
    }
}