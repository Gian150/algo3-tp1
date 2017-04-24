#include "numberPainter.hpp"
#include <vector>
#include <limits>
#include <string>
using namespace std;

void print(vector< vector<int> > *matrix, int* values, int n) {
	cerr << "\t" << "N";
	for(int i = 0; i < n; i++){
		cerr << "\t" << values[i];
	}
	cerr << endl;

	cerr << "N";
	for(int i = 0; i < n+1; i++){
		cerr << "\t" << (*matrix)[0][i];
	}
	cerr << endl;

	for(int i = 1; i < n+1; i++){
		cerr << values[i-1];
		for (int j = 0; j < n+1; j++){
			cerr << "\t" << (*matrix)[i][j];
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
	int bestActualValue = n;
	
	vector< vector<int> > dMatrix = vector< vector<int> >(n+1, vector<int>(n+1, -1));

	dMatrix[0][0] = n;


	for(int r = 0; r < n+1; r++){
		for(int a = 0; a < n+1; a++){
			//cerr << "r=" << r << "\ta=" << a << endl;
			int min = n+1;
			
			if(a == r) 
				dMatrix[r][a] = n;

			else if(a < r) {
				//cerr << "a < r" << endl;
				min = dMatrix[0][a];

				for(int i = 1; i < r; i++) {
					if(min > dMatrix[i][a] and values[i-1] < values[r-1]) 
						min = dMatrix[i][a];
				}

				dMatrix[r][a] = min - 1;

			} else {
				//cerr << "a > r" << endl;
				min = dMatrix[r][0];

				for(int i = 1; i < a; i++) {
					if(min > dMatrix[r][i] and values[i-1] > values[a-1])
						min = dMatrix[r][i];
				}
				
				dMatrix[r][a] = min - 1;
			}
			

			if(bestActualValue > dMatrix[r][a]) bestActualValue = dMatrix[r][a];
			//print(&dMatrix, values, n);
		}
	}


	return bestActualValue;
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