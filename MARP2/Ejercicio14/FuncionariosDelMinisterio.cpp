
// Nombre y Apellidos

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include<climits>

using namespace std;
// propios o los de las estructuras de datos de clase

int tareas[20][20];

struct Nodo {
    vector<int> sol;
    vector<bool> marcaje;
    int k;
    int beneficio; //tiempo acumulado de tareas
    int beneficio_est; //Prioridad
    bool operator<(Nodo const& otro) const {
        return otro.beneficio_est < beneficio_est;
    }
};


/*Para cada funcionario recorremos su fila y le elegimos la tarea que menos tarda en hacer aunque ya este elegida*/
int calculo_voraz(Nodo const& X, int N) {
    int estimacion = X.beneficio;
    int i = X.k + 2;
    int min = tareas[i][0];
    while (i < N) {
        for (int j = 0; j < N; j++) {
            if (min > tareas[i][j]) min = tareas[i][j];
        }
        estimacion += min;
        i++;
        min = tareas[i][0];
    }
    return estimacion;
}

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
void resolver(int N, vector<int>& sol_mejor, vector<int> estimados, int& beneficio_mejor) {

    Nodo Y;
    Y.sol = vector<int>(N);
    Y.marcaje = vector<bool>(N, false);
    Y.k = -1;
    Y.beneficio = 0;
    Y.beneficio_est = calculo_voraz(Y, N);
    priority_queue<Nodo> cola;
    cola.push(Y);
    beneficio_mejor = 9999999;
    while (!cola.empty() && cola.top().beneficio_est < beneficio_mejor) {
        Y = cola.top(); cola.pop();
        Nodo X(Y);
        ++X.k;

        //Generamos los hijos en función de las tareas
        for (int i = 0; i < N; i++) {
            if (!X.marcaje[i]) {
                X.marcaje[i] = true;
                X.sol[X.k] = i;
                X.beneficio = Y.beneficio + tareas[X.k][i];
                X.beneficio_est = X.beneficio + estimados[X.k];




                if (X.beneficio_est < beneficio_mejor) {
                    if (X.k == N - 1) {
                        sol_mejor = X.sol;
                        beneficio_mejor = X.beneficio;
                    }
                    else {
                        cola.push(X);
                    }
                }
                X.marcaje[i] = false;
                X.beneficio = Y.beneficio;

            }
        }

    }


}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    int N, aux;

    cin >> N;
    if (N == 0)
        return false;

    vector<int> minimos(N, INT_MAX);
    vector<int> estimaciones(N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> aux;
            tareas[i][j] = aux;
            if (tareas[i][j] < minimos[i])minimos[i] = tareas[i][j];
        }
    }

    vector<int> sol(N);
 
    int beneficion_mejor;
    estimaciones[N - 1] = 0;
    for (int i = N - 2; i >= 0; i--) {
        estimaciones[i] = estimaciones[i + 1] + minimos[i + 1];
    }
    resolver(N, sol,estimaciones, beneficion_mejor);

    cout << beneficion_mejor << '\n';
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
