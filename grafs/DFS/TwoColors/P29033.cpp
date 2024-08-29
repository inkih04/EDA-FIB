#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<int>> MatrizAdy;

bool coloreoRecursivo(const MatrizAdy& grafo, vector<int>& colores, int vertice, int color) {
    colores[vertice] = color;

    for (int vecino : grafo[vertice]) {
        if (colores[vecino] == -1) {
            // Si el vecino no está coloreado, realiza la llamada recursiva con el color opuesto
            if (!coloreoRecursivo(grafo, colores, vecino, 1 - color)) {
                return false;
            }
        } else if (colores[vecino] == color) {
            // Si el vecino tiene el mismo color que el vértice actual, el grafo no es bipartito
            return false;
        }
    }

    return true;
}

bool esBipartito(const MatrizAdy& grafo) {
    int n = grafo.size();
    vector<int> colores(n, -1);

    // Realiza el coloreo recursivo para cada componente conexa del grafo
    for (int i = 0; i < n; ++i) {
        if (colores[i] == -1 && !coloreoRecursivo(grafo, colores, i, 0)) {
            return false;
        }
    }

    return true;
}

int main() {
    int n, m;
    while (cin >> n >> m) {
        MatrizAdy grafo(n);

        for (int i = 0; i < m; ++i) {
            int x, y;
            cin >> x >> y;
            grafo[x].push_back(y);
            grafo[y].push_back(x);
        }

        if (esBipartito(grafo)) {
            cout << "yes" << endl;
        } else {
            cout << "no" << endl;
        }
    }

    return 0;
}
