#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <list>

using namespace std;

using VE = vector <int>;
using VVE = vector <VE>;
using PQ = priority_queue <int, vector<int>, greater<int>>;
using L = list<int>;

int n,m;
VVE G;
VE ge;

L topological_sort() {

    PQ pq;
    for (int i = 0; i < n; ++i)
        if (ge[i] == 0)
            pq.push(i);

    L l;
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
    while (cin >> n >> m) {
        G = VVE(n);
        ge = VE(n,0);
        for (int i = 0; i < m; ++i) {
            int x,y;
            cin >> x  >> y;
            G[x].push_back(y);
            ++ge[y];
        }
        L l;
        l = topological_sort();
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
