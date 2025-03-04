#include <iostream>
#include <vector>

using namespace std;

const int INF = 100;
int nr_varfuri, nr_muchii, start;
vector<vector<int>> graf;
vector<int> distMin, predMin, distMax, predMax;

void introducereGraf() {
    cout << "Numarul de varfuri si muchii: " << endl;
    cin >> nr_varfuri >> nr_muchii;
    graf.assign(nr_varfuri + 1, vector<int>(nr_varfuri + 1, -INF));
    for (int i = 1; i <= nr_varfuri; i++) graf[i][i] = 0;

    cout << "Muchii (start sfarsit cost):" << endl;
    for (int i = 0; i < nr_muchii; i++) {
        int x, y, cost;
        cin >> x >> y >> cost;
        if (x >= 1 && x <= nr_varfuri && y >= 1 && y <= nr_varfuri) graf[x][y] = cost;
        else {
            cout << "Muchie invalida, reintroduceti." << endl;
            i--;
        }
    }
}

void bellmanFord(bool minim) {
    vector<int> &dist = minim ? distMin : distMax;
    vector<int> &pred = minim ? predMin : predMax;

    dist.assign(nr_varfuri + 1, minim ? INF : -INF);
    pred.assign(nr_varfuri + 1, -1);
    dist[start] = 0;

    for (int k = 1; k < nr_varfuri; k++) {
        for (int i = 1; i <= nr_varfuri; i++) {
            for (int j = 1; j <= nr_varfuri; j++) {
                if (graf[i][j] != -INF && dist[i] != (minim ? INF : -INF)) {
                    int nouDist = dist[i] + graf[i][j];
                    if ((minim && nouDist < dist[j]) || (!minim && nouDist > dist[j])) {
                        dist[j] = nouDist;
                        pred[j] = i;
                    }
                }
            }
        }
    }
}

void afisareDrum(vector<int> &pred, vector<int> &dist, string tip) {
    int destinatie;
    cout << "Nod final: " << endl;
    cin >> destinatie;
    if (destinatie < 1 || destinatie > nr_varfuri || pred[destinatie] == -1) {
        cout << "Drum inexistent!" << endl;
        return;
    }
    cout << tip << " de la " << start << " la " << destinatie << ": " << dist[destinatie] << endl;
    cout << "Drumul: ";
    for (int v = destinatie; v != -1; v = pred[v]) cout << v << " ";
    cout << endl;
}

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
            introducereGraf();
            meniu();
            break;
        case 2:
            if (nr_varfuri == 0 || nr_muchii == 0) {
                cout << "Graful nu a fost introdus. Utilizati optiunea 1 mai intai." << endl;
            } else {
                cout << "Start: " << endl;
                cin >> start;
                if (start < 1 || start > nr_varfuri) {
                    cout << "Nod invalid!" << endl;
                } else {
                    bellmanFord(true);
                    cout << "Drumul minim a fost calculat. Utilizati optiunea 4 pentru afisare." << endl;
                }
            }
            meniu();
            break;
        case 3:
            if (nr_varfuri == 0 || nr_muchii == 0) {
                cout << "Graful nu a fost introdus. Utilizati optiunea 1 mai intai." << endl;
            } else {
                cout << "Start: " << endl;
                cin >> start;
                if (start < 1 || start > nr_varfuri) {
                    cout << "Nod invalid!" << endl;
                } else {
                    bellmanFord(false);
                    cout << "Drumul maxim a fost calculat. Utilizati optiunea 5 pentru afisare." << endl;
                }
            }
            meniu();
            break;
        case 4:
            if (distMin.empty()) {
                cout << "Drumul minim nu a fost calculat. Utilizati optiunea 2 mai intai." << endl;
            } else {
                afisareDrum(predMin, distMin, "Drumul minim");
            }
            meniu();
            break;
        case 5:
            if (distMax.empty()) {
                cout << "Drumul maxim nu a fost calculat. Utilizati optiunea 3 mai intai." << endl;
            } else {
                afisareDrum(predMax, distMax, "Drumul maxim");
            }
            meniu();
            break;
        case 0:
            cout << "Iesire din program." << endl;
            break;
        default:
            cout << "Optiune invalida." << endl;
            meniu();
    }
}

int main() {
    meniu();
    return 0;
}
