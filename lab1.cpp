#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <list>
#include <typeinfo>
using namespace std;

vector<list<int>> lista_adiacenta;
vector<vector<int>> matrice_adiacenta;
vector<vector<int>> matrice_incidenta;
int nr_noduri, nr_muchii;

template <typename T>
ostream& operator<<(ostream& os, const vector<T>& vec) {
    os << "[ ";
    for (const auto& v : vec) {
        os << v << " ";
    }
    os << "]";
    return os;
}

template <typename T>
ostream& operator<<(ostream& os, const list<T>& lst) {
    os << "( ";
    for (const auto& v : lst) {
        os << v << " ";
    }
    os << ")";
    return os;
}

ostream& operator<<(ostream& os, const vector<list<int>>& graf) {
    os << "\nReprezentare Lista de Adiacenta:\n";
    for (size_t i = 1; i < graf.size(); ++i) {
        os << "Nodul " << i << ": " << graf[i] << "\n";
    }
    return os;
}

ostream& operator<<(ostream& os, const vector<vector<int>>& matrice) {
    os << "\nReprezentare Matrice de Adiacenta:\n";
    for (size_t i = 1; i < matrice.size(); ++i) {
        for (size_t j = 1; j < matrice[i].size(); ++j) {
            os << matrice[i][j] << " ";
        }
        os << "\n";
    }
    return os;
}

template <typename T>
void afisare_debug(const char* nume, const T& variabila) {
    cout << "DEBUG: " << nume << " (Tip: " << typeid(variabila).name() << ") = " << variabila << endl;
}

void citire_lista_adiacenta(vector<list<int>>& lista, int nr_noduri) {
    for (int i = 1; i <= nr_noduri; ++i) {
        int vecin;
        cout << "Vecinii nodului " << i << ": ";
        while (cin >> vecin && vecin != 0) {
            lista[i].push_back(vecin);
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void citire_matrice_adiacenta(vector<vector<int>>& matrice) {
    cout << "Introduceti matricea de adiacenta (" << nr_noduri << "x" << nr_noduri << "):\n";
    matrice.resize(nr_noduri + 1, vector<int>(nr_noduri + 1, 0));
    for (int i = 1; i <= nr_noduri; ++i) {
        for (int j = 1; j <= nr_noduri; ++j) {
            cin >> matrice[i][j];
        }
    }
}

void citire_matrice_incidenta(vector<vector<int>>& matrice, int nr_noduri, int nr_muchii) {
    cout << "Introduceti numarul de muchii: ";
    cin >> nr_muchii;
    cout << "Introduceti matricea de incidenta (" << nr_noduri << "x" << nr_muchii << "):\n";
    matrice.resize(nr_noduri + 1, vector<int>(nr_muchii + 1, 0));
    for (int i = 1; i <= nr_noduri; ++i) {
        for (int j = 1; j <= nr_muchii; ++j) {
            cin >> matrice[i][j];
        }
    }
}

void afisare_lista_adiacenta(vector<list<int>>& lista, int nr_noduri) {
    cout << "\nLista de adiacenta este:\n";
    for (int i = 1; i <= nr_noduri; ++i) {
        cout << "Nodul " << i << ": ";

        if (lista[i].empty()) {
            cout << "Nu are vecini.";
        } else {
            for (int vecin : lista[i]) {
                cout << vecin << " ";
            }
        }
        cout << endl;
    }
}

void afisare_matrice_adiacenta(vector<vector<int>>& matrice) {
    if (matrice.empty()) {
        cout << "matricea de adiacenta este goala. cititi matricea de la tastatura sau efectuati o transformare.";
        return;
    }
    for (int i = 1; i <= nr_noduri; ++i) {
        for (int j = 1; j <= nr_noduri; ++j) {
            cout << matrice[i][j] << " ";
        }
        cout << endl;
    }
}

vector<vector<int>> lista_in_matrice() {
    vector<vector<int>> matrice(nr_noduri + 1, vector<int>(nr_noduri + 1, 0));
    for (int i = 1; i <= nr_noduri; ++i) {
        for (int vecin : lista_adiacenta[i]) {
            matrice[i][vecin] = 1;
        }
    }
    cout << "Transformare finalizata: lista de adiacenta in matrice de adiacenta!\n";
    return matrice;
}

vector<list<int>> matrice_in_lista() {
    vector<list<int>> lista(nr_noduri + 1);
    for (int i = 1; i <= nr_noduri; ++i) {
        for (int j = 1; j <= nr_noduri; ++j) {
            if (matrice_adiacenta[i][j] == 1) {
                lista[i].push_back(j);
            }
        }
    }
    cout << "Transformare finalizata: matrice de adiacenta in lista adiacenta!\n";
    return lista;
}

void meniu() {
    int optiune;
    cout << "\n MENIU \n";
    cout << "1. citire lista de adiacenta.\n";
    cout << "2. citire matrice de adiacenta.\n";
    cout << "3. citire matrice de incidenta.\n";
    cout << "4. afisare lista de adiacenta.\n";
    cout << "5. afisare matrice de adiacenta.\n";
    cout << "6. Transformare: lista de adiacenta in matrice de adiacenta.\n";
    cout << "7. Transformare: matrice de adiacenta in lista de adiacenta.\n";
    cout << "0. Iesire.\n";
    cout << "Introduceti optiunea: ";
    cin >> optiune;

    switch (optiune) {
        case 1:
            citire_lista_adiacenta(lista_adiacenta, nr_noduri);
            meniu();
            break;
        case 2:
            citire_matrice_adiacenta(matrice_adiacenta);
            meniu();
            break;
        case 3:
            citire_matrice_incidenta(matrice_incidenta, nr_noduri, nr_muchii);
            meniu();
            break;
        case 4:
            afisare_lista_adiacenta(lista_adiacenta, nr_noduri);
            meniu();
            break;
        case 5:
            afisare_matrice_adiacenta(matrice_adiacenta);
            meniu();
            break;
        case 6:
            matrice_adiacenta = lista_in_matrice();
            meniu();
            break;
        case 7:
            lista_adiacenta = matrice_in_lista();
            meniu();
            break;
        case 0:
            cout << "Iesire din program.\n";
            break;
        default:
            cout << "Optiune invalida.\n";
            meniu();
    }
}

int main() {
    cout << "Introduceti numarul de noduri: ";
    cin >> nr_noduri;
    lista_adiacenta.resize(nr_noduri + 1);
    meniu();
    return 0;
}
