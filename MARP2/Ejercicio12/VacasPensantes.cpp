
// Nombre y Apellidos

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>


using namespace std;

int sol[1001][1001];

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...

/*
* 
*   sol(i,j) : máxima comida que va ha poder comer la vaca desde los cubos i hasta el j
*   
*   Casos base:
*      sol(i,i) = cubos[i]    0 <= i < N
*      sol(i+1, i) = max(cubos[i],cubos[j])
*   
*   Rescursion:
*       devoradora:
*           cubos[i] > cubos[j] : sol(i+1,j)
*           cubos[i] < cubos[j] : sol(i,j-1)
*       
*       vaca:
*           max(sol(i+1,j) + cubos[i], sol(i,j-1) + cubos[j]
* 
*  Llamada inicial:
*       sol(cubos,0,N-1)
* 
* 
*/

int vaca1(vector <int> const& cubos, int i, int j);
/*
int devoradora(vector <int> const& cubos, int i, int j) {
    int& res = sol[i][j];

    if (res == -1) {
        if (cubos[i] > cubos[j])
            res = vaca1(cubos,  i + 1, j);

        else res = vaca1(cubos, i, j - 1);
    }
    return res;
}

int vaca1(vector <int> const& cubos, int i, int j) {
    int& res = sol[i][j];

    if (res == -1) {
        if (i == j)
            res = cubos[i];
        else if (i + 1 == j)
            res = max(cubos[i], cubos[j]);
        else
            res = max(devoradora(cubos,  i + 1, j) + cubos[i],
                devoradora(cubos,  i, j - 1) + cubos[j]);
    }
    return res;
}
*/

int resolver(vector<int> cubos, int i, int j, int turno) {
    int& res = sol[i][j];
    if (res != -1)
        return res;
    if (i == j && turno % 2 == 0)
        return cubos[i];
    else if (i + 1 == j && turno % 2 == 0)
        return max(cubos[i], cubos[j]);
    else {
        if (turno % 2 != 0 && cubos[i] > cubos[j]) res = resolver(cubos, i + 1, j, turno + 1);
        else if (turno % 2 != 0 && cubos[i] < cubos[j]) res = resolver(cubos, i, j - 1, turno + 1);
        else res = max(resolver(cubos, i, j - 1, turno + 1) + cubos[j], resolver(cubos, i + 1, j, turno + 1) + cubos[i]);
    }
    return res;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    int N;
    int aux;
    vector<int> cubos;
    cin >> N;
    if (N == 0)
        return false;

    for (int i = 0; i < N; i++) {
        cin >> aux;
        cubos.push_back(aux);
    }

    for (int i = 0; i < cubos.size(); i++) {
        for (int j = 0; j < cubos.size(); j++) {
            sol[i][j] = -1;
        }
    }

    cout << resolver(cubos, 0, N - 1,0) << endl;

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
