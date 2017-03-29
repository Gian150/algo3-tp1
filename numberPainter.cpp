#include "numberPainter.hpp"

NumberPainter::NumberPainter(int n, int* values){
	this->n = n;
	this->values = values;
	this->colors = new int[n];
	this->red_values_q = 0;
	this->blue_values_q = 0;
	this->colorless_values_q = 0;
};


NumberPainter::NumberPainter(NumberPainter& other){
	// @TODO
}

void NumberPainter::paint_with(int algorithm_type){
	if(algorithm_type == BACKTRACKING){
		backtracking_solve();
	} else if(algorithm_type == BACKTRACKING_WITH_BOUNDS){
		backtracking_bounds_solve();
	} else {
		dynamic_solve();
	}
}

void NumberPainter::backtracking_solve(){
	// Pinto el primero de rojo, busco la mejor solución
	int firstRed = backtracking(1, 0, -1, 0);
	// Pinto el primero de azul, busco la mejor solución
	int firstBlue = backtracking(1,-1, 1, 0);
	// No pinto el primero, busco la mejor solución
	int firstColorless = backtracking(1,-1,-1,1);

	this->colorless_values_q = min(firstRed, firstBlue, firstColorless);

}


int NumberPainter::min(int a,int b,int c){
	int min = (a < b)? a : b;
	return (min < c)? min : c;
};