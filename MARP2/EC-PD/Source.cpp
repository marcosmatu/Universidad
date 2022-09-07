
// Nombre y Apellidos

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

using namespace std;

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
int resolver(vector<vector<int>> &sol,int i, int j,vector<int> bizcocho) {
    if (i >= j)return 0;

    if (sol[i][j] == -1) {

        int centro = resolver(sol, i + 1, j - 1, bizcocho) + 1;
        int derecha = resolver(sol, i, j - 2, bizcocho);
        int izquierda = resolver(sol, i + 2, j, bizcocho);

        sol[i][j] = max(centro, max(izquierda, derecha));
    }
    return sol[i][j];
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    int N;
   
    cin >> N;
    if (!std::cin)  // fin de la entrada
        return false;

    vector<int> bizcocho(N);
    for (int i = 0; i < N; i++) {
        cin >> bizcocho[i];
    }
    vector<vector<int>>sol(N,vector<int>(N,-1));
    cout << resolver(sol,0,bizcocho.size() - 1,bizcocho) << endl;

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
