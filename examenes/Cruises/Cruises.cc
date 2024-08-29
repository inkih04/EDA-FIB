#include <iostream>
#include <map>
using namespace std;


struct Info {
  string code;
  int price;
};

void s_funcion(const map<int, Info>& M) {
  if (M.size() < 2) cout << "no" << endl;
  else {
      auto it = M.begin();
      ++it;
      cout << it->second.code << " " << it->first << " " <<it->second.price << endl;
    }
}

void q_funcion(const map<int, Info>& M, int l) {
    auto it = M.find(l);
    if (it != M.end()) {
        cout << it->second.price << endl;
    }
    else cout << "-1" << endl;
}
 
 
void p_funcion(const map<int, Info>& M) {
    auto it = M.begin();
    while (it != M.end()) {
        cout << it->second.code << " " << it->first << " " <<it->second.price << endl;
        ++it;
    }
}


int main() {
  map<int, Info> M;
  char c;
  while (cin >> c) {
    if (c == 'n') {
      cout << "num: "<< M.size() << endl;
    }
    else if (c == 'u') {
      string code;
      int length, price;
      cin >> code >> length >> price;
      M[length] = {code, price};
    }
    else if (c == 'q') {
      int length;
      cin >> length;
      q_funcion(M, length);
    }
    else if (c == 'p') {
      cout << string(10, '-') << endl;
      p_funcion(M);
      cout << string(10, '*') << endl;
    }
    else { // c == 's'
      s_funcion(M);
    }
  }
}
