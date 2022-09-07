
//Marcos Matute Fernández

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

using namespace std;

int tablero[501][501];
int sol[501][501];

/*
*   maxPunt(i,j) = max(maxPunt(i-1,j), maxPunt(i-1,j+1)) + TAB(i,j) si j = 0
*   max(maxPunt(i-1,j-1), maxPunt(i-1,j),maxPunt(i-1,j+1)) + TAB(i,j) si 0 < j < N
*   max(maxPunt(i-1,j-1), maxPunt(i-1,j)) + TAB(i,j) si j = N 
*/
pair<int, int> resolver(int N) {

    for (int i = 0; i < N; i++) {
        sol[0][i] = tablero[0][i];
    }

    for (int i = 1; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (j == 0) sol[i][j] = max(sol[i - 1][j], sol[i - 1][j + 1]) + tablero[i][j];
            else if (j == N - 1)sol[i][j] = max(sol[i - 1][j], sol[i - 1][j - 1]) + tablero[i][j];
            else sol[i][j] = max(max(sol[i - 1][j], sol[i - 1][j + 1]), sol[i - 1][j - 1]) + tablero[i][j];
        }
    }

    pair<int, int> solucion = make_pair(sol[N - 1][0], 1);

    for (int i = 1; i < N; i++) {
        if (sol[N - 1][i] > solucion.first) {
            solucion.first = sol[N - 1][i];
            solucion.second = i + 1;
        }
    }
    return solucion;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    int N, aux;
    cin >> N;


    if (!std::cin)  // fin de la entrada
        return false;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> aux;
            tablero[i][j] = aux;
        }
    }

    pair<int, int> sol = resolver(N);

    cout << sol.first << ' ' << sol.second << '\n';

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
