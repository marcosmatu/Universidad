
// Nombre y Apellidos

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <math.h>
#include "EnterosInf.h"
using namespace std;

int minBombillas[1001][1001];


/*
*   Casos base: minBombillas[0][j] = INF    0 <= j <= PMax
*               minbombillas[i][0] = 0      1 <= i <= N
* 
*   Casos recursivos: minBombillas[i][j] = minBombillas[i-1][j]     potencia[i-1] > j
*                     minBombillas[i][j] = min(minBombillas[i-1][j], minBombillas[i][j - potencia[i-1]] + coste[i-1])
*
*/
void resolver(vector<int> potencia, vector<int> coste, int Pmax, int Pmin) {
    for (int j = 0; j <= Pmax; j++) {

        minBombillas[0][j] = EntInf::_intInf;

    }
    vector<int> minB(Pmax + 1, EntInf::_intInf);
    minB[0] = 0;
    for (int i = 1; i <= coste.size(); i++) {
        for (int j = 1; j <= Pmax; j++) {
            if (potencia[i - 1] > j) {
                minB[j] = minB[j];
            }
            else {
                minB[j] = min(minB[j], minB[j - potencia[i - 1]] + coste[i - 1]);
            }
        }
    }

    int min = EntInf::_intInf;
    int j = 0;

    for (int i = Pmin; i <= Pmax; i++) {
        if (minB[i] < min) {
            j = i;
            min = minB[i];
        }
    }
 
    if (min == EntInf::_intInf) cout << "IMPOSIBLE\n";
    else cout << min << ' ' << j << '\n';

    
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    int N, Pmax, Pmin, aux;
    vector<int> potencia;
    vector<int> coste;
    cin >> N;
    if (!std::cin)  // fin de la entrada
        return false;
    cin >> Pmax;
    cin >> Pmin;
    for (int i = 0; i < N; i++) {
        cin >> aux;
        potencia.push_back(aux);
    }

    for (int i = 0; i < N; i++) {
        cin >> aux;
        coste.push_back(aux);
    }

    resolver(potencia, coste, Pmax, Pmin);
    
   // pair<int, int> sol = resolver(potencia, coste, Pmax, Pmin);


    
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
