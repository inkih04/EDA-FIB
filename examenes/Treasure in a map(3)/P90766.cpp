#include <iostream>
#include <vector>
#include <queue>

using namespace std;


int dfs_rec(vector<vector<char>>& mat, int x, int y) {
    if (x < 0 or x >= mat.size() or y < 0 or y >= mat[0].size() ) return false; // si te sales del tablero retornas falso   
    if (mat[x][y] == 'X') return 0;
    if (mat[x][y] == 't') {
        mat[x][y] = 'X'; 
        return 1+ dfs_rec(mat, x+1,y) + dfs_rec(mat, x - 1, y) + dfs_rec(mat, x,y+1) + dfs_rec(mat, x, y -1);  ; // si has encontrado una t has ganado
    }    
    else mat[x][y] = 'X';
    return dfs_rec(mat, x+1,y) + dfs_rec(mat, x - 1, y) + dfs_rec(mat, x,y+1) + dfs_rec(mat, x, y -1);  
}

int main() {
    int f, c;
    cin >> f >> c;
    vector<vector<char>> mat(f, vector<char>(c));
    for (int i = 0; i < f; ++i) {
        for (int j = 0; j < c; ++j) { 
            char x;
            cin >> x;
            mat[i][j] = x;
        }    
    }
    int x, y ;
    cin >> x >> y;
    --x; --y;
    cout << dfs_rec(mat, x, y) << endl;
}    
