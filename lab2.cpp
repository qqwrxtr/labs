#include <iostream>
#include <vector>

using namespace std;

const int INF = 100; // constanta pentru infinit, folosita pentru distante
int nr_varfuri, nr_muchii, start; // variabile globale pentru nr de noduri, muchii si nodul de start
vector<vector<int>> graf; // matrice de adiacenta pentru stocarea grafului
vector<int> distMin, predMin, distMax, predMax; // vectori pentru distante minime/maxime si predecesori

// functie pentru citirea grafului
void introducereGraf() {
    cout << "Numarul de varfuri si muchii: " << endl;
    cin >> nr_varfuri >> nr_muchii;
    
    // initializam matricea de adiacenta cu -INF (indica lipsa muchiei)
    graf.assign(nr_varfuri + 1, vector<int>(nr_varfuri + 1, -INF));
    
    // distanta de la un nod la el insusi e 0
    for (int i = 1; i <= nr_varfuri; i++) graf[i][i] = 0;

    cout << "Muchii (start sfarsit cost):" << endl;
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

// implementare algoritm bellman-ford pentru drum minim/maxim
// parametrul minim = true pentru drum minim, false pentru drum maxim
void bellmanFord(bool minim) {
    // referinte catre vectorii corespunzatori (minim sau maxim)
    vector<int> &dist = minim ? distMin : distMax;
    vector<int> &pred = minim ? predMin : predMax;

    // initializam vectorii de distante si predecesori
    dist.assign(nr_varfuri + 1, minim ? INF : -INF); // pentru minim initializam cu INF, pentru maxim cu -INF
    pred.assign(nr_varfuri + 1, -1); // -1 inseamna ca nu exista predecesor
    dist[start] = 0; // distanta de la start la start e 0

    // aplicam algoritmul bellman-ford (n-1 iteratii)
    for (int k = 1; k < nr_varfuri; k++) {
        for (int i = 1; i <= nr_varfuri; i++) {
            for (int j = 1; j <= nr_varfuri; j++) {
                // verificam daca exista muchie si daca nodul i e accesibil
                if (graf[i][j] != -INF && dist[i] != (minim ? INF : -INF)) {
                    int nouDist = dist[i] + graf[i][j];
                    
                    // actualizam distanta daca e mai buna (mai mica pentru minim, mai mare pentru maxim)
                    if ((minim && nouDist < dist[j]) || (!minim && nouDist > dist[j])) {
                        dist[j] = nouDist;
                        pred[j] = i; // actualizam predecesorul
                    }
                }
            }
        }
    }
}

// functie pentru afisarea drumului catre o destinatie
void afisareDrum(vector<int> &pred, vector<int> &dist, string tip) {
    int destinatie;
    cout << "Nod final: " << endl;
    cin >> destinatie;
    
    // verificam daca destinatia e valida si accesibila
    if (destinatie < 1 || destinatie > nr_varfuri || pred[destinatie] == -1) {
        cout << "Drum inexistent!" << endl;
        return;
    }
    
    // afisam costul drumului
    cout << tip << " de la " << start << " la " << destinatie << ": " << dist[destinatie] << endl;
    
    // afisam drumul (in ordine inversa, de la destinatie la start)
    cout << "Drumul: ";
    for (int v = destinatie; v != -1; v = pred[v]) cout << v << " ";
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
                cout << "Start: " << endl;
                cin >> start;
                
                // verificam daca nodul de start e valid
                if (start < 1 || start > nr_varfuri) {
                    cout << "Nod invalid!" << endl;
                } else {
                    bellmanFord(true); // calculam drumul minim
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
                cout << "Start: " << endl;
                cin >> start;
                
                // verificam daca nodul de start e valid
                if (start < 1 || start > nr_varfuri) {
                    cout << "Nod invalid!" << endl;
                } else {
                    bellmanFord(false); // calculam drumul maxim
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
            cout << "Iesire din program." << endl; // terminam programul
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
