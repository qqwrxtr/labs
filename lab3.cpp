#include <iostream>
#include <vector>
#include <limits>

using namespace std;

const int INF = 100; // constanta pentru infinit folosita la distante
int nr_varfuri, nr_muchii, destinatie; // variabile globale pentru noduri, muchii si nodul destinatie
vector<vector<int>> graf; // matrice de adiacenta pentru graf
vector<int> distMin, predMin, distMax, predMax; // vectori pentru distante si predecesori

// functie pentru citirea grafului de la tastatura
void introducereGraf() {
    cout << "Numar de varfuri si muchii: " << endl;
    cin >> nr_varfuri >> nr_muchii;
    
    // initializam matricea de adiacenta cu -INF (lipsa muchiei)
    graf.assign(nr_varfuri + 1, vector<int>(nr_varfuri + 1, -INF));
    
    // distanta de la un nod la el insusi e 0
    for (int i = 1; i <= nr_varfuri; i++) graf[i][i] = 0;

    cout << "Muchii (start end cost):" << endl;
    for (int i = 0; i < nr_muchii; i++) {
        int x, y, cost;
        cin >> x >> y >> cost;
        
        // verificam daca nodurile exista in graf
        if (x >= 1 && x <= nr_varfuri && y >= 1 && y <= nr_varfuri) graf[x][y] = cost;
        else {
            cout << "Muchie invalida, reintroduceti." << endl;
            i--; // decrementam contorul pentru a reintroduce muchia
        }
    }
}

// implementare algoritm bellman-kalaba (varianta inversa a lui bellman-ford)
// minim = true pentru drum minim, false pentru drum maxim
void bellmanKalaba(bool minim) {
    // alegem vectorii corespunzatori (minim sau maxim)
    vector<int> &dist = minim ? distMin : distMax;
    vector<int> &pred = minim ? predMin : predMax;

    // initializam vectorii de distante si predecesori
    dist.assign(nr_varfuri + 1, minim ? INF : -INF); // pentru minim folosim INF, pentru maxim -INF
    pred.assign(nr_varfuri + 1, -1); // -1 inseamna lipsa predecesor
    dist[destinatie] = 0; // distanta de la destinatie la ea insasi e 0

    // algoritmul bellman-kalaba - calculeaza distantele de la toate nodurile la destinatie
    // diferit de bellman-ford care calculeaza distantele de la un nod de start la toate celelalte
    for (int k = 1; k < nr_varfuri; k++) {
        for (int i = 1; i <= nr_varfuri; i++) {
            for (int j = 1; j <= nr_varfuri; j++) {
                // verificam daca exista muchie de la j la i si daca j e accesibil
                if (graf[j][i] != -INF && dist[j] != (minim ? INF : -INF)) {
                    int nouDist = dist[j] + graf[j][i];
                    
                    // actualizam distanta daca e mai buna (mai mica pentru minim, mai mare pentru maxim)
                    if ((minim && nouDist < dist[i]) || (!minim && nouDist > dist[i])) {
                        dist[i] = nouDist;
                        pred[i] = j; // actualizam predecesorul
                    }
                }
            }
        }
    }
}

// functie pentru afisarea drumului de la un nod de start la destinatie
void afisareDrum(vector<int> &pred, vector<int> &dist, string tip) {
    int start;
    cout << "Nod initial: " << endl;
    cin >> start;
    
    // verificam daca nodul de start e valid si accesibil
    if (start < 1 || start > nr_varfuri || pred[start] == -1) {
        cout << "Drum inexistent!" << endl;
        return;
    }
    
    // afisam costul drumului
    cout << tip << " de la " << start << " la " << destinatie << ": " << dist[start] << endl;
    
    // afisam drumul (de la start la destinatie)
    cout << "Drumul: ";
    for (int v = start; v != -1; v = pred[v]) cout << v << " ";
    cout << endl;
}

// meniul interactiv
void meniu() {
    int optiune;
    cout << "\n1. Introducere graf" << endl;
    cout << "2. Drum minim" << endl;
    cout << "3. Drum maxim" << endl;
    cout << "4. Afisare drum minim" << endl;
    cout << "5. Afisare drum maxim" << endl;
    cout << "0. Iesire din program" << endl;
    cout << "Optiune: ";
    cin >> optiune;

    switch (optiune) {
        case 1:
            introducereGraf(); // citim graful
            meniu();
            break;
        case 2:
            // verificam daca graful a fost introdus
            if (nr_varfuri == 0 || nr_muchii == 0) {
                cout << "Graful nu a fost introdus. Utilizati optiunea 1 mai intai." << endl;
            } else {
                cout << "Destinatie: " << endl;
                cin >> destinatie;
                
                // verificam daca nodul destinatie e valid
                if (destinatie < 1 || destinatie > nr_varfuri) {
                    cout << "Nod invalid!" << endl;
                } else {
                    bellmanKalaba(true); // calculam drumuri minime catre destinatie
                    cout << "Drumul minim a fost calculat. Utilizati optiunea 4 pentru afisare." << endl;
                }
            }
            meniu();
            break;
        case 3:
            // verificam daca graful a fost introdus
            if (nr_varfuri == 0 || nr_muchii == 0) {
                cout << "Graful nu a fost introdus. Utilizati optiunea 1 mai intai." << endl;
            } else {
                cout << "Destinatie: " << endl;
                cin >> destinatie;
                
                // verificam daca nodul destinatie e valid
                if (destinatie < 1 || destinatie > nr_varfuri) {
                    cout << "Nod invalid!" << endl;
                } else {
                    bellmanKalaba(false); // calculam drumuri maxime catre destinatie
                    cout << "Drumul maxim a fost calculat. Utilizati optiunea 5 pentru afisare." << endl;
                }
            }
            meniu();
            break;
        case 4:
            // verificam daca drumul minim a fost calculat
            if (distMin.empty()) {
                cout << "Drumul minim nu a fost calculat. Utilizati optiunea 2 mai intai." << endl;
            } else {
                afisareDrum(predMin, distMin, "Drumul minim"); // afisam drumul minim
            }
            meniu();
            break;
        case 5:
            // verificam daca drumul maxim a fost calculat
            if (distMax.empty()) {
                cout << "Drumul maxim nu a fost calculat. Utilizati optiunea 3 mai intai." << endl;
            } else {
                afisareDrum(predMax, distMax, "Drumul maxim"); // afisam drumul maxim
            }
            meniu();
            break;
        case 0:
            cout << "Iesire din program." << endl; // iesim din program
            break;
        default:
            cout << "Optiune invalida." << endl; // optiune inexistenta
            meniu();
    }
}

// functia main - punctul de start al programului
int main() {
    meniu(); // apelam meniul
    return 0;
}
