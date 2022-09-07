
// Nombre y Apellidos

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>


using namespace std;


// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...


struct Nodo {
    vector<bool> sol;
    vector<bool> marcaje;
    int k;
    int beneficio; //tiempo acumulado de tareas
    int beneficio_est; //Prioridad
    bool operator<(Nodo const& otro) const {
        return otro.beneficio_est > beneficio_est;
    }
};

double calculo_voraz(vector<int> const& maximos, int carros, Nodo const& X) {
    int estimacion = X.beneficio;
    int i = X.k + 1;
    if (X.k != carros - 1) {
        while (i < carros) {

            estimacion += maximos[i];
            ++i;
        }
    }
    return estimacion;
}

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
void resolver(int carros,int caminos, vector<bool>& sol_mejor, vector<int> maximos, int& beneficio_mejor, vector<int> anchuraCarros, vector<int> anchuraCaminos, vector<vector<int>> const& calidad) {

    Nodo Y;
    Y.marcaje = vector<bool>(caminos, false);
    Y.sol = vector<bool>(carros, -false);
    Y.k = -1;
    Y.beneficio = 0;
    Y.beneficio_est = calculo_voraz(maximos, carros, Y);
    priority_queue<Nodo> cola;
    cola.push(Y);
    beneficio_mejor = INT_MIN;

    // búsqueda mientras pueda haber algo mejor
    while (!cola.empty() && cola.top().beneficio_est > beneficio_mejor) {

        Y = cola.top();
        cola.pop();
        Nodo X(Y);
        ++X.k;

        // probamos a asignar esta máquina a cada camino.
        for (int i = 0; i < caminos; i++) {
            if (!X.marcaje[i] && anchuraCaminos[i] >= anchuraCarros[X.k]) {
                X.marcaje[i] = true;
                X.sol[X.k] = i;
                X.beneficio = Y.beneficio + calidad[X.k][i];
                X.beneficio_est = calculo_voraz(maximos, carros, X);
                if (X.beneficio_est > beneficio_mejor) {
                    if (X.k == carros - 1) {
                        sol_mejor = X.sol;
                        beneficio_mejor = X.beneficio;
                    }
                    else cola.push(X);
                }
                X.sol[X.k] = -1;
                X.marcaje[i] = false;
                X.beneficio = Y.beneficio;
            }

        }
        X.beneficio = Y.beneficio;
        X.beneficio_est = calculo_voraz(maximos, carros, X);
        if (X.beneficio_est > beneficio_mejor) {
            if (X.k == carros - 1) {
                sol_mejor = X.sol;
                beneficio_mejor = X.beneficio;
            }
            else cola.push(X);
        }

    }
        
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {

    int carros, caminos, aux;
    vector<int> anchuraCarros, anchuraCaminos;

    cin >> carros;
    cin >> caminos;

    vector<vector<int>> calidad(carros, vector<int>(caminos));
    vector<int> maximos(carros, -1);

    for (int i = 0; i < carros; i++) {
        cin >> aux;
        anchuraCarros.push_back(aux);
    }

    for (int i = 0; i < caminos; i++) {
        cin >> aux;
        anchuraCaminos.push_back(aux);
    }

    for (int i = 0; i < carros; i++) {
        for (int j = 0; j < caminos; j++) {
            cin >> calidad[i][j];
            if (calidad[i][j] > maximos[i])maximos[i] = calidad[i][j];
        }
    }

    int beneficion_mejor;
    vector<bool> sol(carros);
    if (carros == 0) cout << "0\n";
    else {
        resolver(carros, caminos, sol, maximos, beneficion_mejor, anchuraCarros, anchuraCaminos, calidad);

        cout << beneficion_mejor << '\n';
    }
    // escribir solución
}

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    /*srand(time(NULL));
    while (true) resuelveCasoCamion();*/
    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i) {
        resuelveCaso();
    }

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
