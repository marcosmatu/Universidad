
// Nombre y Apellidos

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;


struct Nodo {
    vector<int> sol;
    int k;
    vector<bool> asientos_asignados;
    double beneficio; // valor acumulado
    double beneficio_opt; // prioridad
    bool operator<(Nodo const& otro) const {
        return otro.beneficio_opt > beneficio_opt;
    }
};

bool calculoPareja(vector<vector<double>> const& distancias, vector<vector<int>> const& allegados, Nodo  X,int i, int &numParejas) {
    //Posibles casos que sean allegados y cumplan la distancia entonces se suma uno a las parejas, que no sean allegados y no cumplan la distancia en cuyo caso no es solucion valida
    //y que no sean allegados pero cumplan la distancia en cuyo caso es solución parcial valida pero no forma una pareja de allegados.
    for (int j = 0; j < X.k; j++) {
        if (allegados[X.k][j] == 0 && distancias[i][X.sol[j]] < 2) return false; // caso 1
        if (allegados[X.k][j] == 1 && distancias[i][X.sol[j]] < 2) numParejas++; // caso 2 tenemos otra pareja
    }
    //El caso 3 no hace falta contemplarlo por eso ponemos un return true al final
    return true;
}

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
void resolver(vector<vector<double>> const& distancias, vector<vector<int>> const& allegados, vector<int>const& opt, int m, int n, vector<int> sol_mejor, int& coste_mejor) {
    Nodo Y;
    Y.sol = vector<int>(m);
    Y.k = -1;
    Y.beneficio = 0;
    Y.asientos_asignados = vector<bool>(n, false);
    Y.beneficio_opt = opt[0];
    priority_queue<Nodo> cola;
    cola.push(Y);
    coste_mejor = INT_MIN;
    while (!cola.empty() && cola.top().beneficio_opt > coste_mejor) {
        Y = cola.top(); cola.pop();
        Nodo X(Y);
        ++X.k;
        for (int i = 0; i < n; i++) {
            int numParejas = 0;
            if (!X.asientos_asignados[i] && calculoPareja(distancias, allegados, X, i, numParejas)) {
                X.sol[X.k] = i;
                X.asientos_asignados[i] = true;
                X.beneficio = Y.beneficio + numParejas;
                X.beneficio_opt = X.beneficio + opt[X.k];
                if (X.k == m - 1) {
                    if (X.beneficio > coste_mejor) {
                        sol_mejor = X.sol;
                        coste_mejor = X.beneficio;
                    }
                }
                else {

                    cola.push(X);
                }
                X.asientos_asignados[i] = false;
                X.beneficio = Y.beneficio;
            }
        }
    }
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    int plazas, comensales;
    cin >> plazas;
    cin >> comensales;
    // leer los datos de la entrada
    vector<vector<double>> distancia(plazas, vector<double>(plazas));
    vector<vector<int>> alla(comensales, vector<int>(comensales));
    vector<int> optimista(comensales);
    for (int i = 0; i < plazas; i++) {
        for (int j = 0; j < plazas; j++) {
            cin >> distancia[i][j];
        }
    }

    for (int i = 0; i < comensales; i++) {
        for (int j = 0; j < comensales; j++) {
            cin >> alla[i][j];
        }
    }
    int sumalla = 0;
    for (int i = comensales - 1; i >= 0; i--) {
        optimista[i] = sumalla;
        for (int j = 0; j < i; j++) {
            if (alla[i][j] == 1) {
                sumalla++;
            }
        }
    }

    vector<int> sol(comensales);
    int coste_mejor;
    resolver(distancia, alla, optimista, comensales, plazas, sol, coste_mejor);

    if (coste_mejor <= 0)
        cout << "CANCELA\n";
    else
        cout << "PAREJAS " << coste_mejor << '\n';

    // escribir solución
}

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
