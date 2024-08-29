#include <iostream>
#include <vector>
using namespace std;

using VE = vector <int>;
using VVE = vector <VE>;
int n,m;
VVE G;
VE vist;

void depth (int x, int &v, int &a) {
	if (vist[x]) return;
	vist[x] = true;
	++v;
	for (int y : G[x]) {
		++a;
		depth(y, v,a);
	}
}

void forest() {
	vist = VE(n,false);
	int res = 0;
	for (int x = 0; x < n; ++x)
		if (not vist[x]) {
			int v = 0;
			int a = 0;
			++res;
			depth(x,v,a);
			if (a/2 != v - 1) {
				cout << "no" << endl;
				return;
			}
		}
		cout << res << endl;
}

int main() {
	while (cin >> n >> m) {
		G = VVE (n);
		for (int i = 0; i < m; ++i) {
			int x,y; cin >> x >> y;
			G[x].push_back(y);
			G[y].push_back(x);
		}
		forest();
	}
}
