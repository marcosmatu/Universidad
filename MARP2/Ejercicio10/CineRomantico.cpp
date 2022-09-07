
// Nombre y Apellidos

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

//int cine[10000][10000];

/*
cine(i,j) = cantidad de minutos viendo peliculas de i hasta n con j minutos al día

cine(0,j) = 0

cine(i,j) = cine(i-1,j)

cine(i,j) = max(cine(i-1,j), cine(i-1,pelis(i)) + duracion(i) si j >= pelis[i] + duracion[i] + 10


*/


// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
int resolver(vector <pair<int, int>> pelis, int N) {
    vector<int> cine(1451,0);


    for (int i = 1; i < N + 1; i++) {
        for (int j = 0; j <= 1450; j++) {
            if (j >= pelis[i - 1].first + pelis[i - 1].second + 10) {
                cine[j] = max(cine[j], cine[pelis[i - 1].first] + pelis[i - 1].second);
            }
            
        }
    }

    return cine[1450];
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    int N;
    cin >> N;

    if (N == 0)
        return false;


    char aux;
    int horas, minutos, dur, ini;
    vector <pair<int, int>> pelis;
    for (int i = 0; i < N; ++i) {
        cin >> horas >> aux >> minutos >> dur;
        ini = horas * 60 + minutos;
        pelis.push_back({ ini, dur });
    }

    sort(pelis.begin(), pelis.end());
    int sol = resolver(pelis, N);

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
