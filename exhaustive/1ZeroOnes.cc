#include <iostream>
#include <vector>
using namespace std;

int n;

void f(int k, int o, int u, vector <int> &v) {
    if (u > o || k-u > n-o) return; //*Si el numero de 1 es mayor que el que tendria que ser acaba, y si 
    if (n == k) {
        for (int i = 0; i < n; ++i)
            cout << (i ? " " : "") << v[i];
        cout << endl;
    }
    else {
        v[k] = 0; f(k+1, o, u,   v);
	    v[k] = 1; f(k+1, o, u+1, v);
    }

}

int main() {
    int s; cin >> n >> s;
    vector <int> v(n);
    f(0,s,0,v);
}