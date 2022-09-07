
// Marcos Matute Fernández

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

/*
minEsfuerzo(i,j) devuelve el mínimo esfuerzo necesario para cortar el fragmento de tronco que se extiende entre los cortes i y j, siendo 0 <= i <= j <= n + 1

CASOS BASE:

minEsfuerzo(i, i+ 1) = 0 para todo i, 0 <= i <= n;


j > i + 1 entonces:
minEsfuerzo(i, j) = 2 * (longitud[j] - longitud[i]) + min(minEsfuerzo(i,k) + minEsfuerzo(k,j) | i < k < j)

*/
#include <iostream>
#include <fstream>
#include<vector>
#include <algorithm>


using namespace std;

int minEsfuerzo[600][600];
int corte[600][600];

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
int resolver(vector<int> longitud) {
    int n = longitud.size();
    int j, k, minimo,temp;
    for (int i = 0; i < n  + 1; i++) {
        minEsfuerzo[i][i] = 0;
    }
    /*
    int i = n - 1;
    while (i >= 0) {
        j = i + 2;
        while (j <= n + 1) {
            minimo = 9999999999;
            k = i + 1;
            while (k < j) {
                temp = minEsfuerzo[i][k] + minEsfuerzo[k][j];
                if (temp < minimo) {
                    minimo = temp;
                }
                k++;
            }
            minEsfuerzo[i][j] = (longitud[j] - longitud[i]) * 2 + minimo;
            j++;
        }
        i--;
    }
    */


        for (int d = 2; d < n ; d++) {
            for (int i = 0; i < n -d ; i++) {
                j = i + d;
                minimo = 9999999999;
                for (int k = i + 1; k < j; k++) {
                    temp = minEsfuerzo[i][k] + minEsfuerzo[k][j];
                    if (temp < minimo) {
                        minimo = temp;
                    }
                }
                minEsfuerzo[i][j] = (longitud[j] - longitud[i]) * 2 + minimo;
            }
           
        }
    
    return minEsfuerzo[0][n-1];
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    int L, N, aux;
    vector<int> longitud;
    cin >> L;
    cin >> N;


    if(L == 0 && N == 0)
        return false;

    else {
        longitud.push_back(0);
        for (int i = 0; i < N; i++) {
            cin >> aux;
            longitud.push_back(aux);
        }
        longitud.push_back(L);
    }



    int sol = resolver(longitud);

    cout << sol << '\n';

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
