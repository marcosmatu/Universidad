
//Marcos Matute Fernández

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <math.h>
#include <string>


using namespace std;
int sol[101][101];


/*
Programacion dinamica descendente ya que no es posible reducir coste en espacio si queremos reconstruir la solucion y usar ascendente
no nos proporciona ningun beneficio.
minNumLetras(i,j) : minimo numero de letras que hay que añadir para formar un palindromo teniendo en cuenta las letras de la i a la j
N-> longitud(palabra)
Casos base:
    minNumLetras(i,i) = 0 con 0 <= i < N
    minNumLetras(i,j) = 0 con i > j
Caso recursivo:
    minNumLetras(i,j) = minNumLetras(i+1,j-1)   si palabra[i]== palabra[j]
                     eoc -> min(minNumLetras(i+1,j),minNumLetras(i,j-1)) + 1
Llamada inicial:
    minNumLetras(0,N-1)
Espacio: O(N^2)
Tiempo: O(N^2)
*/
int resolver(string palindromo,int i, int j) {
    int& res = sol[i][j];
    if (res != -1)
        return res;
    if (i == j)
        return 0;
    else if (i > j)
        return 0;
    else {
        if (palindromo[i] == palindromo[j]) res = resolver(palindromo, i + 1, j - 1);
        else res = min(resolver(palindromo, i + 1, j), resolver(palindromo, i, j-1)) + 1; //Añadimos a la derecha, añadimos a la izquierda
    }

    return res;
}

string reconstruir(string const& palindromo,  int i, int j) {
    if (i > j) return {};
    if (i == j) return { palindromo[i] };
    if (palindromo[i] == palindromo[j])
        return palindromo[i] + reconstruir(palindromo,  i + 1, j - 1) + palindromo[j];
    else if (sol[i][j] == sol[i+1][j] + 1)
        return  palindromo[i] + reconstruir(palindromo,  i + 1, j) + palindromo[i];
    else
        return palindromo[j] + reconstruir(palindromo,  i, j - 1) + palindromo[j];
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    
    string palindromo;
    cin >> palindromo;

   

    if (!std::cin)  // fin de la entrada
        return false;

    for (int i = 0; i < palindromo.length(); i++) {
        for (int j = 0; j < palindromo.length(); j++) {
            sol[i][j] = -1;
        }

    }

    int sol = resolver(palindromo,0,palindromo.length() - 1);
   
    cout << sol << ' ' << reconstruir(palindromo,  0, palindromo.length() - 1)<< '\n';

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
