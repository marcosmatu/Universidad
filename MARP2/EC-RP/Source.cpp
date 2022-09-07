
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
    int k; //Nivel actual
    vector<int> marcaje; // Capacidades actuales de cada hospital
    int coste; // Coste actual de la solucion
    int coste_optimista; // Coste estimado.


    //Cola de minimos
    bool operator<(Nodo const& otro) const {
        return otro.coste_optimista < coste_optimista;
    }

};


double calculo_estimacion(vector<int> const& minimos, Nodo const& X) {
    double estimacion = X.coste;
    for (int i = X.k + 1; i < minimos.size(); ++i) {
       
            estimacion += minimos[i];
        
    }
    return estimacion;
}

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...

void resolver(vector<vector<int>> const& distanciaH, vector<int> const& minimos, int numH, int numP, vector<int> capacidadH, int& coste_mejor, vector<int> const& maximos) {

    Nodo Y;
    Y.k = -1;
    Y.marcaje = vector<int>(capacidadH);
    Y.coste = 0;
    Y.coste_optimista = calculo_estimacion(minimos, Y);
    coste_mejor = INT_MAX; //Se inicializa al INT_MAX porque estamos minimizando.
    priority_queue<Nodo> cola;
    cola.push(Y);

    while (!cola.empty() && cola.top().coste_optimista <= coste_mejor) {

        Y = cola.top(); cola.pop();
        Nodo X(Y);
        X.k++;

        for (int i = 0; i < numH; i++) {
            //Comprobamos si podemos asignar la persona k al hospital i (si es factible).
            if (X.marcaje[i] > 0) {
                //Marcamos el hijo con sus nuevas propiedades.
                X.marcaje[i]--;
                X.coste += distanciaH[X.k][i];
                X.coste_optimista = calculo_estimacion(minimos, X);

                //Comprobamos si es prometedor

                if (X.coste_optimista <= coste_mejor) {
                    if (X.k == numP - 1) {
                        coste_mejor = X.coste;

                    }
                    else {
                        cola.push(X);

                    }
                }
                //Desmarcamos para dejarlo como estaba.
                X.marcaje[i]++;
                X.coste = Y.coste;

            }

        }

    }
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {

    // leer los datos de la entrada
    int numP, numH;
    cin >> numP;
    cin >> numH;

    vector<int> capacidadH(numH);
    for (int i = 0; i < numH; i++) {
        cin >> capacidadH[i];
    }
    vector<vector<int>> distanciaH(numP, vector<int>(numH));
    vector<int> minimos(numP,9999999);
    vector<int> maximos(numP);
    for (int i = 0; i < numP; i++) {
        for (int j = 0; j < numH; j++) {
            cin >> distanciaH[i][j];
            if (distanciaH[i][j] < minimos[i]) minimos[i] = distanciaH[i][j];
            if (distanciaH[i][j] > maximos[i]) maximos[i] = distanciaH[i][j];
        }
    }
    int coste_mejor;

    resolver(distanciaH, minimos, numH, numP, capacidadH, coste_mejor, maximos);

    cout << coste_mejor *2 << '\n';

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
