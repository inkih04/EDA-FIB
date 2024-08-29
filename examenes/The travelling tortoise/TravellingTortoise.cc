#include <iostream>
#include <vector>

using namespace std; 

typedef vector<vector<char>> Matriz;
typedef vector<vector<bool>> Matriz_visitados;
typedef pair<int, int> Pos;


void escribir_vector(const vector<char> v) {
    int size = v.size();
    if (size >0) cout << v[0];
    for (int i = 1; i < size; ++i) {
        cout << v[i];
    }
    cout << endl;
}


void tortuga(const Matriz& tablero, Matriz_visitados& mat, Pos posicion, const Pos& posicion_final, vector<char> camino) {
    camino.push_back(tablero[posicion.first][posicion.second]);
    if (posicion == posicion_final) escribir_vector(camino); 
    else {
        mat[posicion.first][posicion.second] = true;
        if (posicion.first + 1 < tablero.size() and !mat[posicion.first + 1][posicion.second]) tortuga(tablero, mat, {posicion.first+1, posicion.second}, posicion_final, camino);
        if (posicion.first - 1 >= 0 and !mat[posicion.first - 1][posicion.second]) tortuga(tablero, mat, {posicion.first-1, posicion.second}, posicion_final, camino);
        if (posicion.second + 1 < tablero[0].size() and !mat[posicion.first][posicion.second + 1]) tortuga(tablero, mat, {posicion.first, posicion.second + 1}, posicion_final, camino);
        if (posicion.second - 1 >= 0  and !mat[posicion.first][posicion.second - 1]) tortuga(tablero, mat, {posicion.first, posicion.second -1}, posicion_final, camino);
        mat[posicion.first][posicion.second] = false;  
    }
    camino.pop_back();
}


Matriz leer_tablero(int n, int m) {
    Matriz tablero(n, vector<char>(m));
    for (int i  = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> tablero[i][j];
        }
    }
    return tablero;
}



int main () {
    int n, m;
    cin >> n >> m;
    Matriz tablero = leer_tablero(n, m);
    Pos posicion_original;
    Pos posicion_destino;
    Matriz_visitados visitado(n, vector<bool>(m, false));
    vector<char> resultado;
    cin >> posicion_original.first >> posicion_original.second;
    cin >> posicion_destino.first >> posicion_destino.second;
    tortuga(tablero, visitado, posicion_original, posicion_destino, resultado);
}