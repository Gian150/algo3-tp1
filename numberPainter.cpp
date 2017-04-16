#include "numberPainter.hpp"
#include <vector>
using namespace std;

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

void print(vector< vector< vector<int> > > matrix, int* values) {
	for(int i = 0; i < (int) matrix.size(); i++){
		cerr << "i = " << i << endl;
		cerr << "\t";
		for(int j = 0; j < (int) matrix.size(); j++) {
			cerr << values[j] << "\t";
		}
		cerr << endl;
		for(int j = 0; j < (int) matrix.size(); j++) {
			cerr  << values[j] << "\t";
			for(int k = 0; k < (int) matrix.size(); k++) cerr << matrix[i][j][k] << "\t";
			cerr << endl;
		}
	}
}

int NumberPainter::dynamicAlgorithm(){
	vector< vector< vector<int> > > matrix(n, vector< vector<int> >(n, vector<int>(n, -1)));

	for(int r = 0; r < n; r++) {
		for(int a = 0; a < n; a++) {
			if(r == a)
				matrix[0][r][a] = n;
			else
				matrix[0][r][a] = n-1;
		}
	}

	for(int i = 1; i < n; i++){
		for(int r = 0; r < n; r++){
			for(int a = 0; a < n; a++){
				
				if(r == a) matrix[i][r][a] = n;
				else {
					int dontPaint = matrix[i-1][r][a];
					int paintBlue = (values[i] < values[a])? matrix[i-1][r][i] - 1: n;
					int paintRed = (values[i] > values[r])? matrix[i-1][i][a] - 1 : n;

					matrix[i][r][a] = min(dontPaint, paintBlue, paintRed);
				}

			}
		}

	}

	int finalSolution = n;
	for(int r = 0; r < n; r++)
		finalSolution = (finalSolution > matrix[n-1][r][0])? matrix[n-1][r][0] : finalSolution;

	for(int a = 0; a < n; a++)
		finalSolution = (finalSolution > matrix[n-1][0][a])? matrix[n-1][0][a] : finalSolution;

	return finalSolution;
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