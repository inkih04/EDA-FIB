#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>

using namespace std;

//*Una misma persona no puede votar dos veces la misma propuesta, si la vuelve a votar se quedara el ultimo SI/NO
//*Las propuestas con si > no seran implementadas

void lectura_propostes(map<string, string>& propostes_con_nombre, int n) {
    for (int i = 0; i < n; ++i) {
        string nombre, proposta;
        cin >> nombre >> proposta;
        propostes_con_nombre[proposta] = nombre;
    }
}
void lectura_vots(map<pair<string,string>, bool>& propostes_con_vots) {
    int m; //*Nombre de vots
    cin >> m;
    for (int i = 0; i < m; ++i) {
        string nombre, voto, proposta;
        cin >> nombre >> voto >> proposta;
        propostes_con_vots[{nombre,proposta}] = (voto == "SI");
    } 
}
void conteo_votos(map<string, pair<int,int>>& propuestas_conteo_votos, const map<pair<string,string>, bool>& propostes_con_vots) {
    auto it = propostes_con_vots.begin();
    while (it != propostes_con_vots.end()) {
        string propuesta = it->first.second;
        if (it->second) ++propuestas_conteo_votos[propuesta].first;
        else ++propuestas_conteo_votos[propuesta].second;
        ++it;
    }
}


int main () {
    int n;
    while (cin >> n) {
        map<string, string> propostes_con_nombre;
        lectura_propostes(propostes_con_nombre, n);
        map<pair<string, string>, bool> propostes_con_votos;
        lectura_vots(propostes_con_votos);
        map<string, pair<int,int>> propuestas_conteo_votos;
        conteo_votos(propuestas_conteo_votos, propostes_con_votos);
        //*Escribir resultados
        auto it = propuestas_conteo_votos.begin();
        while (it != propuestas_conteo_votos.end()) {
            if (it->second.first > it->second.second) { //*+ vots positius
                cout << it->first << ", de " << propostes_con_nombre[it->first] <<", que ha guanyat " << it->second.first << "-"
                 << it->second.second << endl; 
            }
            ++it;
        }
        cout << "----------" << endl;
    }
}