#include <iostream>
#include <queue>
#include <vector>

using namespace std;

typedef vector<vector<char>> Tablero;
typedef pair<int, int> Pos; //*first-> x && second -> y
typedef vector<vector<int>> Matriz;
const vector<int> posiciones_i = {-2, -2, -1, 1,  2, 2, -1,  1}; //* Posiciones posibles para los caballos 
const vector<int> posiciones_j = {-1,  1,  2, 2, -1, 1, -2, -2}; 



void escribir_tablero(const Tablero& tablero, int f, int c) {
    cout << "++++++++++++++++++++++++++++++++" << endl;
    for (int i = 0; i < f; ++i) {
        for (int j = 0; j < c; ++j) cout << tablero[i][j];
        cout << endl;
    }
    cout << "---------------------------------" << endl;
}


bool aceptable(const Tablero& tablero, int nx, int ny) {
    if(nx < 0 or  nx >= tablero.size()) return false;
    if(ny < 0 or  ny >= tablero[0].size()) return false;
    return tablero[nx][ny] != 'a'; 
}

Tablero leer_tablero(int f, int c, Pos& pos) {
    Tablero tablero(f, vector<char>(c));
    for (int i = 0; i < f; ++i)
        for (int j = 0; j < c; ++j) { 
            cin >> tablero[i][j];
            if (tablero[i][j] == 'C') pos = {i, j};
        }    
    return tablero;     
}


//?Pre: Lee un tablero y una pos_inicial
//?Post: Devuelve la distancia mas corta hacia una zanahoria o -1 si no existe ningun camino.
int bfs_cavalls(Tablero& tablero, Pos pos_inicial, double& distancia_flors) {
    queue<Pos> cola;
    Matriz distancias (tablero.size(), vector<int>(tablero[0].size(), -1));
    cola.push(pos_inicial);
    distancias[pos_inicial.first][pos_inicial.second] = 0; //*Le asignamos distancia 0 al nodo inicial
    int n_flors_accesibles = 0;   
    while (!cola.empty()) {
        Pos pos = cola.front();
        cola.pop();
        if (tablero[pos.first][pos.second] == 'F') {
           ++n_flors_accesibles;
            distancia_flors += distancias[pos.first][pos.second];
        }
        tablero[pos.first][pos.second] = 'a';
        for (int i = 0; i < 8; ++i) {
            int nx = pos.first + posiciones_i[i];
            int ny = pos.second + posiciones_j[i];
            if (aceptable(tablero, nx, ny) && distancias[nx][ny] == -1) {
                distancias[nx][ny] = distancias[pos.first][pos.second] + 1; //*La nueva distancia es la anterior +1 
                cola.push({nx, ny});
            }
        }   
    }
    if(n_flors_accesibles > 0) distancia_flors = (distancia_flors*1.0)/n_flors_accesibles;
    return n_flors_accesibles;
}

int main() {
    cout.setf(ios::fixed);
    cout.precision(4);
    int f, c;
    cin >> f >> c;
    Pos pos;
    Tablero tablero = leer_tablero(f, c, pos);
    //escribir_tablero(tablero, f, c);
    double distancia_flors = 0;
    int resultado = bfs_cavalls(tablero, pos, distancia_flors);
    if (resultado > 0) cout << "flors accessibles: " << resultado << endl << "distancia mitjana: " << distancia_flors << endl;
    else cout << "el cavall no pot arribar a cap flor" << endl;
}