#include "numberPainter.hpp"
#include <chrono>
#include <stdlib.h>
#include <vector>
#include <utility>
#include <iostream>
#include <math.h> 
using namespace std;


#define ya chrono::high_resolution_clock::now
#define reloj chrono::time_point<std::chrono::high_resolution_clock>


// ./tiempo repeticiones P(puro)/_(poda) n1 n2 n3 ...
// imprime los resultados de tiempo por stdout en formato csv ;

int main(int argc, char const *argv[])
{
	// interpretamos los parametros
	int rep = atoi(argv[1]);
	AlgorithmType choosen_algorithm = (argv[2][0] == 'b')? BACKTRACKING : (argv[2][0] == 'p')?  BACKTRACKING_WITH_BOUNDS : DYNAMIC;

	// Leemos el standar input
	int  n;
	cin >> n;
	int values[n];

	for(int i = 0; i < n; i++){
		cin >> values[i];
	}

	long int times[rep];
 
	for(int i = 0; i < rep; i++){
		NumberPainter painter(n,values);
		reloj start = ya();
		painter.paint_with(choosen_algorithm);
		reloj end = ya();
		times[i] = chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
	}

	float mean = 0;
	for(int i = 0; i < rep; i++){
		mean += times[i];
	}

	mean = mean/n;

	cout << mean/1000000;

	return 0;

}


