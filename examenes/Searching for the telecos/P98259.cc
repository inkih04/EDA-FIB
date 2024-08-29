#include <iostream>
#include <vector>
#include <climits>
#include <queue>
using namespace std;

typedef vector<int> VI;
typedef vector<char> VC;
typedef vector<vector<char>> VVC;
typedef vector<vector<int>> VVI;
typedef pair<int, int> PII;

vector<PII> dirs = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

bool pos_ok(const VVC& T, uint i, uint j) {
    return i >= 0 and i < T.size() and j >= 0 and j < T[0].size() and T[i][j] != '#';
}

PII cerca(const VVC& T) { // returns (distance, people)
    int n = T.size(), m = T[0].size();
    VVI dist(n, VI(m, INT_MAX)), pers(n, VI(m, -1));
    queue<PII> Q;
    Q.push({0, 0});
    dist[0][0] = 0;
    pers[0][0] = (T[0][0] == 'P');

    while (!Q.empty()) {
        int i = Q.front().first, j = Q.front().second;
        Q.pop();

        if (T[i][j] == 'T') return {dist[i][j], pers[i][j]};

        for (auto& d : dirs) {
            int ni = i + d.first, nj = j + d.second;
            int nd = dist[i][j] + 1;

            if (pos_ok(T, ni, nj)) {
                int np = pers[i][j] + int(T[ni][nj] == 'P');

                if (dist[ni][nj] == INT_MAX) {
                    Q.push({ni, nj});
                    dist[ni][nj] = nd;
                    pers[ni][nj] = np;
                } else if (dist[ni][nj] == nd and pers[ni][nj] < np) {
                    pers[ni][nj] = np;
                }
            }
        }
    }

    return {-1, 0};
}

int main() {
    int n, m;

    while (cin >> n >> m) {
        VVC T(n, VC(m));
        bool found = false;

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cin >> T[i][j];
                if (T[i][j] == 'T') found = true;
            }
        }

        if (!found)
            cout << "El telecos ha fugit." << endl;
        else {
            PII res = cerca(T);
            if (res.first == -1)
                cout << "El telecos esta amagat." << endl;
            else
                cout << res.first << " " << res.second << endl;
        }
    }
}
