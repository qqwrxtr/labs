#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <list>
#include <typeinfo>
#include <limits>
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
    os << "\nReprezentare Matrice:\n";
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
    lista.clear();
    lista.resize(nr_noduri + 1);
    
    cout << "Introduceti vecinii pentru fiecare nod (terminati cu 0):\n";
    for (int i = 1; i <= nr_noduri; ++i) {
        int vecin;
        cout << "Vecinii nodului " << i << ": ";
        while (cin >> vecin && vecin != 0) {
            if (vecin >= 1 && vecin <= nr_noduri) {
                lista[i].push_back(vecin);
            } else {
                cout << "Vecin invalid! Introduceti un nod intre 1 si " << nr_noduri << ": ";
            }
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void citire_matrice_adiacenta(vector<vector<int>>& matrice, int nr_noduri) {
    matrice.clear();
    matrice.resize(nr_noduri + 1, vector<int>(nr_noduri + 1, 0));
    
    cout << "Introduceti matricea de adiacenta (" << nr_noduri << "x" << nr_noduri << "):\n";
    cout << "Pentru fiecare element, introduceti 0 sau 1:\n";
    
    for (int i = 1; i <= nr_noduri; ++i) {
        cout << "Linia " << i << ": ";
        for (int j = 1; j <= nr_noduri; ++j) {
            while (!(cin >> matrice[i][j]) || (matrice[i][j] != 0 && matrice[i][j] != 1)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Valoare invalida! Introduceti 0 sau 1 pentru pozitia [" << i << "][" << j << "]: ";
            }
        }
    }
}

void citire_matrice_incidenta(vector<vector<int>>& matrice, int nr_noduri, int& nr_muchii) {
    cout << "Introduceti numarul de muchii: ";
    while (!(cin >> nr_muchii) || nr_muchii < 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Numarul de muchii trebuie sa fie pozitiv. Reintroduceti: ";
    }
    
    matrice.clear();
    matrice.resize(nr_noduri + 1, vector<int>(nr_muchii + 1, 0));
    
    cout << "Introduceti matricea de incidenta (" << nr_noduri << "x" << nr_muchii << "):\n";
    cout << "Pentru fiecare element, introduceti -1, 0 sau 1:\n";
    
    for (int i = 1; i <= nr_noduri; ++i) {
        cout << "Linia " << i << ": ";
        for (int j = 1; j <= nr_muchii; ++j) {
            while (!(cin >> matrice[i][j]) || (matrice[i][j] != -1 && matrice[i][j] != 0 && matrice[i][j] != 1)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Valoare invalida! Introduceti -1, 0 sau 1 pentru pozitia [" << i << "][" << j << "]: ";
            }
        }
    }
}

void afisare_lista_adiacenta(const vector<list<int>>& lista, int nr_noduri) {
    if (lista.size() <= 1) {
        cout << "\nLista de adiacenta este goala. Cititi lista de la tastatura sau efectuati o transformare.\n";
        return;
    }
    
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

void afisare_matrice_adiacenta(const vector<vector<int>>& matrice, int nr_noduri) {
    if (matrice.size() <= 1) {
        cout << "\nMatricea de adiacenta este goala. Cititi matricea de la tastatura sau efectuati o transformare.\n";
        return;
    }
    
    cout << "\nMatricea de adiacenta este:\n";
    for (int i = 1; i <= nr_noduri; ++i) {
        for (int j = 1; j <= nr_noduri; ++j) {
            cout << matrice[i][j] << " ";
        }
        cout << endl;
    }
}

void afisare_matrice_incidenta(const vector<vector<int>>& matrice, int nr_noduri, int nr_muchii) {
    if (matrice.size() <= 1 || nr_muchii == 0) {
        cout << "\nMatricea de incidenta este goala. Cititi matricea de la tastatura sau efectuati o transformare.\n";
        return;
    }
    
    cout << "\nMatricea de incidenta este:\n";
    for (int i = 1; i <= nr_noduri; ++i) {
        for (int j = 1; j <= nr_muchii; ++j) {
            cout << matrice[i][j] << " ";
        }
        cout << endl;
    }
}

vector<vector<int>> lista_in_matrice_adiacenta(const vector<list<int>>& lista, int nr_noduri) {
    vector<vector<int>> matrice(nr_noduri + 1, vector<int>(nr_noduri + 1, 0));
    for (int i = 1; i <= nr_noduri; ++i) {
        for (int vecin : lista[i]) {
            matrice[i][vecin] = 1;
        }
    }
    cout << "Transformare finalizata: lista de adiacenta in matrice de adiacenta!\n";
    return matrice;
}

vector<list<int>> matrice_in_lista_adiacenta(const vector<vector<int>>& matrice, int nr_noduri) {
    vector<list<int>> lista(nr_noduri + 1);
    for (int i = 1; i <= nr_noduri; ++i) {
        for (int j = 1; j <= nr_noduri; ++j) {
            if (matrice[i][j] == 1) {
                lista[i].push_back(j);
            }
        }
    }
    cout << "Transformare finalizata: matrice de adiacenta in lista adiacenta!\n";
    return lista;
}

// Transformare matrice de incidenta in lista de adiacenta
vector<list<int>> matrice_incidenta_in_lista(const vector<vector<int>>& matrice_inc, int nr_noduri, int nr_muchii) {
    vector<list<int>> lista(nr_noduri + 1);
    
    // Parcurgem fiecare muchie
    for (int j = 1; j <= nr_muchii; ++j) {
        int nod_start = -1;
        int nod_end = -1;
        
        // Găsim nodurile conectate de această muchie
        for (int i = 1; i <= nr_noduri; ++i) {
            if (matrice_inc[i][j] == 1) {
                nod_start = i;
            } else if (matrice_inc[i][j] == -1) {
                nod_end = i;
            }
        }
        
        // Pentru graf neorientat (când avem doar valori de 1)
        if (nod_end == -1) {
            // Găsim ambele noduri conectate
            vector<int> noduri;
            for (int i = 1; i <= nr_noduri; ++i) {
                if (matrice_inc[i][j] == 1) {
                    noduri.push_back(i);
                }
            }
            
            // Adăugăm muchiile în ambele direcții pentru graf neorientat
            if (noduri.size() == 2) {
                lista[noduri[0]].push_back(noduri[1]);
                lista[noduri[1]].push_back(noduri[0]);
            }
        } else if (nod_start != -1 && nod_end != -1) {
            // Pentru graf orientat
            lista[nod_start].push_back(nod_end);
        }
    }
    
    // Sortăm listele pentru o reprezentare ordonată
    for (int i = 1; i <= nr_noduri; ++i) {
        lista[i].sort();
        lista[i].unique(); // Eliminăm duplicatele
    }
    
    cout << "Transformare finalizata: matrice de incidenta in lista adiacenta!\n";
    return lista;
}

// Transformare lista de adiacenta in matrice de incidenta
vector<vector<int>> lista_in_matrice_incidenta(const vector<list<int>>& lista, int nr_noduri, int& nr_muchii) {
    // Mai întâi, calculăm numărul de muchii
    nr_muchii = 0;
    for (int i = 1; i <= nr_noduri; ++i) {
        nr_muchii += lista[i].size();
    }
    
    // Pentru grafuri neorientate, fiecare muchie este numărată de două ori
    nr_muchii /= 2;
    
    vector<vector<int>> matrice_inc(nr_noduri + 1, vector<int>(nr_muchii + 1, 0));
    
    int muchie = 1;
    // Adăugăm muchiile în matrice
    for (int i = 1; i <= nr_noduri; ++i) {
        for (int vecin : lista[i]) {
            if (i < vecin) {  // Evităm duplicarea muchiilor pentru graf neorientat
                matrice_inc[i][muchie] = 1;
                matrice_inc[vecin][muchie] = 1;
                muchie++;
            }
        }
    }
    
    cout << "Transformare finalizata: lista de adiacenta in matrice de incidenta!\n";
    return matrice_inc;
}

// Transformare matrice de adiacenta in matrice de incidenta
vector<vector<int>> matrice_adiacenta_in_incidenta(const vector<vector<int>>& matrice_adj, int nr_noduri, int& nr_muchii) {
    // Calculăm numărul de muchii
    nr_muchii = 0;
    for (int i = 1; i <= nr_noduri; ++i) {
        for (int j = i; j <= nr_noduri; ++j) {  // Pentru graf neorientat
            if (matrice_adj[i][j] == 1) {
                nr_muchii++;
            }
        }
    }
    
    vector<vector<int>> matrice_inc(nr_noduri + 1, vector<int>(nr_muchii + 1, 0));
    
    int muchie = 1;
    // Adăugăm muchiile în matrice de incidență
    for (int i = 1; i <= nr_noduri; ++i) {
        for (int j = i; j <= nr_noduri; ++j) {  // Pentru graf neorientat
            if (matrice_adj[i][j] == 1) {
                matrice_inc[i][muchie] = 1;
                matrice_inc[j][muchie] = 1;
                muchie++;
            }
        }
    }
    
    cout << "Transformare finalizata: matrice de adiacenta in matrice de incidenta!\n";
    return matrice_inc;
}

void meniu() {
    int optiune;
    cout << "\n+===================== MENIU ====================+\n";
    cout << "| 1. Citire lista de adiacenta                  |\n";
    cout << "| 2. Citire matrice de adiacenta                |\n";
    cout << "| 3. Citire matrice de incidenta                |\n";
    cout << "| 4. Afisare lista de adiacenta                 |\n";
    cout << "| 5. Afisare matrice de adiacenta               |\n";
    cout << "| 6. Afisare matrice de incidenta               |\n";
    cout << "| 7. Transformare: lista -> matrice adiacenta   |\n";
    cout << "| 8. Transformare: matrice -> lista adiacenta   |\n";
    cout << "| 9. Transformare: matrice inc. -> lista        |\n";
    cout << "| 10. Transformare: lista -> matrice incidenta  |\n";
    cout << "| 11. Transformare: matrice adj. -> incidenta   |\n";
    cout << "| 0. Iesire                                     |\n";
    cout << "+================================================+\n";
    cout << "Introduceti optiunea: ";
    
    while (!(cin >> optiune)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Optiune invalida. Reintroduceti: ";
    }

    switch (optiune) {
        case 1:
            citire_lista_adiacenta(lista_adiacenta, nr_noduri);
            meniu();
            break;
        case 2:
            citire_matrice_adiacenta(matrice_adiacenta, nr_noduri);
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
            afisare_matrice_adiacenta(matrice_adiacenta, nr_noduri);
            meniu();
            break;
        case 6:
            afisare_matrice_incidenta(matrice_incidenta, nr_noduri, nr_muchii);
            meniu();
            break;
        case 7:
            matrice_adiacenta = lista_in_matrice_adiacenta(lista_adiacenta, nr_noduri);
            meniu();
            break;
        case 8:
            lista_adiacenta = matrice_in_lista_adiacenta(matrice_adiacenta, nr_noduri);
            meniu();
            break;
        case 9:
            lista_adiacenta = matrice_incidenta_in_lista(matrice_incidenta, nr_noduri, nr_muchii);
            meniu();
            break;
        case 10:
            matrice_incidenta = lista_in_matrice_incidenta(lista_adiacenta, nr_noduri, nr_muchii);
            meniu();
            break;
        case 11:
            matrice_incidenta = matrice_adiacenta_in_incidenta(matrice_adiacenta, nr_noduri, nr_muchii);
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
    cout << "+================================================+\n";
    cout << "|     PROGRAM PENTRU REPREZENTAREA GRAFURILOR    |\n";
    cout << "+================================================+\n";
    
    cout << "Introduceti numarul de noduri: ";
    while (!(cin >> nr_noduri) || nr_noduri <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Numarul de noduri trebuie sa fie pozitiv. Reintroduceti: ";
    }
    
    lista_adiacenta.resize(nr_noduri + 1);
    matrice_adiacenta.resize(nr_noduri + 1, vector<int>(nr_noduri + 1, 0));
    nr_muchii = 0;  // Inițial nu avem muchii
    
    meniu();
    return 0;
}
