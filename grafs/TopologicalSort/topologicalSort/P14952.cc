#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <list>

using namespace std;

using VE = vector <int>;
using VVE = vector <VE>;
using PQ = priority_queue <int, vector<int>, greater<int>>; //!Min heap
using Lista = list<int>;

VVE G;
VE ge;

Lista topological_sort(int n, int m) {
    PQ pq;
    for (int i = 0; i < n; ++i)
        if (ge[i] == 0)
            pq.push(i);

    Lista l;
    while (not pq.empty()) {
        int x = pq.top();
        pq.pop();
            l.push_back(x);
        for (int v : G[x]){
            if (--ge[v] == 0)
                pq.push(v);
        }
    }
    return l;
}

int main() {
    int n, m;
    while (cin >> n >> m) {
        G = VVE(n);
        ge = VE(n,0);
        for (int i = 0; i < m; ++i) {
            int x,y;
            cin >> x  >> y;
            G[x].push_back(y);
            ++ge[y];
        }
        Lista l;
        l = topological_sort(n, m);
        //*Escribir la lista ya ordenada.
        list <int>::const_iterator L_it = l.begin();
        cout << *L_it;
        ++L_it;            
        while (L_it != l.end()){
            cout << " " << (*L_it);
            ++L_it;
        }
        cout << endl;
    }
}