/*
#include "numberPainter.hpp"
#include <chrono>
#include <stdlib.h>
#include <vector>
#include <utility>
#include <iostream>


#define ya chrono::high_resolution_clock::now

using namespace std;

// ./tiempo repeticiones P(puro)/_(poda) n1 n2 n3 ...
// imprime los resultados de tiempo por stdout en formato csv ;

int main(int argc, char const *argv[])
{
	// interpretamos los parametros
	int repes = atoi(argv[1]);
	int tipo_algoritmo = (argv[2][0] == 'B')? BACKTRACKING : (argv[2] == "BP")?  BACKTRACKING_WITH_BOUNDS : DYNAMIC;

	vector<int> ns(argc-3);
	for (int i = 0; i < ns.size(); i++) {
		ns[i] = atoi(argv[i+3]);
	}
	
	// escribimos el header del csv
	cout << "n;";
	for (int i = 1; i <= repes; ++i)
		cout << "r" << i << ";";
	cout << "solucion;" << endl;

	// corremos los experimentos y vamos escupiendo los datos
	for (auto n : ns) {
		vector<escaque> solucion(n);
		cout << n << ';';
		for (int t = 0; t < repes; t++) {
			cerr << "Empezando medicion nro "<< t+1 << " para n = " << n << endl;
			auto start = ya();
			if (puro) {
				solucion = resolverPuro(n);
			} else {
				solucion = resolverPoda(n);
			}
			auto end = ya();
			cout << chrono::duration_cast<std::chrono::nanoseconds>(end-start).count() << ";";
		}
		for (int i = 0; i < solucion.size(); ++i)
				cout << '(' << solucion[i].first << ", " << solucion[i].second <<"), ";
		cout << ";\n";
	}
}


*/