#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

struct Nodo {
	vector<int> sol;
	int k;
	vector<int> marcaje;
	double beneficio; // valor acumulado
	double beneficio_est; // prioridad
	bool operator<(Nodo const& otro) const {
		return otro.beneficio_est < beneficio_est;
	}
};
int calculo_estimacion(vector<vector<int>> const& objetos, Nodo const& X, int nProd, vector<int> minimos) {
	int estimacion = X.beneficio;
	for (int i = X.k + 1; i < nProd; ++i) {		
			estimacion += minimos[i];		
	}
	return estimacion;
}

void compra_rp(vector<vector<int>> const& objetos, int m,
	vector<int> sol_mejor, int& beneficio_mejor,int nProd,vector<int> minimos) {
	int N = nProd;
	// se genera la raíz
	Nodo Y;
	Y.marcaje = vector<int>(m, 3);
	Y.sol = vector<int>(N);
	Y.k = -1;
	Y.beneficio = 0;
	Y.beneficio_est = calculo_estimacion(objetos,Y,nProd,minimos);
	priority_queue<Nodo> cola;
	cola.push(Y);
	beneficio_mejor = INT_MAX;

	// búsqueda mientras pueda haber algo mejor
	while (!cola.empty() && cola.top().beneficio_est < beneficio_mejor) {

		Y = cola.top();
		cola.pop();
		Nodo X(Y);
		++X.k;

		// probamos a comprar el objeto en cada supermercado.
		for (int i = 0; i < m; i++) {
			if (X.marcaje[i] > 0) {
				//marcamos
				X.marcaje[i]--;
				X.sol[X.k] = i;
				X.beneficio = Y.beneficio + objetos[i][X.k];
				X.beneficio_est = calculo_estimacion(objetos, X, nProd, minimos);
				if (X.beneficio_est < beneficio_mejor) {
					if (X.k == N - 1) {
						if (X.beneficio < beneficio_mejor) {
							sol_mejor = X.sol;
							beneficio_mejor = X.beneficio;
						}
					}
					else cola.push(X);
				}
				//desmarcamos
				X.marcaje[i]++;
			}
		}

	}
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {

	int nProd, mSuper;
	cin >> mSuper >> nProd;

	vector<vector<int>> datos(mSuper, vector<int>(nProd));
	vector<int> minimos(nProd, INT_MAX);

	for (int i = 0; i < mSuper; i++) {
		for (int j = 0; j < nProd; j++) {
			cin >> datos[i][j];
			if (datos[i][j] < minimos[j]) minimos[j] = datos[i][j];
		}
	}

	vector<int> sol(nProd);
	int beneficio_mejor;
	compra_rp(datos, mSuper, sol, beneficio_mejor,nProd,minimos);
	cout << beneficio_mejor << '\n';
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