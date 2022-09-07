
//Marcos Matute Fernández

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

const int MAX_OXIGENO = 10000;
const int MAX_COFRES = 10000;

int cofre[MAX_COFRES][MAX_OXIGENO];

/*
*   Casos base:     cofre[i][0] = 0     0 <= i <= numCofres
*                   cofre[0][i] = 0     0 <= i <= T
* 
*   Recurrencia:    cofre[i][j] = cofre[i - 1][j]                                                                    j < profundidad[i - 1] * 3
*                   cofre[i][j] = max(cofre[i - 1][j], cofre[i - 1][j - (profundidad[i - 1] * 3)] + botin[i - 1])    j >= profundidad[i - 1] * 3
*/

vector<bool> resolver(vector<int> profundidad, vector<int> botin, int T) {
    //Casos base
    for (int i = 0; i <= T; i++) {
        cofre[0][i] = 0;
    }

    for (int i = 0; i <= profundidad.size(); i++) {
        cofre[i][0] = 0;
    }

    //Recurrencia
    for (int i = 1; i <= profundidad.size(); i++) {
        for (int j = 1; j <= T; j++) {
            if (j < profundidad[i - 1] * 3) cofre[i][j] = cofre[i - 1][j];
            else cofre[i][j] = max(cofre[i - 1][j], cofre[i - 1][j - (profundidad[i - 1] * 3)] + botin[i - 1]);
        }
    }

    //Calculo de los objetos
    int i = profundidad.size(), j = T;

    vector<bool> sol(profundidad.size(), false);

    while (i > 0 && j > 0) {
        if (cofre[i][j] != cofre[i - 1][j]) {
            sol[i - 1] = true;  j = j - profundidad[i - 1] * 3;
        }
        --i;
    }

    return sol;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    int T, numCofres, aux;
    cin >> T;
    cin >> numCofres;
    vector<int> profundidad;
    vector<int> botin;

    for (int i = 0; i < numCofres; i++) {
        cin >> aux;
        profundidad.push_back(aux);
        cin >> aux;
        botin.push_back(aux);
    }

    if (!std::cin)  // fin de la entrada
        return false;

    vector<bool> sol = resolver(profundidad, botin, T);
    int cont = 0;

    for (int i = 0; i < sol.size(); i++) {
        if (sol[i] == true) cont++;
    }

    cout << cofre[profundidad.size()][T] << '\n';
    cout << cont << '\n';

    for (int i = 0; i < sol.size(); i++) {
        if (sol[i] == true) {
            cout << profundidad[i] << " " << botin[i] << '\n';
        }
    }
    cout << "---\n";

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