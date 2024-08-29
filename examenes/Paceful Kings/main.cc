#include <iostream>
#include <vector>

using namespace std;
typedef vector<vector<char> > Matriu;


void escriu_tauler (Matriu& tauler) {
	for (int i=0; i < tauler.size(); ++i) {
		for (int j=0; j < tauler[0].size(); ++j) {
			cout << tauler[i][j];
		}
		cout << endl;
	}
	cout << "----------" << endl;
}

bool pos_ok(const Matriu& tablero, int i, int j) {
    int size = tablero.size();
    if (tablero[i][j] == 'K') return false;
    else if (i - 1 >= 0 and j - 1 >= 0 and tablero[i-1][j-1] == 'K') return false;
    else if (i + 1 < size and j - 1 >= 0 and tablero[i+1][j-1] == 'K') return false;
    else if (j + 1 < size and i - 1 >= 0 and tablero[i-1][j+1] == 'K')  return false;
    else if (i + 1 < size and j + 1 < size and tablero[i+1][j+1] == 'K') return false;
    else if (j - 1 >= 0 and tablero[i][j-1] == 'K') return false;
    else if (i + 1 < size and tablero[i+1][j] == 'K') return false;
    else if (j + 1 < size and tablero[i][j+1] == 'K') return false;
    else if (i - 1 >= 0  and tablero[i-1][j] == 'K') return false;
    else return true;
} 

void pacific_kings(vector<vector<char>>& tablero, int n_kings, int k, int x, int y) {
    bool primer = true;
    if (n_kings == k) escriu_tauler(tablero); //*SI se han colocado todos los reyes el programa acaba.
    else {
        for (int i = x; i < tablero.size(); ++i) {
            for(int j = 0; j < tablero[0].size(); ++j) {
                if (primer) {
                    primer = false;
                    j = y;
                }
                if (pos_ok(tablero, i, j)) {
                    tablero[i][j] = 'K';
                    pacific_kings(tablero, n_kings + 1, k, i, j);
                    tablero[i][j] = '.';
                }
            }
        }
    }
}


int main() {
    int n, k;
    cin >> n >> k;
    vector<vector<char>> tablero(n, vector<char>(n, '.'));
    pacific_kings(tablero, 0, k, 0, 0);

}
