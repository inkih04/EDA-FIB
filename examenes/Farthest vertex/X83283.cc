#include <iostream>
#include <vector>
#include <queue>

using namespace std;
typedef vector<vector<int>> MatAdj;
typedef vector<vector<int>> MatDistancias;

//!Moraleja no utilizar matrices de adyacencias de boleanos, aunque parezcan mas intuitivas
//!Antes de realizar esta version la realize de la otra manera y dio time exceed

void escribir_matriz(const MatAdj& mat) {
    for (int i = 0; i < mat.size(); ++i) {
        for(int j = 0; j < mat[0].size(); ++j) cout << mat[i][j];
        cout << endl;
    }
}

void leer_matriz(MatAdj& mat, int m, int n) {
    n = mat.size();
    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        mat[x].push_back(y);
        mat[y].push_back(x);
    }
}

int bfs(MatAdj& mat) {
    pair<int, int> distancia_vertex = {0,0};
    queue<int> vertices;
    vector<int> distancias(mat.size(),-1); distancias[0] = 0;
    vertices.push(0);

    while(!vertices.empty()) {
        int vertex = vertices.front();
        vertices.pop();
        //cout << distancias[vertex] << "[ "<<vertex << "]   "  << distancia_vertex.first << endl;
        if (distancias[vertex] > distancia_vertex.first) {
            distancia_vertex.first = distancias[vertex];
            distancia_vertex.second = vertex;
        }
        else if (distancias[vertex] == distancia_vertex.first && distancia_vertex.second != 0) {
            distancia_vertex.second = min(vertex, distancia_vertex.second);
        } 

        for (int i = 0; i < mat[vertex].size(); ++i) {
            if (distancias[mat[vertex][i]] == -1) {
                distancias[mat[vertex][i]] = distancias[vertex] + 1;
                vertices.push(mat[vertex][i]);
            }
        }
    }
    return distancia_vertex.second;
}

int main() {
    int n, m;
    while (cin >> n >> m) {
        MatAdj mat(n);
        leer_matriz(mat, m, n);
        //escribir_matriz(mat);
        cout << bfs(mat) << endl;
    }
}