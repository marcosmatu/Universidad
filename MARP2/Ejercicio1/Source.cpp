
//Marcos Matute Fernández

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include "EnterosInf.h"

using namespace std;


// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...

long long int numManeras(vector<int> longitud, int L) {
    long long int n = longitud.size();
    vector<long long int> numManeras(L + 1,0);
    numManeras[0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = L; j >= 1; j--) {
            if (longitud[i - 1] <= j) {
                numManeras[j] = numManeras[j] + numManeras[j - longitud[i - 1]];
            }
        }
    }
    return numManeras[L];
}


EntInf minCuerdas(vector<int> longitud, int L) {
    long long int n = longitud.size();
    vector<EntInf> numCuerdas(L + 1, Infinito);
    numCuerdas[0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = L; j >= 1; j--) {
            if (longitud[i - 1] <= j) {
                numCuerdas[j] = min(numCuerdas[j], numCuerdas[j - longitud[i - 1]] + 1);
            }
        }
    }
    return numCuerdas[L];
}

EntInf minCoste(vector<int> longitud, vector<int> coste, int L) {
    long long int n = longitud.size();
    vector<EntInf> costeC(L + 1, Infinito);
    costeC[0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = L; j >= 1; j--) {
            if (longitud[i - 1] <= j) {
                costeC[j] = min(costeC[j], costeC[j - longitud[i - 1]] + coste[i-1]);
            }
        }
    }
    return costeC[L];
}


// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    int numCuerdas, L;
    vector<int> longitud;
    vector<int> coste;
    int aux;
    cin >> numCuerdas;
    cin >> L;

    for (int i = 0; i < numCuerdas; i++) {
        cin >> aux;
        longitud.push_back(aux);
        cin >> aux;
        coste.push_back(aux);
    }

    if (!std::cin)  // fin de la entrada
        return false;
    long long int maneras = numManeras(longitud, L);

    if (maneras > 0) cout << "SI" << " "<< maneras << " " << minCuerdas(longitud,L) << " " << minCoste(longitud,coste,L) <<'\n';
    else cout << "NO\n";
    

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
