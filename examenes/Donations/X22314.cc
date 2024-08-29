 #include <iostream>
 #include <map>
 using namespace std;
 
 
 int main() {
   map<string, int> M;
   char c;
   while (cin >> c) {
     if (c == 'N') {
       cout <<"number: " << M.size() << endl; 
     }
     else if (c == 'D') {
       string nif;
       int money;
       cin >> nif >> money;
       if(M[nif] != 0) M[nif] = M[nif] + money;
       else M[nif] = money;
     }
     else if (c == 'Q') {
       string nif;
       cin >> nif;
       auto it = M.find(nif);
       if (it != M.end()) cout << it->second << endl;
       else cout << "-1" << endl;
     }
     else if (c == 'P') {
       auto it = M.begin();
       bool first = true;
       while (it != M.end()) {
        string nif = it->first;
        int size = nif.size();
        size = size-2;
        int ultimo_numero_nif = nif[size]- '0';
        //cout << nif << "  -->   " << nif[size] << "        "  << ultimo_numero_nif << endl;
        if (first && ultimo_numero_nif%2 == 0) {cout << nif; first = false;}
        else if (ultimo_numero_nif%2 == 0) cout << " " << nif;
        ++it;
       }
       cout << endl;
     }
     else { // c == ’L’
       if (M.size() > 0) {
        auto it = M.end();
        --it;
        cout << it->first << " "<< it->second << endl;
       }
       else cout << "NO LAST NIF" << endl;
     }
   }
 }