#include "numberPainter.hpp"

/******************************************************************/
/*						Constructores							  */
/******************************************************************/


NumberPainter::NumberPainter(int n, int* values){
	this->n = n;
	this->values = values;
	this->colorless_values_q = 0;
	this->bb_partial_solution = n;
};

NumberPainter::~NumberPainter(){
}

void NumberPainter::paint_with(AlgorithmType a){
	if(a == BACKTRACKING){
		backtracking_solve(false);
	} else if(a == BACKTRACKING_WITH_BOUNDS){
		backtracking_solve(true);
	} /*else {
		dynamic_solve();
	}*/
}



void NumberPainter::backtracking_solve(bool use_bounds){
	if(use_bounds){
		this->colorless_values_q = backtracking(0,-1,-1,0,true);
	} else {
		this->colorless_values_q = backtracking(0,-1,-1,0, false);//min(is_red, is_blue, is_colorless);
	}
}

int NumberPainter::backtracking(int index, int lastRedIndex, int lastBlueIndex, int colorless_q, bool use_bounds){
	if(use_bounds && this->bb_partial_solution <= colorless_q) {
		return this->bb_partial_solution;
	} else {
		if(index < this->n){
			int is_red = this->n;
			int is_blue = this->n;
			int is_colorless = backtracking(index+1, lastRedIndex, lastBlueIndex, colorless_q + 1, use_bounds);

			if(lastRedIndex < 0 || this->values[index] < this->values[lastRedIndex]) 
				is_red = backtracking(index+1, index, lastBlueIndex, colorless_q, use_bounds);
			
			if(lastBlueIndex < 0 || this->values[index] > this->values[lastBlueIndex]) 
				is_blue = backtracking(index+1, lastRedIndex, index, colorless_q, use_bounds);
			
			return min(is_red, is_blue, is_colorless);

		} else {
			this->bb_partial_solution = colorless_q;
			return colorless_q;
		}
	}

};

int NumberPainter::get_colorless_q(){
	return this->colorless_values_q;
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

	os << "= Colorless Values: " << np.colorless_values_q << endl; 
	os << "===============================";

	return os;
}