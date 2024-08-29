#include <iostream>
#include <vector>
#include <queue>
#include <sstream> //? Libreria para separar las palabraas por espacios
#include <string>

using namespace std;

typedef vector<queue<string>> CJT_cues;

CJT_cues llegir_cues(int n) {
    string basurilla;
    CJT_cues cues(n, queue<string>());
    getline(cin, basurilla); //!para que el getline no se me falle por culpa de la linea de n
    for (int i = 0; i < n; ++i) { 
        string linea;
        string palabra;
        getline(cin, linea); //?Coje la linea entera
        istringstream ss(linea); //?crea un objeto capaz de separar las palabras de un string por espacios 
        while (ss >> palabra) cues[i].push(palabra); //? >> pone en palabra cada nombre
    }
    return cues;
}

void imprimir_cjtcues(const CJT_cues& cues) {
    int n = cues.size();
    cout << "CONTINGUTS FINALS" << endl;
    cout << "-----------------" << endl;
    for (int i = 0; i < n; ++i) {
        //cout << "->";
        cout << "cua " << i+1 << ":"; 
        queue<string> temporal = cues[i];
        while(!temporal.empty()) {
            cout << " " << temporal.front();   
            temporal.pop();
        }
        cout << endl;
    }
}

void imprimir_cola(queue<string>& sorides) {
    cout << "SORTIDES" << endl;
    cout << "--------" << endl;
    while (!sorides.empty()) {
        cout << sorides.front() << endl;
        sorides.pop();
    }
    cout << endl;
}


int main () {
    int n;
    cin >> n;
    CJT_cues cues = llegir_cues(n);
    string instruccion;
    queue<string> sortides;
    while (cin >> instruccion) {
        if (instruccion == "SURT") {
            int cola;
            cin >> cola;
            --cola;
            if(cola >= 0 && cola < n && !cues[cola].empty()) {
                sortides.push(cues[cola].front()); 
                cues[cola].pop();
            }    
        }
        else if (instruccion == "ENTRA") {
            string nombre; int cola;
            cin >> nombre >> cola;
            --cola;
            if(cola >= 0 && cola < n) cues[cola].push(nombre);
        }
    }
    imprimir_cola(sortides);
    imprimir_cjtcues(cues);
}