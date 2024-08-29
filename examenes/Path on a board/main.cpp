#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;
typedef vector<vector<int>> Mat;
typedef pair<int, int> Pos;
typedef pair<int, Pos> Coste_Pos;

const int inf = numeric_limits<int>::max();
const vector<int> mov_x = {1,  0, -1,  0};
const vector<int> mov_y = {0, -1,  0,  1};

Mat leer_Matriz(int n) {
    Mat mat(n, vector<int>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) cin >> mat[i][j];
    return mat;
}

bool borde(int x, int y, int n) {
    return (x == n-1 or x == 0) or (y == n-1 or y == 0);
}

int cami_minim(const Mat& mat, int n) {
    Mat distancias(n, vector<int>(n, inf));
    vector<vector<bool>> visitados(n, vector<bool>(n, false));
    priority_queue<Coste_Pos,vector<Coste_Pos>,greater<Coste_Pos>> q;
    Pos centro = {n/2, n/2};

    distancias[centro.first][centro.second] = mat[centro.first][centro.second];
    q.push({distancias[centro.first][centro.second] ,centro});
    while (!q.empty()) {
        Pos pos = q.top().second;
        q.pop();
        int x, y;
        x = pos.first; y = pos.second;
        if (!visitados[x][y]) { //!Impide que avance una posicion y piense que el camino mas corto es la casilla de atras
            visitados[x][y] = true;
            if (borde(x,y, n)) return distancias[x][y];
            for (int i = 0; i < 4; ++i) {
                int nx= x + mov_x[i]; int ny = y + mov_y[i]; //*Posicion del vecino
                if (distancias[x][y] + mat[nx][ny] < distancias[nx][ny]) { //!Bloquea un camino que pasa por un nodo, 
                    distancias[nx][ny] = distancias[x][y] + mat[nx][ny];  //!el cual tiene un camino de menos peso                   
                    q.push({distancias[nx][ny],{nx, ny}});
                }
            }
        }    
    }
    return -1;
}


int main () {
    int n;
    while (cin >> n) {
        Mat mat  = leer_Matriz(n);
        cout << cami_minim(mat,n) << endl;
    }
}
