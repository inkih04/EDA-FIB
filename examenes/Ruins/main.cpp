#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool es_vocal(char w){
    return w == 'a' or w == 'e' or w == 'i' or w == 'o' or w == 'u';
}

void combinaciones(vector<char>& solucion_parcial, int index,const vector<char>& letras) {
    if (index == solucion_parcial.size()) {
        for (int i = 0; i < solucion_parcial.size(); ++i) cout <<solucion_parcial[i];
        cout << endl;
        return;
    }                                                               //*Si el anterior era una consonante puedo meter cualquier cosa
    for (int i = 0; i < letras.size(); ++i) {                       //*Sie el que quiero añadir es una consonante siempre puedo
        if (index == 0 or !es_vocal(letras[i]) or !es_vocal(solucion_parcial[index-1])){ //*Si el index es 0 siempre puedo añadir 
            solucion_parcial[index] = letras[i];
            //cout << solucion_parcial[index];
            combinaciones(solucion_parcial, index+1, letras);                                                               
        }
    }
}




int main() {
    int n, m;
    while (cin >> n >> m) {
        vector<char> letras(m);
        for (int i = 0; i < m; ++i) cin >> letras[i];
        sort(letras.begin(), letras.end());
        vector<char> solucion_parcial(n);
        combinaciones(solucion_parcial,0, letras);
        cout << "----------" << endl;
    }
}
