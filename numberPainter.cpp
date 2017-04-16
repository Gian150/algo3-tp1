#include "numberPainter.hpp"
#include <vector>
#include <limits>
#include <string>
using namespace std;

void print(vector< vector< vector<int> > > matrix, int* values) {
	for(int i = 0; i < (int) matrix.size(); i++){
		cerr << "i = " << i << endl;
		cerr << "\t";
		for(int j = 0; j < (int) matrix[i].size(); j++) {
			cerr << values[j] << "\t";
		}
		cerr << endl;
		for(int j = 0; j < (int) matrix[i].size(); j++) {
			cerr  << values[j] << "\t";
			for(int k = 0; k < (int) matrix[i][j].size(); k++) cerr << matrix[i][j][k] << "\t";
			cerr << endl;
		}
	}
}

NumberPainter::NumberPainter(int n, int* values){
	this->n = n;
	this->values = values;
	this->bestActualValue = n;
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

	vector< vector< vector<int> > >matrix(n, vector< vector<int> >(n, vector<int>(n,-1)) );
	
	for(int r = 0; r < n; r++){
		for(int a = 0; a < n; a++){
			matrix[0][r][a] = 0;
		}
	}

	for(int i = 1; i < n; i++){
		for(int r = 0; r < n; r++){
			for(int a = 0; a < n; a++){
				int isBlue = (values[a] > values[i])? matrix[i-1][r][i] : 2*n;
				int isRed = (values[r] < values[i])? matrix[i-1][i][a] : 2*n;
				int colorless = matrix[i-1][r][a] + 1;

				if(r != a){
					matrix[i][r][a] = min(isBlue, isRed, colorless);
				} else {
					matrix[i][r][a] = 2*n;
				}
			}
		}
	}

	//print(matrix, values);
	int solution = 2*n;
	for(int r = 0; r < n; r++){
		for(int a = 0; a < n; a++){
			if(solution > matrix[n-1][r][a]) solution = matrix[n-1][r][a];
		}
	}

	return solution;
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