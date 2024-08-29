#include <iostream>
#include <map>
using namespace std;

int main() {
    map<string, int> bosa;
    string inpt;
    while (cin >> inpt) {
        if (inpt == "store") {
            string word;
            cin >> word;
            if (not bosa[word]) bosa[word] = 1;
            else bosa[word] = bosa[word] + 1;
        }
        else if (inpt == "delete") {
            string word;
            cin >> word;
            if (bosa[word] <= 1) bosa.erase(word);
            else {
                --bosa[word];
            }    
        }
        else if(inpt == "maximum?") {
            if (bosa.empty()) cout << "indefinite maximum" << endl;
            else {
                map<string, int>::iterator it = bosa.end();
                --it;
                cout << "maximum: " << it->first << ", " << it->second << " time(s)" << endl;
            }    
        }
        else if (inpt == "minimum?") {
            map<string, int>::iterator it = bosa.begin();
            if (bosa.empty()) cout << "indefinite minimum" << endl;
            else {
                cout << "minimum: " << it->first << ", " << it->second << " time(s)" << endl;
            }    
        }    
    }
}
