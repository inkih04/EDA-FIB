#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<char>> Matriz;


//?Pre: Recibe una matriz y unos indices
//?Post: Retorna el numero de LOL's que se leen en diagonal vertical y derecha izquierda
int numero_lol(const Matriz& mat, const int& i, const int& j) {
    int n_lol = 0;
    //!Mirar si esta escrito de derecha a izquierda o izquierda derecha es tribial. Hay que escoger una y ser coherentes
    if (j - 2 >= 0 && mat[i][j-2] == 'L' && mat[i][j-1] == 'O') ++n_lol; //* Miro si esta escrito LOL de manera horizontal
    if (j - 2 >= 0 && i - 2 >= 0 && mat[i-2][j-2] == 'L' && mat[i-1][j-1] == 'O') ++n_lol; //*Miro la diagonal '\'
    if (i - 2 >= 0 && j + 1 < mat[0].size() && mat[i-2][j+2] == 'L' && mat[i-1][j+1] == 'O')++n_lol; //*miro diagonal /
    if (i - 2 >= 0 && mat[i-2][j] == 'L' && mat[i-1][j] == 'O') ++n_lol; //*Miro de abajo a arriba
    return n_lol;
}


//?Pre: Le entra una matriz un indice i j y la fila n+1 de la matriz
//?Post: Retorna el numero maximo de veces que se puede escribir LOL
int lolero(Matriz& mat, int i, int j, const int& n) {
    if (j >= mat[0].size()) { //*Mantengo los indices de la matriz coherentes
        ++i;
        j = 0;
    }
    if (i == n) return 0;
    mat[i][j] = 'L';
    //!Solo miro cuantos lol's he podido escribir cuando pongo la l. Solo tiene sentido hacerlo de esta manera 
    int l_n_lol = numero_lol(mat, i, j) + lolero(mat, i, j+1, n);
    mat[i][j] = 'O';
    int o_n_lol = lolero(mat, i, j+1, n);
    return max(l_n_lol, o_n_lol); //*Escojo el valor maximo de lol's entre los que tendria si pongo una 'L' y los que obtendria si
                                 //* pongo una 'O';
}

int main() {
    int n, m;
    while (cin >> n >> m) {
        Matriz mat(n, vector<char>(m));
        cout << lolero(mat, 0, 0, n) << endl;
    }
}