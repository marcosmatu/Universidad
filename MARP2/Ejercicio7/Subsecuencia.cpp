
//Marcos Matute Fernández

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <math.h>

int S[1001][1001];
using namespace std;

/*

*/
void resolver(string const& X, string const& Y) {
    for (int i = 1; i <= X.length(); i++) {
        for (int j = 1; j <= Y.length(); j++) {
            if (X[i - 1] == Y[j - 1]) {
                S[i][j] = S[i - 1][j - 1] + 1;
            }
            else {
                S[i][j] = max(S[i - 1][j], S[i][j - 1]);
            }
        }
    }
}

string reconstruir(string const& X, string const& Y, int i, int j) {

    if (i == 0 || j == 0)return{};
    else if (X[i - 1] == Y[j - 1]) return reconstruir(X, Y,  i - 1, j - 1) +  X[i - 1];
    else {
        if (S[i][j - 1] > S[i - 1][j]) return reconstruir(X, Y,  i, j - 1);
        else return reconstruir(X, Y,  i - 1, j);
    }

}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada

    string X, Y;
    cin >> X;
    cin >> Y;
    if (!std::cin)  // fin de la entrada
        return false;

   // Matriz<int> S(X.length()+1, Y.length()+1, 0);

    resolver(X,Y);
    cout << reconstruir(X,Y,X.length(),Y.length()) << '\n';

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
