#include <iostream>
#include <vector>
using namespace std;

void escriure(vector<int>& v){
    if (v.size() != 0){
        cout << v[0];
        for (int i = 1; i < v.size(); i++){
            cout << ' ' << v[i];
        }
    }
    cout << endl;
}

void zerosiuns(int i, vector<int>& v){
    if ( i > 0) {
        for (int j = 0; j < 2; ++j) {
            v.push_back(j);
            zerosiuns(i -1, v);
            v.pop_back();
        }
    }
    else {
        escriure(v);
    }
}

int main(){
    
    int n;
    cin >> n;
    vector<int> v;
    zerosiuns(n, v);
    
}