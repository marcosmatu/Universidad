#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

/*
int resolver(int N, int C, vector<int> valores, vector<int> monedas){
    vector<vector<int>> minCoste(N+1, vector<int>(C+1,0));
    for (int j = 1; j <= C; j++) minCoste[0][j] = 100000;

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= C; j++) {
            for (int k = 1; k <= monedas[i - 1] ; k++) {
                if (j >= k * valores[i - 1]) {
                    minCoste[i][j] = min(minCoste[i - 1][j], minCoste[i - 1][j - k * valores[i - 1]] + k);
                }
                else {
                    minCoste[i][j] = minCoste[i - 1][j];
                }

            }
        }
    }
    return minCoste[N][C];
}
*/
int resolver(int N, int C, vector<int> valores, vector<int> monedas) {
    vector<int> V(C + 1, 100000);
    V[0] = 0;

    for (int i = 1; i <= N; i++) {
        for (int j = C; j >= 0; j--) {
            for (int k = 1; k <= monedas[i - 1]; k++) {
                if (j >= k * valores[i - 1]) {
                    V[j] = min(V[j - k * valores[i - 1]] + k, V[j]);
                }
               

            }
        }
    }
    return V[C];
}
/*
int resolver(int N, int C, vector<int> valores, vector<int> monedas) {

    vector<int> V(C + 1, 100000);
    V[0] = 0;


    for (int i = 1; i < N + 1; i++) {
        for (int j = C; j >= 0; j--) {
            for (int k = 1; k <= monedas[i - 1] && (j - k * valores[i - 1] >= 0); k++) {
                int tmp = V[j - k * valores[i - 1]] + k;
                V[j] = min(tmp, V[j]);
            }
        }
    }

    return V[C];
}
*/

bool resuelveCaso() {

    // leer los datos de la entrada
    int N, aux, C;
    vector<int> valores;
    vector<int> monedas;

    cin >> N;

    for (int i = 0; i < N; i++) {
        cin >> aux;
        valores.push_back(aux);
    }

    for (int i = 0; i < N; i++) {
        cin >> aux;
        monedas.push_back(aux);
    }



    cin >> C;

    if (!std::cin)  // fin de la entrada
        return false;

    int sol = resolver(N, C, valores, monedas);



    if (sol == 100000) cout << "NO \n";
    else cout << "SI " << sol << '\n';
    // escribir sol

    return true;
}

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}