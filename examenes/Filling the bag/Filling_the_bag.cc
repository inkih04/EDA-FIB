#include <iostream>
#include <set>
#include <string>

using namespace std;

long long valor_maximo(const set<long long, greater<long long>>& jewels, int capacidad) {
    long long max_value = 0;
    auto it = jewels.begin();
    int count = 0;
    while (count < capacidad && it != jewels.end()) {
        max_value += *it;
        ++it;
        ++count;
    }
    return max_value;
}

int main() {
    int capacity;
    cin >> capacity;
    set<long long, greater<long long>> jewels; 
    string action;
    long long value;
    long long maxValue = 0;
    while (cin >> action >> value) {
        if (action == "leave") {
            jewels.insert(value);
            cout << valor_maximo(jewels, capacity) << endl;
        } else if (action == "take") {
            auto it = jewels.find(value);
            if (it != jewels.end()) jewels.erase(it);
            cout << valor_maximo(jewels, capacity) << endl;
        }
    }
}
