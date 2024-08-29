#include <iostream>
#include <vector>
#include <queue>

using namespace std;
typedef vector<vector<char>> Mat;
typedef pair<int, int> Pos;

Mat leer_matriz(int n, int m, int& x, int& y) {
    vector<vector<char>> matriz(n, vector<char> (m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            char caracter;
            cin >> caracter;
            if (caracter == 'I') {
                x = i;
                y = j;
            }
            matriz[i][j] = caracter;
        }
    }
    return matriz;
}

bool posicion_segura(const Mat& matriz, int x, int y) {
    if (x + 1 < matriz.size() && matriz[x+1][y] == 'M') return false;
    if(x - 1 >= 0 && matriz[x-1][y] == 'M') return false;
    if (y + 1 < matriz[0].size() && matriz[x][y + 1] == 'M') return false;
    if (y -1 >= 0 && matriz[x][y -1] == 'M') return false;
    return true;
}

bool existe_camino(Mat& matriz, Pos inicial) {
    queue<Pos> cola;
    cola.push(inicial);
    while (!cola.empty()) {
        Pos actual = cola.front();
        cola.pop();
        if (matriz[actual.first][actual.second] == 'F') return true;
        if (matriz[actual.first][actual.second] == '.' or matriz[actual.first][actual.second] == 'I') {
            int x, y;
            x = actual.first;
            y = actual.second;
            //*Probar arriba
            if (x - 1 >= 0 && posicion_segura(matriz,x-1, y)) cola.push({x-1, y});
            //*Probar abajo
            if (x + 1 < matriz.size() && posicion_segura(matriz, x+1, y) ) cola.push({x+1, y});
            //*Probar derecha
            if (y + 1 < matriz[0].size() && posicion_segura(matriz, x, y+1)) cola.push({x, y+1});
            //*Probar izquierda
            if (y - 1 >= 0 && posicion_segura(matriz, x, y-1)) cola.push({x, y-1});
        }
        matriz[actual.first][actual.second] = 'M'; //!La marco como visitada
    }
    return false;
}



int main () {
    int n, m;
    while ( cin >> n >> m) {
        int x, y;
        Mat matriz = leer_matriz(n, m, x, y);
        if (existe_camino(matriz, {x, y})) cout << "SI" << endl; 
        else cout << "NO" << endl;
    }
}