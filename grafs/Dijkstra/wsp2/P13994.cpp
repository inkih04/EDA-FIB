#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

typedef pair<int, int> posicion; // distancia, vertice
typedef vector<vector<posicion>> Matriz;

//!pre: Recibe un origen un destino y vector con los vertices por donde pasa
//!post: escribe el orden de los vertices del camino mas pequeño
void escribir(int origen, int d, const vector<int> &padres) {
    if (d == origen)
        cout << d;
    else {
        escribir(origen, padres[d], padres);
        cout << " " << d;
    }
}

//!pre: Recibe una matriz, un punto de inicio y uno como objetivo.
//!post:Imprime por el canal estandar de salida el recorrido mas corto del origen al objetivo
void dijkstra(const Matriz &mat, int p_original, int p_destino, int &distancia_resultado) {
    vector<int> distancias(mat.size(), INT_MAX); //* vector iniciado con todas las distancias como infinito.
    distancia_resultado = -1;
    distancias[p_original] = 0;
    priority_queue<posicion> pq;
    vector<int> padres(mat.size(), -1); // ?Inicializamos el vector de padres --> importante

    pq.push(posicion{0, p_original});

    while (!pq.empty()) {
        int pes = -pq.top().first; //! Sacamos el elemento con menos peso de la pq (el menos sirve para eso sino sacariamos el q mas)
        int vertex = pq.top().second;
        pq.pop();

        if (pes == distancias[vertex]) { //*Ha medida que avanza el algoritmo las distancias cambian la primera que encuentre
                                         //*siempre será más pequeña
            if (vertex == p_destino) {
                distancia_resultado = 1;
                escribir(p_original, p_destino, padres);
                cout << endl;
                return; //*Se ha encontrado el camino más corto a el objetivo
            }
            for (int i = 0; i < (int)mat[vertex].size(); ++i) {
                int padj = mat[vertex][i].first;  //*pesAdj
                int vadj = mat[vertex][i].second; //*vertice contiguo
                if (pes + padj < distancias[vadj]) {
                    distancias[vadj] = pes + padj;
                    padres[vadj] = vertex; //!Hey este vector vadj tiene como padre a vertex
                    pq.push({-distancias[vadj], vadj});
                }
            }
        }
    }
}

int main() {
    int n, m;
    while (cin >> n >> m) {
        Matriz mat(n);
        for (int i = 0; i < m; ++i) {
            int a, b, c;
            cin >> a >> b >> c;
            posicion pos = {c, b}; //!pos.first distancia, pos.second vertice
            mat[a].push_back(pos);
        }
        int posicion_original, posicion_destino;
        cin >> posicion_original >> posicion_destino;
        int distancia;
        dijkstra(mat, posicion_original, posicion_destino, distancia);
        if (distancia == -1)
            cout << "no path from " << posicion_original << " to " << posicion_destino << endl;
    }

    return 0;
}
