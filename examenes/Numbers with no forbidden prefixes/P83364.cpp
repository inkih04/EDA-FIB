   
#include <iostream>
#include <vector>

using namespace std;

bool es_multiple(const vector<int>& divisors, int numero) {
    for (int i = 0; i < divisors.size(); ++i) {
        if (numero%divisors[i] == 0) {
            return true;
        }    
    }
    return false;
}


void bactrack(const vector<int>& divisors, vector<int>& solucio_parcial, int n, int index, int numero) {
    if (n == index) {
        for (int i = 0; i < n; ++i) cout << solucio_parcial[i];
        cout << endl;
        return;
    }
    if (index == 0) {
        for (int i = 1; i < 10; ++i) {
            int N_numero = numero*10 +i;
            if ((!es_multiple(divisors, N_numero))) {
                solucio_parcial[index] = i;
                bactrack (divisors, solucio_parcial, n, index+1, N_numero);
            }
        }
    }
    else{
        for (int i = 0; i < 10; ++i) {
            int N_numero = numero*10 +i;
            if ((!es_multiple(divisors, N_numero))) {
                solucio_parcial[index] = i;
                bactrack (divisors, solucio_parcial, n, index+1, N_numero);
            }
        }
    }    
}



int main() {
    int n, m;
    while (cin >> n >> m) {
        vector<int> divisors(m);
        vector<int> solucio_parcial(n);
        for (int i = 0; i < m; ++i) cin >> divisors[i];
        bactrack(divisors, solucio_parcial, n, 0, 0);
        cout << "----------" << endl;
    }
}
