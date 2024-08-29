#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef vector<vector<char>> mat;
typedef vector<vector<int>> MatrizDistancias;
typedef pair<int, int> posicion; //?first-> x second -> y



//? pre: recibe una posicion
//? post: devuelve true si la posicion es aceptable y es diferente de 'X' en caso contrario devuelve false
bool posicion_aceptable(const mat& matriz, const posicion& pos, const int limite_fila, const  int limite_columna) {
    if (pos.first < 0 or pos.second < 0 or pos.first >= limite_fila or pos.second >=limite_columna or matriz[pos.first][pos.second] == 'X') return false;
    return true;
}


//?pre: Lee una matriz de chars donde las X representan muros los . caminos y las t objetivos
//?post: Devuelve la distancia minima a t; su return == -1 no se ha encontrado camino a t.
int bfs(mat& matriz, posicion posicion_original) {
    int size = matriz.size();
    int size_columna = matriz[0].size();
    int max_distance = -1;
    int second_max_distance = -2;

    MatrizDistancias mat_dis(size, vector<int>(size_columna, -1));
    mat_dis[posicion_original.first][posicion_original.second] = 0; //*Distancia desde el punto de partida es igual a 0

    queue<posicion> cola;
    cola.push(posicion_original);

//** Recorrido del BFS
    while (not cola.empty()) {
        posicion pos = cola.front();
        cola.pop();
        int x = pos.first;
        int y = pos.second;
        if(matriz[x][y] == 't') {
            if (max_distance > mat_dis[x][y]) second_max_distance = max(mat_dis[x][y], second_max_distance);
            else {
                second_max_distance = max_distance;
                max_distance = mat_dis[x][y];
            }    
        }
        matriz[x][y] = 'X'; //*Evitar que se vuelvan a explorar posibilades exploradas previamente

        //*Arriba    
        if(posicion_aceptable(matriz, {x+1, y}, size, size_columna) and mat_dis[x+1][y] == -1) {
            cola.push({x+1, y});
            mat_dis[x+1][y] = mat_dis[x][y] + 1;
        }
        //*abajo
        if(posicion_aceptable(matriz, {x-1, y}, size, size_columna) and mat_dis[x-1][y] == -1) {
            cola.push({x-1, y});
            mat_dis[x-1][y] = mat_dis[x][y] + 1;
        }
        //*derecha
        if(posicion_aceptable(matriz, {x, y+1}, size, size_columna) and mat_dis[x][y+ 1] == -1) {
            cola.push({x, y+1});
            mat_dis[x][y+1] = mat_dis[x][y] + 1;
        }
        //*izquierda
        if(posicion_aceptable(matriz, {x, y-1}, size, size_columna) and mat_dis[x][y-1] == -1) {
            cola.push({x, y-1});
            mat_dis[x][y-1] = mat_dis[x][y] + 1;
        }
    }
    return second_max_distance;
}

//? pre: dos enteros >= 0
//? post: una matriz de f filas y c columnas.
mat leer_matriz(int f, int c) {
    mat matriz(f, vector<char> (c));
    for (int i = 0; i < f; ++i) {
        for (int j = 0; j < c; ++j) cin >> matriz[i][j]; 
    }
    return matriz;
}


int main() {
    int f, c;
    cin >> f >> c;
    f; c;
    mat matriz = leer_matriz(f, c);
    posicion p;
    cin >> p.first >> p.second;
   --p.first; --p.second; 
    int dis =  bfs(matriz, p);
    if (dis > 0) cout << "second maximum distance: " << dis << endl;
    else cout << "we cannot reach two or more treasures" << endl;
}