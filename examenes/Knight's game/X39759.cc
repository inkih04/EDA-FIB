#include <iostream>
#include <vector>
#include <limits>
#include <queue>
using namespace std;

const int infinite = numeric_limits<int>::max();
vector<pair<int, int>> dirs = {{1, 2}, {1, -2}, {-1, 2}, {-1, -2},
                                {2, 1}, {-2, 1}, {2, -1}, {-2, -1}};

bool inside(int n, int m, const pair<int, int>& x) {
    return x.first >= 0 and x.first < n and x.second >= 0 and x.second < m;
}

int bfs(int n, int m, const pair<int, int>& ini, const pair<int, int>& fi) {
    vector<vector<int>> dist(n, vector<int>(m, infinite));
    queue<pair<int, int>> Q;
    Q.push(ini);
    dist[ini.first][ini.second] = 0;

    while (!Q.empty()) {
        pair<int, int> x = Q.front();
        Q.pop();

        if (x == fi) return dist[x.first][x.second];

        for (auto& d : dirs) {
            pair<int, int> y = x;
            y.first += d.first;
            y.second += d.second;
            if (inside(n, m, y) and dist[y.first][y.second] == infinite) {
                dist[y.first][y.second] = dist[x.first][x.second] + 1;
                Q.push(y);
            }
        }
    }
    return -1;
}

int main() {
    int n, m, W, L, p;
    while (cin >> n >> m >> W >> L >> p) {
        vector<pair<int, int>> objs(p + 1);
        objs[0] = {0, 0};
        for (int i = 1; i <= p; ++i) {
            int f, c;
            cin >> f >> c;
            objs[i] = {f, c};
        }

        int points = 0;
        int bestPoints = 0;
        bool stop = false;

        for (size_t i = 0; not stop and i < objs.size() - 1; ++i) {
            int dist = bfs(n, m, objs[i], objs[i + 1]);
            if (dist == -1)
                stop = true;
            else {
                points += W;
                points -= L * dist;
                if (points > bestPoints) bestPoints = points;
            }
        }

        cout << bestPoints << endl;
    }
    return 0;
}
