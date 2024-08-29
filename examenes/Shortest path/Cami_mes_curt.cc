#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
typedef vector<vector<int>> Mat;

pair<int, vector<int>> bfs(const Mat& mat) {
    int n = mat.size();
    vector<bool> visitados(n, false);
    vector<int> distancias(n,-1);
    distancias[0] = 0;
    queue<pair<int, vector<int>>> q;
    pair<int, vector<int>> Max_pair = {0, {0}};

    q.push(Max_pair);
    while (!q.empty()) {
        pair<int, vector<int>> nodo = q.front();
        q.pop();
        if (nodo.first == int(mat.size()) - 1) { 
            Max_pair = nodo;
        }    
        for (int u : mat[nodo.first]) {
            if (!visitados[u] && distancias[u] == -1) {
                distancias[u] = distancias[nodo.first] + 1;
                visitados[u] = true;
                vector<int> camino = nodo.second; camino.push_back(u);
                q.push({u, camino});
            }
        }
    }
    return Max_pair;
}

int main() {
    int n, m;
    while (cin >> n >> m) {
        Mat matriz(n);
        for (int i = 0; i < m; ++i) {
            int x, y; cin >> x >> y;
            matriz[x].push_back(y);
        } 
        for (int i = 0; i < n; ++i) {
            sort(matriz[i].begin(), matriz[i].end());
        }
        pair<int, vector<int>> p = bfs(matriz);
        cout << p.second[0];
        for (int i = 1; i < p.second.size(); ++i) cout << " "<< p.second[i];
        cout << endl;
    }
}