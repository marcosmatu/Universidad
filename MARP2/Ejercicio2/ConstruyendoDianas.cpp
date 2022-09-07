// Nombre y Apellidos

// Comentario general sobre la soluci�n,
// explicando c�mo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>


using namespace std;
int minDardos[51][501];

vector<int> resolver(int puntuacion, vector<int> valorSectores) {
    
 
    for (int i = 0; i <= valorSectores.size(); i++) {
        minDardos[i][0] = 0;
    }
    for (int i = 1; i <= puntuacion; i++) {
        minDardos[0][i] = 999999;
    }

    for (int i = 1 ; i <= valorSectores.size(); i++) {
        for (int j = 1; j <= puntuacion; j++) {
            if (valorSectores[i - 1] > j) {
                minDardos[i][j] = minDardos[i - 1][j];
            }
            else {
                minDardos[i][j] = min(minDardos[i - 1][j], minDardos[i][j - valorSectores[i - 1]] + 1);
            }
        }

    }

    //RECUPERACIÓN DE LA SOLUCIÓN;
    int i = valorSectores.size();
    int j = puntuacion;
    vector<int> solucion;
    int valor = minDardos[valorSectores.size()][puntuacion];
    if(minDardos[valorSectores.size()][puntuacion] != 999999){
        while(j > 0){
            if(j >= valorSectores[i-1] && minDardos[i][j] > minDardos[i][j - valorSectores[i-1]]){
                solucion.push_back(valorSectores[i-1]);
                j -= valorSectores[i-1];
            } else{
                i--;
            }
        }
    }

    return solucion;

}

// resuelve un caso de prueba, leyendo de la entrada la
// configuraci�n, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    int puntuacion, S, aux;
    vector<int> valorSectores;
    cin >> puntuacion;
    cin >> S;
    if (!std::cin)  // fin de la entrada
        return false;

    for (int i = 0; i < S; i++) {
        cin >> aux;
        valorSectores.push_back(aux);
   }

    vector<int> sol = resolver(puntuacion, valorSectores);
    if(sol.size() != 0){
        cout << sol.size() << ": " ;
        for(int i = 0; i < sol.size(); i++){
            cout<<sol[i] << ' ';
        }
        cout<<'\n';
    }else{
        cout<<"Imposible\n";
    }
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
  //  system("PAUSE");
#endif
    return 0;
}