#include <iostream>
#include <vector>
#include <limits>

using namespace std;
int inf = numeric_limits<int>::max();


int size_comp(const vector<vector<int>>& G, vector<bool>& visitados, int u) {
    visitados[u] = true;
    int total = 1;
    for (int v: G[u]) {
        if (!visitados[v]) total = total + size_comp(G, visitados, v);
    }
    return total;
}

pair<int,int> dfs(const vector<vector<int>>& v, vector<bool>& visitados) {
    pair<int, int> result = {inf ,0};
    for (int i = 0; i < v.size(); ++i) {
        if (!visitados[i]) {
            int s = size_comp(v, visitados, i);
            result.first = min(result.first, s);
            result.second = max(result.second, s);
        }
    }
    return result;
}

int main() {
    int n, m;
    while (cin >> n >> m) {
        vector<vector<int>> v(n);
        vector<bool> visitados(n, false);
        for(int i = 0; i < m; ++i) {
            int x, y; cin >> x >> y;
            v[x].push_back(y); v[y].push_back(x);
        }
        pair<int, int>p = dfs(v, visitados);
        cout << p.first << " " << p.second << endl;
    }
}
