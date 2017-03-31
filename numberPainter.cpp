#include "numberPainter.hpp"

NumberPainter::NumberPainter(int n, int* values){
	this->n = n;
	this->values = values;
	this->colorless_values_q = 0;
};

NumberPainter::~NumberPainter(){
}


NumberPainter::NumberPainter(const NumberPainter& other){
	// @TODO
}	

void NumberPainter::paint_with(AlgorithmType a){
	if(a == BACKTRACKING){
		backtracking_solve();
	} /*else if(algorithm_type == BACKTRACKING_WITH_BOUNDS){
		backtracking_bounds_solve();
	} else {
		dynamic_solve();
	}*/
}

void NumberPainter::backtracking_solve(){
	this->colorless_values_q = backtracking(0,-1,-1,0);//min(is_red, is_blue, is_colorless);
}

int NumberPainter::backtracking(int index, int lastRedIndex, int lastBlueIndex, int colorless_q){
	if(index < this->n){
		//cout << "index: " << index << ", lastRed: " << lastRedIndex << ", lastBlue: " << lastBlueIndex << ", colorlessValues: " << colorless_q  << endl;
		int is_red = this->n;
		int is_blue = this->n;
		int is_colorless = backtracking(index+1, lastRedIndex, lastBlueIndex, colorless_q + 1);

		if(lastRedIndex < 0 || this->values[index] < this->values[lastRedIndex]) 
			is_red = backtracking(index+1, index, lastBlueIndex, colorless_q);
		
		if(lastBlueIndex < 0 || this->values[index] > this->values[lastBlueIndex]) 
			is_blue = backtracking(index+1, lastRedIndex, index, colorless_q);
		
		//cout << is_red << " " << is_blue << " " << is_colorless << endl;
		return min(is_red, is_blue, is_colorless);

	} else {
		return colorless_q;
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