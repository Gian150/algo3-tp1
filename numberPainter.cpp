#include "numberPainter.hpp"
#include <vector>
#include <limits>
#include <string>
using namespace std;

void print(int** matrix, int* values, int n) {
	
	cerr << "\t" << "N";
	for(int i = 0; i < n; i++){
		cerr << "\t" << values[i];
	}
	cerr << endl;

	cerr << "N";
	for(int i = 0; i < n+1; i++){
		cerr << "\t" << matrix[0][i];
	}
	cerr << endl;

	for(int i = 1; i < n; i++){
		cerr << values[i-1];
		for (int j = 0; j < n+1; j++){
			cerr << "\t" << matrix[i][j];
		}
		cerr << endl;
	}
	cerr << endl;
}

NumberPainter::NumberPainter(int n, int* values){
	this->n = n;
	this->values = values;
	this->bestActualValue = n;
	this->dMatrix = NULL;
};

NumberPainter::~NumberPainter(){}

int NumberPainter::paintWith(AlgorithmType a){
	bestActualValue = n;
	
	if(a == BACKTRACKING){
		return backtracking(0,-1,-1,0,false);
	} else if(a == BACKTRACKING_WITH_BOUNDS){
		return backtracking(0,-1,-1,0,true);
	}

	return dynamicAlgorithm();
}

int NumberPainter::backtracking(int index, int lastRedIndex, int lastBlueIndex, int partialSolution, bool useBounds){

	if(useBounds && bestActualValue <= partialSolution) {
		return bestActualValue;
	}
	if(index < n){
		int isBlue = n;
		if(lastBlueIndex < 0 || values[index] < values[lastBlueIndex]) {
			isBlue = backtracking(index+1, lastRedIndex, index, partialSolution, useBounds);
		}

		int isRed = n;
		if(lastRedIndex < 0 || values[index] > values[lastRedIndex]) {
			isRed = backtracking(index+1, index, lastBlueIndex, partialSolution, useBounds);
		}

		int isColorless = backtracking(index+1, lastRedIndex, lastBlueIndex, partialSolution + 1, useBounds);
		return min(isRed, isBlue, isColorless);

	} else {
		bestActualValue = partialSolution;
		return partialSolution;
	}

};

int NumberPainter::dynamicAlgorithm(){

	dMatrix = new int*[n+1];
	for(int r = 0; r < n+1; r++) {
		dMatrix[r] = new int[n+1];
		for(int a = 0; a < n+1; a++){
			dMatrix[r][a] = -1;
		}
	}

/*	cerr << "===============================================================" << endl;
	cerr << "Esto es apenas inicializamos la matriz" << endl;
	print(dMatrix, values,n);
*/
	for(int r = n-1; r >= 0; r--){
		int value = dynamicAlgorithmRecursion(r, n);
		if(bestActualValue > value ) bestActualValue = value;
	}

	for(int a = n-1; a >= 0; a--){
		int value = dynamicAlgorithmRecursion(a, n+1);
		if(bestActualValue > value) bestActualValue = value;
	}

/*	cerr << "===============================================================" << endl;
	cerr << "Aca terminamos de hacer el algoritmo" << endl;
	print(dMatrix, values,n);
*/
	return bestActualValue;

}

int NumberPainter::dynamicAlgorithmRecursion(int r, int a){
	
	cerr << "===============================================================" << endl;
	cerr << r  << " " << a << endl;
	print(dMatrix, values,n);

	if(dMatrix[r][a] == -1){
		cerr << "La matriz no está definida" << endl;
		if (r == 0 and a == 0) {
			cerr << "Pero es el caso base" << endl;
			dMatrix[0][0] = n;
			return n;

		} else {
			cerr << "Tengo que definir recursivamente el valor para estos indices" << endl;
			int min = n;

			if(r < a){
				cerr << "El indice del ultimo rojo es menor que el indice del ultimo azul" << endl;
				for(int i = 0; i < a; i++){
					int actual = dynamicAlgorithmRecursion(r,i);
					if(min > actual and values[i] < values[r-1]) min = actual;
				}
			} else {
				cerr << "El indice del ultimo rojo es mayor que el indice del ultimo azul" << endl;
				for(int i = 0; i < r; i++){
					int actual = dynamicAlgorithmRecursion(i,a);
					if(min > actual and values[i] > values[a-1]) min = actual;
				}
			}

			if(bestActualValue > min) bestActualValue = min-1;
			dMatrix[r][a] = min-1;
			return min-1;
		}
	} else {
		return dMatrix[r][a];
	}
}

int NumberPainter::min(int a,int b,int c){
	int min = (a < b)? a : b;
	return (min < c)? min : c;
};

std::ostream& operator<< (std::ostream& os, const NumberPainter& np) {
	os << "======== NumberPainter ========" << endl;
	os << "=         Quantity: "  << np.n << endl;
	os << "=           Values: ";

	for(int i = 0; i < np.n; i++) os << np.values[i] << " ";
	os << endl;

	os << "= Colorless Values: " << np.bestActualValue << endl; 
	os << "===============================";

	return os;
}