#include <iostream>
#include <vector>

using namespace std;

int first_occurrence(double x, const vector<double>&v, int esq, int dre) {
    if (esq > dre) return -1; //*No se ha encontrado el numero x en el vector
    else {
        int m = (dre + esq)/2;
        if(v[m] == x) {
            int valor_esq = first_occurrence(x, v, esq ,m-1);
            if (valor_esq == -1) return m;
            return valor_esq;
        }
        else if (v[m] > x) {
            int p_left = first_occurrence(x, v, esq, m-1);
            if (p_left == -1) {
                if(m+1 <= dre and v[m+1] == x) return m+1;
                else return -1;
            }
            return p_left;
        }
        else {
            if (m-1>= esq and v[m-1] == x) return m-1;
            return first_occurrence(x,v,m+1, dre);
        }
    }    
}


int first_occurrence(double x, const vector<double>& v) {
    return first_occurrence(x, v, 0, int(v.size()-1));
}




int main() {
    double n;
    while (cin >> n) {
        vector<double> v = {1, 2, 2, 3, 2, 3,4};
        first_occurrence(n, v);
    }
}