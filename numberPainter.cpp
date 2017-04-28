#include "numberPainter.hpp"
#include <vector>
#include <limits>
#include <string>
using namespace std;

void print(vector< vector<int> > *matrix, int* values, int n) {
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
	this->best_actual_value = n;
	this->d_matrix = NULL;
};

NumberPainter::~NumberPainter(){}

int NumberPainter::paint_with(AlgorithmType a){
	best_actual_value = n;
	
	if(a == BACKTRACKING){
		return backtracking(0,-1,-1,0,false);
	} else if(a == BACKTRACKING_WITH_BOUNDS){
		return backtracking(0,-1,-1,0,true);
	}

	return dynamic_algorithm();
}

int NumberPainter::backtracking(int index, int last_red_index, int last_blue_index, int partial_solution, bool use_bounds){

	if(use_bounds && best_actual_value <= partial_solution) {
		return best_actual_value;
	}
	if(index < n){
		int is_blue = n;
		if(last_blue_index < 0 || values[index] < values[last_blue_index]) {
			is_blue = backtracking(index+1, last_red_index, index, partial_solution, use_bounds);
		}

		int is_red = n;
		if(last_red_index < 0 || values[index] > values[last_red_index]) {
			is_red = backtracking(index+1, index, last_blue_index, partial_solution, use_bounds);
		}

		int is_colorless = backtracking(index+1, last_red_index, last_blue_index, partial_solution + 1, use_bounds);
		return min(is_red, is_blue, is_colorless);

	} else {
		best_actual_value = partial_solution;
		return partial_solution;
	}

};

int NumberPainter::dynamic_algorithm(){
	int best_actual_value = n;
	
	vector< vector<int> > d_matrix = vector< vector<int> >(n+1, vector<int>(n+1, -1));

	d_matrix[0][0] = n;


	for(int r = 0; r < n+1; r++){
		for(int a = 0; a < n+1; a++){
			//cerr << "r=" << r << "\ta=" << a << endl;
			int min = n+1;
			
			if(a == r) 
				d_matrix[r][a] = n;

			else if(a < r) {
				//cerr << "a < r" << endl;
				min = d_matrix[0][a];

				for(int i = 1; i < r; i++) {
					if(min > d_matrix[i][a] and values[i-1] < values[r-1]) 
						min = d_matrix[i][a];
				}

				d_matrix[r][a] = min - 1;

			} else {
				//cerr << "a > r" << endl;
				min = d_matrix[r][0];

				for(int i = 1; i < a; i++) {
					if(min > d_matrix[r][i] and values[i-1] > values[a-1])
						min = d_matrix[r][i];
				}
				
				d_matrix[r][a] = min - 1;
			}
			

			if(best_actual_value > d_matrix[r][a]) best_actual_value = d_matrix[r][a];
			//print(&d_matrix, values, n);
		}
	}


	return best_actual_value;
}

int NumberPainter::min(int a,int b,int c){
	int min = (a < b)? a : b;
	return (min < c)? min : c;
};

std::ostream& operator<< (std::ostream& os, const NumberPainter& np) {
	os << "======== Number Painter =======" << endl;
	os << "=         Quantity: "  << np.n << endl;
	os << "=           Values: ";

	for(int i = 0; i < np.n; i++) os << np.values[i] << " ";
	os << endl;

	os << "= Colorless Values: " << np.best_actual_value << endl; 
	os << "===============================";

	return os;
}